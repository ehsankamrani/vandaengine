//Copyright (C) 2022 Ehsan Kamrani
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

uniform sampler2D image1Normal;
uniform sampler2D image2Normal;
uniform sampler2D image3Normal;

varying float alpha1;
varying float alpha2;

out vec4 myVec40;

void main()
{
	vec4 image1NormalColor = texture2D(image1Normal, gl_TexCoord[0].xy);
	vec4 image2NormalColor = texture2D(image2Normal, gl_TexCoord[1].xy);
	vec4 image3NormalColor = texture2D(image3Normal, gl_TexCoord[2].xy);

	vec4 normalMapColor;
	normalMapColor = mix(image2NormalColor, image1NormalColor, alpha1);
	normalMapColor = mix(image3NormalColor, normalMapColor, alpha2);	

	myVec40 = vec4(normalMapColor.rgb, 0.0);
}
