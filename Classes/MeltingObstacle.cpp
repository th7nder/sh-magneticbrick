//
//  MeltingObstacle.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/05/2017.
//
//

#include "MeltingObstacle.hpp"


USING_NS_CC;
MeltingObstacle::MeltingObstacle() : name(""), triggered(false)
{
    
}

MeltingObstacle::~MeltingObstacle()
{
    
}


void MeltingObstacle::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
    auto scale = Director::getInstance()->getContentScaleFactor();
    size = (props["width"].asFloat() * scale / 54.0);
}

void MeltingObstacle::addSprite()
{
    auto spr = Sprite::create(HorizontalObstacle::centerTexture);
    spr->setAnchorPoint(Vec2::ZERO);
    addChild(spr);
    
    
    auto width = spr->getContentSize().width;
    auto height = spr->getContentSize().height;
    float fAmount = getContentSize().width / width;
    int amount = getContentSize().width / width;
    if(fAmount - amount > 0)
    {
        amount++;
    }
    if(amount > 1)
    {
        spr = Sprite::create(HorizontalObstacle::centerTexture);
        spr->setAnchorPoint(Vec2::ZERO);
        spr->setPosition(Vec2(width, 0));
        spr->setContentSize(Size((amount - 1) * width, height));
        addChild(spr);
    }
    
}
/*void MeltingObstacle::launch()
{
    addIce();
}*/


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
    float delayTime = (0.8f * baseDistance) / 400.0f; //gameHandler->getCurrentPlayerSpeed();
    float appearTime = (0.25f * baseDistance) / 400.0f; //gameHandler->getCurrentPlayerSpeed();
    float disappearTime = (0.10f * baseDistance) / 400.0f;//gameHandler->getCurrentPlayerSpeed();
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
