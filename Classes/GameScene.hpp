//
//  GameScene.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 12/03/2017.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp



#include "cocos2d.h"
#include "network/HttpClient.h"
#include "ui/UIPageView.h"
#include "ui/UIScrollView.h"
#include "Globals.hpp"

#include "TitleLayout.hpp"
#include "SettingsLayout.hpp"
#include "SelectLayout.hpp"
#include "WinLoseLayout.hpp"
#include "WaitLayout.hpp"
#include "ShopLayout.hpp"

#include "SHLevel.hpp"

#include "ThemeManager.hpp"
#include "GameHandler.hpp"

#include "Level.hpp"

#include "ui/UILoadingBar.h"


#include "PostEffectNode.h"
#include "BlurFromTo.hpp"

#include "TutorialLayout.hpp"
#include "RewardLayout.hpp"
#include "PopupLayout.hpp"
#include "KielniaLayout.hpp"

class Player;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) or (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "PluginAdColony/PluginAdColony.h"
#include "PluginIAP/PluginIAP.h"
#include "PluginAdMob/PluginAdMob.h"
#include "PluginChartboost/PluginChartboost.h"
//#include "PluginUnityAds/PluginUnityAds.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) or (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
class GameScene : public cocos2d::Scene, public  GameHandler, public sdkbox::AdColonyListener, public sdkbox::IAPListener, public sdkbox::AdMobListener, public sdkbox::ChartboostListener/*, public sdkbox::UnityAdsListener*/
#else
class GameScene : public cocos2d::Scene, public  GameHandler
#endif
{
private:
    typedef Scene super;
    typedef GameScene self;
#if defined ADS
    void onAdColonyChange(const sdkbox::AdColonyAdInfo& info, bool available) override;
    void onAdColonyReward(const sdkbox::AdColonyAdInfo& info,
                          const std::string& currencyName, int amount, bool success) override;
    void onAdColonyStarted(const sdkbox::AdColonyAdInfo& info) override;
    void onAdColonyFinished(const sdkbox::AdColonyAdInfo& info) override;
    
    virtual void onInitialized(bool ok) override;
    virtual void onSuccess(sdkbox::Product const& p) override;
    virtual void onFailure(sdkbox::Product const& p, const std::string &msg) override;
    virtual void onCanceled(sdkbox::Product const& p) override;
    virtual void onRestored(sdkbox::Product const& p) override;
    virtual void onProductRequestSuccess(std::vector<sdkbox::Product> const &products) override;
    virtual void onProductRequestFailure(const std::string &msg) override;
    void onRestoreComplete(bool ok, const std::string &msg) override;
    
    
    virtual void adViewDidReceiveAd(const std::string &name) override;
    virtual void adViewDidFailToReceiveAdWithError(const std::string &name, const std::string &msg)  override;
    virtual void adViewWillPresentScreen(const std::string &name)  override;
    virtual void adViewDidDismissScreen(const std::string &name)  override;
    virtual void adViewWillDismissScreen(const std::string &name)  override;
    virtual void adViewWillLeaveApplication(const std::string &name) override;
    virtual void reward(const std::string &name, const std::string &currency, double amount) override;
    
    virtual void onChartboostCached(const std::string& name) override;
    virtual bool onChartboostShouldDisplay(const std::string& name) override;
    virtual void onChartboostDisplay(const std::string& name) override;
    virtual void onChartboostDismiss(const std::string& name) override;
    virtual void onChartboostClose(const std::string& name) override;
    virtual void onChartboostClick(const std::string& name) override;
    virtual void onChartboostReward(const std::string& name, int reward) override;
    virtual void onChartboostFailedToLoad(const std::string& name, sdkbox::CB_LoadError e) override;
    virtual void onChartboostFailToRecordClick(const std::string& name, sdkbox::CB_ClickError e) override;
    virtual void onChartboostConfirmation() override;
    virtual void onChartboostCompleteStore() override;
   
    /*
    virtual void unityAdsDidClick(const std::string& placementId) override;
    virtual void  unityAdsPlacementStateChanged(const std::string& placementId,
                                       sdkbox::PluginUnityAds::SBUnityAdsPlacementState oldState,
                                                sdkbox::PluginUnityAds::SBUnityAdsPlacementState newState) override;
    
    virtual void unityAdsReady(const std::string& placementId) override;
    virtual void unityAdsDidError(sdkbox::PluginUnityAds::SBUnityAdsError error, const std::string& message) override;
    
    virtual void unityAdsDidStart(const std::string& placementId) override;
    virtual void unityAdsDidFinish(const std::string& placementId, sdkbox::PluginUnityAds::SBUnityAdsFinishState state) override;*/
    
#endif
    
    void onBuyChapterCompleted();
    void createBackground();
    void createLevel();
    void createUI();
    void createSettings();
    void createSelectLayout();
    void createShopLayout();
    

    cocos2d::Sprite* background;
    B2DebugDrawLayer* debugLayer;
    
    int kielniasUsedOnLevel;
    
    TitleLayout* titleLayout;
    SettingsLayout* settingsLayout;
    SelectLayout* selectLayout;
    WaitLayout* waitLayout;
    WinLoseLayout* winLoseLayout;
    ShopLayout* shopLayout;
    ui::Layout* uiContainer;
    LayerColor* popupLayer;
    PopupLayout* popupLayout;
    KielniaLayout* kielniaLayout;
    
    void createKielniaLayout();
    
    TutorialLayout* tutorialLayout;
    void createTutorialLayout();
    
    RewardLayout* rewardLayout;
    void createRewardLayout();
    
    

    Level* level;
    Level* nextLevel;
    ui::LoadingBar* levelPercentBar;
    Sprite* levelPercentSprite;
    
    Sprite* blackout;
    Sprite* gravity;
    Label* tapToPlay;

    
    Label* bricksReady;
    enum TransitionDirection
    {
        Left = 0,
        Right,
        Up,
        Down
    };
    float weights[64];
    
    void calculateGaussianWeights(const int points, float* weights);
    Size visibleSize;
    static const float transitionTime;
    static const float blurTime;
    bool inLayoutsTransition;
    void moveLayouts(ui::Layout* firstLayout, ui::Layout* secondLayout, TransitionDirection dir);
    void fadeInLayout(ui::Layout* layout);
    void fadeOutLayout(ui::Layout* layout);
    
    void createPopupLayout();

    bool currentStarCollected[3];
    
    void logEventDeath(int themeId, int levelId, int percent, int brick);
    void logEventWin(int themeId, int levelId, int brick);
    
    PostEffectNode* postEffect;
CC_CONSTRUCTOR_ACCESS:
    GameScene();
    virtual ~GameScene();
public:
    CREATE_FUNC(GameScene);
    virtual bool init() override;
    virtual void setGameState(GameState state) override;
    virtual void onPlayButtonClicked() override;
    virtual void onBackButtonClicked() override;
    virtual void onSettingsButtonClicked() override;
    virtual void onBackFromSelectSwiped() override;
    virtual void onReplayButtonClicked() override;
    virtual void onBackFromLoseClicked() override;
    virtual void onSettingsFromLoseClicked() override;
    virtual void onHomeFromLoseClicked() override;
 
    virtual void onStarCollected(int number) override;
    
    virtual void onThemeAndLevelSelected(int themeId, int levelId) override;
    virtual void onPlayerUpdate(float dt, float playerY) override;

    virtual void onFirstClick() override;
    virtual void onPlayerDeath() override;
    virtual void onPlayerWin() override;
    virtual void onPlayNextButtonClicked() override;
    
    void setStartingCameraAndBg(bool animated=false);
    
    virtual void createDebugLayer(b2World* world) override;
    virtual void onPlayerWaited(bool give) override;
    
    virtual void onShopFromWinLose() override;
    
    void onGameExit();
    void onGameEnter();
    
    
    
    virtual void hideUI() override;
    virtual void showUI() override;
    virtual void updateUI() override;
    
    virtual int getCurrentProgress() override;
    
    virtual void onShopButtonClicked() override;
    virtual void onBackFromShop() override;
    virtual void onSkinUsed() override;
    
    virtual void setBlackout(bool var) override;
    virtual void setGravity(bool var) override;
    
    virtual void onBricksMissingFromSelect() override;
    
    virtual void onLetsTryClicked() override;
    virtual void onLetsTryClickedFromLevel() override;
    virtual bool launchChapterReward(int themeId) override;
    virtual void buyChapter(int themeId) override;
    virtual void onPopupCancelled() override;
    
    virtual void onChapterRewardEnded() override;
    virtual bool launchBrickReward() override;
    virtual void onBrickRewardEnded() override;
    
    virtual void launchKielniaTimer() override;
    virtual void onNoThanksClicked() override;
    virtual void onKielniaUsed() override;
    
    virtual void setPlayerVelocities(float speed) override;
    virtual b2World* getWorld() override;
    virtual void setTutorialPlayer(Player* player) override;
    
    virtual void setPostEffectEnabled() override
    {
        postEffect->setPostEffectsEnabled(true);
    }
    
    virtual void onBackFromWait() override;

    void watcher(float dt);

};
#endif /* GameScene_hpp */
