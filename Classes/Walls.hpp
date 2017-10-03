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
#include "DynamicLevelObject.hpp"

class Walls : public DynamicLevelObject
{
private:
    typedef LevelObject super;
    typedef Walls self;
CC_CONSTRUCTOR_ACCESS:
    float speed;
    b2Body* rightBody;
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
    
    
    virtual void interpolate(float alpha) override;
    virtual void savePreviousStates() override;
    virtual void launch() override;
};

#endif /* Walls_hpp */
