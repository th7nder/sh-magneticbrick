//
//  LoadingScene.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 11/03/2017.
//
//

#ifndef LoadingScene_hpp
#define LoadingScene_hpp

#include <string>

#include "cocos2d.h"
#include "ui/UILoadingBar.h"

#include "SimpleAudioEngine.h"

#include "Globals.hpp"
#include "GameScene.hpp"

class LoadingScene : public cocos2d::Scene
{
    typedef cocos2d::Scene super;
    typedef LoadingScene self;
    void loadResources();
    cocos2d::ui::LoadingBar* loadingBar;
    float loadedResources;
    float maxResources;
CC_CONSTRUCTOR_ACCESS:
    LoadingScene();
    virtual ~LoadingScene();
public:
    CREATE_FUNC(LoadingScene);
    virtual bool init() override;
    void updateLoadingBar();
};

#endif /* LoadingScene_hpp */
