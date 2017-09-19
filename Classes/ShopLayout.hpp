//
//  ShopLayout.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 02/06/2017.
//
//

#ifndef ShopLayout_hpp
#define ShopLayout_hpp

#include "cocos2d.h"
#include "ui/UILayout.h"
#include "ui/UIButton.h"
#include "ui/UIPageView.h"

#include "Globals.hpp"
#include "SHButton.hpp"

#include "ThemeManager.hpp"
#include "GameHandler.hpp"
#include "Touchable.hpp"

#include "SHShopItem.hpp"
#include "SHShopBonusItem.hpp"

#if defined ADS
#include "PluginIAP/PluginIAP.h"
#endif
class ShopLayout : public cocos2d::ui::Layout
{
private:
    bool bricks;
    typedef cocos2d::ui::Layout super;
    typedef ShopLayout self;
    GameHandler* gameHandler;
    cocos2d::ui::Layout* backTarget;
    
    
    cocos2d::Label* shopLabel;
    void createShopLabel();
    
    SHButton* switchPageButton;
    void createSwitchPageButton();
    
    SHButton* backButton;
    void createBackButton();
    
    cocos2d::Sprite* starIndicator;
    void createStarIndicator();
    
    cocos2d::Label* starLabel;
    void createStarLabel();
    
    cocos2d::Sprite* kielniaIndicator;
    void createKielniaIndicator();
    
    cocos2d::Label* kielniaLabel;
    void createKielniaLabel();
    
    cocos2d::Sprite* brickAtSprite;
    void createBrickAtSprite();
    
    cocos2d::ui::Layout* bricksContainer;
    void createBricksContainer();
    
    cocos2d::ui::ScrollView* scrollingBricks;
    void createScrollingBricks();
    
    cocos2d::ui::Layout* bonusContainer;
    void createBonusContainer();
    
    cocos2d::ui::Button* removeAds;
    void createRemoveAds();
    
    cocos2d::ui::ScrollView* scrollingBonus;
    void createScrollingBonus();
    cocos2d::Label *numberLabel;
    
    cocos2d::ui::Button* restoreButton;
    void createRestore();
    
    cocos2d::Label* removeAdsPriceLabel;
    SHShopBonusItem* kielnia5;
    SHShopBonusItem* kielnia10;
    SHShopBonusItem* kielnia20;
    SHShopBonusItem* kielnia50;
CC_CONSTRUCTOR_ACCESS:
    ShopLayout();
    virtual ~ShopLayout();
public:
    virtual std::string getDescription() const override
    {
        return "ShopLayout";
    }
    void updateUI();
    static ShopLayout* createWithSize(cocos2d::Size size, GameHandler* handler);
    virtual bool initWithSize(cocos2d::Size size, GameHandler* handler);
    void setBackTarget(cocos2d::ui::Layout* back);
    cocos2d::ui::Layout* getBackTarget()
    {
        return backTarget;
    }
    
    void updateSkins();
    virtual void setBonusActive();
    
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent) override;
    void updateProduct(std::string name, std::string updatedValue, float priceValue);
};

#endif /* ShopLayout_hpp */
