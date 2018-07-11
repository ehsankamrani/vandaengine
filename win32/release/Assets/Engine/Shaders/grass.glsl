//Copyright (C) 2014 Ehsan Kamrani
//This file is licensed and distributed under MIT license

[vert]

#version 110
uniform float time;
void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0; //diffuse and alpha texture coordinates
    vec4 position;
    if( gl_TexCoord[0].t > 0.9 )
		position = gl_Vertex + vec4(sin(time) * 0.02,0.0,0.0, 0.0 );
	else
		position = gl_Vertex;
    gl_Position = gl_ModelViewProjectionMatrix * position;
}

[frag]

#version 110

uniform bool enableFog;

uniform sampler2D colorMap;
uniform sampler2D alphaMap;

void main()
{
	vec4 alpha_color = texture2D(alphaMap, gl_TexCoord[0].xy);
	
	if(alpha_color.r<0.1)
	{
	  	discard;
	}

	vec4 textureColor;
	textureColor = texture2D(colorMap, gl_TexCoord[0].st );
	
	vec4 color = textureColor * 0.6;

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
	
		gl_FragColor = mix(gl_Fog.color, color, fogFactor );
	}
	else
		gl_FragColor = color;
}

