//
//  SHShopBonusItem.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 03/06/2017.
//
//

#include "SHShopBonusItem.hpp"
USING_NS_CC;
SHShopBonusItem* SHShopBonusItem::create(GameHandler* gameHandler, const std::string& icon, const float price, const std::string& marketName)
{
    SHShopBonusItem * ret = new (std::nothrow) SHShopBonusItem();
    if (ret && ret->init(gameHandler, icon, price, marketName))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}


bool SHShopBonusItem::init(GameHandler* handler, const std::string &icon, const float price, const std::string& marketName)
{
    if(!super::init()) return false;
    gameHandler = handler;
    this->marketName = marketName;
    setContentSize(Size(549, 142));
    
    createSpacer();
    createButton();
    strIcon = icon;
    createIcon(Globals::resources[icon + gameHandler->getLastTheme().getElementsColor()]);
    createMoney(price);
    return true;
}



void SHShopBonusItem::createSpacer()
{
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    spacer = Sprite::create(Globals::resources["shop_line_" + strColor]);
    spacer->setAnchorPoint(Vec2::ZERO);
    spacer->setPosition(Vec2(0, 140));
    addChild(spacer);
}

void SHShopBonusItem::createButton()
{
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    button = ui::Button::create(Globals::resources["shop_buy_" + strColor]);
    button->setPosition(Vec2(274, 70));
    
#if defined ADS
    button->addClickEventListener([this](Ref* sender){
        sdkbox::IAP::purchase(marketName);
        playClickSound();
    });
#endif
    addChild(button);

}

void SHShopBonusItem::updateValue(std::string value, float moneyValue)
{

    if(moneyValue > 9.99)
    {
        money->removeFromParent();
        createMoney(9.99);
    }
    
    money->setString(value);
}


void SHShopBonusItem::createIcon(const std::string &icon)
{
    itemIcon = Sprite::create(icon);
    itemIcon->setPosition(Vec2(100, 70));
    addChild(itemIcon);
    

}

void SHShopBonusItem::createMoney(const float price)
{
    money = Label::createWithTTF(StringUtils::format("$%.2f", price), Globals::gameFont, price > 9.9 ? 36.0 : 41.0);
    money->setPosition(Vec2(446, 70));
    money->setColor(gameHandler->getLastTheme().getUIColor());
    addChild(money);
}

void SHShopBonusItem::update()
{
    money->setColor(gameHandler->getLastTheme().getUIColor());
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    spacer->setTexture(Globals::resources["shop_line_" + strColor]);
    button->loadTextureNormal(Globals::resources["shop_buy_" + strColor]);
    itemIcon->setTexture(Globals::resources[strIcon + strColor]);
}
