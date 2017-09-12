//
//  Switch.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 02/02/2017.
//
//

#ifndef Switch_hpp
#define Switch_hpp

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Globals.hpp"
#include "LevelObject.hpp"
#include "Laser.hpp"
#include "SimpleAudioEngine.h"


class Switch : public LevelObject
{
private:
    typedef LevelObject super;
    typedef Switch self;
    enum Side
    {
        NotSet = 0,
        Right,
        Left
    };
    
    Side side;
    Sprite* button;
    b2Body* buttonBody;
    b2Body* underBody;
    Size buttonSize;
    
    b2Body* createUnderbody(b2World* world, float x, float y, float width);
CC_CONSTRUCTOR_ACCESS:
    Switch();
    virtual ~Switch();
public:
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void setProperties(ValueMap& props) override;
    virtual void addSprite() override;
    std::string target;
    
    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override;
};

#endif /* Switch_hpp */
