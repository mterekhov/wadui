#ifndef SPCWAD_AENDOOM_H
#define SPCWAD_AENDOOM_H

//=============================================================================

#include "alump.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
 This class operates with colored texts which you can see in console when quit the game
 */
class AEnDoom
{
public:
    AEnDoom();
    AEnDoom(FILE* wadFile, const ALump& lump);
    ~AEnDoom();
	AEnDoom& operator=(const AEnDoom& rv);

private:
	int _endoomSize;
    unsigned char* _endoomData;
	
    void destroy();
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AENDOOM_H
