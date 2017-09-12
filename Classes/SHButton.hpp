//
//  SHButton.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 14/02/2017.
//
//

#ifndef SHButton_hpp
#define SHButton_hpp

#include "cocos2d.h"
#include "ui/UIButton.h"
#include "GameHandler.hpp"

class SHButton : public cocos2d::ui::Button
{
    GameHandler* gameHandler;
CC_CONSTRUCTOR_ACCESS:
public:
    static SHButton* create(GameHandler* gh, const std::string& normalImage,
                            const std::string& selectedImage = "",
                            const std::string& disableImage = "",
                            TextureResType texType = TextureResType::LOCAL);
    virtual bool init(GameHandler* gh, const std::string& normalImage,
                      const std::string& selectedImage = "",
                      const std::string& disableImage = "",
                      TextureResType texType = TextureResType::LOCAL);
    virtual bool onTouchBegan(cocos2d::Touch* t, cocos2d::Event* unusedEvent) override;
private:
    virtual bool hitTest(const cocos2d::Vec2 &pt, const cocos2d::Camera* camera, cocos2d::Vec3 *p) const override;
};

#endif /* SHButton_hpp */
