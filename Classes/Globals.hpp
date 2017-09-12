//
//  Globals.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 11/03/2017.
//
//

#ifndef Globals_hpp
#define Globals_hpp

#include "cocos2d.h"
#include <map>

#include "ThemeManager.hpp"
#include "SkinManager.hpp"
#include "SimpleAudioEngine.h"

//#define DEBUG_LAYER 1
//#define DOWNLOAD_MAPS 1

#if (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
#define ADS 1
#endif

std::vector<std::string> explode(std::string const & s, char delim);
void playClickSound();

class Globals
{
    static bool smallPhone;
public:
    static void setSmallPhone(bool v) {smallPhone = v;}
    static bool getSmallPhone() {return smallPhone;}
    static std::unordered_map<std::string, std::string> resources;
    static std::unordered_map<std::string, std::string> initializeResources();
    static const std::string gameFont;
    static const std::string gameFontBold;
    static std::string themes;
    
    
    static const int chaptersSteps[10];
    static const int bricksSteps[16];
    
    static const int startingBricks;
    static const int startingThemeId;
    static const int startingKielnias;
    static const int startingMusicVolume;
    static const int startingSfxVolume;
    
    static const int bricksAfterWaiting;
    static const int timeToWait;
    static const float blurRadius;
    static const float backgroundSpeed;
    
    static bool iapLoaded;
};
#endif /* Globals_hpp */
