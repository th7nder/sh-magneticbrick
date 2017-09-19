//
//  Player.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 02/02/2017.
//
//

#ifndef Player_hpp
#define Player_hpp

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Touchable.hpp"
#include "LevelObject.hpp"
#include "SimpleAudioEngine.h"
#include "TeleportIn.hpp"
#include "TeleportOut.hpp"
#include "Walls.hpp"
#include "LevelFollower.hpp"

#include "DynamicLevelObject.hpp"
class Player : public DynamicLevelObject, public Touchable
{
private:
    typedef LevelObject super;
    typedef Player self;
protected:
    float speed;
    bool forceTouch;
    
    b2Body* rightBody;
    Sprite* rightSprite;
    b2Body* leftBarrier;
    b2Body* rightBarrier;
    
    cocos2d::Size playerSize;
    
    float startLeftPos;
    float startRightPos;
    float force;
    cocos2d::Vec2 startTouchPosition;
    
    bool isTouching;
    bool inTeleport;
    
    
    double tempStartPos;
    
    /**************************/
    
    cocos2d::Vec2 previousRightPosition;
    Walls* walls;
    LevelFollower* levelFollower;
    cocos2d::EventListenerTouchAllAtOnce* listener;
    std::string currentTeleportTarget;
    bool tutorialPlayer;
public:
    Player();
    virtual ~Player();
    
    virtual int getZ() const override;
    virtual Sprite* getRightSprite();

    virtual void setProperties(ValueMap& props) override;
    virtual void addSprite() override;
    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* otherBody) override;
    
    
    virtual void interpolate(float alpha) override;
    virtual void savePreviousStates() override;
    
    
    virtual b2FixtureDef* createFixture(b2Shape* shape) override;
    virtual b2BodyDef* createBody(float x, float y) override;
    b2Body* createBarrier(b2World* world, float x, float y);
    b2Body* createDestroyer(b2World* world, float x, float y);
    
    
    void dieAnimation();
    void updateBricksSpacing();
    void resetSpriteY();

    void setVelocities(float v);
    void disableCollisionWithSolids();
    void enableCollisionWithSolids();
    
    
    

    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* event) override;
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event* event) override;
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* event) override;
    virtual void onTouchesCancelled(const std::vector<Touch*>& touches, Event* event) override;

    /* virtual bool isInTeleport()
     {
     return inTeleport;
     }*/
};

#endif /* Player_hpp */
