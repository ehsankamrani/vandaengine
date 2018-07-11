//Copyright (C) 2014 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]
#version 130
void main( void )
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0;

    gl_FrontColor = vec4(1.0, 1.0, 1.0, 1.0);
}

[frag]
#version 130
uniform sampler2D tDiffuse; 
uniform sampler2D tPosition;
uniform sampler2D tNormals;
uniform vec3 cameraPosition;

void main( void )
{
	vec4 image = texture2D( tDiffuse, gl_TexCoord[0].xy );
	vec4 position = texture2D( tPosition, gl_TexCoord[0].xy );
	vec4 normal = texture2D( tNormals, gl_TexCoord[0].xy );
	
	vec3 light = vec3(-15, 15, 15);
	vec3 lightDir = light - position.xyz ;
	
	//normal = normalize(normal);
	lightDir = normalize(lightDir);
	
	vec3 eyeDir = normalize(cameraPosition-position.xyz);
	vec3 vHalfVector = normalize(lightDir.xyz+eyeDir);
	
	vec4 color;
	vec3 n = vec3( normal );

	color = max(dot(n,lightDir),0.0) * image;
	if( dot(n,lightDir) > 0 )
	{
		color += pow(clamp(dot(n,vHalfVector),0.0, 1.0), 160);
	}
	
	gl_FragColor = color ;
	//gl_FragColor = normal;
	//gl_FragColor = position;
	//gl_FragColor = image;
}
