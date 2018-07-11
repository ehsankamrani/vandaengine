//Copyright (C) 2014 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]
void main()
{
	gl_TexCoord[0] = vec4(0.5)*gl_Vertex + vec4(0.5);
	gl_Position = gl_Vertex;
}

[frag]
#version 120
#extension GL_EXT_texture_array : enable

uniform sampler2DArray tex;
uniform float layer;

void main()
{
	vec4 tex_coord = vec4(gl_TexCoord[0].x, gl_TexCoord[0].y, layer, 1.0);
	gl_FragColor = texture2DArray(tex, tex_coord.xyz);
}
