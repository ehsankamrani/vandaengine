//Copyright (C) 2020 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]

#version 130

//Directional Light
#define NR_DIR_LIGHTS 2
uniform int nr_dir_lights;
varying vec3 lightDir[NR_DIR_LIGHTS];

//Point Light
#define NR_POINT_LIGHTS 2  
uniform int nr_point_lights;
varying float pointLightDist[NR_POINT_LIGHTS];
varying vec3 pointLightPos[NR_POINT_LIGHTS];

//spot Lights
#define NR_SPOT_LIGHTS 1
uniform int nr_spot_lights;
varying float spotLightDist[NR_SPOT_LIGHTS];
varying vec3 spotLightPos[NR_SPOT_LIGHTS];
varying vec3 spotLightDir[NR_SPOT_LIGHTS];

varying vec3 viewDir;
varying vec3 normal;
uniform bool enableDirtMap;

//shadow
varying vec4 vPos;

void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
    if( enableDirtMap )
		gl_TexCoord[1] = gl_MultiTexCoord3; //second uv set
    vPos = gl_ModelViewMatrix * gl_Vertex;

	normal = vec3( normalize( gl_NormalMatrix * gl_Normal ) );
		
    viewDir = vec3(-vPos);
  
	int light_index = 0;
 	vec3 tempVec;
	//directional Light
	for(int i = 0; i < nr_dir_lights; i++)
	{
		tempVec = gl_LightSource[light_index].position.xyz;
		lightDir[i] = normalize( tempVec );
		light_index++;
	}

	//Point Lights
	for(int i = 0; i < nr_point_lights; i++)
	{
		tempVec = (gl_LightSource[light_index].position.xyz - vPos.xyz);
		pointLightDist[i] = length(tempVec);
		pointLightPos[i] = normalize(tempVec);
		light_index++;
	}	
	
	//Spot Light
	for(int i = 0; i < nr_spot_lights; i++) // not supporting
	{
		tempVec = (gl_LightSource[light_index].position.xyz - vPos.xyz);
		spotLightDist[i] = length(tempVec);
		spotLightPos[i] = normalize( tempVec );
		spotLightDir[i] = normalize( gl_LightSource[light_index].spotDirection );
		light_index++;
	}	
	// fix of the clipping bug for both Nvidia and ATi
    #ifdef __GLSL_CG_DATA_TYPES
    gl_ClipVertex = vPos;
    #endif

    gl_Position = gl_ProjectionMatrix * vPos;
}

[frag]

#version 130

#extension GL_EXT_texture_array : enable

//Directional Light
#define NR_DIR_LIGHTS 2
uniform int nr_dir_lights;
varying vec3 lightDir[NR_DIR_LIGHTS];
uniform int defaultDirLightIndex;

//Point Light
#define NR_POINT_LIGHTS 2  
uniform int nr_point_lights;
varying float pointLightDist[NR_POINT_LIGHTS];
varying vec3 pointLightPos[NR_POINT_LIGHTS];
uniform float point_light_radius[NR_POINT_LIGHTS];

//spot Lights
#define NR_SPOT_LIGHTS 1
uniform int nr_spot_lights;
varying float spotLightDist[NR_SPOT_LIGHTS];
varying vec3 spotLightPos[NR_SPOT_LIGHTS];
varying vec3 spotLightDir[NR_SPOT_LIGHTS];
uniform float spot_light_radius[NR_SPOT_LIGHTS];

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
uniform vec4 far_d;
varying vec4 vPos;
uniform sampler2DArrayShadow stex;
uniform float shadow_intensity;

const int nsamples = 8;
uniform vec4 offsets[nsamples] = vec4[nsamples](
				                  vec4(0.000000, 0.000000, 0.0, 0.0),
								  vec4(0.079821, 0.165750, 0.0, 0.0),
								  vec4(-0.331500, 0.159642, 0.0, 0.0),
								  vec4(-0.239463, -0.497250, 0.0, 0.0),
								  vec4(0.662999, -0.319284, 0.0, 0.0),
								  vec4(0.399104, 0.828749, 0.0, 0.0),
								  vec4(-0.994499, 0.478925, 0.0, 0.0),
								  vec4(-0.558746, -1.160249, 0.0, 0.0) );

float shadowCoef(float ndotl)
{
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
	
	// transform this fragment's position from view space to scaled light clip space
	// such that the xy coordinates are in [0;1]
	// note there is no need to divide by w for othogonal light sources
	vec4 shadow_coord = gl_TextureMatrix[index]*vPos;
	shadow_coord.w = shadow_coord.z;

	//variable bias
	float bias = 0.001*tan(acos(ndotl));
	bias = clamp(bias, 0,0.0025);

	shadow_coord.w -= bias;

	// tell glsl in which layer to do the look up
	shadow_coord.z = float(index);

	float ret = 1.0;
	// Gaussian 3x3 filter
	ret = shadow2DArray(stex, shadow_coord).x * 0.25;
	ret += shadow2DArrayOffset(stex, shadow_coord, ivec2( -1, -1)).x * 0.0625;
	ret += shadow2DArrayOffset(stex, shadow_coord, ivec2( -1, 0)).x * 0.125;
	ret += shadow2DArrayOffset(stex, shadow_coord, ivec2( -1, 1)).x * 0.0625;
	ret += shadow2DArrayOffset(stex, shadow_coord, ivec2( 0, -1)).x * 0.125;
	ret += shadow2DArrayOffset(stex, shadow_coord, ivec2( 0, 1)).x * 0.125;
	ret += shadow2DArrayOffset(stex, shadow_coord, ivec2( 1, -1)).x * 0.0625;
	ret += shadow2DArrayOffset(stex, shadow_coord, ivec2( 1, 0)).x * 0.125;
	ret += shadow2DArrayOffset(stex, shadow_coord, ivec2( 1, 1)).x * 0.0625;
	
	return ret;
}
out vec4 myVec40;

void main()
{
	float NdotL, att, spotEffect;
	vec2 newTexCoord;
  	vec3 halfV, viewV, ldir, ldirForDynamicShadow, n, sdir;
	vec4 ambient, diffuse, textureColor, finalColor, alphaColor, glossColor, dirtColor, color, ambientGlobal, specular;

	if( enableAlphaMap )
	{
	    alphaColor = texture2D(alphaMap, gl_TexCoord[0].xy);
	
	    if( alphaColor.a < 0.1)
	    	discard;
	}
	n = normalize( normal );
	viewV = normalize( viewDir );
	newTexCoord = gl_TexCoord[0].st;

	int light_index = 0;
	//Directional Light
	for(int i = 0; i < nr_dir_lights; i++)
	{
		if(i == defaultDirLightIndex)
		{
			ambient = gl_FrontMaterial.ambient * gl_LightSource[light_index].ambient;
			diffuse = gl_FrontMaterial.diffuse * gl_LightSource[light_index].diffuse;

			color = ambient;

			ldir = normalize(lightDir[i]); 
			NdotL = max(dot(n,ldir),0.0);
			if( NdotL > 0.0 )
			{
				float shadow_coef = shadowCoef(NdotL);
				color += (diffuse * NdotL );
			
	 			specular = gl_FrontMaterial.specular * gl_LightSource[light_index].specular;
	
				float l_specular = pow(clamp(dot(reflect(-ldir, n), viewV), 0.0, 1.0), 
								gl_FrontMaterial.shininess );
	
				if( enableGlossMap )
				{
	 				glossColor = texture2D(glossMap, newTexCoord );
					color += specular * l_specular * glossColor;
				}
				else
					color += specular * l_specular;

				shadow_coef +=  1.0 - shadow_intensity;
	
				shadow_coef = clamp(shadow_coef, 0.0, 1.0);
				color *= shadow_coef;
			}
			else
			{
				color *= 1.0 - shadow_intensity;
			}
		}
		else
		{
			ambient = gl_FrontMaterial.ambient * gl_LightSource[light_index].ambient;
			diffuse = gl_FrontMaterial.diffuse * gl_LightSource[light_index].diffuse;

			color = ambient;

			ldir = normalize(lightDir[i]); 
			NdotL = max(dot(n,ldir),0.0);
			if( NdotL > 0.0 )
			{
				color += (diffuse * NdotL );
			
	 			specular = gl_FrontMaterial.specular * gl_LightSource[light_index].specular;
	
				float l_specular = pow(clamp(dot(reflect(-ldir, n), viewV), 0.0, 1.0), 
								gl_FrontMaterial.shininess );
	
				if( enableGlossMap )
				{
	 				glossColor = texture2D(glossMap, newTexCoord );
					color += specular * l_specular * glossColor;
				}
				else
					color += specular * l_specular;
			}
		}
		finalColor += color;
		light_index++;
	}

	//point lights
	for(int i = 0; i < nr_point_lights; i++)
	{
		color = vec4(0.0);

		ldir = normalize(pointLightPos[i]); 
		NdotL = max(dot(n,ldir),0.0);
		if( NdotL > 0.0 )
		{
			ambient = gl_FrontMaterial.ambient * gl_LightSource[light_index].ambient;
			diffuse = gl_FrontMaterial.diffuse * gl_LightSource[light_index].diffuse;

			att = ( 1 - ( pointLightDist[i] / point_light_radius[i] ) ) / gl_LightSource[light_index].constantAttenuation;
			att = max(att, 0.0);
			color = att * ambient;

			color += att * (diffuse * NdotL );
			
	 		specular = gl_FrontMaterial.specular * gl_LightSource[light_index].specular;
	
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
	
		finalColor += color;
		light_index++;
	}

	//Spot Lights
	for(int i = 0; i < nr_spot_lights; i++)
	{
		color = vec4(0.0);
		ldir = normalize(spotLightPos[i]); 
		sdir = normalize(spotLightDir[i]);
		NdotL = max(dot(n,ldir),0.0);
		if( NdotL > 0.0 )
		{
			spotEffect = dot(sdir, -ldir);
			if (spotEffect > gl_LightSource[light_index].spotCosCutoff)
			{
				ambient = gl_FrontMaterial.ambient * gl_LightSource[light_index].ambient;
				diffuse = gl_FrontMaterial.diffuse * gl_LightSource[light_index].diffuse;

				spotEffect = pow(spotEffect, gl_LightSource[light_index].spotExponent);
				float tempAtt = ( 1 - ( spotLightDist[i] /  spot_light_radius[i] ) ) / gl_LightSource[light_index].constantAttenuation;
				att = spotEffect * tempAtt;

				color = att * ambient;

				color += att * (diffuse * NdotL );
			
		 		specular = gl_FrontMaterial.specular * gl_LightSource[light_index].specular;
	
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
		}
	
		finalColor += color;
		light_index++;
	}	

	if( enableColorMap )
	{
  		textureColor = texture2D(colorMap, newTexCoord );
		finalColor *= textureColor;
	}

	if( enableDirtMap )
	{
  		dirtColor = texture2D(dirtMap, gl_TexCoord[1].st );
		finalColor *= dirtColor;
	}
	myVec40 = vec4(finalColor.rgb, 0.0);

}


