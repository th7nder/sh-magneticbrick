//
//  LoadingScene.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 11/03/2017.
//
//

#include "LoadingScene.hpp"

USING_NS_CC;

LoadingScene::LoadingScene() : loadingBar(nullptr), loadedResources(0), maxResources(0)
{
    
}


LoadingScene::~LoadingScene()
{
    
}

bool LoadingScene::init()
{
    if(!super::init()) return false;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto background = Sprite::create(Globals::resources["splashscreen"]);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    addChild(background);

    loadingBar = ui::LoadingBar::create(Globals::resources["icon_loadingbar"]);
    loadingBar->setPercent(0);
    loadingBar->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4));
    addChild(loadingBar);
    

    loadResources();
    return true;
}

void LoadingScene::loadResources()
{
    loadedResources = 0;
    maxResources = (float)Globals::resources.size();
    auto fu = FileUtils::getInstance();
    for(auto resource : Globals::resources)
    {
        if(resource.second.find(".mp3") != -1)
        {
            if(resource.second.find("effect") != -1)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(resource.second.c_str());
                updateLoadingBar();
            } else
            {
                if(fu->isFileExist(resource.second))
                {
                   CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(resource.second.c_str());
                }
                
                updateLoadingBar();
                
            }

            
        } else
        {
            if(resource.second.find("/background.png") != -1)
            {
                loadedResources += 1.0;
                updateLoadingBar();
                CCLOG("skipping background %s", resource.second.c_str());
            }
            else
            {
                Director::getInstance()
                ->getTextureCache()
                ->addImageAsync(resource.second, [this](Texture2D* tex)
                                {
                                    this->updateLoadingBar();
                                });
            }

        }

    }
    

    /*auto func = CallFunc::create([this](){
        _director->replaceScene(TransitionFade::create(0.5, GameScene::create()));
    });
    
    loadingBar->runAction(Sequence::create(ProgressFromTo::create(0.5, 0, 100), func, NULL));*/
}

void LoadingScene::updateLoadingBar()
{
    loadedResources += 1.0;
    CCLOG("spierdolony %f %f", loadedResources, maxResources);
    float percent = loadedResources / maxResources;
    this->loadingBar->setPercent(percent * 100);
    CCLOG("max resources %f", percent);
    
    if(percent >= 1.0)
    {
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameScene::create()));
    }
}
