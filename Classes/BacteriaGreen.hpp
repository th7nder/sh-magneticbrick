//
//  BacteriaGreen.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/06/2017.
//
//

#ifndef BacteriaGreen_hpp
#define BacteriaGreen_hpp

#include "DynamicLevelObject.hpp"
#include "Globals.hpp"
class BacteriaGreen : public DynamicLevelObject
{
private:
    typedef BacteriaGreen self;
    typedef DynamicLevelObject super;
    
    b2Vec2 velocity;
    float angle;
public:
    BacteriaGreen();
    virtual ~BacteriaGreen();
    virtual void setProperties(cocos2d::ValueMap& props) override;
    virtual void addSprite() override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* otherBody) override {return true;};
    
    virtual void initPhysics(b2World* world) override;
    
    virtual void launch() override;
};


#endif /* BacteriaGreen_hpp */
