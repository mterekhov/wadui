#ifndef SPCWAD_ATEXTURE_H
#define SPCWAD_ATEXTURE_H

//=============================================================================

#include <vector>
#include <string>

#include "types.h"
#include "aimagedata.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
 Texture is used for walls only, for vertical surfaces only. Every texture is made of list of patches. But the texture does not contains all the patch, only it's chunk. So patchesDescriptionList is the description of what chunk of patch and where should be places
 */
class ATexture
{
public:
    ATexture(FILE* wadFile, const ALump& lump, const TIndexedPicturesList& patchesList);
	ATexture(const ATexture& texture);
    ~ATexture();
	ATexture& operator=(const ATexture& rv);

	bool saveTextureIntoTga(const std::string& fileName);
	std::string textureName() const;

private:
    TPatchesDescriptionList readTextureMetaData(unsigned char *incomingData, const TIndexedPicturesList& patchesList);
    void generateFinalImage(TPatchesDescriptionList& patchesDescriptionList);
    std::string _textureName;
    AImageData _imageData;
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_ATEXTURE_H
