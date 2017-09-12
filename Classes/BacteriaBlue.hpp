//
//  BacteriaBlue.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/06/2017.
//
//

#ifndef BacteriaBlue_hpp
#define BacteriaBlue_hpp

#include "LevelObject.hpp"

class BacteriaBlue : public LevelObject
{
private:
    typedef BacteriaBlue self;
    typedef LevelObject super;
    
    b2Vec2 velocity;
    float angle;
CC_CONSTRUCTOR_ACCESS:
    BacteriaBlue();
public:
    virtual ~BacteriaBlue();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    virtual void setProperties(ValueMap& props) override;
    virtual void addSprite() override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* otherBody) override {return true;};
    
    virtual void initPhysics(b2World* world) override;
    virtual void interpolate(float alpha) override;
    virtual void savePreviousStates() override;
    
    virtual void launch() override;
    
    
};

#endif /* BacteriaBlue_hpp */
