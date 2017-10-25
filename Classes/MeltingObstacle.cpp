//
//  MeltingObstacle.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/05/2017.
//
//

#include "MeltingObstacle.hpp"


MeltingObstacle::MeltingObstacle() : name(""), triggered(false)
{
    
}

MeltingObstacle::~MeltingObstacle()
{
    
}

MeltingObstacle* MeltingObstacle::create(GameHandler* handler)
{
    self* ret = new (std::nothrow) self();
    if (ret && ret->init(handler))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}


bool MeltingObstacle::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    const auto lastThemeCodename = "obstacle_" +  handler->getLastTheme().getCodeName();
    centerTexture = Globals::resources[lastThemeCodename + "_center"];


    return true;
}


void MeltingObstacle::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
    auto scale = Director::getInstance()->getContentScaleFactor();
    size = (props["width"].asFloat() * scale / 54.0);
    
    //CCASSERT(!props["name"].isNull(), "Laser without a name!");
    //auto name = props["name"].asString();
    //setName(name);
}

void MeltingObstacle::addSprite()
{
    auto spr = Sprite::create(centerTexture);
    spr->setAnchorPoint(Vec2::ZERO);

    
    auto width = spr->getContentSize().width;
    auto height = spr->getContentSize().height;
    float fAmount = getContentSize().width / width;
    int amount = getContentSize().width / width;
    if(fAmount - amount > 0)
    {
        amount++;
    }
    
    float centerWidth = (amount - 1) * width;
    if(amount > 1)
    {
        spr = Sprite::create(centerTexture);
        spr->setAnchorPoint(Vec2::ZERO);
        spr->setContentSize(Size(centerWidth + 40, height));
        spr->setPosition(Vec2(width - 40, 0));
        
        addChild(spr);
    }
    
    

    
    
}
void MeltingObstacle::launch()
{
    addIce();
}


void MeltingObstacle::addIce()
{
    if(triggered) return;
    triggered = true;
    setCascadeOpacityEnabled(true);
    sprite = Sprite::create(Globals::resources[StringUtils::format("melting_obstacle_%d", size)]);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);
    
    sprite->setCascadeOpacityEnabled(true);
    sprite->setOpacity(0);
    
    float baseDistance = (600.0f / 1080.0f) * 1136;
    float delayTime = (0.8f * baseDistance) / gameHandler->getCurrentPlayerSpeed();
    float appearTime = (0.25f * baseDistance) / gameHandler->getCurrentPlayerSpeed();
    float disappearTime = (0.10f * baseDistance) / gameHandler->getCurrentPlayerSpeed();
    //CCLOG("time: %f %f %f", delayTime, appearTime, disappearTime);
    
    auto sound = CallFunc::create([](){
        auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
        sae->playEffect(Globals::resources["effect_melting"].c_str());
    });
    sprite->runAction(Sequence::create(DelayTime::create(delayTime), sound, FadeIn::create(appearTime), NULL));
    
    auto func = CallFunc::create([this]()
                                 {
                                     this->remove = true;
                                 });
    

    auto seq = Sequence::create(DelayTime::create(delayTime + appearTime), FadeOut::create(disappearTime), func, NULL);
    runAction(seq);
    
}
