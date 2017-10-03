//
//  DynamicLevelObject.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/09/2017.
//
//

#ifndef DynamicLevelObject_hpp
#define DynamicLevelObject_hpp

#include "LevelObject.hpp"

class DynamicLevelObject : public LevelObject
{
private:
    typedef DynamicLevelObject self;
    typedef LevelObject super;
protected:
    cocos2d::Vec2 startPosition;
    cocos2d::Vec2 previousPosition;
public:
    DynamicLevelObject();
    virtual bool isDynamic() const override;
    virtual void launch() = 0;
    virtual void savePreviousStates();
    virtual void interpolate(float alpha);
    virtual void setProperties(cocos2d::ValueMap& props) override;
    
};

#endif /* DynamicLevelObject_hpp */
