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

class Walls : public LevelObject
{
private:
    typedef LevelObject super;
    typedef Walls self;
CC_CONSTRUCTOR_ACCESS:
    b2Body* rightBody;
    float speed;
    
public:
    virtual std::string getDescription() const override
    {
        return "Walls";
    }
    Walls();
    virtual ~Walls();
    virtual void setProperties(cocos2d::ValueMap& props) override;
    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override;
    
    b2Body* createDestroyer(b2World* world, const cocos2d::Vec2& pos);
    b2Body* getRightBody();
    
};

#endif /* Walls_hpp */
