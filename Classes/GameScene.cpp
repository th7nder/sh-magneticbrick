//
//  GameScene.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 12/03/2017.
//
//

#include "GameScene.hpp"
#include "TH7Bridge.hpp"
#include "ui/UIScale9Sprite.h"

USING_NS_CC;

const float GameScene::transitionTime = 0.3;
const float GameScene::blurTime = 0.3;



GameScene::GameScene() : GameHandler(), background(nullptr),
titleLayout(nullptr),
settingsLayout(nullptr),
selectLayout(nullptr),
waitLayout(nullptr),
winLoseLayout(nullptr),
shopLayout(nullptr),
downloader(nullptr),
level(nullptr), uiContainer(nullptr), levelPercentBar(nullptr), inLayoutsTransition(false), visibleSize(Vec2::ZERO), popupLayout(nullptr), nextLevel(nullptr), tutorialLayout(nullptr), debugLayer(nullptr),
kielniasUsedOnLevel(0),
adColonyReceived(false)
{
    for(int i = 0; i < 10; i++)
    {
        downloadInProgress[i] = false;
    }
}

GameScene::~GameScene()
{
    delete downloader;
}

int nb_nodes, nb_visible_nodes, nb_rgba_nodes, nb_not_letters_nodes,
nb_not_letters_visible_nodes, nb_low_opacity_nodes, levelObjects;

void DEBUGCountNodes(Node *n, bool parent_visible, bool is_letter )
{
    nb_nodes++;
    bool we_are_visible = n->isVisible() && parent_visible;
    bool father_is_label = is_letter;
    bool we_are_label = is_letter || (dynamic_cast<Label*>(n) != nullptr);
    
    if( we_are_visible )
    {
        nb_visible_nodes++;
        CCLOG("%s %s", n->getDescription().c_str(), n->getName().c_str());
    }

    if( we_are_visible && !father_is_label )
        nb_not_letters_visible_nodes++;
    if( !father_is_label )
        nb_not_letters_nodes++;
    
    if(n->getDescription() == "LevelObject")
    {
        levelObjects++;
    }
    
    if(n->isCascadeOpacityEnabled())
    {
        // count low opacity nodes (if below 10/255)
        if(n->getOpacity() < 10 && we_are_visible )
            nb_low_opacity_nodes++;
        nb_rgba_nodes++;
    }

    // recursive part
    auto children = n->getChildren();
    if(n->isVisible() && children.size())
    {
        for( unsigned int i = 0; i < children.size(); i++ )
        {
            DEBUGCountNodes(children.at(i),
                            we_are_visible, we_are_label );
        }
    }
}

// initial function to call, usually with the initial node of your sprite
// hierarchy (mine is called _main_node)
std::string DEBUGCocosNodes(Node *start )
{
    nb_nodes = nb_visible_nodes = nb_rgba_nodes = nb_not_letters_nodes =
    nb_not_letters_visible_nodes = nb_low_opacity_nodes = levelObjects = 0;
    DEBUGCountNodes( start, true, false );
    char str[256];
    sprintf(str, "All:%d/%d NoTxt:%d/%d LowOp:%d LevelObjects: %d", nb_visible_nodes, nb_nodes,
            nb_not_letters_visible_nodes, nb_not_letters_nodes, nb_low_opacity_nodes, levelObjects);
    return str;
}

bool GameScene::init()
{
    if(!super::init()) return false;
    
    auto themes = ThemeManager::getInstance()->getThemes();
    int i = 1;
    auto fu = cocos2d::FileUtils::getInstance();
    std::string writablePath = fu->getWritablePath();
    
    
    for(const auto& theme: themes)
    {
        
        auto codename = theme.getCodeName();
        if(i > 1)
        {
            Globals::resources["music_" + codename] = writablePath + codename + ".mp3";
            CCLOG("h3h3h3h3 %s", Globals::resources["music_" + codename].c_str());
        }
        else
        {
            Globals::resources["music_" + codename] = "sound/music/" + codename + ".mp3";
        }
    }
    
    setForceTouchAvailable(TH7Bridge::forceTouchAvailable());
    if(!TH7Bridge::forceTouchAvailable())
    {
        setForceTouch(false);
    }

    
    visibleSize = Director::getInstance()->getVisibleSize();
    createBackground();
    createLevel();
    createUI();
    
    
    createPopupLayout();
    
    
    CCLOG("forceTouch available TH7: %d", TH7Bridge::forceTouchAvailable());
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) or (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    sdkbox::PluginAdColony::setListener(this);
    sdkbox::IAP::setListener(this);
    sdkbox::PluginAdMob::setListener(this);
    sdkbox::PluginChartboost::setListener(this);
    
    sdkbox::PluginAdColony::init();
    sdkbox::PluginAdMob::init();
    sdkbox::PluginChartboost::init();


    
    // to do wyjebac to calkowicie
    
    /*sdkbox::PluginUnityAds::setListener(this);
    sdkbox::PluginUnityAds::init();*/
    
    initDownloader();
#endif
    
    schedule(schedule_selector(GameScene::watcher), 3.0, kRepeatForever, 3.0);
    
    
    //CCLOG("%s", TextureCache::getInstance()->getCachedTextureInfo().c_str());
    //CCTextureCache::sharedTextureCache()->dumpCachedTextureplayInfo();
    
    

    auto func = CallFunc::create([this]{
        const auto codename = getLastTheme().getCodeName();
        auto path = Globals::resources["music_" + codename];
        auto fu = FileUtils::getInstance();
        if(fu->isFileExist(path))
        {
            auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
            sae->playBackgroundMusic(path.c_str(), true);
        }
    });
    
    auto seq = Sequence::create(DelayTime::create(0.5), func, NULL);
    runAction(seq);

    return true;
}

void GameScene::initDownloader()
{
    downloader = new (std::nothrow) network::Downloader();
    downloader->onTaskProgress = ([] (const network::DownloadTask& task, int64_t bytesReceived, int64_t totalBytesReceived, int64_t totalBytesExpected) {
        CCLOG("Downloader Progress: %d, %d", totalBytesReceived, totalBytesExpected);
    });
    
    downloader->onFileTaskSuccess = ([this] (const network::DownloadTask& task) {
        //file downloaded, do what you need next
        std::string sId = task.identifier;
        int id = atoi(sId.c_str());
        downloadInProgress[id] = false;
    });
    
    downloader->onTaskError = ([this] (const network::DownloadTask& task, int errorCode, int errorCodeInternal, const std::string& errorStr) {
        //file downloading error
        std::string sId = task.identifier;
        int id = atoi(sId.c_str());
        downloadInProgress[id] = false;
    });
}

void GameScene::downloadMusicForTheme(std::string codename, int id)
{
    std::string url = "http://fraj.eu/" + codename + ".mp3";
    std::string filePath = FileUtils::getInstance()->getWritablePath() + codename + ".mp3";
    
    downloader->createDownloadFileTask(url, filePath, StringUtils::format("%d", id));
}

void GameScene::downloadMissingMusic()
{
    CCLOG("Downloader: connected to WiFi | Starting");
    auto fu = FileUtils::getInstance();
    auto themes = ThemeManager::getInstance()->getThemes();
    int i = 0;
    for(auto& theme: themes)
    {
        if(isThemeAvailable(i))
        {
            auto codename = theme.getCodeName();
            if(!fu->isFileExist(Globals::resources["music_" + codename]))
            {
                if(!downloadInProgress[i])
                {
                    CCLOG("Downloader: need to download: %s", Globals::resources["music_" + codename].c_str());
                    downloadInProgress[i] = true;
                    downloadMusicForTheme(theme.getCodeName(), i);
                }
                else
                {
                    CCLOG("Downloader: download in progress");
                }
                
            }
        }
        
        
        i++;
    }
}

void GameScene::watcher(float dt)
{
#if defined ADS
    if(TH7Bridge::isInternetAvailable())
    {
        if(!Globals::iapLoaded)
        {
            sdkbox::IAP::init();
        }
        
        if(getLastAdProvider() == "AdColony" && !sdkbox::PluginAdMob::isAvailable("mb_video"))
        {
            sdkbox::PluginAdMob::cache("mb_video");
        }
        
        if(getLastAdProvider() == "AdMob" && !sdkbox::PluginChartboost::isAvailable("Video"))
        {
            sdkbox::PluginChartboost::cache("Video");
        }
        
        if(TH7Bridge::isConnectedToWifi())
        {
            downloadMissingMusic();
        }
    }
#endif
}


void GameScene::calculateGaussianWeights(const int points, float* weights)
{
    float dx = 1.0f/float(points-1);
    float sigma = 1.0f/3.0f;
    float norm = 1.0f/(sqrtf(2.0f*M_PI)*sigma*points);
    float divsigma2 = 0.5f/(sigma*sigma);
    weights[0] = 1.0f;
    for (int i = 1; i < points; i++)
    {
        float x = float(i)*dx;
        weights[i] = norm*expf(-x*x*divsigma2);
        weights[0] -= 2.0f*weights[i];
    }
}

void GameScene::createBackground()
{

   // calculateGaussianWeights(64, weights);
    
    postEffect = PostEffectNode::create();
    postEffect->setName("Post Effect");
    postEffect->setContentSize(visibleSize);

#define OPT_DIVIDER 8
    cocos2d::Vector<GLProgramState *>passes;
   {
        GLProgram *program = GLProgram::createWithFilenames("res/shader1.vsh", "res/blur13.fsh");
        program->link();
        program->updateUniforms();
        GLProgramState *state = GLProgramState::create(program);
        state->setUniformFloat("resolution", visibleSize.width / OPT_DIVIDER);
        state->setUniformVec2("dir", Vec2(1, 0));
        state->setUniformFloat("radius", Globals::blurRadius / 1.5f);
        passes.pushBack(state);
    }
    {
        GLProgram *program = GLProgram::createWithFilenames("res/shader1.vsh", "res/blur13.fsh");
        program->link();
        program->updateUniforms();
        GLProgramState *state = GLProgramState::create(program);
        state->setUniformFloat("resolution", visibleSize.height / OPT_DIVIDER);
        state->setUniformVec2("dir", Vec2(0, 1));
        state->setUniformFloat("radius", Globals::blurRadius / 1.5f);
        passes.pushBack(state);
    }
    {
        GLProgram *program = GLProgram::createWithFilenames("res/shader1.vsh", "res/blur13.fsh");
        program->link();
        program->updateUniforms();
        GLProgramState *state = GLProgramState::create(program);
        state->setUniformFloat("resolution", visibleSize.width / OPT_DIVIDER);
        state->setUniformVec2("dir", Vec2(1, 0));
        state->setUniformFloat("radius", Globals::blurRadius);
        passes.pushBack(state);
    }
    {
        GLProgram *program = GLProgram::createWithFilenames("res/shader1.vsh", "res/blur13.fsh");
        program->link();
        program->updateUniforms();
        GLProgramState *state = GLProgramState::create(program);
        state->setUniformFloat("resolution", visibleSize.height / OPT_DIVIDER);
        state->setUniformVec2("dir", Vec2(0, 1));
        state->setUniformFloat("radius", Globals::blurRadius);
        passes.pushBack(state);
    }


    
    postEffect->setShaderPasses(passes);
    postEffect->setAnchorPoint(Point::ZERO);
    postEffect->setPostEffectsEnabled(true);
    postEffect->setStaticDrawing(false);
    addChild(postEffect);
    
    
    
    
    
    background = Sprite::create(getLastTheme().getBackgroundPath());
    //background = Sprite::createWithSpriteFrameName(getLastTheme().getBackgroundPath());
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setName("Background");
    postEffect->addChild(background);
}

DrawNode* GameScene::createStarBarStencilDown(float delta)
{
    DrawNode* stencil = DrawNode::create();
    stencil->setAnchorPoint(Vec2::ZERO);
    //CCLOG("%f", clippingNode->getContentSize().width);
    
    stencil->drawTriangle(Vec2(-15 + delta, -25), Vec2(15 + delta, -25), Vec2(0 + delta, 25), Color4F::MAGENTA);
    
    return stencil;
}

DrawNode* GameScene::createStarBarStencilUp(float delta)
{
    DrawNode* stencil = DrawNode::create();
    stencil->setAnchorPoint(Vec2::ZERO);
    stencil->drawTriangle(Vec2(0 + delta, -25), Vec2(16.8 + delta, 9), Vec2(-16.8 + delta, 9), Color4F::MAGENTA);
    //stencil->drawTriangle(Vec2(-15 + delta, -25), Vec2(15 + delta, -25), Vec2(0 + delta, 25), Color4F::MAGENTA);

    return stencil;
}

void GameScene::createStarBar(float y, bool collected, int starId)
{
    float wholeDistance = finishLineY - playerStartY; // not so sure;
    float curr = finishLineY - y;
    float percent = (1.0f - (curr / wholeDistance));
    float delta = -300 + (percent) * 600;
    
    auto sprite = Sprite::create(Globals::resources[collected ? "barstar_full" : "barstar_empty"]);
    sprite->setColor(Color3B(255, 215, 0));
    sprite->setPosition(Vec2((visibleSize.width / 2) + delta, visibleSize.height - 46));
    sprite->setTag(starId);
    starBarContainer->addChild(sprite);
    
    stencilContainer->addChild(createStarBarStencilUp(delta));
    stencilContainer->addChild(createStarBarStencilDown(delta));

}

void GameScene::addStarBar(float y, bool collected, int starId)
{
    if(y > finishLineY)
    {
        StarBarInfo i = {y, collected, starId};
        starBarQueue.push_back(i);
    }
    else
    {
        createStarBar(y, collected, starId);
    }
}

void GameScene::setFinishLineY(float y)
{
    finishLineY = y;
    
    if(y > 0)
    {
        for(const auto& sb : starBarQueue)
        {
            createStarBar(sb.y, sb.filled, sb.starId);
        }
        
        starBarQueue.clear();
    }
    else
    {

        removeChildByTag(2044);
        removeChildByTag(2044);
        removeChildByTag(2044); // cocos2dx sugggzzzz
        starBarContainer->removeAllChildren();
        stencilContainer->removeAllChildren();
    }

}

void GameScene::createLevel()
{
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    level = Level::create(this);
    postEffect->addChild(level);
    levelPercentBar = ui::LoadingBar::create(Globals::resources["icon_progressbar_filled_white"]);
    levelPercentBar->setPosition(Vec2::ZERO);
    //levelPercentBar->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));
    levelPercentBar->setPercent(0);
    levelPercentBar->setName("Level Percent Bar");
    //addChild(levelPercentBar);
    
    
    levelPercentSprite = Sprite::create(Globals::resources["icon_progressbar_stroke_white"]);
    //levelPercentSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));
    levelPercentSprite->setPosition(Vec2::ZERO);
    levelPercentSprite->setName("Level Percent Sprite");
    //addChild(levelPercentSprite);
    

 
    
    
    auto clippingNode = ClippingNode::create();
    clippingNode->setContentSize(levelPercentSprite->getContentSize());
    clippingNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));

    stencilContainer = Node::create();
    
    starBarContainer = Node::create();
    starBarContainer->setVisible(false);
    addChild(starBarContainer, 1999);
    
    
    clippingNode->setStencil(stencilContainer);
    clippingNode->setInverted(true);
    
    addChild(clippingNode);
    clippingNode->addChild(levelPercentSprite);
    clippingNode->addChild(levelPercentBar);
    
    


    
    levelPercentSprite->setVisible(false);
    levelPercentBar->setVisible(false);
    
    tapToPlay = Label::createWithTTF("TAP TO PLAY!", Globals::gameFontBold, 51.0);
    tapToPlay->setPosition(Vec2(320, 852));
    tapToPlay->setOpacity(0);
    tapToPlay->setVisible(true);
    tapToPlay->setName("Tap To Play");
    
    
   
    
    bricksReady = Label::createWithTTF("BRICKS READY!", Globals::gameFontBold, 51.0);
    bricksReady->setPosition(Vec2(320, 568));
    bricksReady->setName("Bricks Ready");
    bricksReady->setVisible(false);
    bricksReady->setColor(Color3B(199,57,60));
    addChild(bricksReady, 1000);
    
    auto seq = Sequence::create(TintTo::create(0.25, 255, 255, 100), TintTo::create(0.25, 25, 255, 255), TintTo::create(0.25, 255, 50, 255), NULL);
    auto action = RepeatForever::create(seq);
    tapToPlay->runAction(action);
    addChild(tapToPlay);
    
    
    blackout = Sprite::create(Globals::resources["obstacle_blackout"]);
    blackout->setName("Blackout");
    blackout->setAnchorPoint(Vec2::ZERO);
    blackout->setVisible(false);
    blackout->setCascadeOpacityEnabled(true);
    addChild(blackout);
    
    
    gravity = Sprite::create(Globals::resources["obstacle_blackout"]);
    gravity->setAnchorPoint(Vec2::ZERO);
    gravity->setName("Gravity");
    gravity->setVisible(false);
    addChild(gravity);
    
    
}

void GameScene::setBlackout(bool var)
{
    GameHandler::setBlackout(var);
    

    if(var)
    {
        blackout->setOpacity(0);
        blackout->runAction(Sequence::create(FadeIn::create(0.05), DelayTime::create(0.1), FadeOut::create(0.04),
                                             FadeIn::create(0.05), DelayTime::create(0.15), FadeOut::create(0.07),
                                             FadeIn::create(0.05), DelayTime::create(0.12), FadeOut::create(0.03),
                                             FadeIn::create(0.05), DelayTime::create(0.16), FadeOut::create(0.06),
                                             FadeIn::create(0.05), DelayTime::create(0.20), FadeOut::create(0.08),
                                             
                                             FadeIn::create(0.1), NULL));
        blackout->setVisible(var);
    }
    else
    {
        blackout->runAction(FadeOut::create(0.5));
    }
}

void GameScene::setGravity(bool var)
{
    GameHandler::setGravity(var);
}

void GameScene::createUI()
{
    uiContainer = ui::Layout::create();
    uiContainer->setName("UI Container");
    addChild(uiContainer);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto lastTheme = getLastTheme();
    currentUIColor = lastTheme.isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0);
  
    const bool removeAds = getRemoveAds();
    const int bricksRemaining = getBricksRemaining();
    const std::string playButton = lastTheme.getPlayButtonPath();
    
    titleLayout = TitleLayout::createWithSize(visibleSize, this, currentUIColor, removeAds, bricksRemaining, playButton);
    titleLayout->setEnabled(true);
    titleLayout->setTouchEnabled(true);
    titleLayout->setVisible(true);
    uiContainer->addChild(titleLayout);
    
    
    winLoseLayout = WinLoseLayout::createWithSize(visibleSize, this);
    winLoseLayout->setPositionX(-visibleSize.width * 2);
    winLoseLayout->setEnabled(false);
    winLoseLayout->setTouchEnabled(true);
    winLoseLayout->setCascadeOpacityEnabled(true);
    winLoseLayout->setVisible(false);
    uiContainer->addChild(winLoseLayout);
    
    createSettings();
    createTutorialLayout();
    
    waitLayout = WaitLayout::createWithSize(visibleSize, this);
    waitLayout->setVisible(false);
    waitLayout->setCascadeOpacityEnabled(true);
    //waitLayout->setColor(currentUIColor);
    uiContainer->addChild(waitLayout);
    
    createShopLayout();
    createSelectLayout();
    
    createRewardLayout();
    
    createKielniaLayout();
    

}


void GameScene::createKielniaLayout()
{
    kielniaLayout = KielniaLayout::createWithSize(visibleSize, currentUIColor, getKielnias(), this);
    kielniaLayout->setCascadeOpacityEnabled(true);
    kielniaLayout->setVisible(false);
    kielniaLayout->setEnabled(true);
    uiContainer->addChild(kielniaLayout);
}
void GameScene::createTutorialLayout()
{
    tutorialLayout = TutorialLayout::createWithSize(visibleSize, this);
    tutorialLayout->setVisible(false);
    tutorialLayout->setCascadeOpacityEnabled(true);
    addChild(tutorialLayout);
}

void GameScene::createRewardLayout()
{
    rewardLayout = RewardLayout::createWithSize(visibleSize, this);
    rewardLayout->setCascadeOpacityEnabled(true);
    rewardLayout->setVisible(false);
    rewardLayout->setEnabled(false);
    uiContainer->addChild(rewardLayout);
}

void GameScene::createSettings()
{
    settingsLayout = SettingsLayout::createWithSize(visibleSize, this);
    settingsLayout->setColor(currentUIColor);
    settingsLayout->setPositionX(visibleSize.width);
    settingsLayout->setVisible(false);
    settingsLayout->setEnabled(false);
    settingsLayout->setTouchEnabled(true);
    settingsLayout->setBackTarget(titleLayout);
    uiContainer->addChild(settingsLayout);
    

}

void GameScene::createShopLayout()
{
    shopLayout = ShopLayout::createWithSize(visibleSize, this);
    shopLayout->setPositionX(-visibleSize.width);
    shopLayout->setVisible(false);
    shopLayout->setEnabled(false);
    shopLayout->setTouchEnabled(true);
    shopLayout->setBackTarget(titleLayout);
    uiContainer->addChild(shopLayout);
}

void GameScene::createSelectLayout()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    selectLayout = SelectLayout::createWithSize(visibleSize, this);
    selectLayout->setPositionY(-visibleSize.height);
    selectLayout->setEnabled(false);
    selectLayout->setVisible(false);
    selectLayout->setCascadeOpacityEnabled(true);
    uiContainer->addChild(selectLayout);
}


void GameScene::createPopupLayout()
{
    popupLayer = LayerColor::create(Color4B(0, 0, 0, 128), visibleSize.width, visibleSize.height);
    popupLayer->setVisible(false);
    addChild(popupLayer);
    
    
    popupLayout = PopupLayout::createWithSize(visibleSize, this);
    popupLayout->setCascadeOpacityEnabled(true);
    popupLayer->addChild(popupLayout);
    

}


// TO DO
void GameScene::onPlayerUpdate(float dt, float playerY)
{
    if(getGameState() == WinAfter) return;
    auto pos = level->getPositionY() - (getCurrentPlayerSpeed() * dt);
    if(playerY == -466)
    {
       level->setPositionY(pos);
    }

#if defined DEBUG_LAYER
    debugLayer->setPositionY(pos);
#endif
    float wholeDistance = finishLineY - playerStartY;
    float curr = finishLineY - playerY;
    float percent = (1.0f - (curr / wholeDistance)) * 100.0f;
    levelPercentBar->setPercent(percent);
}

// TO DO
void GameScene::onThemeAndLevelSelected(int themeId, int levelId)
{
    bricksReady->setVisible(false);
    selectLayout->setEnabled(false);
    postEffect->setPostEffectsEnabled(true);
    int currentThemeId = getLastThemeId();
    setLastThemeId(themeId);
    setLastLevelId(levelId);
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    const auto codename = getLastTheme().getCodeName();
    if(themeId != currentThemeId || !sae->isBackgroundMusicPlaying())
    {
        if(sae->isBackgroundMusicPlaying())
        {
            sae->stopBackgroundMusic();
        }

        // to do if file exists
        auto path = Globals::resources["music_" + codename];
        auto fu = FileUtils::getInstance();
        if(fu->isFileExist(path))
        {
            sae->playBackgroundMusic(path.c_str(), true);
        }
    }
    
    for(int i =0; i < 3; i++)
    {
        currentStarCollected[i] = false;
    }
    kielniasUsedOnLevel = 0;
    

    if(!getRemoveAds())
    {
        setBricksRemaining(getBricksRemaining() - 1);
    }


    updateUI();
    setStartingCameraAndBg();
    setGameState(ReadyToPlay);
    

    
    level->load(themeId, levelId);
    

    
    tutorialLayout->setVisible(true);
    tutorialLayout->setOpacity(255);
    tutorialLayout->setEnabled(true);
    setGameState(Tutorial);
    level->setStopped(true);
    if(!getTutorialDisplayed())
    {
        level->setStopped(false);
        tutorialLayout->displayControl();
    }
    else if(codename == "desert" && !getDesertDisplayed())
    {
        setDesertDisplayed(true);
        tutorialLayout->displayDesert();
    }
    else if(codename == "cosmic" && !getSpaceDisplayed())
    {
        setSpaceDisplayed(true);
        tutorialLayout->displaySpace();
    }
    else if(codename == "western" && !getWesternDisplayed())
    {
        setWesternDisplayed(true);
        tutorialLayout->displayWestern();
    }
    else if(codename == "snowland" && !getSnowlandDisplayed())
    {
        setSnowlandDisplayed(true);
        tutorialLayout->displaySnowland();
    }
    else if(codename == "graveyard" && !getGraveyardDisplayed())
    {
        setGraveyardDisplayed(true);
        tutorialLayout->displayGraveyard();
    }
    else if(codename == "mouth" && !getMouthDisplayed())
    {
        setMouthDisplayed(true);
        tutorialLayout->displayMouth();
    }
    else
    {
        level->setStopped(false);
        tutorialLayout->setVisible(false);
        setGameState(ReadyToPlay);
        postEffect->setPostEffectsEnabled(false);
        tapToPlay->runAction(FadeTo::create(0.3, 255));
    }
    
}


void GameScene::onPlayerDeath()
{
    if(getGameState() == Died)
        return;
    
    

    kielniaLayout->setEnabled(false);
    kielniaLayout->setVisible(false);
    
    logEventDeath(getLastThemeId(), getLastLevelId(), getCurrentProgress(), getCurrentSkinId());
    
    if(getCurrentProgress() > getLevelProgress(getLastThemeId(), getLastLevelId()))
    {
        setLevelProgress(getLastThemeId(), getLastLevelId(), getCurrentProgress());
    }
    

    setGameState(Died);
    winLoseLayout->updateUI();
    
    selectLayout->updateLevel(getLastThemeId(), getLastLevelId());
    showUI();
    
    shopLayout->updateUI();
    
    
    
    
    postEffect->setPostEffectsEnabled(true);
    postEffect->runAction(BlurFromTo::create(blurTime, 0.0, Globals::blurRadius));
    
    if(getKielnias() > 0 && kielniasUsedOnLevel + 1 <= 2)
    {
        fadeInLayout(kielniaLayout);
        kielniaLayout->launchTimer();
    }
    else
    {
        setFinishLineY(-1.0);
        fadeInLayout(winLoseLayout);
        blackout->setVisible(false);
    }

}


void GameScene::onPlayerWin()
{
    setFinishLineY(-1.0f);
    setGameState(Win);
    logEventWin(getLastThemeId(), getLastLevelId(), getCurrentProgress());

    int collectedStars = 0;
    for(int i = 0; i < 3; i++)
    {
        if(currentStarCollected[i])
        {
            saveStar(i + 1);
            collectedStars++;
        }
    }
    winLoseLayout->updateUI();
    showUI();
    
    setBlackout(false);
    
    
    postEffect->setPostEffectsEnabled(true);
    postEffect->runAction(BlurFromTo::create(blurTime, 0.0, Globals::blurRadius));

    
    
    setLevelProgress(getLastThemeId(), getLastLevelId(), 100);
    selectLayout->updateLevel(getLastThemeId(), getLastLevelId());
    
    shopLayout->updateUI();

    /*if(getLastLevelId() == 6)
    {
        setThemeAvailable(getLastThemeId() + 1);
        selectLayout->updateTheme(getLastThemeId() + 1);
        selectLayout->updateLevel(getLastThemeId() + 1, 1);
    } else {
        selectLayout->updateLevel(getLastThemeId(), getLastLevelId() + 1);
    }*/
    


    
   /* auto seq = Sequence::create(DelayTime::create(6.0), CallFunc::create([this](){
        if(this->getGameState() == Win)
        {
            this->setGameState(WinAfter);
        }
    }), nullptr);
    seq->setTag(1666);
    runAction(seq);*/
    level->player->getSprite()->runAction(MoveBy::create(6.0, Vec2(0, 6.0 * level->player->speed)));
    level->player->getRightSprite()->runAction(MoveBy::create(6.0, Vec2(0, 6.0 * level->player->speed)));
    
    
    int starsCount = getStarCount();
    auto themes = ThemeManager::getInstance()->getThemes();
    for(int i = 0; i < themes.size(); i++)
    {
        if(!isThemeAvailable(i) && starsCount >= Globals::chaptersSteps[i])
        {
            setThemeAvailable(i);
            selectLayout->updateTheme(i);
            if(i + 1 < themes.size())
            {
                selectLayout->updateTheme(i + 1);
            }
            for(int j = 1; j <= 6; j++)
            {
                selectLayout->updateLevel(i, j);
            }
            launchChapterReward(i);
            return;
        }
    }
    


    

    for(int i = 1; i < 16; i++)
    {
        if(starsCount >= Globals::bricksSteps[i] && !brickAtStepUnlocked(i))
        {
            setBrickAtStepUnlocked(i);
            launchBrickReward();
            return;
        }
    }
    
    int lastDifference = 999;
    int currDiff = 0;
    int themeRewardInfo = 0;
    for(int i = 1; i < themes.size(); i++)
    {
        currDiff = Globals::chaptersSteps[i] - starsCount;
        if(currDiff > 0 && currDiff < lastDifference && !isThemeAvailable(i))
        {
            lastDifference = currDiff;
            themeRewardInfo = i;
        }
    }
    
    
    CCLOG("info about theme: %s", themes[themeRewardInfo].getCodeName().c_str());
    
    int stepInfo = 666;
    for(int i = 15; i >= 0; i--)
    {
        if(!brickAtStepUnlocked(i))
        {
            stepInfo = i;
        }
    }
    
    if(themeRewardInfo != 0 && stepInfo != 666)
    {
        winLoseLayout->createRewardPopup(Globals::resources["thumbnail_" + themes[themeRewardInfo].getCodeName() + "_unlockable"], starsCount - collectedStars, starsCount, Globals::bricksSteps[stepInfo], true, 1);
        winLoseLayout->createRewardPopup(Globals::resources["reward_guess"], starsCount - collectedStars, starsCount, Globals::bricksSteps[stepInfo], false, 2);
    }
    else if(themeRewardInfo != 0)
    {
        winLoseLayout->createRewardPopup(Globals::resources["thumbnail_" + themes[themeRewardInfo].getCodeName() + "_unlockable"], starsCount - collectedStars, starsCount, Globals::chaptersSteps[themeRewardInfo], true, 0);
    }
    else if(stepInfo != 666)
    {
        winLoseLayout->createRewardPopup(Globals::resources["reward_guess"], starsCount - collectedStars, starsCount, Globals::bricksSteps[stepInfo], false, 0);
    }
    
    
    
    
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    sae->playEffect(Globals::resources["effect_lvlcompleted"].c_str());
    
    
    
    
    winLoseLayout->setEnabled(false);
    winLoseLayout->setVisible(true);
    winLoseLayout->setOpacity(0);
    winLoseLayout->setPosition(Vec2::ZERO);
    auto func = CallFunc::create([this]()
                                 {
                                     winLoseLayout->setEnabled(true);
                                 });
    
    auto seq = Sequence::create(FadeIn::create(transitionTime), func, NULL);
    winLoseLayout->runAction(seq);
}


void GameScene::onPlayerWaited(bool give)
{
    waitLayout->stopTimers();
    if(give)
    {
        setBricksRemaining(getBricksRemaining() + Globals::bricksAfterWaiting);
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    if(!give)
    {
        setBricksRemaining(getBricksRemaining() + Globals::bricksAfterWaiting);
    }
#endif
    
    const int remainingBricks = getBricksRemaining();
    winLoseLayout->updateUI();
    titleLayout->updateRemainingBricks(getRemoveAds(), remainingBricks);
    
    
    if(waitLayout->isVisible())
    {
        fadeInLayout(waitLayout->getBackTarget());
        fadeOutLayout(waitLayout);
    }
    else
    {
        bricksReady->setVisible(true);
        bricksReady->setOpacity(0);
        
        auto seq = Sequence::create(TintTo::create(0.25, 255, 255, 100), TintTo::create(0.25, 25, 255, 255), TintTo::create(0.25, 255, 50, 255), NULL);
        auto action = Repeat::create(seq, 4);
        auto seqMaster = Sequence::create(FadeIn::create(0.1), action, FadeOut::create(0.1), NULL);
        bricksReady->runAction(seqMaster);
    }

}

void GameScene::onBackFromWait()
{
    playClickSound();
    fadeInLayout(waitLayout->getBackTarget());
    fadeOutLayout(waitLayout);
}

void GameScene::onReplayButtonClicked()
{
    bricksReady->setVisible(false);
    playClickSound();
    stopActionByTag(1666);
    if(!getRemoveAds() && getBricksRemaining() < 1)
    {
        fadeOutLayout(winLoseLayout);
        fadeInLayout(waitLayout);
        waitLayout->setBackTarget(winLoseLayout);
        waitLayout->launchTimer();
        return;
    }
    
    if(!getRemoveAds())
    {
        setBricksRemaining(getBricksRemaining() - 1);
    }

    
    
    for(int i = 0; i < 3; i++)
    {
        currentStarCollected[i] = false;
    }
    
    kielniasUsedOnLevel = 0;
    
    
    winLoseLayout->setEnabled(false);
    winLoseLayout->setVisible(false);
    level->reload();
    
    auto func = CallFunc::create([this](){
        this->hideUI();
        this->setGameState(ReadyToPlay);
        this->postEffect->setPostEffectsEnabled(false);

        tapToPlay->runAction(FadeTo::create(0.3, 255));
    });

    float time = 1;
    postEffect->runAction(BlurFromTo::create(time, Globals::blurRadius, 0));
    this->setStartingCameraAndBg(true);
    
    auto seq = Sequence::create(FadeTo::create(time, 0), func, NULL);
    winLoseLayout->runAction(seq);
    
}


void GameScene::setTutorialPlayer(Player *player)
{
    level->setTutorialPlayer(player);
}






void GameScene::onPlayNextButtonClicked()
{
    playClickSound();
    stopActionByTag(1666);
    if(!getRemoveAds() && getBricksRemaining() < 1)
    {
        fadeOutLayout(winLoseLayout);
        fadeInLayout(waitLayout);
        waitLayout->setBackTarget(winLoseLayout);
        waitLayout->launchTimer();
        return;
    }
    
    for(int i = 0; i < 3; i++)
    {
        currentStarCollected[i] = false;
    }
    
    kielniasUsedOnLevel = 0;
    if(!getRemoveAds())
    {
        setBricksRemaining(getBricksRemaining() - 1);
    }
    
    
    
    setStartingCameraAndBg();
    winLoseLayout->setEnabled(false);
    if(getLastLevelId() + 1 > 6 && isThemeAvailable(getLastThemeId() + 1))
    {
        setLastLevelId(1);
        if(getLastThemeId() + 1 < 10)
        {
            setLastThemeId(getLastThemeId() + 1);
            const auto codename = getLastTheme().getCodeName();
            auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
            if(sae->isBackgroundMusicPlaying())
            {
                sae->stopBackgroundMusic();
            }

            // to do exists
            auto path = Globals::resources["music_" + codename];
            auto fu = FileUtils::getInstance();
            if(fu->isFileExist(path))
            {
                sae->playBackgroundMusic(path.c_str(), true);
            }
            
        }
        
    }
    else if(getLastLevelId() + 1 > 6)
    {
        updateUI();
        winLoseLayout->setEnabled(true);
        buyChapter(getLastThemeId() + 1);
        return;
    }
    else
    {
        setLastLevelId(getLastLevelId() + 1);
    }
    
    setGameState(Win);


    nextLevel = Level::create(this);
    nextLevel->load(getLastThemeId(), getLastLevelId());
    nextLevel->setPositionY(visibleSize.height);
    nextLevel->setStopped(true);
    postEffect->addChild(nextLevel);
    
    updateUI();
    hideUI();
    level->setStopped(true);
    level->removeAllChildrenWithCleanup(true);
    level->removeFromParentAndCleanup(true);
    level = nextLevel;
    nextLevel = nullptr;

    
    auto func = CallFunc::create([this](){
        /*postEffect->setPostEffectsEnabled(false);
        this->setGameState(ReadyToPlay);
        tapToPlay->setOpacity(0);
        tapToPlay->runAction(FadeTo::create(0.3, 255));
        
        level->setStopped(false);*/
        const auto codename = getLastTheme().getCodeName();
        tutorialLayout->setVisible(true);
        tutorialLayout->setOpacity(255);
        tutorialLayout->setEnabled(true);
        setGameState(Tutorial);
        level->setStopped(true);
        if(!getTutorialDisplayed())
        {
            level->setStopped(false);
            tutorialLayout->displayControl();
        }
        else if(codename == "desert" && !getDesertDisplayed())
        {
            setDesertDisplayed(true);
            tutorialLayout->displayDesert();
        }
        else if(codename == "cosmic" && !getSpaceDisplayed())
        {
            setSpaceDisplayed(true);
            tutorialLayout->displaySpace();
        }
        else if(codename == "western" && !getWesternDisplayed())
        {
            setWesternDisplayed(true);
            tutorialLayout->displayWestern();
        }
        else if(codename == "snowland" && !getSnowlandDisplayed())
        {
            setSnowlandDisplayed(true);
            tutorialLayout->displaySnowland();
        }
        else if(codename == "graveyard" && !getGraveyardDisplayed())
        {
            setGraveyardDisplayed(true);
            tutorialLayout->displayGraveyard();
        }
        else if(codename == "mouth" && !getMouthDisplayed())
        {
            setMouthDisplayed(true);
            tutorialLayout->displayMouth();
        }
        else
        {
            level->setStopped(false);
            tutorialLayout->setVisible(false);
            setGameState(ReadyToPlay);
            postEffect->setPostEffectsEnabled(false);
            tapToPlay->runAction(FadeTo::create(0.3, 255));
        }
    });
    
    auto seq = Sequence::create(/*BlurFromTo::create(1.0, Globals::blurRadius, 0), */DelayTime::create(1.0), func, NULL);
    postEffect->runAction(seq);
    
    level->runAction(MoveBy::create(1.0, Vec2(0, -visibleSize.height)));
    

}


void GameScene::launchKielniaTimer()
{
    kielniaLayout->launchTimer();
}



void GameScene::setStartingCameraAndBg(bool animated)
{
    if(animated)
    {
        level->runAction(MoveTo::create(1.0, Vec2::ZERO));
    }
    else
    {
        level->setPositionY(0);
    }


    //levelPercentBar->setPositionY(50);
    //levelPercentSprite->setPositionY(50);
}

void GameScene::onStarCollected(int number, float x)
{
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    sae->playEffect(Globals::resources["effect_star"].c_str());
    currentStarCollected[number - 1] = true;
    
    Sprite* star = starBarContainer->getChildByTag<Sprite*>(number);
    
    if(star == nullptr) return;
    
    
    
    
    //Skew
    
    auto starAnim = cocos2d::Sprite::create(Globals::resources["icon_star_collect_white"]);
    starAnim->setPosition(Vec2(x, playerStartY));
    starAnim->setColor(Color3B(255, 215, 0));
    
    addChild(starAnim);
    
    //RotateBy::create
    float ratio = star->getContentSize().width / starAnim->getContentSize().width;
    starAnim->setScale(ratio);
    const float time = 0.5;
    auto spawn = Spawn::create(ScaleTo::create(time, ratio), RotateBy::create(time, 180.0, 180.0), MoveTo::create(time, star->getPosition()), NULL);
    auto func = CallFunc::create([starAnim, star]{
        starAnim->removeFromParent();
        star->setTexture(Globals::resources["barstar_full"]);
    });
    auto seq = Sequence::create(spawn, func, NULL);
    starAnim->runAction(seq);
    starAnim->setTag(2044);

}


void GameScene::createDebugLayer(b2World *world)
{
    debugLayer = B2DebugDrawLayer::create(world, kPixelsPerMeter);
    addChild(debugLayer, 9999);
}


void GameScene::setGameState(GameHandler::GameState state)
{
    GameHandler::setGameState(state);
    if(state == Playing)
    {
        tapToPlay->runAction(FadeTo::create(transitionTime, 0));
        levelPercentSprite->setVisible(true);
        levelPercentBar->setVisible(true);
        starBarContainer->setVisible(true);
    }
    else
    {
        levelPercentSprite->setVisible(false);
        levelPercentBar->setVisible(false);
        starBarContainer->setVisible(false);
    }
}

void GameScene::onGameExit()
{
    waitLayout->onGameExit();
    

    postEffect->setPostEffectsEnabled(false);
    if(getGameState() == Playing)
    {
        setGameState(ReadyToPlay);
        tapToPlay->runAction(FadeTo::create(0.3, 255));
    }
    
}

void GameScene::onGameEnter()
{
    if(getGameState() != Playing && getGameState() != ReadyToPlay)
    {
        postEffect->setPostEffectsEnabled(true);
        postEffect->requestRedraw();
    }
    waitLayout->onGameEnter();
}


void GameScene::hideUI()
{
    uiContainer->setVisible(false);
    uiContainer->setEnabled(false);
    winLoseLayout->setVisible(false);

}

void GameScene::showUI()
{
    uiContainer->setEnabled(true);
    uiContainer->setVisible(true);
    selectLayout->setPositionX(-visibleSize.width);
}

void GameScene::updateUI()
{
    const auto lastTheme = getLastTheme();
    currentUIColor = lastTheme.isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0);
    const std::string playButton = lastTheme.getPlayButtonPath();
    titleLayout->updateUITheme(currentUIColor, playButton);
    kielniaLayout->updateUI(currentUIColor, getKielnias());
    
    
    
    background->setTexture(lastTheme.getBackgroundPath());
    //background->setSpriteFrame(lastTheme.getBackgroundPath());
    levelPercentBar->setColor(currentUIColor);
    levelPercentSprite->setColor(currentUIColor);

    settingsLayout->setColor(currentUIColor);
    waitLayout->setColor(currentUIColor);
    winLoseLayout->updateUI();
    shopLayout->updateUI();
    
    
    
    ///////////////////////////////////
 
  
}



void GameScene::moveLayouts(ui::Layout *firstLayout, ui::Layout *secondLayout, TransitionDirection dir)
{
    if(inLayoutsTransition)
    {
        return;
    }
    
    static Vec2 directions[] = {
        Vec2(-visibleSize.width, 0),
        Vec2(visibleSize.width, 0),
        Vec2(0, visibleSize.height),
        Vec2(0, -visibleSize.height),
    };
    
    secondLayout->setPosition(-directions[dir]);
    
    
    firstLayout->setVisible(true);
    secondLayout->setVisible(true);
    

    inLayoutsTransition = true;
    auto moveAction = MoveBy::create(transitionTime, directions[dir]);
    auto func = CallFunc::create([this, firstLayout, secondLayout]()
    {
        secondLayout->setEnabled(true);
        firstLayout->setVisible(false);
        this->inLayoutsTransition = false;
    });
    
    auto seq = Sequence::create(DelayTime::create(transitionTime), func, NULL);
    
    firstLayout->setEnabled(false);
    secondLayout->setEnabled(false);
    firstLayout->setOpacity(255);
    secondLayout->setOpacity(255);
    
    firstLayout->runAction(moveAction);
    secondLayout->runAction(MoveBy::create(transitionTime, directions[dir]));
    runAction(seq);

}



void GameScene::fadeInLayout(ui::Layout *layout)
{
    layout->setEnabled(false);
    layout->setVisible(true);
    layout->setOpacity(0);
    layout->setPosition(Vec2::ZERO);
    auto func = CallFunc::create([layout]()
    {
        layout->setEnabled(true);
    });
    
    auto seq = Sequence::create(FadeIn::create(transitionTime), func, NULL);
    layout->runAction(seq);
}

void GameScene::fadeOutLayout(ui::Layout *layout)
{
    layout->setEnabled(false);
    auto func = CallFunc::create([layout]()
                                 {
                                     layout->setVisible(false);
                                 });
    auto seq = Sequence::create(FadeOut::create(transitionTime), func, NULL);
    
    layout->runAction(seq);
}


void GameScene::onSettingsButtonClicked()
{
    playClickSound();
    settingsLayout->setBackTarget(titleLayout);
    moveLayouts(titleLayout, settingsLayout, Left);
}


void GameScene::onShopFromWinLose()
{
    playClickSound();
    shopLayout->setBackTarget(winLoseLayout);
    shopLayout->setBonusActive();
    moveLayouts(winLoseLayout, shopLayout, Right);
}

void GameScene::onBackButtonClicked()
{
    playClickSound();
    moveLayouts(settingsLayout, settingsLayout->getBackTarget(), Right);
}

void GameScene::onPlayButtonClicked()
{
    bricksReady->setVisible(false);
    playClickSound();
    
    selectLayout->setAnchorPoint(Vec2::ZERO);
    selectLayout->setScale(1.0);

    moveLayouts(titleLayout, selectLayout, Up);
    
    setGameState(Died);
    
    auto func = CallFunc::create([this](){
                                      postEffect->setPostEffectsEnabled(false);
                                  });
    auto seq = Sequence::create(DelayTime::create(0.3), func, NULL);
    runAction(seq);

}


void GameScene::onBackFromSelectSwiped()
{
    if(getGameState() == Died || getGameState() == Win || getGameState() == WinAfter)
    {
        level->setPositionY(0);
        level->removeAllChildren();
        level->resetRandomBackground();
        setGameState(UI);
    }
    postEffect->setPostEffectsEnabled(true);
    moveLayouts(selectLayout, titleLayout, Down);
}

void GameScene::onHomeFromLoseClicked()
{
    playClickSound();
    if(getGameState() == Died || getGameState() == Win || getGameState() == WinAfter)
    {
        level->setPositionY(0);
        level->removeAllChildren();
        level->resetRandomBackground();
        setGameState(UI);
    }
    selectLayout->setVisible(false);
    moveLayouts(winLoseLayout, titleLayout, Down);
    
    postEffect->setPostEffectsEnabled(true);
}


void GameScene::onShopButtonClicked()
{
    playClickSound();
    moveLayouts(titleLayout, shopLayout, Right);
}

void GameScene::onBackFromShop()
{
    playClickSound();
    moveLayouts(shopLayout, shopLayout->getBackTarget(), Left);
}


void GameScene::onBackFromLoseClicked()
{
    playClickSound();
    selectLayout->setAnchorPoint(Vec2::ZERO);
    selectLayout->setScale(1.0);

    moveLayouts(winLoseLayout, selectLayout, Right);
    
    auto func = CallFunc::create([this](){
        postEffect->setPostEffectsEnabled(false);
    });
    auto seq = Sequence::create(DelayTime::create(0.3), func, NULL);
    runAction(seq);
}


void GameScene::onSettingsFromLoseClicked()
{
    playClickSound();
    settingsLayout->setBackTarget(winLoseLayout);
    moveLayouts(winLoseLayout, settingsLayout, Left);
}

int GameScene::getCurrentProgress()
{
    return (int)levelPercentBar->getPercent();
}


void GameScene::onSkinUsed()
{
    shopLayout->updateSkins();
}

void GameScene::onBricksMissingFromSelect()
{
    fadeOutLayout(selectLayout);
    fadeInLayout(waitLayout);
    waitLayout->setBackTarget(selectLayout);
    waitLayout->launchTimer();
}


void GameScene::onLetsTryClicked()
{
    playClickSound();
    postEffect->setPostEffectsEnabled(false);
    setGameState(ReadyToPlay);
    tapToPlay->runAction(FadeTo::create(0.3, 255));
    fadeOutLayout(tutorialLayout);
    setTutorialDisplayed(true);
    auto func = CallFunc::create([this](){
        this->tutorialLayout->hideDefault();
    });
    
    auto seq = Sequence::create(DelayTime::create(0.3), func, NULL);
    runAction(seq);
    
    level->setTutorialPlayer(nullptr);
    level->setStopped(false);
}

void GameScene::onLetsTryClickedFromLevel()
{
    playClickSound();
    postEffect->setPostEffectsEnabled(false);
    setGameState(ReadyToPlay);
    tapToPlay->runAction(FadeTo::create(0.3, 255));
    fadeOutLayout(tutorialLayout);
    level->setTutorialPlayer(nullptr);
    level->setStopped(false);
}

bool GameScene::launchChapterReward(int themeId)
{
    rewardLayout->setEnabled(true);
    rewardLayout->setVisible(true);
    winLoseLayout->setVisible(false);
    return rewardLayout->launchChapterReward(themeId);
}

bool GameScene::launchBrickReward()
{
    rewardLayout->setEnabled(true);
    rewardLayout->setVisible(true);
    winLoseLayout->setVisible(false);
    return rewardLayout->launchBrickReward();
}

void GameScene::buyChapter(int themeId)
{
    playClickSound();
    uiContainer->setEnabled(false);
    popupLayer->setOpacity(0);
    popupLayer->setVisible(true);
    popupLayer->runAction(FadeTo::create(0.3, 128));
    fadeInLayout(popupLayout);
    
    popupLayout->setPriceAndTheme(Globals::chaptersSteps[themeId], themeId);
}

void GameScene::onPopupCancelled()
{
    playClickSound();
    auto func = CallFunc::create([this](){
        this->popupLayer->setVisible(false);
        this->uiContainer->setEnabled(true);
    });
    auto seq = Sequence::create(FadeOut::create(0.3), func, NULL);
    popupLayer->runAction(seq);
    fadeOutLayout(popupLayout);
}

void GameScene::onBuyChapterCompleted()
{
    auto func = CallFunc::create([this](){
        this->popupLayer->setVisible(false);
        this->uiContainer->setEnabled(true);
    });
    auto seq = Sequence::create(FadeOut::create(0.3), func, NULL);
    popupLayer->runAction(seq);
    fadeOutLayout(popupLayout);
}

void GameScene::onChapterRewardEnded()
{
    int starsCount = getStarCount();
    for(int i = 1; i < 16; i++)
    {
        if(starsCount >= Globals::bricksSteps[i] && !brickAtStepUnlocked(i))
        {
            setBrickAtStepUnlocked(i);
            launchBrickReward();
            return;
        }
    }
    
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    sae->playEffect(Globals::resources["effect_lvlcompleted"].c_str());
    fadeInLayout(winLoseLayout);
}

void GameScene::onBrickRewardEnded()
{
    fadeOutLayout(rewardLayout);
    fadeInLayout(winLoseLayout);
    shopLayout->updateUI();
    
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    sae->playEffect(Globals::resources["effect_lvlcompleted"].c_str());
}

void GameScene::onKielniaUsed()
{
    //playClickSound();
    fadeOutLayout(kielniaLayout);
    
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
#if !defined DOWNLOAD_MAPS
    kielniasUsedOnLevel++;
#endif
#endif
    

    setKielnias(getKielnias() - 1);
    kielniaLayout->updateUI(getLastTheme().getUIColor(), getKielnias());
    auto func = CallFunc::create([this](){
        postEffect->setPostEffectsEnabled(false);
        this->setGameState(ReadyToPlay);
        level->resetPlayerPosY();
        tapToPlay->setOpacity(0);
        tapToPlay->runAction(FadeTo::create(0.3, 255));
    });
    
    auto seq = Sequence::create(BlurFromTo::create(blurTime, Globals::blurRadius, 0), func, NULL);
    postEffect->runAction(seq);
    
}

void GameScene::onNoThanksClicked()
{
    playClickSound();
    fadeOutLayout(kielniaLayout);
    setBlackout(false);
    fadeInLayout(winLoseLayout);
    
    setFinishLineY(-1.0);

}

void GameScene::logEventDeath(int themeId, int levelId, int percent, int brick)
{
    return;
    network::HttpRequest* request = new cocos2d::network::HttpRequest();
    const std::string url = StringUtils::format("http://api.skyhorn.tech/?game=magnetic_brick&event=death&themeId=%d&levelId=%d&percent=%d&brick=%d", themeId, levelId, percent, brick);
    CCLOG("%s", url.c_str());
    request->setUrl(url.c_str());
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    //request->setResponseCallback( CC_CALLBACK_2(HttpClientTest::onHttpRequestCompleted, this));
    request->setTag("GET push");
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
    
    Data data;
    //ud->setDataForKey(<#const char *key#>, <#const cocos2d::Data &value#>)
}



void GameScene::logEventWin(int themeId, int levelId, int brick)
{
    return;
    network::HttpRequest* request = new cocos2d::network::HttpRequest();
    const std::string url = StringUtils::format("http://api.skyhorn.tech/?game=magnetic_brick&event=win&themeId=%d&levelId=%d&brick=%d", themeId, levelId, brick);
    CCLOG("%s", url.c_str());
    request->setUrl(url.c_str());
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    //request->setResponseCallback( CC_CALLBACK_2(HttpClientTest::onHttpRequestCompleted, this));
    request->setTag("GET push");
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}


void GameScene::setPlayerVelocities(float speed)
{
    if(level->player)
    {
        level->player->setVelocities(speed);
    }
}

b2World* GameScene::getWorld()
{
    return level->world;
}



#if defined ADS
void GameScene::onAdColonyChange(const sdkbox::AdColonyAdInfo& info, bool available)
{
    adColonyReceived = available;
}
void GameScene::onAdColonyReward(const sdkbox::AdColonyAdInfo& info,
                      const std::string& currencyName, int amount, bool success)
{
    CCLOG("ad colony reward");
    if(success)
    {
        CCLOG("reward adColony %d", amount);
        setBricksRemaining(getBricksRemaining() + amount);
        winLoseLayout->updateUI();
        titleLayout->updateRemainingBricks(getRemoveAds(), getBricksRemaining());
        auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
        sae->resumeBackgroundMusic();
    }

}

void GameScene::onAdColonyStarted(const sdkbox::AdColonyAdInfo& info)
{
    CCLOG("onAdColonyStarted");
}
void GameScene::onAdColonyFinished(const sdkbox::AdColonyAdInfo& info)
{
    CCLOG("onAdColonyFinished");
}
 

 

void GameScene::onInitialized(bool ok)
{
    CCLOG("IAP Initialized: %d", ok);
}

void GameScene::onSuccess(sdkbox::Product const& p)
{
    CCLOG("IAP Success");
    if(p.name == "kielnia5")
    {
        setKielnias(getKielnias() + 5);
    }
    else if(p.name == "kielnia10")
    {
        setKielnias(getKielnias() + 10);
    }
    else if(p.name == "kielnia20")
    {
        setRemoveAds(true);
        setKielnias(getKielnias() + 20);
    }
    else if(p.name == "kielnia50")
    {
        setRemoveAds(true);
        setKielnias(getKielnias() + 50);
    }
    else if(p.name == "unlock1")
    {
        int i = 1;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);
        onBuyChapterCompleted();
    }
    else if(p.name == "unlock2")
    {
        int i = 2;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);
        onBuyChapterCompleted();
    }
    else if(p.name == "unlock3")
    {
        int i = 3;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);
        onBuyChapterCompleted();
    }
    else if(p.name == "unlock4")
    {
        int i = 4;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);
        onBuyChapterCompleted();
    }
    else if(p.name == "unlock5")
    {
        int i = 5;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);
        onBuyChapterCompleted();
    }
    else if(p.name == "unlock6")
    {
        int i = 6;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);
        onBuyChapterCompleted();
    }
    else if(p.name == "unlock7")
    {
        int i = 7;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);
        onBuyChapterCompleted();
    }
    else if(p.name == "unlock8")
    {
        int i = 8;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);
        onBuyChapterCompleted();
    }
    else if(p.name == "unlock9")
    {
        int i = 9;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        onBuyChapterCompleted();
    }
    else if(p.name == "remove_ads")
    {
        setRemoveAds(true);
        titleLayout->updateRemainingBricks(true);
    }

    
    
    winLoseLayout->updateUI();
    shopLayout->updateUI();
}

void GameScene::onFailure(sdkbox::Product const& p, const std::string &msg)
{
    CCLOG("IAP Failure");//xw %s %s", p.name.c_str(), msg.c_str());
}

void GameScene::onCanceled(sdkbox::Product const& p)
{
    CCLOG("IAP Cancelled");
}

void GameScene::onRestored(sdkbox::Product const& p)
{
    CCLOG("IAP Restorred");
    CCLOG("%s", p.name.c_str());
    if(p.name == "remove_ads")
    {
        setRemoveAds(true);
        titleLayout->updateRemainingBricks(true);
    }
    else if(p.name == "unlock1")
    {
        int i = 1;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);
    }
    else if(p.name == "unlock2")
    {
        int i = 2;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);
    }
    else if(p.name == "unlock3")
    {
        int i = 3;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);
    }
    else if(p.name == "unlock4")
    {
        int i = 4;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);
    }
    else if(p.name == "unlock5")
    {
        int i = 5;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);;
    }
    else if(p.name == "unlock6")
    {
        int i = 6;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);
    }
    else if(p.name == "unlock7")
    {
        int i = 7;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);
    }
    else if(p.name == "unlock8")
    {
        int i = 8;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
        selectLayout->updateTheme(i + 1);
    }
    else if(p.name == "unlock9")
    {
        int i = 9;
        setThemeAvailable(i);
        selectLayout->updateTheme(i);
    }
    
    winLoseLayout->updateUI();
    shopLayout->updateUI();
}

void GameScene::onProductRequestSuccess(std::vector<sdkbox::Product> const &products)
{

    for(const auto product : products)
    {
        CCLOG("updating: %s %s", product.name.c_str(), product.price.c_str());
        shopLayout->updateProduct(product.name, product.price, product.priceValue);
    }
    CCLOG("IAP RequestSuccess");
    Globals::iapLoaded = true;
}

void GameScene::onProductRequestFailure(const std::string &msg)
{
    CCLOG("IAP RequestFailure %s", msg.c_str());
    Globals::iapLoaded = false;
}

void GameScene::onRestoreComplete(bool ok, const std::string &msg)
{
    CCLOG("IAP Restore Completed");
}


void GameScene::adViewDidReceiveAd(const std::string &name)
{
    CCLOG("didReceiveAd: %s", name.c_str());
    adColonyReceived = true;
}

void GameScene::adViewDidFailToReceiveAdWithError(const std::string &name, const std::string &msg)
{
   CCLOG("adViewDidFail: %s %s", name.c_str(), msg.c_str());
}

void GameScene::adViewWillPresentScreen(const std::string &name)
{
    CCLOG("adViewWillPresent %s", name.c_str());
}

void GameScene::adViewDidDismissScreen(const std::string &name)
{
    CCLOG("adViewDidDismiss %s", name.c_str());


}

void GameScene::reward(const std::string &name, const std::string &currency, double amount)
{
    int value = (int)amount;
    CCLOG("reward %d", value);
    setBricksRemaining(getBricksRemaining() + value);
    winLoseLayout->updateUI();
    titleLayout->updateRemainingBricks(getRemoveAds(), getBricksRemaining());
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    sae->resumeBackgroundMusic();
}

void GameScene::adViewWillDismissScreen(const std::string &name)
{
    CCLOG("adViewWillDismiss %s", name.c_str());
    
    sdkbox::PluginAdMob::cache("mb_video");
    
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    sae->resumeBackgroundMusic();
}


void GameScene::adViewWillLeaveApplication(const std::string &name)
{
    CCLOG("adVieWillLeaveApp %s", name.c_str());
}


void GameScene::onChartboostCached(const std::string& name)
{
    CCLOG("onChartboostChached: %s", name.c_str());
}

bool GameScene::onChartboostShouldDisplay(const std::string& name)
{
    CCLOG("onChartboostShouldDisplay: %s", name.c_str());
    return true;
}

void GameScene::onChartboostDisplay(const std::string& name)
{
    CCLOG("onChartboostDisplay: %s", name.c_str());
}

void GameScene::onChartboostDismiss(const std::string& name)
{
    CCLOG("onChartboostDismiss: %s", name.c_str());
}

void GameScene::onChartboostClose(const std::string& name)
{
    CCLOG("onChartboostClose: %s", name.c_str());
}
void GameScene::onChartboostClick(const std::string& name)
{
    CCLOG("onChartboostClick: %s", name.c_str());
}

void GameScene::onChartboostReward(const std::string& name, int reward)
{
    CCLOG("onChartboostReward: %s %d", name.c_str(), reward);
    
    CCLOG("reward chartboost 20");
    setBricksRemaining(getBricksRemaining() + reward);
    winLoseLayout->updateUI();
    titleLayout->updateRemainingBricks(getRemoveAds(), getBricksRemaining());
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    sae->resumeBackgroundMusic();
}

void GameScene::onChartboostFailedToLoad(const std::string& name, sdkbox::CB_LoadError e)
{
    CCLOG("onChartboostFailedtoLoad: %s", name.c_str());
}

void GameScene::onChartboostFailToRecordClick(const std::string& name, sdkbox::CB_ClickError e)
{
    CCLOG("onChartboostFailedtoRecordClick: %s", name.c_str());
}

void GameScene::onChartboostConfirmation()
{
    CCLOG("onChartboostConfirmation");
}

void GameScene::onChartboostCompleteStore()
{
    CCLOG("onChartboostCompleteStore");
}

/*
void GameScene::unityAdsDidClick(const std::string& placementId) {
    CCLOG("unityads click %s", placementId.c_str());
}

void GameScene::unityAdsPlacementStateChanged(const std::string& placementId,
                                            sdkbox::PluginUnityAds::SBUnityAdsPlacementState oldState,
                                            sdkbox::PluginUnityAds::SBUnityAdsPlacementState newState) {
    CCLOG("unityads state change %s %d->%d", placementId.c_str(), oldState, newState);
}

void GameScene::unityAdsReady(const std::string& placementId) {
    CCLOG("unityads ready %s", placementId.c_str());
}

void GameScene::unityAdsDidError(sdkbox::PluginUnityAds::SBUnityAdsError error, const std::string& message) {
    CCLOG("unityads error %d %s", error, message.c_str());
}

void GameScene::unityAdsDidStart(const std::string& placementId) {
    CCLOG("unityads start %s", placementId.c_str());
}

void GameScene::unityAdsDidFinish(const std::string& placementId, sdkbox::PluginUnityAds::SBUnityAdsFinishState state) {
    CCLOG("unityads finish %d %s", state, placementId.c_str());
    if(state == sdkbox::PluginUnityAds::SBUnityAdsFinishState::kUnityAdsFinishStateCompleted)
    {
        CCLOG("reward unity 20");
        setBricksRemaining(getBricksRemaining() + Globals::bricksAfterWaiting);
        winLoseLayout->updateUI();
        titleLayout->updateUI();
        auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
        sae->resumeBackgroundMusic();
    }
}
*/

#endif
