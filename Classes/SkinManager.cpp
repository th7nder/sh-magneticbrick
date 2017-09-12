//
//  SkinManager.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 12/06/2017.
//
//

#include "SkinManager.hpp"

SkinManager::SkinManager()
{
    skins.push_back(Skin(0, "Default", "default"));
    skins.push_back(Skin(1, "Game Cube", "gamecube"));
    skins.push_back(Skin(2, "Basket", "basket"));
    skins.push_back(Skin(3, "Checked", "checked"));
    skins.push_back(Skin(4, "Donut", "donut"));
    skins.push_back(Skin(5, "Eyes", "eyes"));
    skins.push_back(Skin(6, "Gold", "gold"));
    skins.push_back(Skin(7, "Honeycomb", "honeycomb"));
    skins.push_back(Skin(8, "Neon", "neon"));
    skins.push_back(Skin(9, "Piniata", "piniata"));
    skins.push_back(Skin(10, "Rainbow", "rainbow"));
    skins.push_back(Skin(11, "Rasta", "rasta"));
    skins.push_back(Skin(12, "Shell", "shell"));
    skins.push_back(Skin(13, "Silver", "silver"));
    skins.push_back(Skin(14, "Skull", "skull"));


    
    /*for(int i = 1; i < 15; i++)
    {
        skins[i].setAccess(false);
    }*/
}


SkinManager::~SkinManager()
{
    
}



SkinManager* SkinManager::getInstance()
{
    static SkinManager* sm;
    if(!sm)
    {
        sm = new SkinManager();
    }
    return sm;
}

Skin SkinManager::getSkin(int id)
{
    return skins[id];
}

std::vector<Skin>& SkinManager::getSkins()
{
    return skins;
}
