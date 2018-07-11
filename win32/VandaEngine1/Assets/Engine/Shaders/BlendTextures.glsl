//Copyright (C) 2014 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]
void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
}

[frag]
uniform sampler2D tex_unit_0;
uniform sampler2D tex_unit_1;
uniform bool blendLights;
void main()
{
	vec4 sample1 = texture2D(tex_unit_0, gl_TexCoord[0].st).rgba;
	vec4 sample2 = texture2D(tex_unit_1, gl_TexCoord[0].st).rgba;
	
	if( blendLights )
	{
		gl_FragColor = sample1 + sample2;
	}	
	else
	{
		float fogFactor;
		if( sample2.r > 0.0 )
			fogFactor = sample2.r/ gl_Fog.color.r;
		else if( sample2.g > 0.0 )
			fogFactor = sample2.g/ gl_Fog.color.g;
		else if( sample2.b > 0.0 )
			fogFactor = sample2.b/ gl_Fog.color.b;
	
		gl_FragColor = vec4(mix(sample1, sample2, fogFactor ).rgb, sample1.a + sample2.a);

	}
}
