//
//  KielniaLayout.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 17/06/2017.
//
//

#ifndef KielniaLayout_hpp
#define KielniaLayout_hpp


#include "cocos2d.h"

#include "ui/UILayout.h"
#include "ui/UIButton.h"
#include "ui/UIPageView.h"

#include "Globals.hpp"
#include "SHButton.hpp"

#include "ThemeManager.hpp"
#include "GameHandler.hpp"

class KielniaLayout : public cocos2d::ui::Layout
{
private:
    typedef cocos2d::ui::Layout super;
    typedef KielniaLayout self;
    GameHandler* gameHandler;
    
    cocos2d::Sprite* shine;
    cocos2d::Sprite* timerSprite;
    cocos2d::ProgressTimer* timer;
    cocos2d::Sprite* body;
    SHButton* sure;
    
    cocos2d::Label* noThanksLabel;
    SHButton* noThanks;
    
    cocos2d::Label* continueLabel;
    cocos2d::Label* remainingLabel;
    cocos2d::Label* kielniasRemaining;
    cocos2d::Label* kielniasRemainingSecond;
    
    cocos2d::Label* removeLabel;
    
    cocos2d::Label* removeSecondLabel;
    
CC_CONSTRUCTOR_ACCESS:
    KielniaLayout();
    virtual ~KielniaLayout();
public:
    virtual std::string getDescription() const override
    {
        return "KielniaLayout";
    }
    void launchTimer();
    static KielniaLayout* createWithSize(cocos2d::Size size, cocos2d::Color3B color, int kielnias, GameHandler* handler);
    virtual bool initWithSize(cocos2d::Size size, cocos2d::Color3B& color, int kielnias, GameHandler* handler);
    virtual void setOpacity(GLubyte opacity) override;
    
    void updateUI(cocos2d::Color3B color, int kielnias);
    virtual void setEnabled(bool enabled) override;
    
};

#endif /* KielniaLayout_hpp */
