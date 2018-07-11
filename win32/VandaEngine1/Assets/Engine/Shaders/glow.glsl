//Copyright (C) 2014 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]
void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
}

[frag]
uniform sampler2D tex_unit_0; // blurred screen space texture

void main()
{
	vec3 sample = texture2D(tex_unit_0, gl_TexCoord[0].st).rgb;
	
	sample = (sample - vec3(0.1, 0.15 , 0.15) )*1.0;
	
	gl_FragColor = 	vec4(sample, 1.0);
}

