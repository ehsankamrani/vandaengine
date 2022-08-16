//Copyright (C) 2022 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]

#version 130
varying vec4 position;
uniform mat4 camera_inverse_matrix;
void main()
{
    vec4 vPos = gl_ModelViewMatrix * gl_Vertex;
    gl_Position = gl_ProjectionMatrix * vPos;

	mat4 modelMatrix = camera_inverse_matrix * gl_ModelViewMatrix;
    position = modelMatrix * gl_Vertex;
}

[frag]

#version 130
varying vec4 position;
out vec4 colorOut;
void main()
{
	vec4 pos = normalize( position );
	colorOut = vec4(pos.xyz,0.0);
}


