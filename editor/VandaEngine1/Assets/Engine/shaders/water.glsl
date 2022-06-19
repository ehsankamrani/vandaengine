//Copyright (C) 2023 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]

#version 130
varying vec4 refrCoords; 
varying vec4 normCoords; 
varying vec4 viewCoords;
varying vec4 viewTangetSpace;
varying vec4 lightTangetSpace;

uniform vec4 lightPos, cameraPos;


void main()
{
	// Because we have a flat plane for water we already know the vectors for tangent space
	vec4 tangent = vec4(1.0, 0.0, 0.0, 0.0);
	vec4 normal = vec4(0.0, 1.0, 0.0, 0.0);
	vec4 biTangent = vec4(0.0, 0.0, 1.0, 0.0);

	// Calculate the vector coming from the vertex to the camera
	vec4 viewDir = cameraPos -  gl_Vertex;

	// Compute tangent space for the view direction
	viewTangetSpace.x = dot(viewDir, tangent);
	viewTangetSpace.y = dot(viewDir, biTangent);
	viewTangetSpace.z = dot(viewDir, normal);
	viewTangetSpace.w = 1.0;

	// Calculate the vector that the light hits the vertex
	vec4 lightDir = lightPos - gl_Vertex;

	// Compute tangent space for the light direction
	lightTangetSpace.x = dot(lightDir, tangent);
	lightTangetSpace.y = dot(lightDir, biTangent);
	lightTangetSpace.z = dot(lightDir, normal);
	lightTangetSpace.w = 1.0;

	gl_TexCoord[0] = gl_MultiTexCoord0;
	refrCoords = gl_MultiTexCoord1;
	normCoords = gl_MultiTexCoord2;

	// This calculates our current projection coordinates
	viewCoords = gl_ModelViewProjectionMatrix * gl_Vertex;

	gl_Position = viewCoords;
}
[frag]

#version 130

varying vec4 refrCoords; 
varying vec4 normCoords; 
varying vec4 viewCoords;
varying vec4 viewTangetSpace;
varying vec4 lightTangetSpace;

uniform sampler2D reflection;
uniform sampler2D refraction;
uniform sampler2D normalMap;
uniform sampler2D dudvMap;
uniform sampler2D depthMap;
uniform vec4 waterColor;
uniform bool renderAboveWater;
void main()
{
	const float kShine = 128.0;
	const float kDistortion = 0.015;
	const float kRefraction = 0.009;

	vec4 distOffset = texture2D(dudvMap, normCoords.xy) * kDistortion;
	vec4 dudvColor = texture2D(dudvMap, vec2(refrCoords + distOffset));
	dudvColor = normalize(dudvColor * 2.0 - 1.0) * kRefraction;

	vec4 normalVector = texture2D(normalMap, vec2(refrCoords + distOffset));
	normalVector = normalVector * 2.0 - 1.0;
	normalVector.a = 0.0;

	vec4 lightReflection = normalize( reflect(-lightTangetSpace, normalVector) );

	vec4 invertedFresnel = vec4( dot(normalVector, lightReflection ) );
	vec4 fresnelTerm = 1.0 - invertedFresnel;

	vec4 projCoord = viewCoords / viewCoords.q;
	projCoord = (projCoord + 1.0) * 0.5;
	projCoord += dudvColor;
	projCoord = clamp(projCoord, 0.001, 0.999);
	
	vec4 depthValue = texture2D(depthMap, projCoord.xy);
		
	vec4 invDepth = 1.0 - depthValue;

	vec4 localView = normalize(viewTangetSpace);		
	float intensity = max(0.0, dot(lightReflection, localView) );
	vec4 specular = vec4(pow(intensity, kShine));

	if(renderAboveWater)
	{
		vec4 refractionColor  = texture2D(refraction, projCoord.xy);
		refractionColor *= invertedFresnel * invDepth;
		refractionColor +=  waterColor * depthValue * invertedFresnel;

		vec4 reflectionColor  = texture2D(reflection, projCoord.xy);
		reflectionColor *= fresnelTerm;
		gl_FragColor = vec4(refractionColor.xyz + reflectionColor.xyz + specular.xyz, 0.0); 
	}
	else
	{
		vec4 refractionColor  = texture2D(refraction, gl_TexCoord[0].xy);
		refractionColor *= invertedFresnel * invDepth;
		refractionColor +=  waterColor * depthValue * invertedFresnel;

		vec4 color = waterColor * fresnelTerm;
		gl_FragColor = vec4(refractionColor.xyz + color.xyz + specular.xyz, 0.0); 
	}
}
