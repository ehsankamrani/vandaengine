//Copyright (C) 2014 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]

#version 130
varying float Blur;
uniform float focalDistance, focalRange;

void main()
{
    //DOF data
    vec4 PosWV = gl_ModelViewMatrix * gl_Vertex;
    float distance = abs(-PosWV.z - focalDistance);
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

varying float Blur;
uniform bool enableFog;
out vec4 myVec40;
void main()
{
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
	
		myVec40 = vec4(mix(gl_Fog.color, vec4(0.0,0.0,0.0,0.0), fogFactor ).rgb, Blur);
	}
	else
		myVec40 = vec4(0.0, 0.0, 0.0, Blur);
}


