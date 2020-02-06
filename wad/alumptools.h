#ifndef SPCWAD_ALUMPTOOLS_H
#define SPCWAD_ALUMPTOOLS_H

//=============================================================================

#include <string>
#include <list>

//=============================================================================

namespace spcWAD
{
    
//=============================================================================
    
enum ELumpType {
    LUMPTYPE_UNKNOWN,
    LUMPTYPE_PICTURE, //  special picture format
    LUMPTYPE_IMAGE, //  raw rgb data for floor and ceiling
    LUMPTYPE_TEXTURE, //  complex description of what LUMPTYPE_PICTUREs and how should be merged to assemble final image
    LUMPTYPE_SOUND,
    LUMPTYPE_MAP,
    LUMPTYPE_PALETTE,
    LUMPTYPE_COLOR_MAP,
    LUMPTYPE_ENCODED_TEXT,
    LUMPTYPE_DEMO
};

struct SLumpDescription {
    std::string description;
    ELumpType type;
};

//=============================================================================

class ALumpTools
{
public:
    static SLumpDescription lumpDescription(const std::string& lumpName);
    static std::list<std::string> doom1MapLumpsNames();
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ALUMPTOOLS_H
