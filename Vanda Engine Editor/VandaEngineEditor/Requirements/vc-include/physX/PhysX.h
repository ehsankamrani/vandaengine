#ifndef PHYSX_H

#define PHYSX_H

class NxPhysicsSDK;

bool px_init(void);
void px_simulate(float dtime);
void px_release(void);
void px_render(void *d3device,void *hwnd,const void *view,const void *projection,float dtime);
void px_onDeviceReset(void *device);
void px_onLostDevice(void);
void px_setWorld(const void *world);
bool px_togglePaused(void);
bool px_setPaused(bool state);
bool px_createGroundPlane(void);
bool px_shootSphere(void);
void px_setGravity(const float *p);
void px_fetchResults(void);
void px_setAsync(bool state);
void px_setTimeScale(float scale);
bool px_paused();

NxPhysicsSDK * getSDK(void);


#endif
