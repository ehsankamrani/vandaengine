//Copyright (C) 2014 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]

#version 130
void main()
{
	vec4 vPos;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    vPos = gl_ModelViewMatrix * gl_Vertex;
    gl_Position = gl_ProjectionMatrix * vPos;
}

[frag]

#version 130
uniform bool enableColorMap;

uniform sampler2D colorMap;

uniform bool firstPass;

out vec4 myVec40;

void main()
{

	vec2 newTexCoord;
	newTexCoord = gl_TexCoord[0].st;
	
	vec4 colorColor;
		
	if( enableColorMap )
	{
		colorColor = texture2D(colorMap, newTexCoord );
    }
	    	 
	//if( firstPass )
	//{
		myVec40 =  vec4(colorColor.rgb, 0.0);
	//}	
}


