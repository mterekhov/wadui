//
//  glod.cpp
//  game
//
//  Created by Michael Terekhov on 11.01.2022.
//

#include "alod.h"
#include "aloditem.h"
#include <list>

namespace spcWAD {

void ALod::readSprite(const std::string& lodFileName, const ALodItem& lodItem) {
    FILE *lodFile = fopen(lodFileName.c_str(), "rb");
    
    fseek(lodFile, lodItem.offset, SEEK_SET);
    unsigned char *lodItemData = new unsigned char[lodItem.size];
    fread(lodItemData, lodItem.size, 1, lodFile);
    fclose(lodFile);
    
    int spriteWidth = 0;
    int spriteHeight = 0;
    int bytesOffset = 0;
    char filename[16] = {0};
    memcpy(filename, lodItemData, 16);
    FILE* tgaFile = fopen(filename, "wb");
    fwrite(&lodItemData[16], lodItem.size - 16, 1, tgaFile);
    fclose(tgaFile);

    delete [] lodItemData;
}

std::list<ALodItem> ALod::extractItems(const std::string& lodFileName) {
    std::list<ALodItem> lodItemsList;

    FILE *lodFile = fopen(lodFileName.c_str(), "rb");
    if (!checkSignature(lodFile)) {
        printf("GaneshaEngine: wrong LOD file format\n");
        return lodItemsList;
    }
    
    fseek(lodFile, 256, SEEK_SET);
    
    int headerSize = 32;
    unsigned char *chunkData = new unsigned char [headerSize];
    memset(chunkData, 0, headerSize);
    fread(chunkData, headerSize, 1, lodFile);
    
    int bytesOffset = 16;
    int tableOfContentOffset = 0;
    memcpy(&tableOfContentOffset, &chunkData[bytesOffset], 4);
    bytesOffset += 4;
    int sizeOfAllFilesInLOD = 0;
    memcpy(&sizeOfAllFilesInLOD, &chunkData[bytesOffset], 4);
    bytesOffset += 8;
    int numberOfFilesInLOD = 0;
    memcpy(&numberOfFilesInLOD, &chunkData[bytesOffset], 4);
    
    int lodItemSize = 32;
    for (int i = 0; i < numberOfFilesInLOD; i++) {
        fread(chunkData, lodItemSize, 1, lodFile);
        
        char itemName[16] = {0};
        memcpy(itemName, chunkData, 16);
        ALodItem newItem;
        newItem.name = itemName;
        std::transform(newItem.name.begin(), newItem.name.end(), newItem.name.begin(), tolower);
        memcpy(&newItem.offset, &chunkData[16], 4);
        newItem.offset += tableOfContentOffset;
        memcpy(&newItem.size, &chunkData[20], 4);
        
        lodItemsList.push_back(newItem);
        printf(">> %i. %s\n", i + 1, newItem.name.c_str());
    }
    
    fclose(lodFile);

    return lodItemsList;
}

bool ALod::checkSignature(FILE* lodFile) {
    char magic[16] = {0};
    size_t read = fread(magic, 1, sizeof(magic), lodFile);
    if (read != 16)
        return false;

    if (strncmp(magic, "LOD", 3)) {
        return false;
    }

    if (strncmp(magic + 4, "MMVI", 3)) {
        return false;
    }

    return true;
}

};
