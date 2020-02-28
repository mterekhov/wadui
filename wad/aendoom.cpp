#include "aendoom.h"
#include "alumptools.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

AEnDoom::AEnDoom() : _endoomSize(0), _endoomData(0)
{
    
}

//=============================================================================

AEnDoom::AEnDoom(FILE* wadFile, const ALump& lump) : _endoomSize(lump.lumpSize)
{
    if (lump.lumpSize)
    {
        _endoomData = new unsigned char [lump.lumpSize];
        ALumpTools::readLumpData(wadFile, lump, _endoomData);
    }
}

//=============================================================================

AEnDoom::~AEnDoom()
{
	destroy();
}

//=============================================================================

void AEnDoom::destroy()
{
	if (_endoomSize)
	{
		_endoomSize = 0;
		delete [] _endoomData;
		_endoomData = 0;
	}
}

//=============================================================================

AEnDoom& AEnDoom::operator=(const AEnDoom& rv)
{
	if (this == &rv)
	{
		return *this;
	}
	
	destroy();

	_endoomSize = rv._endoomSize;
	_endoomData = new unsigned char[rv._endoomSize];
	memcpy(_endoomData, rv._endoomData, rv._endoomSize);
	
	return *this;
}

//=============================================================================

};  //  namespace spcWAD
