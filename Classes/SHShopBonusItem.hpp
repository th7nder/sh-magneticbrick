//
//  SHShopBonusItem.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 03/06/2017.
//
//

#ifndef SHShopBonusItem_hpp
#define SHShopBonusItem_hpp

#include "cocos2d.h"
#include "ui/UIButton.h"

#include "SHSwitch.hpp"
#include "Globals.hpp"
#include "GameHandler.hpp"

#if defined ADS
#include "PluginIAP/PluginIAP.h"
#endif

class SHShopBonusItem : public cocos2d::Node
{
    typedef cocos2d::Node super;
    GameHandler* gameHandler;
    
    cocos2d::Sprite* spacer;
    void createSpacer();
    
    cocos2d::ui::Button* button;
    void createButton();
    
    cocos2d::Sprite* itemIcon;
    void createIcon(const std::string& icon);
    
    cocos2d::Label* money;
    void createMoney(const float price);
    std::string strIcon;
    
    std::string marketName;
    

public:
    static SHShopBonusItem* create(GameHandler* gameHandler, const std::string& icon, const float price, const std::string& marketName);
    virtual bool init(GameHandler* gameHandler, const std::string& icon, const float price, const std::string& marketName);
    virtual void update();
    void updateValue(std::string value, float moneyValue);
    
};


#endif /* SHShopBonusItem_hpp */
