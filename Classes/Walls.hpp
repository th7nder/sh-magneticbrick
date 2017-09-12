//
//  Walls.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 26/05/2017.
//
//

#ifndef Walls_hpp
#define Walls_hpp
#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "LevelObject.hpp"
#include "GameHandler.hpp"

class Walls : public LevelObject
{
private:
    typedef LevelObject super;
    typedef Walls self;
CC_CONSTRUCTOR_ACCESS:
    Walls();
    b2Body* rightBody;
    float speed;
    
public:
    virtual ~Walls();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    virtual void setProperties(ValueMap& props) override;
    virtual void initPhysics(b2World* world) override;
    b2Body* createDestroyer(b2World* world, float x, float y);
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override {return true;}
    b2Body* getRightBody() {return rightBody;}
    
};

#endif /* Walls_hpp */
