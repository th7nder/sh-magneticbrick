//
//  SHShopItem.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 03/06/2017.
//
//

#ifndef SHShopItem_hpp
#define SHShopItem_hpp


#include "cocos2d.h"
#include "ui/UIButton.h"

#include "SHSwitch.hpp"
#include "Globals.hpp"
#include "GameHandler.hpp"


class SHShopItem : public cocos2d::Node
{
    enum State
    {
        Locked = 0,
        Available,
        Current
    };
    
    void updateState();
    State currentState;
    std::string setState();

    typedef cocos2d::Node super;
    GameHandler* gameHandler;
    
    cocos2d::Sprite* spacer;
    void createSpacer();
    
    cocos2d::ui::Button* button;
    void createButton();
    
    cocos2d::Sprite* itemIcon;
    void createIcon(const std::string& icon);
    
    Skin skin;
    int skinId;
    SHShopItem();
public:
    static SHShopItem* create(GameHandler* gameHandler, Skin skin, int id);
    virtual bool init(GameHandler* gameHandler, Skin skin, int id);
    void update();
};



#endif /* SHShopItem_hpp */
