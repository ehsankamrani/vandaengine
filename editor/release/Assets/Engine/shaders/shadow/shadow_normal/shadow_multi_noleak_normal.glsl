//Copyright (C) 2014 Ehsan Kamrani
//This file is licensed and distributed under MIT license

[vert]

#version 130
varying vec3 lightDir;
varying vec4 ambient;
varying vec4 diffuse;
varying float dist;
varying vec3 viewDir;
varying vec3 normal;
//varying vec4 position;
//varying vec3 GNormal;
uniform mat4 camera_inverse_matrix;
uniform float focalDistance, focalRange;
uniform bool enableDirtMap;
uniform bool pointLight;
varying vec4 vPos;
void main()
{
	mat4 modelMatrix = camera_inverse_matrix * gl_ModelViewMatrix;
	mat3 modelMatrix3x3 = mat3(modelMatrix); 
	
    gl_TexCoord[0] = gl_MultiTexCoord0;
    if( enableDirtMap )
		gl_TexCoord[1] = gl_MultiTexCoord3; //second uv set

    vec3 vertexPos = vec3(gl_ModelViewMatrix * gl_Vertex);
    vPos = gl_ModelViewMatrix * gl_Vertex;

	//GNormal = normalize( modelMatrix3x3 * gl_Normal );
	
    vec3 n, t, b;
   
    viewDir = -vertexPos;
  
	mat3 tbnMatrix;
	n = normalize(gl_NormalMatrix * gl_Normal);
	t = normalize(gl_NormalMatrix * gl_MultiTexCoord1.xyz);
	b = normalize(gl_NormalMatrix * gl_MultiTexCoord2.xyz);
		
    tbnMatrix = mat3(t.x, b.x, n.x,
                     t.y, b.y, n.y,
                     t.z, b.z, n.z);
                          
	viewDir = tbnMatrix * viewDir;
 	vec3 tempVec;
 	if( pointLight )
 		tempVec = (gl_LightSource[0].position.xyz - vPos.xyz);
 	else
 		tempVec = gl_LightSource[0].position.xyz;
    dist = length(tempVec );
	lightDir = normalize( tbnMatrix * tempVec );	
			
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
    // fix of the clipping bug for both Nvidia and ATi
    #ifdef __GLSL_CG_DATA_TYPES
    gl_ClipVertex = gl_ModelViewMatrix * gl_Vertex;
    #endif

    gl_Position = gl_ProjectionMatrix * vPos;
    //position = modelMatrix * gl_Vertex;
}

[frag]

#version 130
#extension GL_EXT_texture_array : enable
varying vec3 lightDir;
varying float dist;
uniform float light_radius;
varying vec4 ambient;
varying vec4 diffuse;
varying vec3 viewDir;
varying vec3 normal;  //It's just used for per pixel lighting without normal map
//varying vec4 position;
//varying vec3 GNormal;
uniform bool enableParallaxMap;
uniform bool enableAlphaMap;
uniform bool enableColorMap;
uniform bool enableDirtMap;
uniform bool enableGlossMap;

uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform sampler2D alphaMap;
uniform sampler2D heightMap;
uniform sampler2D glossMap;
uniform sampler2D dirtMap;

uniform bool firstPass;
uniform float parallaxMapScale;
uniform float parallaxMapBias;

out vec4 myVec40;
out vec4 myVec41;
out vec4 myVec42;
out vec4 myVec43;
out vec4 myVec44;
out vec4 myVec45;
out vec4 myVec46;
out vec4 myVec47;
//out vec4 myVec48;

uniform bool pointLight;
//shadow
uniform vec4 far_d;
uniform vec2 texSize; // x - size, y - 1/size
varying vec4 vPos;
uniform sampler2DArray stex;
uniform bool character_shadow;
uniform float shadow_intensity;
// sample offsets
const int nsamples = 8;
uniform vec4 offset[nsamples] = vec4[nsamples](                   vec4(0.000000, 0.000000, 0.0, 0.0),
								  vec4(0.079821, 0.165750, 0.0, 0.0),
								  vec4(-0.331500, 0.159642, 0.0, 0.0),
								  vec4(-0.239463, -0.497250, 0.0, 0.0),
								  vec4(0.662999, -0.319284, 0.0, 0.0),
								  vec4(0.399104, 0.828749, 0.0, 0.0),
								  vec4(-0.994499, 0.478925, 0.0, 0.0),
								  vec4(-0.558746, -1.160249, 0.0, 0.0) );

float getOccCoef(vec4 shadow_coord)
{
	// get the stored depth
	float shadow_d = texture2DArray(stex, shadow_coord.xyz).x;
	
	// get the difference of the stored depth and the distance of this fragment to the light
	float diff = shadow_d - shadow_coord.w;
	
	// smoothen the result a bit, so that we don't get hard shadows
	return clamp( diff*250.0 + 1.0, 0.0, 1.0);
}


float shadowCoef()
{
	const float scale = 2.0/4096.0;
	int index;
	if(gl_FragCoord.z < far_d.x)
		index = 0;
	else if(gl_FragCoord.z < far_d.y)
		index = 1;
	else if(gl_FragCoord.z < far_d.z)
		index = 2;
	else if(gl_FragCoord.z < far_d.w)
		index = 3;
	else
		return 1.0f;
	
	// transform this fragment's position from world space to scaled light clip space
	// such that the xy coordinates are in [0;1]
	vec4 shadow_coord = gl_TextureMatrix[index]*vPos;
	
	vec4 light_normal4 = gl_TextureMatrix[index+4]*vec4(normal, 0.0);
	vec3 light_normal = normalize(light_normal4.xyz);
	
	float d = -dot(light_normal, shadow_coord.xyz);
	
	shadow_coord.w = shadow_coord.z;
	
	// tell glsl in which layer to do the look up
	shadow_coord.z = float(index);

    // sum shadow samples	
	float shadow_coef = getOccCoef(shadow_coord);

	for(int i=1; i<nsamples; i++)
	{
		vec4 shadow_lookup = shadow_coord + scale*offset[i];
		float lookup_z = -(light_normal.x*shadow_lookup.x + light_normal.y*shadow_lookup.y + d)/light_normal.z;
		shadow_lookup.w = lookup_z;
		shadow_coef += getOccCoef(shadow_lookup);
	}
	shadow_coef /= nsamples;
	
	return shadow_coef;
}

void main()
{
	vec4 alphaColor;
	if( enableAlphaMap )
	{
	    alphaColor = texture2D(alphaMap, gl_TexCoord[0].xy);
	
	    if(alphaColor.a<0.1)
	    	discard;
	}
  	vec3 halfV,viewV,ldir,ldirForDynamicShadow;
	float NdotL;

	vec4 ambientGlobal, specular;	
  	ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;

	vec4 color = ambientGlobal;
	float att;

	viewV = normalize( viewDir );

	vec2 newTexCoord;

	if( enableParallaxMap )
	{
		//parallax mapping
		float height = texture2D(normalMap, gl_TexCoord[0].st).a;
        
		height = height * parallaxMapScale + parallaxMapBias;
		newTexCoord = gl_TexCoord[0].st + (height * viewV.xy) * texture2D(normalMap, gl_TexCoord[0].st ).z;
	}
	else 
		newTexCoord = gl_TexCoord[0].st;
		
	vec3 n, dynamicShadowN;
	vec4 normalColor;
	normalColor = texture2D(normalMap, newTexCoord );
    n = normalize(texture2D(normalMap, newTexCoord ).rgb * 2.0 - 1.0);
	dynamicShadowN = normalize( normal );	
	    	 
	vec4 textureColor;
	vec4 shadowColor = vec4(0.0, 0.0, 0.0, 0.0 );
	vec4 dirtColor;
	vec4 glossColor;
	
  	//att = 1.0 / (gl_LightSource[0].constantAttenuation +
	//		gl_LightSource[0].linearAttenuation * dist +
	//		gl_LightSource[0].quadraticAttenuation * dist * dist);
	if( pointLight )
		att = ( 1 - ( dist / light_radius ) ) / gl_LightSource[0].constantAttenuation;
	else 
		att = 1.0;
	
	color += att * ambient;

	ldir = normalize(lightDir); 
	NdotL = max(dot(n,ldir),0.0);
	if( NdotL > 0.0 )
	{
		color += att * (diffuse * NdotL );
			
	 	specular = gl_FrontMaterial.specular * gl_LightSource[0].specular;
	
		float l_specular = pow(clamp(dot(reflect(-ldir, n), viewV), 0.0, 1.0), 
					 gl_FrontMaterial.shininess );
	
		if( enableGlossMap )
		{
	 		glossColor = texture2D(glossMap, newTexCoord );
			color += att * specular * l_specular * glossColor;
		}
		else
			color += att * specular * l_specular;
	}
	
	if( enableColorMap )
	{
  		textureColor = texture2D(colorMap, newTexCoord );
		color *= textureColor;
	}

	if( enableDirtMap )
	{
  		dirtColor = texture2D(dirtMap, gl_TexCoord[1].st );
		color *= dirtColor;
	}
	if( firstPass )
	{
		float shadow_coef = shadowCoef();
		if( character_shadow )
		{
			shadow_coef *= NdotL;
		}
		shadow_coef +=  1.0 - shadow_intensity;
	
		shadow_coef = clamp(shadow_coef, 0.0, 1.0);
		color *= shadow_coef;
	}	
		//vec4 pos = normalize( position );
		//myVec41 = vec4(pos.xyz,0);
		//vec3 norm = normalize( GNormal );
		//myVec42 = vec4( norm.xyz,0 );
		//myVec43 =  textureColor;
		//myVec44 =  normalColor;
		//myVec45 =  glossColor;
		//myVec46 =  shadowColor;
		//myVec47 =  dirtColor;
		//myVec48 =  alphaColor;
	//}
	
	myVec40 = vec4(color.rgb, 0.0);
}

