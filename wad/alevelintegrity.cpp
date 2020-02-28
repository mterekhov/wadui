#include "alevelintegrity.h"
#include "autilities.h"
#include "alumptools.h"

//=============================================================================

namespace spcWAD
{
    
//=============================================================================

ALevelIntegrity::ALevelIntegrity()
{
    _completeIntegrity = calculateCompleteIntegrity();
}

//=============================================================================

ALevelIntegrity::~ALevelIntegrity()
{
    
}

//=============================================================================

bool ALevelIntegrity::checkIntegrity(const int integrityToCheck)
{
    return (integrityToCheck == _completeIntegrity);
}

//=============================================================================
    
int ALevelIntegrity::calculateCompleteIntegrity()
{
    int shifter = 1;
    std::vector<std::string> LevelIntegrityLumps = ALumpTools::mapLumpsNames();
    std::vector<std::string>::iterator integrityItem = LevelIntegrityLumps.begin();
    integrityItem++;
    for (;integrityItem != LevelIntegrityLumps.end(); integrityItem++)
    {
        shifter |= shifter << 1;
    }
    
    return shifter;
}

//=============================================================================

int ALevelIntegrity::integrityEnum(const std::string& integrityString)
{
    int shifter = 1;
    std::vector<std::string> LevelIntegrityLumps = ALumpTools::mapLumpsNames();
    for (std::vector<std::string>::iterator integrityItem = LevelIntegrityLumps.begin(); integrityItem != LevelIntegrityLumps.end(); integrityItem++)
    {
        if (AUtilities::stringCompare(integrityString, *integrityItem))
        {
            return shifter;
        }
        shifter = shifter << 1;
    }
    
    return 0;
}

//=============================================================================

int ALevelIntegrity::appendIntegrity(int currentIntegrity, const std::string& levelLumpName)
{
    int lumpIntegrity = integrityEnum(levelLumpName);
    
    if (currentIntegrity == 0)
    {
        return lumpIntegrity;
    }
    
    return lumpIntegrity | currentIntegrity;
}

//=============================================================================

};  //  namespace spcWAD
