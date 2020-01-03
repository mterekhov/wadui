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
    
std::string ALumpTools::lumpDescription(const std::string& lumpName)
{
    std::string description = "about";
    
    if (AUtilities::stringCompare(lumpName, "PLAYPAL"))
    {
        description = "Palette for images";
    }
    
    if (AUtilities::stringCompare(lumpName, "COLORMAP"))
    {
        description = "Map of colors for different brightness";
    }
    
    if (AUtilities::stringCompare(lumpName, "ENDDOOM"))
    {
        description = "Message for DOS when you are exit";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "DEMO"))
    {
        description = "DEMO record which can be played by engine";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "DP"))
    {
        description = "PC speaker sound effects";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "ds"))
    {
        description = "Digital sound effects";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "d_"))
    {
        description = "Music in MUS format";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "genmidi"))
    {
        description = "The General MIDI standard instruments";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "DMXGUS"))
    {
        description = "Instrument patch mappings on the Gravis Ultra-Sound soundcard";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "ST"))
    {
        description = "Status-bar image";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "WI"))
    {
        description = "Image between levels";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "M_"))
    {
        description = "Image for main menu";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "HELP1"))
    {
        description = "Ad-screen says Register!, with some screen shots.";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "HELP2"))
    {
        description = "Actual help, all the controls explained.";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "TITLEPIC"))
    {
        description = "Maybe this is the title screen? Gee, I dunno...";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "INTERPIC"))
    {
        description = "Maybe this is the title screen? Gee, I dunno...";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "CREDIT"))
    {
        description = "People at id Software who created this great game.";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "VICTORY2"))
    {
        description = "Screen shown after a victorious end to episode 2.";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "PFUB1"))
    {
        description = "A nice little rabbit minding his own peas and queues...";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "PFUB2"))
    {
        description = "...a hint of what's waiting in Doom 2.";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "END"))
    {
        description = "big red THE END gets shot up";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "AMMNUM"))
    {
        description = "Small grey digits for ammo count (15/200 etc)";
    }
    
    if (AUtilities::stringPrefixCompare2(lumpName, "BRDR_"))
    {
        description = "Tiny pictures used as a border between a less-than-full screen view and the outside marbleized zone. TL is top left, BR bottom right, you can guess the rest";
    }
    
    return description;
}
    
//=============================================================================
    
};  //  namespace spcWAD
