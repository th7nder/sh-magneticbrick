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
#include "GameHandler.hpp"
#include "Touchable.hpp"
#include "LevelObject.hpp"
#include "SimpleAudioEngine.h"
#include "TeleportIn.hpp"
#include "TeleportOut.hpp"
#include "Walls.hpp"
#include "LevelFollower.hpp"
class Player : public LevelObject, public Touchable
{
private:
    typedef LevelObject super;
    typedef Player self;
CC_CONSTRUCTOR_ACCESS:
    Player();
    b2Body* rightBody;
    Sprite* rightSprite;
    b2Body* leftBarrier;
    b2Body* rightBarrier;
    
    float speed;
    
    
    cocos2d::Size playerSize;
    
    float startLeftPos;
    float startRightPos;
    float force;
    Vec2 startTouchPosition;
    
    bool isTouching;
    bool inTeleport;
    
    
    double tempTime;
    double tempStartPos;
    double getCurrentTimeInSeconds();
    
    /**************************/
    
    Vec2 previousRightPosition;
    Walls* walls;
    LevelFollower* levelFollower;
    EventListenerTouchAllAtOnce* listener;
    std::string currentTeleportTarget;
    bool tutorialPlayer;
public:
    virtual int getZ() const override
    {
        return 30;
    }
    virtual bool isInTeleport()
    {
        return inTeleport;
    }
    virtual ~Player();
    static self* create(GameHandler* handler, Walls* w, LevelFollower* lf);
    virtual bool init(GameHandler* handler, Walls* w, LevelFollower* lf);
    virtual void setProperties(ValueMap& props) override;
    virtual void addSprite() override;
    b2Body* createBarrier(b2World* world, float x, float y);

    b2Body* createDestroyer(b2World* world, float x, float y);
    void die();
    
    virtual void initPhysics(b2World* world) override;
    virtual b2FixtureDef* createFixture(b2Shape* shape) override;
    virtual b2BodyDef* createBody(float x, float y) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* otherBody) override;
    virtual bool OnContactEnd(LevelObject* other) override;
        virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* event) override;
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event* event) override;
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* event) override;
    virtual void onTouchesCancelled(const std::vector<Touch*>& touches, Event* event) override;
    void updateBricksSpacing();
    virtual void interpolate(float alpha) override;

    virtual void savePreviousStates() override;


    void setVelocities(float v);
    void disableCollisionWithSolids();
    void enableCollisionWithSolids();
    
    void resetSpriteY();
    
    virtual Sprite* getRightSprite() {return rightSprite;}
    

    
};

#endif /* Player_hpp */