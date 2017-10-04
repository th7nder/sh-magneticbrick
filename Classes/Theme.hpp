//
//  Theme.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 29/01/2017.
//
//

#ifndef Theme_hpp
#define Theme_hpp

#include "cocos2d.h"
class Theme
{
private:
    std::string codeName;
    std::string displayName;
    std::string backgroundPath;
    std::string playButtonPath;
    std::string replayButtonPath;
    std::string thumbnailUnlockedPath;
    std::string thumbnailLockedPath;
    std::string thumbnailUnlockablePath;
    std::string thumbnailBackgroundPath;
    std::string musicPath;
    cocos2d::Color4B themeColor;
    cocos2d::Color3B uiColor;
    bool whiteElements;
    bool downloadInProgress;
public:
    Theme(const std::string& codeName, const std::string& displayName, const cocos2d::Color4B& themeColor, bool whiteElements);
    std::string getElementsColor() const
    {
        return whiteElements ? "white" : "black";
        //return "white";
    }
    
    
    
    cocos2d::Color3B getUIColor()
    {
        return uiColor;
    }
    
    Theme& operator=(Theme other)
    {
        codeName = other.codeName;
        displayName = other.displayName;
        backgroundPath = other.backgroundPath;
        playButtonPath = other.playButtonPath;
        replayButtonPath = other.replayButtonPath;
        thumbnailLockedPath = other.thumbnailLockedPath;
        thumbnailUnlockedPath = other.thumbnailUnlockedPath;
        thumbnailUnlockablePath = other.thumbnailUnlockablePath;
        thumbnailBackgroundPath = other.thumbnailBackgroundPath;
        musicPath = other.musicPath;
        themeColor = other.themeColor;
        whiteElements = other.whiteElements;
        return *this;
    }
    
    bool isWhite() const
    {
        return whiteElements;
    }
    
    std::string getBackgroundPath() const
    {
        return backgroundPath;
    }
    
    std::string getPlayButtonPath() const
    {
        return playButtonPath;
    }
    
    std::string getReplayButtonPath() const
    {
        return replayButtonPath;
    }
    
    std::string getCodeName() const
    {
        return codeName;
    }
    
    std::string getThumbnailUnlockedPath() const
    {
        return thumbnailUnlockedPath;
    }
    
    std::string getThumbnailLockedPath() const
    {
        return thumbnailLockedPath;
    }
    
    std::string getThumbnailUnlockablePath() const
    {
        return thumbnailUnlockablePath;
    }
    
    cocos2d::Color4B getThemeColor() const
    {
        return themeColor;
    }
    
    std::string getMusicPath() const
    {
        return musicPath;
    }
    
    std::string getThumbnailBackgroundPath() const
    {
        return thumbnailBackgroundPath;
    }
    
    bool isDownloadInProgress() const
    {
        return downloadInProgress;
    }
    
    void setDownloadInProgress(bool value)
    {
        downloadInProgress = value;
    }
};

#endif /* Theme_hpp */
