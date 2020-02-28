#ifndef SPCWAD_ALUMPTOOLS_H
#define SPCWAD_ALUMPTOOLS_H

//=============================================================================

#include "alump.h"
#include "types.h"

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
    static std::vector<std::string> doom1MapLumpsNames();
    static std::vector<std::string> mapLumpsNames();
    
    /**
     Search of lumps which names begins with lumpsNameMask
     
     @param lumpsNameMask prefix of lump name to find
     @param lumpsList the list of lumps in which the search should be done
     @return the resulting list of lumps of end iterator in case of no results
     */
    static TLumpsList findLumpsList(const std::string& lumpsNameMask, const TLumpsList& lumpsList);
    
    /**
     Search of flat in flat lists with exact name flatNameToFind
     
     @param flatNameToFind name of flat to find
     @param flatList list in which the search should be done
     @return reference to founded flat
     */
    static const AFlat& findFlat(const std::string& flatNameToFind, const TFlatsList& flatList);
    
    /**
     Search of lump iterator in lumps list
     
     @param lumpNameToFind exasct name of lump to find
     @param lumpsList list in which the search should be done
     @return const iterator to founded lump
     */
    static TLumpsListConstIter findLumpIter(const std::string& lumpNameToFind, const TLumpsList& lumpsList);
    
    /**
     Read data of lump lumpToRead from file into already allocated memory lumpData
     
     @param wadFile file pointer to wad file
     @param lumpToRead lump which should be read
     @param lumpData allocated memory where to read the data
     @return true in case of success, or false in case of error
     */
    static bool readLumpData(FILE* wadFile, const ALump& lumpToRead, unsigned char *lumpData);
    
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ALUMPTOOLS_H
