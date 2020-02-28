#ifndef SPCWAD_ACOLORMAP_H
#define SPCWAD_ACOLORMAP_H

//=============================================================================

#include "alump.h"
#include <stdio.h>

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
	This class operates with colors maps which are used to color the entire screen. For example when you are wearing radiation suit it's all become in green
*/
class AColorMap
{
public:
    AColorMap();
    AColorMap(FILE* wadFile, const ALump& lump);
    ~AColorMap();
	AColorMap& operator=(const AColorMap& rv);

private:
	int _mapcolorSize;
    unsigned char* _mapcolorData;
	
    void destroy();
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ACOLORMAP_H
