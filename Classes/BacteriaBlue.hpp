//
//  BacteriaBlue.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/06/2017.
//
//

#ifndef BacteriaBlue_hpp
#define BacteriaBlue_hpp

#include "DynamicLevelObject.hpp"
#include "Globals.hpp"

class BacteriaBlue : public DynamicLevelObject
{
private:
    typedef BacteriaBlue self;
    typedef DynamicLevelObject super;
    
    b2Vec2 velocity;
    float angle;
public:
    BacteriaBlue();
    virtual ~BacteriaBlue();
    
    virtual void setProperties(cocos2d::ValueMap& props) override;
    virtual void addSprite() override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* otherBody) override {return true;};
    
    virtual void initPhysics(b2World* world) override;
    
    virtual void launch() override;
    
    
};

#endif /* BacteriaBlue_hpp */
