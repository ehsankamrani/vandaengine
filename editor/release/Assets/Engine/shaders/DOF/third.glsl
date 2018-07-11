//Copyright (C) 2014 Ehsan Kamrani
//This file is licensed and distributed under MIT license

[vert]
varying vec2 Tap[4], TapNeg[3];
uniform int Width;

void main(void)
{
	vec2 horzTapOffs[7];
	vec2 TexCoord = gl_MultiTexCoord0.st;

	float dx = 1.0/float(Width);
	horzTapOffs[0] = vec2(0.0, 0.0);
	horzTapOffs[1] = vec2(1.3366 * dx, 0.0);
	horzTapOffs[2] = vec2(3.4295 * dx, 0.0);
	horzTapOffs[3] = vec2(5.4264 * dx, 0.0);
	horzTapOffs[4] = vec2(7.4359 * dx, 0.0);
	horzTapOffs[5] = vec2(9.4436 * dx, 0.0);
	horzTapOffs[6] = vec2(11.4401 * dx, 0.0);

	Tap[0] = TexCoord;
	Tap[1] = TexCoord + horzTapOffs[1];
	Tap[2] = TexCoord + horzTapOffs[2];
	Tap[3] = TexCoord + horzTapOffs[3];

	TapNeg[0] = TexCoord - horzTapOffs[1];
	TapNeg[1] = TexCoord - horzTapOffs[2];
	TapNeg[2] = TexCoord - horzTapOffs[3];

	gl_Position = ftransform();
	gl_TexCoord[0] = gl_MultiTexCoord0;
}

[frag]
varying vec2 Tap[4], TapNeg[3];
uniform sampler2D Tex0;
uniform int Width;
uniform bool debugMode;
void main (void)
{
	if( debugMode )
	{
		vec4 debugValue = vec4(1.0);
		gl_FragData[0] = debugValue;
		return;
	}
	
	vec2 horzTapOffs[7];
	vec2 Tap4[3], TapNeg4[3];

	// Thresholds for computing sample weights
	const vec4 Thresh0 = vec4(0.1, 0.1, 0.1, 1.0);
	const vec4 Thresh1 = vec4(0.7, 0.0, 0.7, 1.0);

	// Samples
	vec4 s[7], Weights4;
	vec3 Weights3, ColorSum;
	float WeightSum;

	float dx = 1.0/float(Width);
	horzTapOffs[0] = vec2(0.0, 0.0);
	horzTapOffs[1] = vec2(1.3366 * dx, 0.0);
 	horzTapOffs[2] = vec2(3.4295 * dx, 0.0);
	horzTapOffs[3] = vec2(5.4264 * dx, 0.0);
	horzTapOffs[4] = vec2(7.4359 * dx, 0.0);
	horzTapOffs[5] = vec2(9.4436 * dx, 0.0);
	horzTapOffs[6] = vec2(11.4401 * dx, 0.0);


	// Sample taps with coordinates from VS
	s[0] = texture2D(Tex0, Tap[0]);
	s[1] = texture2D(Tex0, Tap[1]);
	s[2] = texture2D(Tex0, Tap[2]);
	s[3] = texture2D(Tex0, Tap[3]);
	s[4] = texture2D(Tex0, TapNeg[0]);
	s[5] = texture2D(Tex0, TapNeg[1]);
	s[6] = texture2D(Tex0, TapNeg[2]);

	// Compute weights for 4 first samples (including center tap)
	// by thresholding blurriness (in sample alpha)
	Weights4.x = clamp(s[1].a - Thresh0.x, 0.0, 1.0);
	Weights4.y = clamp(s[2].a - Thresh0.y, 0.0, 1.0);
	Weights4.z = clamp(s[3].a - Thresh0.x, 0.0, 1.0);
	Weights4.w = clamp(s[0].a - Thresh0.w, 0.0, 1.0);

	// Accumulate weighted samples
	ColorSum = vec3(s[0] * Weights4.x + s[1] * Weights4.y + s[2] * Weights4.z + s[3] * Weights4.w);

	// Sum weights using DOT
	WeightSum = dot(Weights4, vec4(1.0));

	// Compute weights for 3 remaining samples
	Weights3.x = clamp(s[4].a - Thresh0.x, 0.0, 1.0);
	Weights3.y = clamp(s[5].a - Thresh0.y, 0.0, 1.0);
	Weights3.z = clamp(s[6].a - Thresh0.z, 0.0, 1.0);

	// Accumulate weighted samples
	ColorSum += vec3(s[4] * Weights3.x + s[4] * Weights3.y + s[6] * Weights3.z);

	// Sum weights using DOT
	WeightSum += dot(Weights3, vec3(1.0));

	// Compute tex coords for other taps
	Tap4[0] = Tap[0] + horzTapOffs[4];
	Tap4[1] = Tap[0] + horzTapOffs[5];
	Tap4[2] = Tap[0] + horzTapOffs[6];
	TapNeg4[0] = Tap[0] - horzTapOffs[4];
	TapNeg4[1] = Tap[0] - horzTapOffs[5];
	TapNeg4[2] = Tap[0] - horzTapOffs[6];

	// Sample the taps
	s[0] = texture2D(Tex0, Tap4[0]);
	s[1] = texture2D(Tex0, Tap4[1]);
	s[2] = texture2D(Tex0, Tap4[2]);
	s[3] = texture2D(Tex0, TapNeg4[0]);
	s[4] = texture2D(Tex0, TapNeg4[1]);
	s[5] = texture2D(Tex0, TapNeg4[2]);

	// Compute weights for 3 samples
	Weights3.x = clamp(s[0].a - Thresh1.x, 0.0, 1.0);
	Weights3.y = clamp(s[1].a - Thresh1.y, 0.0, 1.0);
	Weights3.z = clamp(s[2].a - Thresh1.z, 0.0, 1.0);
	
	// Accumulate weighted samples
	ColorSum += vec3(s[0] * Weights3.x + s[1] * Weights3.y + s[2] * Weights3.z);

	// Sum weights using DOT
	WeightSum += dot(Weights3, vec3(1.0));

	// Compute weights for 3 samples
	Weights3.x = clamp(s[3].a - Thresh1.x, 0.0, 1.0);
	Weights3.y = clamp(s[4].a - Thresh1.y, 0.0, 1.0);
	Weights3.z = clamp(s[5].a - Thresh1.z, 0.0, 1.0);

	// Accumulate weighted samples
	ColorSum += vec3(s[3] * Weights3.x + s[4] * Weights3.y + s[5] * Weights3.z);

	// Sum weights using DOT
	WeightSum += dot(Weights3, vec3(1.0));

	// Divide weighted sum of samples by sum of all weights
	ColorSum /= WeightSum;
	
	// Color and weights sum output
	gl_FragData[0] = vec4(ColorSum, WeightSum);
}
