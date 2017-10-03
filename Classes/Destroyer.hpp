//
//  Destroyer.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 27/09/2017.
//

#ifndef Destroyer_hpp
#define Destroyer_hpp
#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "DynamicLevelObject.hpp"

class Destroyer : public DynamicLevelObject
{
private:
    typedef LevelObject super;
    typedef Destroyer self;
CC_CONSTRUCTOR_ACCESS:
    float speed;
public:
    virtual std::string getDescription() const override
    {
        return "Destroyer";
    }
    Destroyer();
    virtual ~Destroyer();
    virtual void setProperties(cocos2d::ValueMap& props) override;
    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override;
    
    
    virtual void interpolate(float alpha) override;
    virtual void savePreviousStates() override;
    virtual void launch() override;
};

#endif /* Destroyer_hpp */
