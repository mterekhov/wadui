#ifndef SPCWAD_AUTILITIES_H
#define SPCWAD_AUTILITIES_H

//=============================================================================

#include <string>

//=============================================================================

namespace spcWAD
{

//=============================================================================

/**
	Some utilities
*/
class AUtilities
{
public:
    /**
     converts booth strings to lower case and then compares on equality

     @param one first string
     @param two second string
     @return result of comparison
     */
    static bool stringCompare(const std::string& one, const std::string& two);

    /**
        Checks if substring is in the string

     @param string the string in which we are trying to find prefix
     @param substring string which should be as part of first parameter
     @return result of comparison, true if substring is in the string
     */
    static bool stringContainsSubstring(const std::string& string, const std::string& substring);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AUTILITIES_H
