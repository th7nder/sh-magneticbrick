//
//  PopupLayout.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 08/06/2017.
//
//

#ifndef PopupLayout_hpp
#define PopupLayout_hpp

#include "cocos2d.h"
#include "GameHandler.hpp"
#include "SHButton.hpp"
#include "ui/UILayout.h"

#if defined ADS
#include "PluginIAP/PluginIAP.h"
#endif

class PopupLayout : public cocos2d::ui::Layout
{
    typedef cocos2d::ui::Layout super;
    typedef PopupLayout self;
    
    GameHandler* gameHandler;
    PopupLayout();
    
    cocos2d::Sprite* main;
    void createMain();
    cocos2d::ui::Button* cancel;
    void createCancel();
    cocos2d::ui::Button* buy;
    void createBuy();
    int themeId;
    int price;
    
    cocos2d::Label* priceLabel;
    void createPriceLabel();
    
    cocos2d::Label* priceDollarsLabel;
    void createPriceDollarsLabel();
    
    cocos2d::Sprite* star;
    void createStar();
public:
    virtual std::string getDescription() const override
    {
        return "PopupLayout";
    }
    virtual ~PopupLayout();
    static PopupLayout* createWithSize(cocos2d::Size size, GameHandler* handler);
    virtual bool initWithSize(cocos2d::Size size, GameHandler* handler);
    virtual void setPriceAndTheme(int price, int themeId);
    
};


#endif /* PopupLayout_hpp */
