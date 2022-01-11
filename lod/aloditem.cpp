//
//  gloditem.cpp
//  game
//
//  Created by Michael Terekhov on 12.01.2022.
//

#include "aloditem.h"

namespace spcWAD {

ALodItem::ALodItem(const std::string &itemName, const int itemSize, const int itemOffset, const int itemHZ, const int itemNum) : name(itemName), size(itemSize), offset(itemOffset), hz(itemHZ), num(itemNum) {
    
}

ALodItem::ALodItem() : name("unknown"), size(0), offset(0), hz(0), num(0) {
    
}

ALodItem::~ALodItem() {
    
}

}
