// ===============================================================================
//
//							NVIDIA PhysX SDK Samples
//
// This file contains settings used by all the sample applications, for connecting
// to the Visual Remote Debugger (VRD). Edit this file to make the samples connect
// to the computer running the VRD application.
//
// ===============================================================================

#ifndef SAMPLES_VRD_SETTINGS
#define SAMPLES_VRD_SETTINGS

#include "NxRemoteDebugger.h"

//Set this to 0 to stop the samples from trying to connect to the VRD
#define SAMPLES_USE_VRD 1

//Change this setting to the IP number or DNS name of the computer that is running the VRD
#define SAMPLES_VRD_HOST "localhost"
//Change this setting to the port on which the VRD is listening, or keep the default: NX_DBG_DEFAULT_PORT
#define SAMPLES_VRD_PORT NX_DBG_DEFAULT_PORT
//Change this setting to decide what type of information is sent to the VRD. Default: NX_DBG_EVENTMASK_EVERYTHING
#define SAMPLES_VRD_EVENTMASK NX_DBG_EVENTMASK_EVERYTHING

#endif //SAMPLES_VRD_SETTINGS
