//
//  ThemeManager.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 29/01/2017.
//
//

#include "ThemeManager.hpp"

ThemeManager::ThemeManager()
{
    themes.push_back(Theme("construction", "Construction Site", cocos2d::Color4B(104, 203, 225, 255), false));
    themes.push_back(Theme("jungle", "Jungle", cocos2d::Color4B(104, 203, 225, 255), true));
    themes.push_back(Theme("desert", "Desert", cocos2d::Color4B(227, 202, 160, 255), false));
    themes.push_back(Theme("cosmic", "Space", cocos2d::Color4B(86, 90, 97, 255), true));
    themes.push_back(Theme("western", "Western", cocos2d::Color4B(9, 219, 218, 255), true));
    themes.push_back(Theme("snowland", "Snowland", cocos2d::Color4B(9, 219, 218, 255), false));
    themes.push_back(Theme("underwater", "Underwater", cocos2d::Color4B(26, 82, 137, 255), true));
    themes.push_back(Theme("graveyard", "Graveyard", cocos2d::Color4B(191, 164, 145, 255), true));
    themes.push_back(Theme("mouth", "Mouth", cocos2d::Color4B(170, 61, 58, 255), true));
    themes.push_back(Theme("hell", "Hell", cocos2d::Color4B(209, 80, 80, 255), false));
}

ThemeManager* ThemeManager::getInstance()
{
    static ThemeManager* tm;
    if(!tm)
    {
        tm = new ThemeManager();
    }
    
    return tm;
}

Theme ThemeManager::getTheme(int id) const
{
    return themes[id];
}
