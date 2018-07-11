//Copyright (C) 2014 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]

#version 130
uniform bool enableDirtMap;
void main()
{
	vec4 vPos;
	if( enableDirtMap )
		gl_TexCoord[1] = gl_MultiTexCoord3; //second uv set	
    vPos = gl_ModelViewMatrix * gl_Vertex;
    gl_Position = gl_ProjectionMatrix * vPos;
}

[frag]

#version 130
uniform bool enableDirtMap;

uniform sampler2D dirtMap;

uniform bool firstPass;

out vec4 myVec40;

void main()
{

	vec2 newTexCoord;
	newTexCoord = gl_TexCoord[1].st;
	
	vec4 dirtColor;
		
	if( enableDirtMap )
	{
		dirtColor = texture2D(dirtMap, newTexCoord );
    }
	    	 
	//if( firstPass )
	//{
		myVec40 =  vec4(dirtColor.rgb, 0.0);
	//}	
}


