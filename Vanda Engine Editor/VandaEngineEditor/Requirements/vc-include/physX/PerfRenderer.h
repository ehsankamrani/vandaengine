/*----------------------------------------------------------------------------*\
|
|						    NVIDIA PhysX Technology
|
|							    www.nvidia.com
|
\*----------------------------------------------------------------------------*/


#include "NxPhysics.h"

class PerfRenderer
{

private:
	bool m_profilerOn;

	static const unsigned int FPS_AVG_FRAMES=15;

	float fpsTimes[FPS_AVG_FRAMES];//we measure the fps as an average of the last n frames.
	int fpsIndex;

	float lastTime;

public:
	PerfRenderer();
	bool toggleEnable();
	void render(const NxProfileData* prof, int width, int height);

private:
	float computeFPS();

};

