#include "autilities.h"
#include "aflat.h"

//=============================================================================

namespace spcWAD
{

//=============================================================================

bool AUtilities::stringCompare(const std::string& one, const std::string& two)
{
    if (one.length() != two.length()) {
        return false;
    }
    
	std::string oneCase;
	oneCase.resize(one.size());
	std::transform(one.begin(),
				   one.end(),
				   oneCase.begin(),
				   ::tolower);

	std::string twoCase;
	twoCase.resize(two.size());
	std::transform(two.begin(),
				   two.end(),
				   twoCase.begin(),
				   ::tolower);
	if (!oneCase.compare(twoCase))
	{
		return true;
	}
	
	return false;
}

//=============================================================================

bool AUtilities::stringContainsSubstring(const std::string& string, const std::string& substring)
{
    if (substring.length() > string.length())
    {
        return false;
    }
    
	std::string substringCase;
	substringCase.resize(substring.size());
	std::transform(substring.begin(),
				   substring.end(),
				   substringCase.begin(),
				   ::tolower);

	std::string stringCase;
	stringCase.resize(string.size());
	std::transform(string.begin(),
				   string.end(),
				   stringCase.begin(),
				   ::tolower);

    if (stringCase.find(substringCase) != std::string::npos)
	{
		return true;
	}

	return false;
}

//=============================================================================

};  //  namespace spcWAD
