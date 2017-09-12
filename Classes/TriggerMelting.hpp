//
//  TriggerMelting.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 01/06/2017.
//
//

#ifndef TriggerMelting_hpp
#define TriggerMelting_hpp

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Globals.hpp"
#include "LevelObject.hpp"
#include "MeltingObstacle.hpp"
#include "SimpleAudioEngine.h"


class TriggerMelting : public LevelObject
{
private:
    typedef LevelObject super;
    typedef TriggerMelting self;

CC_CONSTRUCTOR_ACCESS:
    TriggerMelting();
    virtual ~TriggerMelting();
public:
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void setProperties(ValueMap& props) override;
    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override;
    std::string target;
};

#endif /* TriggerMelting_hpp */
