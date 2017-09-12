//
//  Theme.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 29/01/2017.
//
//

#include "Theme.hpp"

Theme::Theme(const std::string& codeName, const std::string& displayName, const cocos2d::Color4B& color, bool whiteElements) :
codeName(codeName), displayName(displayName), themeColor(color), whiteElements(whiteElements)
{
    backgroundPath = "themes/" + codeName + "/background.png";
    playButtonPath = "themes/" + codeName + "/play_button.png";
    replayButtonPath = "themes/" + codeName + "/replay_button.png";
    thumbnailUnlockedPath = "themes/" + codeName + "/thumbnail-unlocked.png";
    thumbnailLockedPath = "themes/" + codeName + "/thumbnail-locked.png";
    thumbnailUnlockablePath = "themes/" + codeName + "/thumbnail-unlockable.png";
    thumbnailBackgroundPath = "themes/" + codeName + "/thumbnail-background.png";
    musicPath = "sound/music/" + codeName + ".mp3";
    
    if(whiteElements)
    {
        uiColor = cocos2d::Color3B(255, 255, 255);
    }
    else
    {
        uiColor = cocos2d::Color3B(0, 0, 0);
    }
}
