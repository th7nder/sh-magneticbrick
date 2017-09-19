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
#include "Skin.hpp"
class Player : public DynamicLevelObject, public Touchable
{
private:
    typedef LevelObject super;
    typedef Player self;
protected:
    float speed;
    bool forceTouch;
    const Skin* currentSkin;
    
    b2Body* rightBody;
    Sprite* rightSprite;
    b2Body* leftBarrier;
    b2Body* rightBarrier;
    
    bool modifierGravity;
    
    cocos2d::Size playerSize;
    
    float startLeftPos;
    float startRightPos;
    float halfPlayerWidth;
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
    virtual cocos2d::Sprite* getRightSprite();

    virtual void setProperties(cocos2d::ValueMap& props) override;
    virtual void addSprite() override;
    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* otherBody) override;
    
    
    virtual void interpolate(float alpha) override;
    virtual void savePreviousStates() override;
    
    
    virtual b2FixtureDef* createFixture(b2Shape* shape) override;
    virtual b2BodyDef* createBody(const cocos2d::Vec2& pos) override;
    b2Body* createBarrier(b2World* world, float x, float y);
    b2Body* createDestroyer(b2World* world, float x, float y);
    
    
    void dieAnimation();
    void updateBricksSpacing();
    void resetSpriteY();

    void setVelocities(float v);
    void disableCollisionWithSolids();
    void enableCollisionWithSolids();
    
    
    

    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) override;
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) override;
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) override;
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) override;

    /* virtual bool isInTeleport()
     {
     return inTeleport;
     }*/
};

#endif /* Player_hpp */
