//Copyright (C) 2023 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]

#version 130
uniform bool enableGlossMap;
void main()
{
	vec4 vPos;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	vPos = gl_ModelViewMatrix * gl_Vertex;
    gl_Position = gl_ProjectionMatrix * vPos;
}

[frag]

#version 130
uniform bool enableGlossMap;

uniform sampler2D glossMap;

uniform bool firstPass;

out vec4 colorOut;

void main()
{

	vec2 newTexCoord;
	newTexCoord = gl_TexCoord[0].st;
	
	vec4 glossColor;
		
	if( enableGlossMap )
	{
		glossColor = texture2D(glossMap, newTexCoord );
    }
	    	 
	//if( firstPass )
	//{
		colorOut =  vec4(glossColor.rgb, 0.0);
	//}	
}


