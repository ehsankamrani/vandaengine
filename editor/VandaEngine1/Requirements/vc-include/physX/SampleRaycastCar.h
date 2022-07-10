#define NOMINMAX 

#if defined(WIN32)
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#elif defined(__APPLE__)
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#endif
#include <stdio.h>

#include "OrthographicDrawing.h"

// Physics code
#undef random
#include "NxPhysics.h"
#include "NxVehicle.h"

enum CreationModes { MODE_NONE, MODE_CAR, MODE_TRUCK };

extern NxPhysicsSDK*	gPhysicsSDK;
extern NxScene*			gScene;
extern NxSpringDesc wheelSpring;
extern bool keyDown[256];

extern NxUserContactReport * carContactReport;
//void initCar();
//void createCar(const NxVec3& pos);
void createCarWithDesc(const NxVec3& pos, bool frontWheelDrive, bool backWheelDrive, bool corvetteMotor, bool monsterTruck, bool oldStyle, NxPhysicsSDK* physicsSDK);
void createCart(const NxVec3& pos, bool frontWheelDrive, bool backWheelDrive, bool oldStyle);
NxVehicleDesc* createTruckPullerDesc(const NxVec3& pos, NxU32 nbGears, bool oldStyle);
NxVehicleDesc* createTruckTrailer1(const NxVec3& pos, NxReal length, bool oldStyle);
NxVehicleDesc* createFullTruckDesc(const NxVec3& pos, NxReal length, NxU32 nbGears, bool has4Axes, bool oldStyle);
NxVehicleDesc* createTwoAxisTrailer(const NxVec3& pos, NxReal length, bool oldStyle);

NxVehicle* createTruckPuller(const NxVec3& pos, NxU32 nbGears, bool oldStyle);
NxVehicle* createFullTruck(const NxVec3& pos, NxU32 nbGears, bool has4Axes, bool oldStyle);
NxVehicle* createTruckWithTrailer1(const NxVec3& pos, NxU32 nbGears, bool oldStyle);
NxVehicle* createFullTruckWithTrailer2(const NxVec3& pos, NxU32 nbGears, bool oldStyle);
//void tickCar();

void InitTerrain();
void RenderTerrain();
void RenderAllActors();
void renderHUD(OrthographicDrawing& orthoDraw);
