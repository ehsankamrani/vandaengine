//Copyright (C) 2014 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]

#version 130

varying vec4 vPos;
void main()
{
    vPos = gl_ModelViewMatrix * gl_Vertex;

    gl_Position = gl_ProjectionMatrix * vPos;
}

[frag]

#version 130

#extension GL_EXT_texture_array : enable


out vec4 myVec40;
uniform vec4 far_d;
varying vec4 vPos;
uniform sampler2DArray stex;

uniform vec4 color[4] = vec4[4](	vec4(0.0, 0.0, 0.5, 1.0),
									vec4(0.0, 0.5, 0.0, 1.0),
									vec4(0.5, 0.0, 0.0, 1.0),
									vec4(0.5, 0.5, 0.0, 1.0));
									
vec4 shadowCoef()
{
	int index;
	if(gl_FragCoord.z < far_d.x)
		index = 0;
	else if(gl_FragCoord.z < far_d.y)
		index = 1;
	else if(gl_FragCoord.z < far_d.z)
		index = 2;
	else if(gl_FragCoord.z < far_d.w)
		index = 3;
	else
		return vec4( 1.0, 1.0, 1.0, 1.0);
	
	vec4 shadow_coord = gl_TextureMatrix[index]*vPos;
	
	shadow_coord.w = shadow_coord.z;
	shadow_coord.z = float(index);
	
	float shadow_d = texture2DArray(stex, shadow_coord.xyz).x;
	float diff = shadow_d - shadow_coord.w;
	return clamp( diff*250.0 + 1.0, 0.0, 1.0)*color[index];
}

void main()
{
	vec4 color;
	vec4 shadowColor = vec4(0.5, 0.5, 0.5, 0.5 );

	color += shadowColor;
	vec4 shadow_coef = shadowCoef();
	color *= shadow_coef;

	myVec40 = vec4(color.rgb, 0.0);
}


