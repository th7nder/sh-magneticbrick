//
//  LevelFollower.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 28/06/2017.
//
//

#ifndef LevelFollower_hpp
#define LevelFollower_hpp


#include "DynamicLevelObject.hpp"

class LevelFollower : public DynamicLevelObject
{
private:
    typedef LevelObject super;
    typedef LevelFollower self;
protected:
    float speed;
public:
    virtual std::string getDescription() const override
    {
        return "LevelFollower";
    }
    LevelFollower();
    virtual ~LevelFollower();
    virtual void setProperties(cocos2d::ValueMap& props) override;
    virtual void initPhysics(b2World* world) override;
    virtual void launch() override;
    virtual void interpolate(float alpha) override;
    
    
};
#endif /* LevelFollower_hpp */
