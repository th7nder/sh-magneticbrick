//
//  BulletTimeEnd.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 01/06/2017.
//
//

#ifndef BulletTimeEnd_hpp
#define BulletTimeEnd_hpp

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Globals.hpp"
#include "LevelObject.hpp"
#include "SimpleAudioEngine.h"
#include "Bullet.hpp"

class BulletTimeEnd : public LevelObject
{
private:
    typedef LevelObject super;
    typedef BulletTimeEnd self;
    
CC_CONSTRUCTOR_ACCESS:
    BulletTimeEnd();
    virtual ~BulletTimeEnd();
public:
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override;
    virtual void launch() override;
};


#endif /* BulletTimeEnd_hpp */
