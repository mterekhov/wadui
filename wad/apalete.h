#ifndef SPCWAD_APALETE_H
#define SPCWAD_APALETE_H

//=============================================================================

#include "alump.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
	This class operates with palette for all images in resources, aka PLAYPAL lump
*/
class APalete
{
public:
    APalete();
    APalete(FILE* wadFile, const ALump& lump);
    ~APalete();
	APalete& operator=(const APalete& rv);

    const unsigned char red(const int index) const;
    const unsigned char green(const int index) const;
    const unsigned char blue(const int index) const;

private:
	int _paleteSize;
    unsigned char* _paleteData;
	
    void init(unsigned char* incomingData, const int incomingSize);
    void destroy();
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_APALETE_H
