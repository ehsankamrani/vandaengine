#ifndef SOFT_MESH_PSK_H

#define SOFT_MESH_PSK_H

namespace SOFTBODY
{

	class SoftMeshInterface;

	typedef bool (__cdecl *Callback_LoadSoftMeshPSK) (const char *oname,SoftMeshInterface *smi);

	extern Callback_LoadSoftMeshPSK gUserLoadSoftMeshPSK;

}; // END OF SOFTBODY NAMESPACE


#endif
