#ifndef	CORE_DUMP_H

#define	CORE_DUMP_H


bool         NxCoreDump(NxPhysicsSDK *sdk,const char *fname,bool binary,bool saveCooked);
unsigned int NxGetCoreVersion(NxPhysicsSDK *sdk); // return munged version number id of this SDK or current header files.


#endif
