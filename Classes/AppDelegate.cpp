#include "AppDelegate.h"
#include "LoadingScene.hpp"
#include "GameScene.hpp"
#include "Globals.hpp"

#if defined ADS
#include "PluginIAP/PluginIAP.h"
#endif

USING_NS_CC;


static cocos2d::Size designResolutionSize = cocos2d::Size(640, 1136);
static cocos2d::Size smallResolutionSize = cocos2d::Size(640, 1136);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(750, 1334);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1080, 1920);


double getCurrentTimeInSeconds()
{
    static struct timeval currentTime;
    gettimeofday(&currentTime, nullptr);
    return (currentTime.tv_sec) + (currentTime.tv_usec / 1000000.0);
}

AppDelegate::AppDelegate() : leftAppTime(0), enterAppTime(0)
{
}

AppDelegate::~AppDelegate() 
{

}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}


bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("MagneticBrick", cocos2d::Rect(0, 0, mediumResolutionSize.width, mediumResolutionSize.height));
#else
        glview = GLViewImpl::create("MagneticBrick");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
    auto frameSize = glview->getFrameSize();
    std::vector<std::string> searchPaths;
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(largeResolutionSize.width/designResolutionSize.width);
        searchPaths.push_back("3x");

    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {
        director->setContentScaleFactor((mediumResolutionSize.width)/designResolutionSize.width);
        searchPaths.push_back("2x");

    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(smallResolutionSize.width/designResolutionSize.width);
        searchPaths.push_back("1x");

    }

    register_all_packages();


    if(frameSize.width < designResolutionSize.width)
    {
        Globals::setSmallPhone(true);
    }
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    

    auto scene = LoadingScene::create();
    //auto scene = GameScene::create();
    director->runWithScene(scene);
    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    
    leftAppTime = getCurrentTimeInSeconds();
    UserDefault::getInstance()->setDoubleForKey("leftAppTime", leftAppTime);
    // if you use SimpleAudioEngine, it must be paused
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    
    if(sae->isBackgroundMusicPlaying())
    {
        sae->pauseBackgroundMusic();
    }
#endif


    
    GameScene* scene = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
    if(scene != nullptr) scene->onGameExit();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
#if (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
    sdkbox::IAP::refresh();
#endif
    
    Director::getInstance()->startAnimation();

    enterAppTime = getCurrentTimeInSeconds();
    UserDefault::getInstance()->setDoubleForKey("enterAppTime", enterAppTime);

    // if you use SimpleAudioEngine, it must resume here
     GameScene* scene = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
    if(scene != nullptr) scene->onGameEnter();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    
    // to do exists
    sae->resumeBackgroundMusic();
    
#endif
    

}
