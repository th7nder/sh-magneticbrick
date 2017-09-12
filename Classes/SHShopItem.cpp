//
//  SHShopItem.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 03/06/2017.
//
//

#include "SHShopItem.hpp"
USING_NS_CC;

SHShopItem::SHShopItem()
{

}

SHShopItem* SHShopItem::create(GameHandler* gameHandler, Skin skin, int id)
{
    SHShopItem * ret = new (std::nothrow) SHShopItem();
    if (ret && ret->init(gameHandler, skin, id))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}


bool SHShopItem::init(GameHandler* handler, Skin skin, int id)
{
    if(!super::init()) return false;
    gameHandler = handler;
    skinId = id;
    this->skin = skin;
    setContentSize(Size(549, 142));
    
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    createSpacer();
    createButton();
    createIcon(currentState == Locked ? Globals::resources["shop_question_" + strColor] : skin.getIconPath());
    
    return true;
}



void SHShopItem::createSpacer()
{
    
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    spacer = Sprite::create(Globals::resources["shop_line_" + strColor]);
    spacer->setAnchorPoint(Vec2::ZERO);
    spacer->setPosition(Vec2(0, 140));
    addChild(spacer);
}

std::string SHShopItem::setState()
{
    std::string buttonIcon;
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    if(skin.getAccess())
    {
        if(gameHandler->getCurrentSkinId() == skinId)
        {
            buttonIcon = Globals::resources["shop_current_" + strColor];
            currentState = Current;
        }
        else
        {
            buttonIcon = Globals::resources["shop_use_" + strColor];
            currentState = Available;
        }
    }
    else
    {
        currentState = Locked;
        buttonIcon = Globals::resources["shop_locked_" + strColor];
    }
    
    return buttonIcon;
}

void SHShopItem::updateState()
{
    std::string buttonIcon;
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    switch(currentState)
    {
        case Locked:
        {
            buttonIcon = Globals::resources["shop_locked_" + strColor];
        }
        case Available:
        {
            buttonIcon = Globals::resources["shop_use_" + strColor];
        }
            
        case Current:
        {
            buttonIcon = Globals::resources["shop_current_" + strColor];
        }
    }
    button->loadTextureNormal(buttonIcon);
}

void SHShopItem::update()
{
    button->loadTextureNormal(setState());
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    spacer->setTexture(Globals::resources["shop_line_" + strColor]);
    
    itemIcon->setTexture(currentState == Locked ? Globals::resources["shop_question_" + strColor] : skin.getIconPath());
    
}

void SHShopItem::createButton()
{
    button = ui::Button::create(setState());
    button->setPosition(Vec2(356, 70));
    button->addClickEventListener([this](Ref* sender){
        if(currentState == Available)
        {
            playClickSound();
            currentState = Current;
            gameHandler->setCurrentSkinId(skinId);
            gameHandler->onSkinUsed();
            updateState();
        } else
        {
            auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
            sae->playEffect(Globals::resources["effect_denied"].c_str());
        }
    });
    
    addChild(button);
}


void SHShopItem::createIcon(const std::string &icon)
{
    itemIcon = Sprite::create(icon);
    itemIcon->setPosition(Vec2(177, 70));
    addChild(itemIcon);
}
