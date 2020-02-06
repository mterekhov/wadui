#include <sstream>

#include "alumptools.h"
#include "autilities.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

std::list<std::string> ALumpTools::doom1MapLumpsNames()
{
    std::list<std::string> list = {"THINGS", "LINEDEFS", "SIDEDEFS", "VERTEXES", "SEGS", "SSECTORS", "NODES", "SECTORS", "REJECT", "BLOCKMAP"};
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
    SLumpDescription description = {"unknown", LUMPTYPE_UNKNOWN};

    if (AUtilities::stringCompare(lumpName, "PLAYPAL"))
    {
        description = {"Palette for images", LUMPTYPE_PALETTE};
    }
    
    if (AUtilities::stringCompare(lumpName, "COLORMAP"))
    {
        description = {"Map of colors for different brightness", LUMPTYPE_COLOR_MAP};
    }
    
    if (AUtilities::stringCompare(lumpName, "ENDDOOM"))
    {
        description = {"Message for DOS when you are exit", LUMPTYPE_ENCODED_TEXT};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "DEMO"))
    {
        description = {"DEMO record which can be played by engine", LUMPTYPE_DEMO};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "DP"))
    {
        description = {"PC speaker sound effects", LUMPTYPE_SOUND};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "ds"))
    {
        description = {"Digital sound effects", LUMPTYPE_SOUND};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "d_"))
    {
        description = {"Music in MUS format", LUMPTYPE_SOUND};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "genmidi"))
    {
        description = {"The General MIDI standard instruments", LUMPTYPE_SOUND};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "DMXGUS"))
    {
        description = {"Instrument patch mappings on the Gravis Ultra-Sound soundcard", LUMPTYPE_SOUND};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "ST"))
    {
        description = {"Status-bar image", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "WI"))
    {
        description = {"Image between levels", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "M_"))
    {
        description = {"Image for main menu", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "HELP1"))
    {
        description = {"Ad-screen says Register!, with some screen shots.", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "HELP2"))
    {
        description = {"Actual help, all the controls explained.", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "TITLEPIC"))
    {
        description = {"Maybe this is the title screen? Gee, I dunno...", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "INTERPIC"))
    {
        description = {"Maybe this is the title screen? Gee, I dunno...", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "CREDIT"))
    {
        description = {"People at id Software who created this great game.", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "VICTORY2"))
    {
        description = {"Screen shown after a victorious end to episode 2.", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "PFUB1"))
    {
        description = {"A nice little rabbit minding his own peas and queues...", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "PFUB2"))
    {
        description = {"...a hint of what's waiting in Doom 2.", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "END"))
    {
        description = {"big red THE END gets shot up", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "AMMNUM"))
    {
        description = {"Small grey digits for ammo count (15/200 etc)", LUMPTYPE_PICTURE};
    }
    
    if (AUtilities::stringContainsSubstring(lumpName, "BRDR_"))
    {
        description = {"Tiny pictures used as a border between a less-than-full screen view and the outside marbleized zone. TL is top left, BR bottom right, you can guess the rest", LUMPTYPE_PICTURE};
    }
    
    return description;
}
    
//=============================================================================
    
};  //  namespace spcWAD
