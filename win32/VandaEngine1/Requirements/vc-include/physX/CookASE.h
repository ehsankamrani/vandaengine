class NxActor;
class NxScene;
#include <string>
#include <NxVec3.h>

NxActor* CookASE(const std::string& filename, NxScene* scene, NxVec3 offset = NxVec3(0,0,0), NxVec3 scale = NxVec3(1,1,1));
