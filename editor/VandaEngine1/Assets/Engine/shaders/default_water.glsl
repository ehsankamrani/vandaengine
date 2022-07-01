//Copyright (C) 2022 Ehsan Kamrani
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

varying vec3 viewDir;
varying vec3 normal;
uniform bool enableDirtMap;

varying float Blur;
uniform float focalDistance, focalRange;

void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
    if( enableDirtMap )
		gl_TexCoord[1] = gl_MultiTexCoord3; //second uv set
	vec4 vPos;
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
	
    // fix of the clipping bug for both Nvidia and ATi
    #ifdef __GLSL_CG_DATA_TYPES
    gl_ClipVertex = vPos;
    #endif

    //DOF data
    float distance = abs(-vPos.z - focalDistance);
    if( distance < focalRange )
    {
		Blur = 0.0;
	}
	else
	{
   		Blur = clamp( (distance - focalRange) / focalRange, 0.0, 1.0);
   	}

    gl_Position = gl_ProjectionMatrix * vPos;
}

[frag]

#version 130

#extension GL_EXT_texture_array : enable

//Directional Light
#define NR_DIR_LIGHTS 2
uniform int nr_dir_lights;
varying vec3 lightDir[NR_DIR_LIGHTS];

//Point Light
#define NR_POINT_LIGHTS 2  
uniform int nr_point_lights;
varying float pointLightDist[NR_POINT_LIGHTS];
varying vec3 pointLightPos[NR_POINT_LIGHTS];
uniform float point_light_radius[NR_POINT_LIGHTS];

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

varying float Blur;
uniform bool enableFog;

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

		}
	
		finalColor += color;
		light_index++;
	}

	if( enableFog )
	{
		//Compute the fog here
		const float LOG2 = 1.442695; 
		float z = gl_FragCoord.z / gl_FragCoord.w;
		float fogFactor = exp2( -gl_Fog.density * 
			   gl_Fog.density * 
			   z * 
			   z * 
			   LOG2 );
		fogFactor = clamp(fogFactor, 0.0, 1.0);
	
		myVec40 = vec4(mix(gl_Fog.color, finalColor, fogFactor ).rgb, Blur);
	}
	else
		myVec40 = vec4(finalColor.r, finalColor.g, finalColor.b, Blur);
}


