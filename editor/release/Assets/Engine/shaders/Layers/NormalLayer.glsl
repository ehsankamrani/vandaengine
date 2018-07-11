//Copyright (C) 2014 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]

#version 130
varying vec3 GNormal;
uniform mat4 camera_inverse_matrix;
void main()
{
	mat4 modelMatrix = camera_inverse_matrix * gl_ModelViewMatrix;
	mat3 modelMatrix3x3 = mat3(modelMatrix); 
	
	GNormal = normalize( modelMatrix3x3 * gl_Normal );
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
}

[frag]

#version 130
varying vec3 GNormal;
out vec4 myVec40;

void main()
{
	vec3 norm = normalize( GNormal );
	myVec40 = vec4( norm.xyz,0.0 );
}


