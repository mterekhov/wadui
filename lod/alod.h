//
//  glod.hpp
//  game
//
//  Created by Michael Terekhov on 11.01.2022.
//

#ifndef SPCWAD_ALOD_H
#define SPCWAD_ALOD_H

#include <string>
#include <list>
#include <stdio.h>
#include "aloditem.h"

namespace spcWAD {

class ALod {
public:
    std::list<ALodItem> extractItems(const std::string& lodFileName);
    void readSprite(const std::string& lodFileName, const ALodItem& lodItem);

private:
    bool checkSignature(FILE* lodFile);
};

};   //  namespace spcWAD

#endif  //  SPCWAD_ALOD_H
