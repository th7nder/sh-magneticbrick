//
//  ShopLayout.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 02/06/2017.
//
//

#include "ShopLayout.hpp"
USING_NS_CC;
ShopLayout::ShopLayout() : backTarget(nullptr), scrollingBricks(nullptr), bricks(true)
{
    
}

ShopLayout::~ShopLayout()
{
    
}

ShopLayout* ShopLayout::createWithSize(cocos2d::Size size, GameHandler* handler)
{
    ShopLayout * ret = new (std::nothrow) ShopLayout();
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

bool ShopLayout::initWithSize(cocos2d::Size size, GameHandler* handler)
{
    if(!super::init()) return false;
    gameHandler = handler;
    
    setContentSize(size);
    createShopLabel();
    createSwitchPageButton();

    createStarIndicator();
    createBackButton();
    createStarLabel();
    
    createKielniaLabel();
    createKielniaIndicator();
    
    createBricksContainer();
    createBonusContainer();

    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
        {
            if(this->getPositionY() == 0 && this->isEnabled() && this->isVisible() && this->getOpacity() >= 255)
            {
                this->gameHandler->onBackFromShop();
            }
        }
    };
    
    auto dispatcher = this->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    if(Globals::getSmallPhone())
    {
        for(const auto& child : getChildren())
        {
            child->setPositionY(child->getPositionY() - 30);
        }
    }


    return true;
}

void ShopLayout::createBricksContainer()
{
    bricksContainer = ui::Layout::create();
    bricksContainer->setContentSize(Size(549, 782));
    bricksContainer->setPosition(Vec2(45, 43));
    addChild(bricksContainer);

    createBrickAtSprite();
    createScrollingBricks();
}


void ShopLayout::createBonusContainer()
{
    bonusContainer = ui::Layout::create();
    bonusContainer->setContentSize(Size(549, 782));
    bonusContainer->setPosition(Vec2(45, 43));
    bonusContainer->setVisible(false); // TO DO
    addChild(bonusContainer);
    
    
    createRemoveAds();
    createScrollingBonus();
    
}


void ShopLayout::createRemoveAds()
{
    removeAds = ui::Button::create(Globals::resources["shop_removeads"]);
    removeAds->setPosition(Vec2(275, 716));
    
    auto label = Label::createWithTTF("REMOVE ADS", Globals::gameFontBold, 41.0);
    label->setPosition(Vec2(183, 67));
    label->setColor(Color3B(0, 0, 0));
    removeAds->addChild(label);
    
    removeAdsPriceLabel = Label::createWithTTF(StringUtils::format("$%.2f", 2.99), Globals::gameFont, 41.0);
    removeAdsPriceLabel->setPosition(Vec2(444, 67));
    removeAdsPriceLabel->setColor(Color3B(0, 0, 0));
    removeAds->addChild(removeAdsPriceLabel);
    
    if(gameHandler->getRemoveAds())
    {
        removeAds->setVisible(false);
        removeAds->setEnabled(false);
    } else {
        removeAds->setVisible(true);
        removeAds->setEnabled(true);
    }
    
    createRestore();

    

#if defined ADS
    removeAds->addClickEventListener([this](Ref* sender){
        if(((ui::Button*)sender)->isEnabled())
        {
            sdkbox::IAP::purchase("remove_ads");
            playClickSound();
        }

    });
#endif
    
    
    bonusContainer->addChild(removeAds);
}


void ShopLayout::createScrollingBonus()
{
    const float boxHeight = 142;
    scrollingBonus = ui::ScrollView::create();
    scrollingBonus->setContentSize(Size(bricksContainer->getContentSize().width, 603)); // 603
    scrollingBonus->setPosition(Vec2::ZERO);
    scrollingBonus->setBounceEnabled(true);
    scrollingBonus->setScrollBarEnabled(false);
    scrollingBonus->setInnerContainerSize(Size(bricksContainer->getContentSize().width, 4 * boxHeight));
    scrollingBonus->setPositionY(-50);
    if(gameHandler->getRemoveAds())
    {
        scrollingBonus->setPositionY(40);
    }
    bonusContainer->addChild(scrollingBonus);
    
    const float innerHeight = 4 * boxHeight;
    SHShopBonusItem* shopItem = SHShopBonusItem::create(gameHandler, "shop_kielnia5_", 0.99, "kielnia5");
    shopItem->setPosition(Vec2(0, innerHeight - boxHeight));
    scrollingBonus->addChild(shopItem);
    
    kielnia5 = shopItem;
    
    shopItem = SHShopBonusItem::create(gameHandler, "shop_kielnia10_", 1.99, "kielnia10");
    shopItem->setPosition(Vec2(0, innerHeight - boxHeight * 2));
    scrollingBonus->addChild(shopItem);
    
    kielnia10 = shopItem;
    
    shopItem = SHShopBonusItem::create(gameHandler, "shop_kielnia20_", 2.99, "kielnia20");
    shopItem->setPosition(Vec2(0, innerHeight - boxHeight * 3));
    scrollingBonus->addChild(shopItem);
    
    kielnia20 = shopItem;
    
    shopItem = SHShopBonusItem::create(gameHandler, "shop_kielnia50_", 4.99, "kielnia50");
    shopItem->setPosition(Vec2(0, innerHeight - boxHeight * 4));
    scrollingBonus->addChild(shopItem);

    kielnia50 = shopItem;
    
    
}

void ShopLayout::setBackTarget(cocos2d::ui::Layout *back)
{
    backTarget = back;
}

void ShopLayout::updateUI()
{
    auto color = gameHandler->getLastTheme().getUIColor();
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    shopLabel->setColor(color);
    
    int kielniaCount = gameHandler->getKielnias();
    kielniaLabel->setString(StringUtils::format("%d", kielniaCount));
    if(kielniaCount > 99)
    {
        kielniaLabel->setPositionX(392);
    }
    else if(kielniaCount > 9)
    {
        kielniaLabel->setPositionX(410);
    }
    else
    {
        kielniaLabel->setPositionX(425);
    }

    kielniaLabel->setColor(color);
    restoreButton->loadTextureNormal(Globals::resources["shop_restore_" + gameHandler->getLastTheme().getElementsColor()]);
    

    int starCount = gameHandler->getStarCount();
    if(starCount > 99)
    {
        starLabel->setPositionX(148);
    } else if(starCount > 9)
    {
        starLabel->setPositionX(165);
    }
    else
    {
        starLabel->setPositionX(177);
    }

    starLabel->setString(StringUtils::format("%d", starCount));
    starLabel->setColor(color);
    

    
    if(gameHandler->getRemoveAds())
    {
        scrollingBonus->setPositionY(40);
        restoreButton->setPositionY(585 + removeAds->getContentSize().height);
    } else {
        scrollingBonus->setPositionY(-50);
        restoreButton->setPositionY(585);
    }

    
    int step = -1;
    for(int i = 1; i < 16; i++)
    {
        if(!gameHandler->brickAtStepUnlocked(i))
        {
            step = Globals::bricksSteps[i];
            break;
        }
    }
    
    numberLabel->setString(StringUtils::format("%d", step));
    
    
    backButton->loadTextureNormal(Globals::resources["icon_back_right_" + strColor]);
    if(bricks)
    {
        switchPageButton->loadTextureNormal(Globals::resources["shop_tab_bricks_" + strColor]);
    }
    else
    {
        switchPageButton->loadTextureNormal(Globals::resources["shop_tab_bonus_" + strColor]);
    }
    
    starIndicator->setTexture(Globals::resources["shop_star_indicator_" + strColor]);
    kielniaIndicator->setTexture(Globals::resources["shop_kielnia_indicator_" + strColor]);
    
    auto skins = SkinManager::getInstance()->getSkins();
    

    
    scrollingBricks->removeFromParent();
    createScrollingBricks();
    
    if(gameHandler->getRemoveAds())
    {
        removeAds->setVisible(false);
        removeAds->setEnabled(false);
    } else {
        removeAds->setVisible(true);
        removeAds->setEnabled(true);
    }

    
    /*for(const auto& child : scrollingBricks->getChildren())
    {
        SHShopItem* item = dynamic_cast<SHShopItem*>(child);
        item->update();
    }*/
    
    for(const auto& child : scrollingBonus->getChildren())
    {
        SHShopBonusItem* item = dynamic_cast<SHShopBonusItem*>(child);
        item->update();
    }
}

void ShopLayout::createShopLabel()
{
    const Vec2 pos(320, 1070);
    shopLabel = Label::createWithTTF("SHOP", Globals::gameFont, 51.0);
    shopLabel->setColor(gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0));
    shopLabel->setPosition(pos);
    addChild(shopLabel);
}

void ShopLayout::createSwitchPageButton()
{
    const Vec2 pos(320, 889);
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    
    switchPageButton = SHButton::create(gameHandler, Globals::resources["shop_tab_bricks_" + strColor]);
    switchPageButton->setPosition(pos);
    switchPageButton->addClickEventListener([this](Ref* sender){
        playClickSound();
        if(bricks)
        {
            switchPageButton->loadTextureNormal(Globals::resources["shop_tab_bonus_" + gameHandler->getLastTheme().getElementsColor()]);
            bricksContainer->setVisible(false);
            bonusContainer->setVisible(true);
        }
        else
        {
            switchPageButton->loadTextureNormal(Globals::resources["shop_tab_bricks_" + gameHandler->getLastTheme().getElementsColor()]);
            bricksContainer->setVisible(true);
            bonusContainer->setVisible(false);
        }
        bricks = !bricks;
    });
    addChild(switchPageButton);
    
}

void ShopLayout::setBonusActive()
{
    if(bricks)
    {
        auto strColor = gameHandler->getLastTheme().getElementsColor();
        switchPageButton->loadTextureNormal(Globals::resources["shop_tab_bonus_" + strColor]);
        bricksContainer->setVisible(false);
        bonusContainer->setVisible(true);
        bricks = !bricks;
    }
}

void ShopLayout::createBackButton()
{
    const Vec2 pos(586, 1070);
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    backButton = SHButton::create(gameHandler, Globals::resources["icon_back_right_" + strColor]);
    backButton->setPosition(pos);
    addChild(backButton);
    
    backButton->addClickEventListener([this](Ref* sender)
                                      {
                                          this->gameHandler->onBackFromShop();
                                      });
    
}


void ShopLayout::createStarIndicator()
{
    const Vec2 pos(228, 985);
    starIndicator = Sprite::create(Globals::resources["shop_star_indicator_" +gameHandler->getLastTheme().getElementsColor()]);
    starIndicator->setPosition(pos);
    addChild(starIndicator);
}


void ShopLayout::createStarLabel()
{
    // 177 165 148
    Vec2 pos(177, 984);
    int starCount = gameHandler->getStarCount();
    if(starCount > 9)
    {
        pos.x = 165;
    }
    if(starCount > 99)
    {
        pos.x = 148;
    }
    starLabel = Label::createWithTTF(StringUtils::format("%d", starCount), Globals::gameFont, 51.0);
    starLabel->setColor(gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0));
    starLabel->setPosition(pos);
    addChild(starLabel);
}


void ShopLayout::createKielniaIndicator()
{
    const Vec2 pos(477, 985);
    kielniaIndicator = Sprite::create(Globals::resources["shop_kielnia_indicator_" +gameHandler->getLastTheme().getElementsColor()]);
    kielniaIndicator->setPosition(pos);
    addChild(kielniaIndicator);
}


void ShopLayout::createKielniaLabel()
{
    Vec2 pos(425, 984);
    int kielniaCount = gameHandler->getKielnias();
    // 425 410 392
    if(kielniaCount > 9)
    {
        pos.x = 410;
    }
    if(kielniaCount > 99)
    {
        pos.x = 392;
    }
    kielniaLabel = Label::createWithTTF(StringUtils::format("%d", kielniaCount), Globals::gameFont, 51.0);
    kielniaLabel->setColor(gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0));
    kielniaLabel->setPosition(pos);
    addChild(kielniaLabel);
}


void ShopLayout::createBrickAtSprite()
{
    //const Vec2 pos(320, 730);
// 2 cyfry + 24 px w prawo gwiazdka ||// -2 px w lewo label
// 3 cyfry + 48 px w prawo gwiazdka || -2px w lewo
    brickAtSprite = Sprite::create(Globals::resources["shop_brick_at"]);
    const Vec2 pos(bricksContainer->getContentSize().width / 2, bricksContainer->getContentSize().height - brickAtSprite->getContentSize().height / 2);
    brickAtSprite->setPosition(pos);
    bricksContainer->addChild(brickAtSprite);
    
    auto label = Label::createWithTTF("NEW BRICK AT", Globals::gameFont, 41.0);
    label->setColor(Color3B(0, 0, 0));
    label->setPosition(Vec2(pos.x, pos.y + 50));
    bricksContainer->addChild(label);
    
    
    auto star = Sprite::create(Globals::resources["shop_bigstar_indicator_white"]);
    star->setColor(Color3B::BLACK);
    star->setPosition(Vec2(pos.x + 32 + 24, pos.y - 23));
    bricksContainer->addChild(star);
    
    int step = -1;
    for(int i = 1; i < 16; i++)
    {
        if(!gameHandler->brickAtStepUnlocked(i))
        {
            step = Globals::bricksSteps[i];
            break;
        }
    }
    numberLabel = Label::createWithTTF(StringUtils::format("%d", step), Globals::gameFontBold, 84.0);
    numberLabel->setColor(Color3B(0, 0, 0));
    numberLabel->setPosition(Vec2(pos.x - 46 - 2, pos.y - 23));
    bricksContainer->addChild(numberLabel);
    
    

}

void ShopLayout::createScrollingBricks()
{
    
    const float boxHeight = 142;
    auto sm = SkinManager::getInstance();
    auto skins = sm->getSkins();
    const unsigned long skinsAmount = skins.size();
    float innerHeight = skinsAmount * boxHeight;
    if(innerHeight < 550)
    {
        innerHeight = 550;
    }
    scrollingBricks = ui::ScrollView::create();
    scrollingBricks->setContentSize(Size(bricksContainer->getContentSize().width, 550));
    scrollingBricks->setPosition(Vec2::ZERO);
    scrollingBricks->setBounceEnabled(true);
    scrollingBricks->setScrollBarEnabled(false);
    scrollingBricks->setInnerContainerSize(Size(bricksContainer->getContentSize().width, innerHeight));
    bricksContainer->addChild(scrollingBricks);
    
    
    int lastAvailable = 1;
    for(int i = 1; i < skins.size(); i++)
    {
        if(skins[i].getAccess())
        {
            std::swap(skins[lastAvailable++], skins[i]);
            if(lastAvailable >= skins.size())
            {
                break;
            }
        }
    }
    
    int i = 1;
    for(const auto& skin : skins)
    {
        SHShopItem* shopItem = SHShopItem::create(gameHandler, skin, skin.getId());
        shopItem->setPosition(Vec2(0, innerHeight - boxHeight * i));
        scrollingBricks->addChild(shopItem);
        i++;
    }
    
}

void ShopLayout::updateSkins()
{
    auto children = scrollingBricks->getChildren();
    for(const auto& child : children)
    {
        SHShopItem* item = static_cast<SHShopItem*>(child);
        item->update();
    }
}

void ShopLayout::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    
    if(isEnabled())
    {
        if(touch->getDelta().x < -50)
        {
            gameHandler->onBackFromShop();
        }
    }
    
}

void ShopLayout::createRestore()
{
    restoreButton = ui::Button::create(Globals::resources["shop_restore_" + gameHandler->getLastTheme().getElementsColor()]);

    restoreButton->setPosition(Vec2(275, 585));
    if(gameHandler->getRemoveAds())
    {
        restoreButton->setPositionY(585 + removeAds->getContentSize().height);
    }
#if defined ADS
    restoreButton->addClickEventListener([this](Ref* sender){
        sdkbox::IAP::restore();
    });
#endif
    bonusContainer->addChild(restoreButton);
}

void ShopLayout::updateProduct(std::string name, std::string updatedValue, float priceValue){
    if(name == "remove_ads")
    {
        removeAdsPriceLabel->setString(updatedValue);
    }
    else if(name == "kielnia5")
    {
        kielnia5->updateValue(updatedValue, priceValue);
    }
    else if(name == "kielnia10")
    {
        kielnia10->updateValue(updatedValue, priceValue);
    }
    else if(name == "kielnia20")
    {
        kielnia20->updateValue(updatedValue, priceValue);
    }
    else if(name == "kielnia50")
    {
        kielnia50->updateValue(updatedValue, priceValue);
    }
    else if(name == "unlock1")
    {
        int i = 1;
        gameHandler->setThemePrice(i, updatedValue);
    }
    else if(name == "unlock2")
    {
        int i = 2;
        gameHandler->setThemePrice(i, updatedValue);
    }
    else if(name == "unlock3")
    {
        int i = 3;
        gameHandler->setThemePrice(i, updatedValue);
    }
    else if(name == "unlock4")
    {
        int i = 4;
        gameHandler->setThemePrice(i, updatedValue);
    }
    else if(name == "unlock5")
    {
        int i = 5;
        gameHandler->setThemePrice(i, updatedValue);
    }
    else if(name == "unlock6")
    {
        int i = 6;
        gameHandler->setThemePrice(i, updatedValue);
    }
    else if(name == "unlock7")
    {
        int i = 7;
        gameHandler->setThemePrice(i, updatedValue);
    }
    else if(name == "unlock8")
    {
        int i = 8;
        gameHandler->setThemePrice(i, updatedValue);
        
    }
    else if(name == "unlock9")
    {
        int i = 9;
        gameHandler->setThemePrice(i, updatedValue);
    }

}
//320 730

