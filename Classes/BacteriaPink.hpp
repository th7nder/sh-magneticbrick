//
//  BacteriaPink.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/06/2017.
//
//

#ifndef BacteriaPink_hpp
#define BacteriaPink_hpp


#include "LevelObject.hpp"

class BacteriaPink : public LevelObject
{
private:
    typedef BacteriaPink self;
    typedef LevelObject super;
    
    b2Vec2 velocity;
    float angle;
CC_CONSTRUCTOR_ACCESS:
    BacteriaPink();
public:
    virtual ~BacteriaPink();
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


#endif /* BacteriaPink_hpp */
