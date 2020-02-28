#include "atexture.h"
#include "autilities.h"
#include "aflat.h"
#include "atgaexporter.h"
#include "apicture.h"
#include <stdlib.h>
#include "alumptools.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

ATexture::ATexture(FILE* wadFile, const ALump& lump, const TIndexedPicturesList& patchesList)
{
    if (lump.lumpSize)
    {
        unsigned char *lumpData = new unsigned char [lump.lumpSize];
        ALumpTools::readLumpData(wadFile, lump, lumpData);
        TPatchesDescriptionList patchesDescription = readTextureMetaData(lumpData, patchesList);
        generateFinalImage(patchesDescription);
    }
}

//=============================================================================

TPatchesDescriptionList ATexture::readTextureMetaData(unsigned char *incomingData, const TIndexedPicturesList& patchesList)
{
    int bytesOffset = 0;
    char textureName[9] = {0};
    memcpy(textureName, &incomingData[bytesOffset], 8);
    _textureName = textureName;
    
    bytesOffset += 8;
    bytesOffset += 4;    //    skiping 4 bytes
    short textureWidth = 0;
    memcpy(&textureWidth, &incomingData[bytesOffset], 2);
    bytesOffset += 2;
    short textureHeight = 0;
    memcpy(&textureHeight, &incomingData[bytesOffset], 2);
    bytesOffset += 2;
    _imageData = AImageData(textureWidth, textureHeight);

    bytesOffset += 4;    //    skiping 4 bytes
    short texturePatchNumbers = 0;
    memcpy(&texturePatchNumbers, &incomingData[bytesOffset], 2);
    bytesOffset += 2;
    
    TPatchesDescriptionList patchesDescriptionList;
    for (int patchIndex = 0; patchIndex < texturePatchNumbers; patchIndex++)
    {
        short xOffset = 0;
        memcpy(&xOffset, &incomingData[bytesOffset], 2);
        bytesOffset += 2;
        
        short yOffset = 0;
        memcpy(&yOffset, &incomingData[bytesOffset], 2);
        bytesOffset += 2;
        
        int patchIndexInPatchDirectory = 0;
        memcpy(&patchIndexInPatchDirectory, &incomingData[bytesOffset], 2);
        bytesOffset += 2;
        bytesOffset += 4;    //    skiping 4 bytes
        
        if ((patchIndexInPatchDirectory > patchesList.size()) || (patchIndexInPatchDirectory < 0))
        {
            printf("\t\t\t%s can not be created because patch does not exist\n", textureName);
            continue;
        }
        
        SPatchDescription newDescription = {xOffset, yOffset, patchesList[patchIndexInPatchDirectory]};
        patchesDescriptionList.push_back(newDescription);
    }
    
    return patchesDescriptionList;
}

//=============================================================================

void ATexture::generateFinalImage(TPatchesDescriptionList& patchesDescriptionList)
{
    unsigned char *textureData = _imageData.data();
	for (TPatchesDescriptionListIter iter = patchesDescriptionList.begin(); iter != patchesDescriptionList.end(); iter++)
	{
		SPatchDescription& patchDescription = *iter;

		//	Соотнесем размер патча и размер текстуры в которую суем его
		//	Ну чтобы не получилось что патч больше текстуры по размерам
		int patchChunkHeight = patchDescription.patch.imageData.height();	//	Это как раз та высота которую мы должны выкусить из патча
		int patchChunkWidth = patchDescription.patch.imageData.width();

		int injectionY = patchDescription.y_offset;	//	это позиция внутри текстуры в которую надо впихать патч
		int patchY = 0;	//	это позиция внутри патча начиная с которой будем выкусывать кусочек патча
		if (injectionY < 0)
		{
			injectionY = 0;
			patchY = abs(patchDescription.y_offset);
			patchChunkHeight = patchDescription.patch.imageData.height() - patchY;
		}
		if (injectionY + patchChunkHeight > _imageData.height())
		{
			patchChunkHeight = _imageData.height() - injectionY;
		}

		int injectionX = patchDescription.x_offset;	//	это позиция внутри текстуры в которую надо впихать патч
		int patchX = 0;	//	это позиция внутри патча начиная с которой будем выкусывать кусочек патча
		if (injectionX < 0)
		{
			injectionX = 0;
			patchX = abs(patchDescription.x_offset);
			patchChunkWidth = patchDescription.patch.imageData.width() - patchX;
		}
		if (injectionX + patchChunkWidth > _imageData.width())
		{
			patchChunkWidth = _imageData.width() - injectionX;
		}

		unsigned char* flatData = patchDescription.patch.imageData.data();
		for (int y = injectionY; y < injectionY + patchChunkHeight; y++)
		{
			for (int x = injectionX; x < injectionX + patchChunkWidth; x++)
			{
				int patchPixelIndexX = patchX + x - injectionX;
				int patchPixelIndexY = patchY + y - injectionY;
				int patchPixelIndex = patchPixelIndexY * patchDescription.patch.imageData.width() + patchPixelIndexX;
				int texturePixelIndex = _imageData.width() * y + x;
				if (flatData[3 * patchPixelIndex] == PIXEL_TRANSPARENCY_MARKER)
				{
					continue;
				}
				memcpy(&textureData[3 * texturePixelIndex], &flatData[3 * patchPixelIndex], 3);
			}
		}
	}
}

//=============================================================================

ATexture::ATexture(const ATexture& texture) : _imageData(texture._imageData), _textureName(texture._textureName)
{
}

//=============================================================================

ATexture::~ATexture()
{
}

//=============================================================================

ATexture& ATexture::operator=(const ATexture& rv)
{
	if (this == &rv)
	{
		return *this;
	}
	
	_textureName = rv._textureName;
    _imageData = rv._imageData;
    
	return *this;
}

//=============================================================================

std::string ATexture::textureName() const
{
	return _textureName;
}

//=============================================================================

bool ATexture::saveTextureIntoTga(const std::string& fileName)
{
    return _imageData.exportIntoTga(fileName);
}

//=============================================================================

};  //  namespace spcWAD
