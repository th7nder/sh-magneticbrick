//
//  GameHandler.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 12/03/2017.
//
//

#include "GameHandler.hpp"
USING_NS_CC;
#include "Player.hpp"

GameHandler::GameHandler() : bricksRemaining(0), lastThemeId(0), currentPlayerSpeed(0.0), currentState(UI), lastLevelId(0), kielnias(0), musicVolume(0), sfxVolume(0), bulletTime(false), gravity(false), infection(false), blackoutEnabled(false), finishLineY(-1)
{
    ud = UserDefault::getInstance();
    bricksRemaining = ud->getIntegerForKey("bricksRemaining", Globals::startingBricks);
    lastThemeId = ud->getIntegerForKey("lastTheme", Globals::startingThemeId);
    kielnias = ud->getIntegerForKey("kielnias", Globals::startingKielnias);
    musicVolume = ud->getIntegerForKey("musicVolume", Globals::startingMusicVolume);
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    sae->setBackgroundMusicVolume((float)musicVolume / 100.0f);
    sfxVolume = ud->getIntegerForKey("sfxVolume", Globals::startingSfxVolume);
    sae->setEffectsVolume((float)sfxVolume / 100.0f);
    previousMusicVolume = ud->getIntegerForKey("previousMusicVolume", 0);
    previousSfxVolume = ud->getIntegerForKey("previousSfxVolume", 0);
    forceTouch = ud->getBoolForKey("forceTouch", true);
    forceTouchAvailable = ud->getBoolForKey("forceTouchAvailable", true);
    
    currentSkinId = ud->getIntegerForKey("currentSkin", 0);
    starCount = ud->getIntegerForKey("starCount", 0);
    tutorialDisplayed = ud->getBoolForKey("tutorialDisplayed", false);
    
    desertTutorial = ud->getBoolForKey("desertDisplayed", false);
    spaceTutorial = ud->getBoolForKey("spaceDisplayed", false);
    westernTutorial = ud->getBoolForKey("westernDisplayed", false);
    snowlandTutorial = ud->getBoolForKey("snowlandDisplayed", false);
    graveyardTutorial = ud->getBoolForKey("graveyardDisplayed", false);
    mouthTutorial = ud->getBoolForKey("mouthDisplayed", false);
    removeAds = ud->getBoolForKey("removeAds", false);
    ud->setBoolForKey("brick_atstep0", true);
    lastAdProvider = ud->getStringForKey("lastAdProvider", "AdMob");
    
    auto skins = SkinManager::getInstance()->getSkins();
    skins[0].setAccess(true);

    
    for(int i = 0; i < 10; i++)
    {
        themePrices[i] = "$2.99";
    }
    
    if(!ud->getBoolForKey("resetted699", false))
    {
        ud->setBoolForKey("resetted699", true);
        setRemoveAds(false);
        setKielnias(Globals::startingKielnias);
        bricksRemaining = Globals::startingBricks;
        ud->setIntegerForKey("bricksRemaining", bricksRemaining);
        for(int i = 1; i < 16; i++)
        {
            ud->setBoolForKey(StringUtils::format("brick_atstep%d", i).c_str(), false);
        }
        setMusicVolume(Globals::startingMusicVolume);
        setSfxVolume(Globals::startingSfxVolume);
        setLastThemeId(0);
        setTutorialDisplayed(false);
        setCurrentSkinId(0);
        setCurrentSkinId(0);
        ud->setIntegerForKey("starCount", 0);
        starCount = 0;
        setDesertDisplayed(false);
        setSpaceDisplayed(false);
        setWesternDisplayed(false);
        setSnowlandDisplayed(false);
        setGraveyardDisplayed(false);
        setMouthDisplayed(false);
        
        
        for(int k = 0; k < 10; k++)
        {
            ud->setBoolForKey(StringUtils::format("theme_available_%d", k).c_str(), false);
            for(int i = 1; i <= 6; i++)
            {
                setLevelProgress(k, i, 0);
                for(int j = 1; j <= 3; j++)
                {
                    ud->setBoolForKey(StringUtils::format("level_star_%d%d_%d", k, i, j).c_str(), false);
                }
            }
        }
        

        for(int i = 1; i < 15; i++)
        {
            skins[i].setAccess(false);
        }
    }

    
}

GameHandler::~GameHandler()
{
    
}


int GameHandler::getLastAvailableChapter()
{
    auto themes = ThemeManager::getInstance()->getThemes();
    for(int i = 0; i < 10; i++)
    {
        if(!isThemeAvailable(i))
        {
            return i - 1;
        }
    }
    
    return -1;
}

bool GameHandler::getRemoveAds() const
{
    return removeAds;
}

void GameHandler::setRemoveAds(bool v)
{
    removeAds = v;
    ud->setBoolForKey("removeAds", v);
}


bool GameHandler::getTutorialDisplayed() const
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return true;
#endif
    
    return tutorialDisplayed;
}

void GameHandler::setTutorialDisplayed(bool v)
{
    tutorialDisplayed = v;
    ud->setBoolForKey("tutorialDisplayed", v);
}

bool GameHandler::getDesertDisplayed() const
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return true;
#endif
    

    return desertTutorial;
}

void GameHandler::setDesertDisplayed(bool v)
{
    desertTutorial = v;
    ud->setBoolForKey("desertDisplayed", v);
}


bool GameHandler::getSpaceDisplayed() const
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return true;
#endif
    return spaceTutorial;
}

void GameHandler::setSpaceDisplayed(bool v)
{
    spaceTutorial = v;
    ud->setBoolForKey("spaceDisplayed", v);
}


bool GameHandler::getWesternDisplayed() const
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return true;
#endif
    return westernTutorial;
}

void GameHandler::setWesternDisplayed(bool v)
{
    westernTutorial = v;
    ud->setBoolForKey("westernDisplayed", v);
}


bool GameHandler::getSnowlandDisplayed() const
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return true;
#endif
    return snowlandTutorial;
}

void GameHandler::setSnowlandDisplayed(bool v)
{
    snowlandTutorial = v;
    ud->setBoolForKey("snowlandDisplayed", v);
}

bool GameHandler::getGraveyardDisplayed() const
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return true;
#endif
    
   return graveyardTutorial;
}

void GameHandler::setGraveyardDisplayed(bool v)
{
    graveyardTutorial = v;
    ud->setBoolForKey("graveyardDisplayed", v);
}


bool GameHandler::getMouthDisplayed() const
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    return true;
#endif
#if defined DOWNLOAD_MAPS
    return true;
#endif
    return mouthTutorial;
}

void GameHandler::setMouthDisplayed(bool v)
{
    mouthTutorial = v;
    ud->setBoolForKey("mouthDisplayed", v);
}








int GameHandler::getStarCount()
{
    return starCount;
}

int GameHandler::getCurrentSkinId() const
{
    return currentSkinId;
}

void GameHandler::setCurrentSkinId(int var)
{
    currentSkinId = var;
    ud->setIntegerForKey("currentSkin", var);

}

Skin GameHandler::getCurrentSkin() const
{
    return SkinManager::getInstance()->getSkin(currentSkinId);
}


void GameHandler::setBricksRemaining(int value)
{
    bricksRemaining = value;
    UserDefault::getInstance()->setIntegerForKey("bricksRemaining", value);
}

int GameHandler::getBricksRemaining()
{
    return bricksRemaining;
}

int GameHandler::getLastThemeId()
{
    return lastThemeId;
}


void GameHandler::setLastThemeId(int value)
{
    lastThemeId = value;
    UserDefault::getInstance()->setIntegerForKey("lastTheme", value);
}

Theme GameHandler::getLastTheme() const
{
    return ThemeManager::getInstance()->getTheme(lastThemeId);
}


int GameHandler::getKielnias()
{
    return kielnias;
}

void GameHandler::setKielnias(int value)
{
    kielnias = value;
    UserDefault::getInstance()->setIntegerForKey("kielnias", value);
}

int GameHandler::getSfxVolume()
{
    return sfxVolume;
}

int GameHandler::getMusicVolume()
{
    return musicVolume;
}

bool GameHandler::getInfection() const
{
    return infection;
}

void GameHandler::setInfection(bool var)
{
    infection = var;
}
void GameHandler::setSfxVolume(int percent)
{
    sfxVolume = percent;
    UserDefault::getInstance()->setIntegerForKey("sfxVolume", percent);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume((float)percent / 100.0f);
}

void GameHandler::setMusicVolume(int percent)
{
    musicVolume = percent;
    UserDefault::getInstance()->setIntegerForKey("musicVolume", percent);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((float)percent / 100.0f);
}

int GameHandler::getPreviousSfxVolume()
{
    return previousSfxVolume;
}

int GameHandler::getPreviousMusicVolume()
{
    return previousMusicVolume;
}

void GameHandler::setPreviousSfxVolume(int percent)
{
    previousSfxVolume = percent;
    UserDefault::getInstance()->setIntegerForKey("previuosSfxVolume", percent);
}

void GameHandler::setPreviousMusicVolume(int percent)
{
    previousMusicVolume = percent;
    UserDefault::getInstance()->setIntegerForKey("previousMusicVolume", percent);
}


bool GameHandler::getForceTouch()
{
    return forceTouch;
}

void GameHandler::setForceTouch(bool enabled)
{
    forceTouch = enabled;
    UserDefault::getInstance()->setBoolForKey("forceTouch", forceTouch);
}



bool GameHandler::getForceTouchAvailable()
{
    return forceTouchAvailable;
}

void GameHandler::setForceTouchAvailable(bool enabled)
{
    forceTouchAvailable = enabled;
    UserDefault::getInstance()->setBoolForKey("forceTouchAvailable", forceTouchAvailable);
}




bool GameHandler::isThemeAvailable(int theme)
{
    if(theme == 0) return true;

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
 //   return true;
//#endif
   
#if defined DOWNLOAD_MAPS
    return true;
#else
    

    
    return ud->getBoolForKey(StringUtils::format("theme_available_%d", theme).c_str(), false);
#endif
}


void GameHandler::setThemeAvailable(int theme)
{
    ud->setBoolForKey(StringUtils::format("theme_available_%d", theme).c_str(), true);
}

bool GameHandler::isLevelAvailable(int theme, int level)
{
    if(level == 1 && theme == 0) return true;
    
    if(isThemeAvailable(theme)) return true;
    
    return false;
    
}

void GameHandler::setLevelProgress(int theme, int level, int progress)
{
    auto ud = UserDefault::getInstance();
    ud->setIntegerForKey(StringUtils::format("level_progress%d%d", theme, level).c_str(), progress);
}

int GameHandler::getLevelProgress(int theme, int level)
{
    auto ud = UserDefault::getInstance();
    return ud->getIntegerForKey(StringUtils::format("level_progress%d%d", theme, level).c_str(), 0);
}

void GameHandler::saveStar(int number)
{
    auto ud = UserDefault::getInstance();
    starCount++;
    ud->setIntegerForKey("starCount", starCount);
    ud->setBoolForKey(StringUtils::format("level_star_%d%d_%d", lastThemeId, lastLevelId, number).c_str(), true);
}

bool GameHandler::getStar(int number)
{
    return ud->getBoolForKey(StringUtils::format("level_star_%d%d_%d", lastThemeId, lastLevelId, number).c_str(), false);
}

bool GameHandler::getStar(int themeId, int levelId, int number)
{
    return ud->getBoolForKey(StringUtils::format("level_star_%d%d_%d", themeId, levelId, number).c_str(), false);
}

int GameHandler::getStarsAt(int themeId, int levelId)
{
    int count = 0;
    for(int i = 1; i <= 3; i++)
    {
        if(getStar(themeId, levelId, i))
        {
            count++;
        }
    }
    
    return count;
}


std::string GameHandler::getLastAdProvider() const
{
    return lastAdProvider;
}

void GameHandler::setLastAdProvider(std::string var)
{
    lastAdProvider = var;
    ud->setStringForKey("lastAdProvider", var);
}

bool GameHandler::getBlackout() const
{
    return blackoutEnabled;
}

void GameHandler::setBlackout(bool var)
{
    blackoutEnabled = var;
}

bool GameHandler::getGravity() const
{
    return gravity;
}

void GameHandler::setGravity(bool var)
{
    gravity = var;
}


Theme GameHandler::getTheme(int themeId)
{
    return ThemeManager::getInstance()->getTheme(themeId);
}

void GameHandler::setBrickAtStepUnlocked(int step)
{
    ud->setBoolForKey(StringUtils::format("brick_atstep%d", step).c_str(), true);
}

bool GameHandler::brickAtStepUnlocked(int step)
{
    return ud->getBoolForKey(StringUtils::format("brick_atstep%d", step).c_str(), false);
}
