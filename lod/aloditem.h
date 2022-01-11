//
//  gloditem.hpp
//  game
//
//  Created by Michael Terekhov on 12.01.2022.
//

#ifndef SPCWAD_ALODITEM_H
#define SPCWAD_ALODITEM_H

#include <string>
#include <stdio.h>

namespace spcWAD {

class ALodItem {
public:

    std::string name;
    int offset;
    int size;
    int hz;
    int num;
    
    ALodItem(const std::string &itemName, const int itemSize, const int itemOffset, const int itemHZ, const int itemNum);
    ALodItem(FILE *lodFile);
    ALodItem();
    ~ALodItem();
};

};   //  namespace spcWAD

#endif  //  SPCWAD_ALODITEM_H
