//Copyright (C) 2024 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]
#version 130
void main()
{
    gl_Position = ftransform();
}

[frag]
#version 130

void main()
{
	vec4 color = gl_FrontMaterial.emission;
	
	gl_FragColor = 	vec4(color.rgb, 0.0);
}

