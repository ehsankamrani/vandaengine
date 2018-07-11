//Copyright (C) 2014 Ehsan Kamrani
//This file is licensed and distributed under MIT license
[vert]
varying vec2 Tap[4], TapNeg[3];
uniform int Height;

void main(void)
{
	vec2 vertTapOffs[7];
	vec2 TexCoord = gl_MultiTexCoord0.st;

	float dy = 1.0/float(Height);
	vertTapOffs[0] = vec2(0.0, 0.0);
	vertTapOffs[1] = vec2(0.0, 1.3366 * dy);
	vertTapOffs[2] = vec2(0.0, 3.4295 * dy);
	vertTapOffs[3] = vec2(0.0, 5.4264 * dy);
	vertTapOffs[4] = vec2(0.0, 7.4359 * dy);
	vertTapOffs[5] = vec2(0.0, 9.4436 * dy);
	vertTapOffs[6] = vec2(0.0, 11.4401 * dy);

	Tap[0] = TexCoord;
	Tap[1] = TexCoord + vertTapOffs[1];
	Tap[2] = TexCoord + vertTapOffs[2];
	Tap[3] = TexCoord + vertTapOffs[3];

	TapNeg[0] = TexCoord - vertTapOffs[1];
	TapNeg[1] = TexCoord - vertTapOffs[2];
	TapNeg[2] = TexCoord - vertTapOffs[3];

	gl_Position = ftransform();
	gl_TexCoord[0] = gl_MultiTexCoord0;
}

[frag]
varying vec2 Tap[4], TapNeg[3];
uniform sampler2D Tex0;
uniform int Height;

void main (void)
{
	vec2 vertTapOffs[7];
	vec2 Tap4[3], TapNeg4[3];

	const vec4 Weights0 = vec4(0.080, 0.075, 0.070, 0.100);
	const vec4 Weights1 = vec4(0.065, 0.060, 0.055, 0.050);

	// Samples
	vec4 s[7];
	// Acumulated color and weights
	vec4 ColorWeightSum;

	float dy = 1.0/float(Height);
	vertTapOffs[0] = vec2(0.0, 0.0);
	vertTapOffs[1] = vec2(0.0, 1.3366 * dy);
	vertTapOffs[2] = vec2(0.0, 3.4295 * dy);
	vertTapOffs[3] = vec2(0.0, 5.4264 * dy);
	vertTapOffs[4] = vec2(0.0, 7.4359 * dy);
	vertTapOffs[5] = vec2(0.0, 9.4436 * dy);
	vertTapOffs[6] = vec2(0.0, 11.4401 * dy);


	// Sample taps with coordinates from VS
	s[0] = texture2D(Tex0, Tap[0]);
	s[1] = texture2D(Tex0, Tap[1]);
	s[2] = texture2D(Tex0, Tap[2]);
	s[3] = texture2D(Tex0, Tap[3]);
	s[4] = texture2D(Tex0, TapNeg[0]);
	s[5] = texture2D(Tex0, TapNeg[1]);
	s[6] = texture2D(Tex0, TapNeg[2]);

	// Modulate sampled color values by the weights stored
	// in the alpha channel of each sample
	s[0].rgb = s[0].rgb * s[0].a;
	s[1].rgb = s[1].rgb * s[1].a;
	s[2].rgb = s[2].rgb * s[2].a;
	s[3].rgb = s[3].rgb * s[3].a;
	s[4].rgb = s[4].rgb * s[4].a;
	s[5].rgb = s[5].rgb * s[5].a;
	s[6].rgb = s[6].rgb * s[6].a;

	// Aggregate all samples weighting them with pre-defined
	// kernel weights, weight sum in alpha
	ColorWeightSum = s[0] * Weights0.w +
      (s[1] + s[4]) * Weights0.x +
      (s[2] + s[5]) * Weights0.y +
      (s[3] + s[6]) * Weights0.z;

	// Compute tex coords for other taps
	Tap4[0] = Tap[0] + vertTapOffs[4];
	Tap4[1] = Tap[0] + vertTapOffs[5];
	Tap4[2] = Tap[0] + vertTapOffs[6];
	TapNeg4[0] = Tap[0] - vertTapOffs[4];
	TapNeg4[1] = Tap[0] - vertTapOffs[5];
	TapNeg4[2] = Tap[0] - vertTapOffs[6];

	// Sample the taps
	s[0] = texture2D(Tex0, Tap4[0]);
	s[1] = texture2D(Tex0, Tap4[1]);
	s[2] = texture2D(Tex0, Tap4[2]);
	s[3] = texture2D(Tex0, TapNeg4[0]);
	s[4] = texture2D(Tex0, TapNeg4[1]);
	s[5] = texture2D(Tex0, TapNeg4[2]);

	// Modulate sampled color values by the weights stored
	// in the alpha channel of each sample
	s[0].rgb = s[0].rgb * s[0].a;
	s[1].rgb = s[1].rgb * s[1].a;
	s[2].rgb = s[2].rgb * s[2].a;
	s[3].rgb = s[3].rgb * s[3].a;
	s[4].rgb = s[4].rgb * s[4].a;
	s[5].rgb = s[5].rgb * s[5].a;

	 // Aggregate all samples weighting them with pre-defined
	// kernel weights, weight sum in alpha
	ColorWeightSum += (s[1] + s[3]) * Weights1.x +
      (s[1] + s[4]) * Weights1.y +
      (s[2] + s[5]) * Weights1.z;

	// Average combined sample for all samples in the kernel
	ColorWeightSum.rgb /= ColorWeightSum.a;

	// Final sum output
	gl_FragData[0] = ColorWeightSum;
}
