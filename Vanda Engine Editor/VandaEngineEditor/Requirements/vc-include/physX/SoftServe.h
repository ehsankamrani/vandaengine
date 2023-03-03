#ifndef SOFT_SERVE_H

#define SOFT_SERVE_H

// saves a softbody as an NxuStream asset on disk.

class NxSoftBodyDesc;
class NxSoftBodyMeshDesc;

namespace SOFTBODY
{

class TetraModel;


bool saveSoftBodyNxuStream(const char *fname,      // the name to store the asset on disk.
                           const char *userProperties,  // user properties associated with this asset (identify graphics mesH)
                           const NxSoftBodyDesc &desc,        // The descriptor for the soft body
                           const NxSoftBodyMeshDesc &mesh);        // The descriptor for the soft body tetrahedral mesh

bool saveSoftBodyObj(const char *oname,const char *tname,TetraModel *model); // save as an OBJ + TET file.

bool saveSoftBodyEZM(const char *fname,TetraModel *model); // save as an EZ mesh file with TETs embedded in it.

void concatFile(char *dest,const char *source,const char *extension); // adds a different file name extension.

const char *getQuoteString(const char *str); // returns the source string in quotes if it contains seperator characters (space,tab,comma)

const char *lastDot(const char *src);

}; // END OF SOFTBODY NAMESPACE

#endif
