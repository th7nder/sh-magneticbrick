//
//  Skin.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 12/06/2017.
//
//

#include "Skin.hpp"
USING_NS_CC;
Skin::Skin()
{
    
}
Skin::Skin(int skinId, const std::string& display, const std::string& code) : displayName(display), codeName(code), id(skinId)
{
    leftPath = "player/" + codeName + "/left.png";
    rightPath = "player/" + codeName + "/right.png";
    iconPath = "player/" + codeName + "/icon.png";
    key = "skin_" + codeName;
    
    access = UserDefault::getInstance()->getBoolForKey(key.c_str(), false);
}

Skin::~Skin()
{
    
}

int Skin::getId() const
{
    return id;
}




std::string Skin::getDisplayName() const
{
    return displayName;
}

std::string Skin::getCodeName() const
{
    return codeName;
}

std::string Skin::getLeftPath() const
{
    return leftPath;
}


std::string Skin::getRightPath() const
{
    return rightPath;
}

std::string Skin::getIconPath() const
{
    return iconPath;
}

bool Skin::getAccess() const
{
    return UserDefault::getInstance()->getBoolForKey(key.c_str(), false);
}

void Skin::setAccess(bool acc)
{
    UserDefault::getInstance()->setBoolForKey(key.c_str(), acc);
    access = acc;
}
