//
//  BaseLayout.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 18/09/2017.
//
//

#ifndef BaseLayout_hpp
#define BaseLayout_hpp

class BaseLayout : public cocos2d::ui::Layout
{
    typedef cocos2d::ui::Layout super;
    
    cocos2d::EventListenerKeyboard* keyboardListener;
protected:
    bool isTopView();
public:
    virtual bool init() override;
    virtual void setColor(const cocos2d::Color3B& color) override;
    
    virtual void actionBackButton() = 0;
    
};

#endif /* BaseLayout_hpp */
