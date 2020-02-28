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
     Checks if prefix string is the begining of string

     @param prefix prefix which should be the start of string
     @param string the string in which we are trying to find prefix
     @return result of comparison, true if prefix is the prefix of string and false in other cases
     */
    static bool stringContainsSubstring(const std::string& string, const std::string& substring);
};

//=============================================================================

};  //  namespace spcWAD

//=============================================================================

#endif  //  SPCWAD_AUTILITIES_H
