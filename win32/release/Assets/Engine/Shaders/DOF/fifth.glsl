//Copyright (C) 2014 Ehsan Kamrani
//This file is licensed and distributed under MIT license

[vert]
void main(void)
{
	gl_Position = ftransform();
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_MultiTexCoord1;
}

[frag]
uniform sampler2D Tex0, Tex1;

void main (void)
{
	vec4 Fullres = texture2D(Tex0, gl_TexCoord[0].st);
	vec4 Blurred = texture2D(Tex1, gl_TexCoord[1].st);

	// GLSL linear interpolation function
	gl_FragColor = Fullres + Fullres.a * (Blurred - Fullres);
}
