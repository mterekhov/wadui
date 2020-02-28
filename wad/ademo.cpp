#include "ademo.h"
#include "alumptools.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

ADemo::ADemo() : _demoSize(0), _demoData(0)
{
    
}

//=============================================================================

ADemo::ADemo(FILE* wadFile, const ALump& lump) : _demoSize(lump.lumpSize)
{
    if (lump.lumpSize)
    {
        _demoData = new unsigned char [lump.lumpSize];
        ALumpTools::readLumpData(wadFile, lump, _demoData);
    }
}

//=============================================================================

ADemo::~ADemo()
{
	destroy();
}

//=============================================================================

void ADemo::destroy()
{
	if (_demoSize)
	{
		_demoSize = 0;
		delete [] _demoData;
		_demoData = 0;
	}
}

//=============================================================================

ADemo& ADemo::operator=(const ADemo& rv)
{
	if (this == &rv)
	{
		return *this;
	}

	destroy();
	
	_demoName = rv._demoName;
	_demoSize = rv._demoSize;
	_demoData = new unsigned char[rv._demoSize];
	
	memcpy(_demoData, rv._demoData, rv._demoSize);
	
	return *this;
}

//=============================================================================

};  //  namespace spcWAD
