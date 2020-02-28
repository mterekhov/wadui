#include <sstream>

#include "alumptools.h"
#include "autilities.h"
#include "aflat.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

std::vector<std::string> ALumpTools::mapLumpsNames()
{
    return {
        "THINGS",
        "LINEDEFS",
        "SIDEDEFS",
        "VERTEXES",
        "SSECTORS",
        "NODES",
        "SECTORS",
        "REJECT",
        "BLOCKMAP",
        "SEGS",
    };

}
    
//=============================================================================

std::vector<std::string> ALumpTools::doom1MapLumpsNames()
{
    std::vector<std::string> list = ALumpTools::mapLumpsNames();
    for (int episode = 1; episode < 5; episode++)
    {
        for (int level = 1; level < 10; level++)
        {
            std::stringstream stream;
            stream << "E" << episode << "M" << level;
            list.push_back(stream.str());
        }
    }
    
    return list;
}

//=============================================================================
    
SLumpDescription ALumpTools::lumpDescription(const std::string& lumpName)
{
    if (AUtilities::stringCompare(lumpName, "PLAYPAL"))
    {
        return {"Palette for images", LUMPTYPE_PALETTE};
    }
    
    if (AUtilities::stringCompare(lumpName, "COLORMAP"))
    {
        return {"Map of colors for different brightness", LUMPTYPE_COLOR_MAP};
    }
    
    if (AUtilities::stringCompare(lumpName, "ENDDOOM"))
    {
        return {"Message for DOS when you are exit", LUMPTYPE_ENCODED_TEXT};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "DEMO"))
    {
        return {"DEMO record which can be played by engine", LUMPTYPE_DEMO};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "DP"))
    {
        return {"PC speaker sound effects", LUMPTYPE_SOUND};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "ds"))
    {
        return {"Digital sound effects", LUMPTYPE_SOUND};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "d_"))
    {
        return {"Music in MUS format", LUMPTYPE_SOUND};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "genmidi"))
    {
        return {"The General MIDI standard instruments", LUMPTYPE_SOUND};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "DMXGUS"))
    {
        return {"Instrument patch mappings on the Gravis Ultra-Sound soundcard", LUMPTYPE_SOUND};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "ST"))
    {
        return {"Status-bar image", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "WI"))
    {
        return {"Image between levels", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "M_"))
    {
        return {"Image for main menu", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "HELP1"))
    {
        return {"Ad-screen says Register!, with some screen shots.", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "HELP2"))
    {
        return {"Actual help, all the controls explained.", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "TITLEPIC"))
    {
        return {"Maybe this is the title screen? Gee, I dunno...", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "INTERPIC"))
    {
        return {"Maybe this is the title screen? Gee, I dunno...", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "CREDIT"))
    {
        return {"People at id Software who created this great game.", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "VICTORY2"))
    {
        return {"Screen shown after a victorious end to episode 2.", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "PFUB1"))
    {
        return {"A nice little rabbit minding his own peas and queues...", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "PFUB2"))
    {
        return {"...a hint of what's waiting in Doom 2.", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "END"))
    {
        return {"big red THE END gets shot up", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "AMMNUM"))
    {
        return {"Small grey digits for ammo count (15/200 etc)", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "BRDR_"))
    {
        return {"Tiny pictures used as a border between a less-than-full screen view and the outside marbleized zone. TL is top left, BR bottom right, you can guess the rest", LUMPTYPE_PICTURE};
    }
    
    return {"unknown", LUMPTYPE_UNKNOWN};
}
    
//=============================================================================
    
TLumpsList ALumpTools::findLumpsList(const std::string& lumpsNameMask, const TLumpsList& lumpsList)
{
    TLumpsList founded;
    for (TLumpsListConstIter iter = lumpsList.begin(); iter != lumpsList.end(); iter++)
    {
        if (AUtilities::stringContainsSubstring(lumpsNameMask, iter->lumpName))
        {
            founded.push_back(*iter);
        }
    }
    
    return founded;
}

//=============================================================================

TLumpsListConstIter ALumpTools::findLumpIter(const std::string& lumpNameToFind, const TLumpsList& lumpsList)
{
    for (TLumpsListConstIter iter = lumpsList.begin(); iter != lumpsList.end(); iter++)
    {
        if (AUtilities::stringCompare(iter->lumpName, lumpNameToFind))
        {
            return iter;
        }
    }
    
    return lumpsList.end();
}

//=============================================================================

const AFlat& ALumpTools::findFlat(const std::string& flatNameToFind, const TFlatsList& flatList)
{
    for (TFlatsListConstIter iter = flatList.begin(); iter != flatList.end(); iter++)
    {
        if (!strncmp(iter->flatName().c_str(), flatNameToFind.c_str(), iter->flatName().length()))
        {
            return (*iter);
        }
    }
    
    return *flatList.end();
}

//=============================================================================

bool ALumpTools::readLumpData(FILE* wadFile, const ALump& lumpToRead, unsigned char *lumpData)
{
    if (fseek(wadFile, lumpToRead.lumpOffset, SEEK_SET))
    {
        return false;
    }
    
    memset(lumpData, 0, lumpToRead.lumpSize);
    int read = fread(lumpData, lumpToRead.lumpSize, 1, wadFile);
    if (read != 1)
    {
        return false;
    }
    
    return true;
}

//=============================================================================

};  //  namespace spcWAD
