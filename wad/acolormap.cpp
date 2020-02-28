#include "acolormap.h"
#include "alumptools.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================
    
AColorMap::AColorMap() : _mapcolorSize(0), _mapcolorData(0)
{
    
}

//=============================================================================

AColorMap::AColorMap(FILE* wadFile, const ALump& lump) : _mapcolorSize(lump.lumpSize)
{
    if (lump.lumpSize)
    {
        _mapcolorData = new unsigned char [lump.lumpSize];
        ALumpTools::readLumpData(wadFile, lump, _mapcolorData);
    }
}

//=============================================================================

AColorMap::~AColorMap()
{
	destroy();
}

//=============================================================================

void AColorMap::destroy()
{
	if (_mapcolorSize)
	{
		_mapcolorSize = 0;
		delete [] _mapcolorData;
		_mapcolorData = 0;
	}
}

//=============================================================================

AColorMap& AColorMap::operator=(const AColorMap& rv)
{
	if (this == &rv)
	{
		return *this;
	}
	
	if (_mapcolorData && _mapcolorSize)
	{
		delete [] _mapcolorData;
		_mapcolorSize = 0;
	}
	
	_mapcolorSize = rv._mapcolorSize;
	_mapcolorData = new unsigned char[rv._mapcolorSize];
	memcpy(_mapcolorData, rv._mapcolorData, rv._mapcolorSize);
	
	return *this;
}

//=============================================================================

};  //  namespace spcWAD
