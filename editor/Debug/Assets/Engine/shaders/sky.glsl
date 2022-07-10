//Copyright (C) 2022 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]
#version 130
varying float Blur;
uniform float focalDistance, focalRange;

void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;

	vec4 vPos;
    vPos = gl_ModelViewMatrix * gl_Vertex;

    //DOF data
    float distance = abs(-vPos.z - focalDistance);
    if( distance < focalRange )
    {
		Blur = 0.0;
	}
	else
	{
   		Blur = clamp( (distance - focalRange) / focalRange, 0.0, 1.0);
   	}

    gl_Position = ftransform();
}

[frag]
#version 130
uniform sampler2D tex_unit_0; // texture unit
varying float Blur;
uniform bool enableFog;

out vec4 finalColor;

void main()
{
	vec4 color = texture2D(tex_unit_0, gl_TexCoord[0].xy);
	
	if( enableFog )
	{
		//Compute the fog here
		const float LOG2 = 1.442695; 
		float z = gl_FragCoord.z / gl_FragCoord.w;
		float fogFactor = exp2( -gl_Fog.density * 
			   gl_Fog.density * 
			   z * 
			   z * 
			   LOG2 );
		fogFactor = clamp(fogFactor, 0.0, 1.0);
	
		finalColor = vec4(mix(gl_Fog.color, color, fogFactor ).rgb, Blur);
	}
	else
		finalColor = vec4(color.r, color.g, color.b, Blur);
}

