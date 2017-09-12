//
//  Skin.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 12/06/2017.
//
//

#ifndef Skin_hpp
#define Skin_hpp

#include "cocos2d.h"

class Skin
{
    CC_PROPERTY_READONLY(std::string, displayName, DisplayName);
    CC_PROPERTY_READONLY(std::string, codeName, CodeName);
    CC_PROPERTY_READONLY(std::string, leftPath, LeftPath);
    CC_PROPERTY_READONLY(std::string, rightPath, RightPath);
    CC_PROPERTY_READONLY(std::string, iconPath, IconPath);
    std::string key;
    CC_PROPERTY(bool, access, Access);
    CC_PROPERTY_READONLY(int, id, Id);
public:
    Skin();
    Skin(int id, const std::string& display, const std::string& code);
    virtual ~Skin();
};

#endif /* Skin_hpp */
