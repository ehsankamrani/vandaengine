/*----------------------------------------------------------------------------*\
|
|						     Nvidia PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/

// 
//          NXML
//
// For loading a physics scene from 
// an xml physics file format.
// 
// TODO: expose api
// If we want to provide the functions 
// here as a library for people to use
// for loading in xml into the physics 
// engine for them.
//
// Function:  nxmlLoadScene() - 
// The function takes a filename of
// an xml file that describes the
// physics scene.  See some of the sample files
// for an example of how it looks.
// The application must initialize 
// its physics engine itself.  This 
// layer is above the physics middleware.
// If no scene is provided one is created.
// Return value: the scene.
//
// nxmlContext() returns a string indicating the current 
// file and node context - useful to call during your
// PhysX error handler.  Then you'll know which object
// caused the error.  For example:
//    OutputStream::print(char *m) {
//       char *c=nxmlContext();
//       if(*c) printf("%s\n",c);
//       printf("%s\n",m);
//    }
//
//

#ifndef NXML_H
#define NXML_H

class NxScene;
class NxPhysicsSDK;

char *nxmlContext();    
NxScene *nxmlLoadScene(char *filename,NxPhysicsSDK* sdk,NxScene *scene=NULL);

#endif

//AGCOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright (c) 2005 NVIDIA Technologies.
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//AGCOPYRIGHTEND
