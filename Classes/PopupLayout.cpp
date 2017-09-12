//
//  PopupLayout.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 08/06/2017.
//
//

#include "PopupLayout.hpp"
USING_NS_CC;

PopupLayout::PopupLayout() : main(nullptr), cancel(nullptr), buy(nullptr)
{
    
}

PopupLayout::~PopupLayout()
{
    
}

PopupLayout* PopupLayout::createWithSize(cocos2d::Size size, GameHandler* handler)
{
    PopupLayout * ret = new (std::nothrow) PopupLayout();
    if (ret && ret->initWithSize(size, handler))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool PopupLayout::initWithSize(cocos2d::Size size, GameHandler* handler)
{
    if(!super::init()) return false;
    gameHandler = handler;
    setContentSize(size);
    
    createMain();
    createCancel();
    createBuy();
  
    return true;
}

void PopupLayout::createMain()
{
    const Vec2 pos(320, 644);
    main = Sprite::create(Globals::resources["popup_main"]);
    main->setPosition(pos);
    addChild(main);
    
    createPriceLabel();
    createStar();
    createPriceDollarsLabel();
}


void PopupLayout::createCancel()
{
    const Vec2 pos(184, 351);
    cancel = ui::Button::create(Globals::resources["popup_cancel"]);
    cancel->setPosition(pos);
    cancel->addClickEventListener([this](Ref* sender){
        this->gameHandler->onPopupCancelled();
    });
    addChild(cancel);
}

void PopupLayout::createBuy()
{
    const Vec2 pos(455, 351);
    buy = ui::Button::create(Globals::resources["popup_buy"]);
    buy->setPosition(pos);
    addChild(buy);
    
#if defined ADS
    buy->addClickEventListener([this](Ref* sender){
        sdkbox::IAP::purchase(StringUtils::format("unlock%d", this->themeId).c_str());
    });
#endif
}

void PopupLayout::createPriceLabel()
{
    priceLabel = Label::createWithTTF("69", Globals::gameFont, 80);
    priceLabel->setColor(Color3B(0, 0, 0));
    priceLabel->setPosition(Vec2(276, 714));
    addChild(priceLabel);
}


void PopupLayout::createStar()
{
    star = Sprite::create(Globals::resources["icon_star_collect_black"]);
    star->setPosition(Vec2(343, 714));
    addChild(star);
}

void PopupLayout::setPriceAndTheme(int price, int themeId)
{
    this->themeId = themeId;
    this->price = price;
    
    priceLabel->setString(StringUtils::format("%d", price));
    priceDollarsLabel->setString(gameHandler->getThemePrice(themeId));
    if(price < 10)
    {
        star->setPositionX(343);
    }
    else if(price < 100)
    {
        star->setPositionX(371);
    }
    else
    {
        star->setPositionX(398);
    }
    // to do
}


void PopupLayout::createPriceDollarsLabel()
{
    priceDollarsLabel = Label::createWithTTF("$1.99", Globals::gameFont, 80);
    priceDollarsLabel->setColor(Color3B(0, 0, 0));
    priceDollarsLabel->setPosition(Vec2(320, 524));
    addChild(priceDollarsLabel);
}
