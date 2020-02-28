#include <stdio.h>

#include "awad.h"
#include "alump.h"
#include "apalete.h"
#include "aflat.h"
#include "atexture.h"
#include "autilities.h"
#include "alumptools.h"
#include "alevel.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

#pragma mark - Constructor&Destructor -
    
//=============================================================================

AWAD::AWAD(const std::string& fileName) : _type(WADTYPE_UNKNOWN), _fileName(fileName)
{
	FILE* wadFile = 0;
	wadFile = fopen(fileName.c_str(), "rb");
	if (!wadFile)
		throw;

	if (!checkSignature(wadFile))
        throw;

    if (!readTableOfContents(wadFile))
        throw;

	if (!readPalete(wadFile))
		throw;
	
    if (!readFlats(wadFile))
        throw;

    if (!readPatches(wadFile))
        throw;

    if (!readTextures(wadFile))
        throw;
    
	if (!readColorMap(wadFile))
		throw;

	if (!readEndDoom(wadFile))
		throw;

	if (!readDemos(wadFile))
		throw;
	
	if (!readLevel(wadFile))
		throw;


//    for (TIndexedPicturesListIter iter = _patchesList.begin(); iter != _patchesList.end(); iter++)
//    {
//        APicture& patch = *iter;
//        std::string path = "/Users/michael/Pictures/patch/";
//        path += patch.patchName();
//        path += ".tga";
//        patch.savePatchIntoTga(path);
//    }
//
//    for (TFlatsListIter iter = _flatsList.begin(); iter != _flatsList.end(); iter++)
//    {
//        AFlat& flat = *iter;
//        std::string path = "/Users/michael/Pictures/flat/";
//        path += flat.flatName();
//        path += ".tga";
//        flat.saveFlatIntoTga(path);
//    }
//
//    for (TTexturesListIter iter = _texturesList.begin(); iter != _texturesList.end(); iter++)
//    {
//        ATexture& texture = *iter;
//        std::string path = "/Users/michael/Pictures/texture/";
//        path += texture.textureName();
//        path += ".tga";
//        texture.saveTextureIntoTga(path);
//    }
//
//    int i = 0;
//    for (TLumpsListIter iter = _tableOfContents.begin(); iter != _tableOfContents.end(); iter++)
//    {
//        printf("%i. <%s>\n", ++i, iter->lumpName.c_str());
//    }

	fclose(wadFile);
}

//=============================================================================

AWAD::~AWAD()
{
}

//=============================================================================
    
#pragma mark - Public -
    
//=============================================================================

const TLumpsList& AWAD::lumpsList() const
{
    return _tableOfContents;
}

//=============================================================================

void AWAD::exportLump(const ALump& lump, const std::string& folderToExport)
{
    FILE* wadFile = 0;
    wadFile = fopen(_fileName.c_str(), "rb");
    if (!wadFile)
        throw;

    if (lump.lumpSize == 0)
    {
        return;
    }
    
    unsigned char *lumpData = new unsigned char [lump.lumpSize];
    ALumpTools::readLumpData(wadFile, lump, lumpData);
    fclose(wadFile);

    std::string exportPath = folderToExport + "/" + lump.lumpName + ".lump";
    FILE *exportFile = fopen(exportPath.c_str(), "wb+");
    if (!exportFile)
        throw;
    fwrite(lumpData, lump.lumpSize, 1, exportFile);
    
    fclose(exportFile);
    delete [] lumpData;
}

//=============================================================================

#pragma mark - Routine -

//=============================================================================

bool AWAD::checkSignature(FILE* wadFile)
{
    char magic[4] = {0};
    int read = fread(magic, 1, 4, wadFile);
    if (read != 4)
        return false;

    if (!strncmp(magic, "IWAD", 4))
        _type = WADTYPE_INTERNAL_WAD;

    if (!strncmp(magic, "PWAD", 4))
        _type = WADTYPE_PATCH_WAD;

    return true;
}

//=============================================================================

bool AWAD::readTableOfContents(FILE* wadFile)
{
    int lumpsNumber = 0;
    int read = fread(&lumpsNumber, 4, 1, wadFile);
    if (read != 1)
        return false;

    int lumpsTOCOffset = 0;
    read = fread(&lumpsTOCOffset, 4, 1, wadFile);
    if (read != 1)
        return false;

    if (fseek(wadFile, lumpsTOCOffset, SEEK_SET))
        return false;

    for (int i = 0; i < lumpsNumber; i++)
    {
        int offset = 0;
        //  read offset
        read = fread(&offset, 4, 1, wadFile);
        if (read != 1)
            return false;

        //  read size of lump
        int size = 0;
        read = fread(&size, 4, 1, wadFile);
        if (read != 1)
            return false;

        //  read name of lump
        char name[9] = {0};
        read = fread(&name, 8, 1, wadFile);
        if (read != 1)
            return false;
		ALump newLump(size, offset, name);
        _tableOfContents.push_back(newLump);
    }

    return true;
}

//=============================================================================

bool AWAD::readPalete(FILE* wadFile)
{
	TLumpsListConstIter playpalLumpIter = ALumpTools::findLumpIter("PLAYPAL", _tableOfContents);
	if (playpalLumpIter == _tableOfContents.end())
	{
		return false;
	}
	
	const ALump& playpalLump = *playpalLumpIter;
    _palete = APalete(wadFile, playpalLump);

    return true;
}

//=============================================================================

bool AWAD::readColorMap(FILE* wadFile)
{
	TLumpsListConstIter colorMapLumpIter = ALumpTools::findLumpIter("COLORMAP", _tableOfContents);
	if (colorMapLumpIter == _tableOfContents.end())
	{
		return false;
	}
	const ALump& colorMapLump = *colorMapLumpIter;
	_colorMap = AColorMap(wadFile, colorMapLump);

    return true;
}

//=============================================================================

bool AWAD::readEndDoom(FILE* wadFile)
{
	TLumpsListConstIter endoomLumpIter = ALumpTools::findLumpIter("ENDOOM", _tableOfContents);
	if (endoomLumpIter == _tableOfContents.end())
	{
		return false;
	}
	const ALump& endoomLump = *endoomLumpIter;
	_enDoom = AEnDoom(wadFile, endoomLump);

    return true;
}

//=============================================================================

bool AWAD::readDemos(FILE* wadFile)
{
	TLumpsList demosList = ALumpTools::findLumpsList("DEMO", _tableOfContents);
	for (TLumpsListIter iter = demosList.begin(); iter != demosList.end(); iter++)
	{
		TLumpsListConstIter demoLumpIter = ALumpTools::findLumpIter(iter->lumpName, _tableOfContents);
		if (demoLumpIter == _tableOfContents.end())
		{
			continue;
		}
		const ALump& demoLump = *demoLumpIter;
		_demosList.push_back(ADemo(wadFile, demoLump));
	}

	return true;
}

//=============================================================================

bool AWAD::readFlats(FILE* wadFile)
{
    //  read second part of flats
    if (!readFlatsRange(wadFile, "F1_START", "F1_END"))
        return false;

    return true;
}

//=============================================================================

bool AWAD::readFlatsRange(FILE* wadFile, const std::string& beginLumpName, const std::string& endLumpName)
{
	TLumpsListConstIter beginLump = ALumpTools::findLumpIter(beginLumpName, _tableOfContents);
	TLumpsListConstIter endLump = ALumpTools::findLumpIter(endLumpName, _tableOfContents);
    TLumpsListIter lumpListEnd = _tableOfContents.end();
	
    if ((beginLump != lumpListEnd) && (endLump != lumpListEnd))
    {
        ++beginLump;
		for (TLumpsListConstIter iter = beginLump; iter != endLump; iter++)
		{
			ALump flatLump = (*iter);
			_flatsList.push_back(AFlat(wadFile, flatLump, _palete));
		}
    }

    return true;
}

//=============================================================================

bool AWAD::readPatches(FILE* wadFile)
{
	TLumpsListConstIter pNamesLumpIter = ALumpTools::findLumpIter("PNAMES", _tableOfContents);
	if (pNamesLumpIter == _tableOfContents.end())
	{
		return false;
	}
	
	const ALump& patchesNamesLump = *pNamesLumpIter;
	unsigned char *lumpData = new unsigned char [patchesNamesLump.lumpSize];
	ALumpTools::readLumpData(wadFile, patchesNamesLump, lumpData);
	int bytesOffset = 0;

    int patchesCount = 0;
    memcpy(&patchesCount, lumpData, 4);
    bytesOffset += 4;

	//	Read all patches lumps names
	std::list<std::string> patchesLumpsNamesList;
	int patchNameSizeInBytes = 8;
	for (int i = 0; i < patchesCount; i++)
	{
		char patchName[9] = {0};
	    memcpy(patchName, &lumpData[bytesOffset], patchNameSizeInBytes);
	    bytesOffset += patchNameSizeInBytes;
		patchesLumpsNamesList.push_back(patchName);
	}
	delete [] lumpData;

	//	Read all PATCHES pointed in list
	for (std::list<std::string>::iterator iter = patchesLumpsNamesList.begin(); iter != patchesLumpsNamesList.end(); iter++)
	{
		std::string patchLumpName = *iter;
		TLumpsListConstIter patchLumpIter = ALumpTools::findLumpIter(patchLumpName, _tableOfContents);
		if (patchLumpIter == _tableOfContents.end())
		{
			printf("NO CHANCE TO FIND <%s>\n", patchLumpName.c_str());
			continue;
		}
		const ALump& patchLump = *patchLumpIter;
		if (!patchLump.lumpSize)
		{
			continue;
		}
		lumpData = new unsigned char [patchLump.lumpSize];
		ALumpTools::readLumpData(wadFile, patchLump, lumpData);

		APicture newPatch(lumpData, patchLumpName, _palete);
		_patchesList.push_back(newPatch);

		delete [] lumpData;
	}

    return true;
}

//=============================================================================

bool AWAD::readTextures(FILE* wadFile)
{
	TLumpsListConstIter textureLumpIter = ALumpTools::findLumpIter("TEXTURE1", _tableOfContents);
	if (textureLumpIter == _tableOfContents.end())
	{
		return false;
	}
	
	const ALump& textureLump = *textureLumpIter;
	unsigned char *lumpData = new unsigned char [textureLump.lumpSize];
	ALumpTools::readLumpData(wadFile, textureLump, lumpData);
	int bytesOffset = 0;

    int texturesCount = 0;
    memcpy(&texturesCount, lumpData, 4);
	bytesOffset += 4;

	std::vector<int> texturesOffsetsList;
    for (int i = 0; i < texturesCount; i++)
    {
	    int textureOffset = 0;
		memcpy(&textureOffset, &lumpData[bytesOffset], 4);
		bytesOffset += 4;

		texturesOffsetsList.push_back(textureOffset);
    }

	for (std::vector<int>::iterator iter = texturesOffsetsList.begin(); iter != texturesOffsetsList.end(); iter++)
	{
		_texturesList.push_back(generateSingleTexture((*iter), lumpData));
	}
	
	delete [] lumpData;
	
    return true;
}

//=============================================================================

ATexture AWAD::generateSingleTexture(const int textureOffset, unsigned char *lumpData)
{
	int bytesOffset = textureOffset;
	char textureName[9] = {0};
	memcpy(textureName, &lumpData[bytesOffset], 8);
	bytesOffset += 8;
	bytesOffset += 4;	//	skiping 4 bytes
	short textureWidth = 0;
	memcpy(&textureWidth, &lumpData[bytesOffset], 2);
	bytesOffset += 2;
	short textureHeight = 0;
	memcpy(&textureHeight, &lumpData[bytesOffset], 2);
	bytesOffset += 2;
	bytesOffset += 4;	//	skiping 4 bytes
	short texturePatchNumbers = 0;
	memcpy(&texturePatchNumbers, &lumpData[bytesOffset], 2);
	bytesOffset += 2;

	TPatchesDescriptionList patchesDescriptionList;
	for (int patchIndex = 0; patchIndex < texturePatchNumbers; patchIndex++)
	{
		short xOffset = 0;
		memcpy(&xOffset, &lumpData[bytesOffset], 2);
		bytesOffset += 2;

		short yOffset = 0;
		memcpy(&yOffset, &lumpData[bytesOffset], 2);
		bytesOffset += 2;
		
		int patchIndexInPatchDirectory = 0;
		memcpy(&patchIndexInPatchDirectory, &lumpData[bytesOffset], 2);
		bytesOffset += 2;
		bytesOffset += 4;	//	skiping 4 bytes

		if ((patchIndexInPatchDirectory > _patchesList.size()) || (patchIndexInPatchDirectory < 0))
		{
			printf("\t\t\t%s can not be created because patch does not exist\n", textureName);
			continue;
		}

		SPatchDescription newDescription = {xOffset, yOffset, _patchesList[patchIndexInPatchDirectory]};
		patchesDescriptionList.push_back(newDescription);
	}
	
	ATexture newTexture(patchesDescriptionList, textureName, textureWidth, textureHeight);
	return newTexture;
}

//=============================================================================
    
ALevel AWAD::readLevel(const std::string& levelName)
{
    TLumpsListConstIter levelLumpIter = ALumpTools::findLumpIter(levelName, _tableOfContents);
    if (levelLumpIter == _tableOfContents.end())
    {
        return ALevel();
    }
    
    FILE* wadFile = 0;
    wadFile = fopen(_fileName.c_str(), "rb");
    ALevel level(wadFile, levelLumpIter, _tableOfContents, _palete);
    fclose(wadFile);

    return level;
}
    
//=============================================================================

bool AWAD::readLevel(FILE* wadFile)
{
//    TLumpsListConstIter levelLumpIter = AUtilities::findLumpIter("e1m8", _tableOfContents);
//    if (levelLumpIter == _tableOfContents.end())
//    {
//        return false;
//    }
//    
//    ALevel level(wadFile, levelLumpIter, _tableOfContents, _palete);
	
    return true;
}

//=============================================================================

};  //  namespace spcWAD
