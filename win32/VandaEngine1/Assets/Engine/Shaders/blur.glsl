//Copyright (C) 2014 Ehsan Kamrani
//This file is licensed and distributed under MIT license

[vert]
#version 110
uniform float radius_x, radius_y; // typycally radius_x = 1.0 / (texture resolution x)

void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0 - vec4(-radius_x, 0.0, 0.0, 0.0);
    gl_TexCoord[1] = gl_MultiTexCoord0 - vec4(radius_x, 0.0, 0.0, 0.0);
    gl_TexCoord[2] = gl_MultiTexCoord0 - vec4(0.0, -radius_y, 0.0, 0.0);
    gl_TexCoord[3] = gl_MultiTexCoord0 - vec4(0.0, radius_y, 0.0, 0.0);
    
    gl_Position = ftransform();
}

[frag]
#version 110
uniform sampler2D tex_unit_0; // texture from previous blurring stage

void main()
{
	vec4 sample[4];
	
	sample[0] = texture2D(tex_unit_0, gl_TexCoord[0].st);
	sample[1] = texture2D(tex_unit_0, gl_TexCoord[1].st);
	sample[2] = texture2D(tex_unit_0, gl_TexCoord[2].st);
	sample[3] = texture2D(tex_unit_0, gl_TexCoord[3].st);

	gl_FragColor = 	(sample[0] + sample[1] + sample[2] + sample[3]) / 4.0;
}
