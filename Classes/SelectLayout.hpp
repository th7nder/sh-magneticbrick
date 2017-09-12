//
//  SelectLayout.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 13/03/2017.
//
//

#ifndef SelectLayout_hpp
#define SelectLayout_hpp

#include "cocos2d.h"
#include "ui/UIScrollView.h"

#include "ThemeManager.hpp"
#include "GameHandler.hpp"
#include "SHLevel.hpp"

class SelectLayout : public cocos2d::ui::ScrollView

{
private:
    typedef cocos2d::ui::ScrollView super;

    
    GameHandler* gameHandler;
    cocos2d::EventListenerKeyboard* keyboardListener;
CC_CONSTRUCTOR_ACCESS:
    SelectLayout();
    virtual ~SelectLayout();
    void scrollChildren(const cocos2d::Vec2& deltaMove) override;

public:
    virtual std::string getDescription() const override
    {
        return "SelectLayout";
    }
    static SelectLayout* createWithSize(cocos2d::Size size, GameHandler* handler);
    virtual bool initWithSize(cocos2d::Size size, GameHandler* handler);
    void updateLevel(int theme, int level);
    void updateTheme(int theme);
};


#endif /* SelectLayout_hpp */
