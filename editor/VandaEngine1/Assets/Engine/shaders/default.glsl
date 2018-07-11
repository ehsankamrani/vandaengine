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

	normal = vec3( normalize( gl_NormalMatrix * gl_Normal ) );
		
    vec3 n, t, b;
   
    viewDir = -vertexPos;
  
	mat3 tbnMatrix;
 	vec3 tempVec;
 	if( pointLight )
 		tempVec = (gl_LightSource[0].position.xyz - vPos.xyz);
 	else
 		tempVec = gl_LightSource[0].position.xyz;
    dist = length(tempVec );
	lightDir = normalize( tempVec );
			
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
    // fix of the clipping bug for both Nvidia and ATi
    #ifdef __GLSL_CG_DATA_TYPES
    gl_ClipVertex = gl_ModelViewMatrix * gl_Vertex;
    #endif

    gl_Position = gl_ProjectionMatrix * vPos;
}

[frag]

#version 130
#extension GL_EXT_texture_array : enable
varying vec3 lightDir;
varying float dist;
varying vec4 ambient;
varying vec4 diffuse;
varying vec3 viewDir;
varying vec3 normal;  //It's just used for per pixel lighting without normal map
uniform bool enableAlphaMap;
uniform bool enableColorMap;
uniform bool enableDirtMap;
uniform bool enableGlossMap;

uniform sampler2D colorMap;
uniform sampler2D alphaMap;
uniform sampler2D heightMap;
uniform sampler2D glossMap;
uniform sampler2D dirtMap;

//shadow
uniform vec2 texSize; // x - size, y - 1/size
varying vec4 vPos;


uniform bool pointLight;
out vec4 myVec40;

uniform float light_radius;

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

	newTexCoord = gl_TexCoord[0].st;
		
	vec3 n;
	n = normalize( normal );
	    	 
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
	myVec40 = vec4(color.rgb, 0.0);
}


