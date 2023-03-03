//Copyright (C) 2022 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]
#version 130
void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
}

[frag]
#version 130
uniform sampler2D tex_unit_0; // texture unit
uniform float red;
uniform float green;
uniform float blue;

void main()
{
	vec4 color = texture2D(tex_unit_0, gl_TexCoord[0].xy);
	
	if( color.a < 0.1)
	   	discard;
	
	color.r *= red;
	color.g *= green;
	color.b *= blue;

	gl_FragColor = 	vec4(color.rgb, 0.0);
}

