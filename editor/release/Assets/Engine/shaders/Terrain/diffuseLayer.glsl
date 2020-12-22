//Copyright (C) 2020 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]

#version 130

varying float alpha1;
varying float alpha2;

void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0; //bottom
    gl_TexCoord[1] = gl_MultiTexCoord1; //slope
    gl_TexCoord[2] = gl_MultiTexCoord2; //top

	alpha1 = gl_Color.r;
	alpha2 = gl_Color.a;

    gl_Position = ftransform();
}

[frag]

#version 130

uniform sampler2D image1;
uniform sampler2D image2;
uniform sampler2D image3;

varying float alpha1;
varying float alpha2;

out vec4 myVec40;

void main()
{
	vec4 image1Color = texture2D(image1, gl_TexCoord[0].xy);
	vec4 image2Color = texture2D(image2, gl_TexCoord[1].xy);
	vec4 image3Color = texture2D(image3, gl_TexCoord[2].xy);

	vec4 finalColor;
	finalColor = mix(image2Color, image1Color, alpha1);
	finalColor = mix(image3Color, finalColor, alpha2);	

	myVec40 = vec4(finalColor.rgb, 0.0);
}
