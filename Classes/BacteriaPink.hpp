//
//  BacteriaPink.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/06/2017.
//
//

#ifndef BacteriaPink_hpp
#define BacteriaPink_hpp


#include "DynamicLevelObject.hpp"
#include "Globals.hpp"

class BacteriaPink : public DynamicLevelObject
{
private:
    typedef BacteriaPink self;
    typedef LevelObject super;
    
    b2Vec2 velocity;
    float angle;
public:
    BacteriaPink();
    virtual ~BacteriaPink();
    virtual void setProperties(cocos2d::ValueMap& props) override;
    virtual void addSprite() override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* otherBody) override {return true;};
    
    virtual void initPhysics(b2World* world) override;
    
    virtual void launch() override;
    
    
};


#endif /* BacteriaPink_hpp */
