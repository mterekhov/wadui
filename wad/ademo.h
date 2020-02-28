#ifndef SPCWAD_ADEMO_H
#define SPCWAD_ADEMO_H

//=============================================================================

#include "alump.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
	This class operates with data for demos at the begining of the game
*/
class ADemo
{
public:
    ADemo();
    ADemo(FILE* wadFile, const ALump& lump);
    ~ADemo();
	ADemo& operator=(const ADemo& rv);

private:
	int _demoSize;
    unsigned char* _demoData;
    std::string _demoName;
	
    void destroy();
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ADEMO_H
