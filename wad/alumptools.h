#ifndef SPCWAD_ALUMPTOOLS_H
#define SPCWAD_ALUMPTOOLS_H

//=============================================================================

#include <string>
#include <list>

//=============================================================================

namespace spcWAD
{
    
//=============================================================================

class ALumpTools
{
public:
    static std::string lumpDescription(const std::string& lumpName);
    static std::list<std::string> doom1MapLumpsNames();
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ALUMPTOOLS_H
