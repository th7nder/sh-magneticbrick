//
//  GameHandler.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 12/03/2017.
//
//

#ifndef GameHandler_hpp
#define GameHandler_hpp

#include "cocos2d.h"
#include "Globals.hpp"
#include "ThemeManager.hpp"
#include <Box2D/Box2D.h>
#include "SimpleAudioEngine.h"
#include "SkinManager.hpp"
#include "Skin.hpp"

class Player;
class GameHandler
{
    cocos2d::UserDefault* ud;
public:
    static GameHandler* instance;
    static void setInstance(GameHandler* handler)
    {
        instance = handler;
    }
    static GameHandler* sharedInstance()
    {
        return instance;
    }
    enum GameState
    {
        UI = 0,
        ReadyToPlay,
        Playing,
        Died,
        Win,
        WinAfter,
        Tutorial
    };

protected:
    GameHandler();
    int bricksRemaining;
    bool forceTouch;
    bool forceTouchAvailable;
    int lastThemeId;
    int lastLevelId;
    float currentPlayerSpeed;
    GameState currentState;
    
    int musicVolume;
    int sfxVolume;
    int previousMusicVolume;
    int previousSfxVolume;
    
    int kielnias;
    
    float playerStartY;
    float finishLineY;
    bool bulletTime;
    int starCount;
    
    CC_PROPERTY(std::string, lastAdProvider, LastAdProvider);
    CC_PROPERTY(bool, blackoutEnabled, Blackout);
    CC_PROPERTY(bool, gravity, Gravity);
    CC_PROPERTY(bool, infection, Infection);
    
    CC_PROPERTY(bool, tutorialDisplayed, TutorialDisplayed);
    
    CC_PROPERTY(bool, desertTutorial, DesertDisplayed);
    CC_PROPERTY(bool, spaceTutorial,  SpaceDisplayed);
    CC_PROPERTY(bool, westernTutorial, WesternDisplayed);
    CC_PROPERTY(bool, snowlandTutorial, SnowlandDisplayed);
    CC_PROPERTY(bool, graveyardTutorial, GraveyardDisplayed);
    CC_PROPERTY(bool, mouthTutorial, MouthDisplayed);
    
    CC_PROPERTY(bool, removeAds, RemoveAds);


    std::string themePrices[10];
public:
    std::string getThemePrice(int themeId) const
    {
        return themePrices[themeId];
    }
    
    void setThemePrice(int themeId, std::string value)
    {
        themePrices[themeId] = value;
    }
    int getStarsAt(int themeId, int levelId);
    bool brickAtStepUnlocked(int step);
    void setBrickAtStepUnlocked(int step);
    int getStarCount();
    bool isBulletTime()
    {
        return bulletTime;
    }
    
    void setBulletTime(bool bullet)
    {
        bulletTime = bullet;
    }
    void setPlayerStartY(float y)
    {
        playerStartY = y;
    }
    
    void setFinishLineY(float y)
    {
        finishLineY = y;
    }
    bool getForceTouch();
    void setForceTouch(bool enabled);
    
    bool getForceTouchAvailable();
    void setForceTouchAvailable(bool enabled);
    
    int getMusicVolume();
    void setMusicVolume(int percent);
    
    int getSfxVolume();
    void setSfxVolume(int percent);
    
    int getPreviousMusicVolume();
    void setPreviousMusicVolume(int percent);
    
    int getPreviousSfxVolume();
    void setPreviousSfxVolume(int percent);
    
    int getBricksRemaining();
    void setBricksRemaining(int value);
    
    int getLastThemeId();
    void setLastThemeId(int value);
    Theme getLastTheme() const;
    
    int getLastLevelId()
    {
        return lastLevelId;
    }
    
    void setLastLevelId(int levelId)
    {
        lastLevelId = levelId;
    }
    
    void setCurrentPlayerSpeed(float speed)
    {
        this->currentPlayerSpeed = speed;
    }
    
    float getCurrentPlayerSpeed()
    {
        return currentPlayerSpeed;
    }
    
    virtual b2World* getWorld() = 0;
    
    int getKielnias();
    void setKielnias(int value);
    
    int getLastAvailableChapter();

    
    bool isLevelAvailable(int theme, int level);
    int getLevelProgress(int theme, int level);
    void setLevelProgress(int theme, int level, int progress);
    
    bool isThemeAvailable(int theme);
    void setThemeAvailable(int theme);
    
    virtual void onPlayButtonClicked() = 0;
    virtual void onBackButtonClicked() = 0;
    virtual void onSettingsButtonClicked() = 0;
    virtual void onBackFromSelectSwiped() = 0;
    virtual void hideUI() = 0;
    virtual void updateUI() = 0;
    virtual void showUI() = 0;
    
    virtual void onReplayButtonClicked() = 0;
    virtual void onBackFromLoseClicked() = 0;
    virtual void onSettingsFromLoseClicked() = 0;
    virtual void onHomeFromLoseClicked() = 0;
    virtual void onPlayerWaited(bool give) = 0;
    
    virtual void onShopButtonClicked() = 0;
    virtual void onBackFromShop() = 0;
    virtual void onShopFromWinLose() = 0;
    
    
    virtual void onStarCollected(int number) = 0;
    
    
    virtual void onPlayNextButtonClicked() = 0;
    
    
    virtual void onThemeAndLevelSelected(int themeId, int levelId) = 0;
    
    virtual void onPlayerUpdate(float dt, float playerY) = 0;
    virtual void onPlayerDeath() = 0;
    virtual void onPlayerWin() = 0;
    
    virtual int getCurrentProgress() = 0;
    
    void saveStar(int number);
    bool getStar(int number);
    bool getStar(int themeId, int levelId, int number);

    virtual void setGameState(GameState state)
    {
        currentState = state;
    }
    
    GameState getGameState()
    {
        return currentState;
    }
    
    virtual void createDebugLayer(b2World* world) = 0;
    
    
    virtual ~GameHandler();
    
    virtual void onSkinUsed() = 0;
    
    virtual void onBricksMissingFromSelect() = 0;
    
    
    CC_PROPERTY(int, currentSkinId, CurrentSkinId);
    virtual Skin getCurrentSkin() const;
    
    
    virtual void onLetsTryClicked() = 0;
    
    virtual void onLetsTryClickedFromLevel() = 0;
    virtual bool launchChapterReward(int themeId) = 0;
    virtual void buyChapter(int themeId) = 0;
    virtual void onPopupCancelled() = 0;
    virtual void onChapterRewardEnded() = 0;
    virtual bool launchBrickReward() = 0;
    virtual void onBrickRewardEnded() = 0;
    
    virtual Theme getTheme(int themeId);
    virtual void launchKielniaTimer() = 0;
    virtual void onNoThanksClicked() = 0;
    virtual void onKielniaUsed() = 0;
    
    virtual void setPlayerVelocities(float speed) = 0;
    virtual void setTutorialPlayer(Player* player) = 0;
    
    virtual void setPostEffectEnabled() = 0;
    
    virtual void onBackFromWait() = 0;
    
    
};

#endif /* GameHandler_hpp */
