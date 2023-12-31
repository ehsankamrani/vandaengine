//Copyright (C) 2024 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]

#version 130

varying float alpha1;
varying float alpha2;

void main()
{
    gl_Position = ftransform();
}

[frag]

#version 130

out vec4 colorOut;

void main()
{
	colorOut = vec4(0.0);
}
