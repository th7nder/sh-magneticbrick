//
//  LevelObject.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 30/01/2017.
//
//

#ifndef LevelObject_hpp
#define LevelObject_hpp

class LevelObject : public Node
{
private:
    typedef LevelObject self;
    typedef Node super;
CC_CONSTRUCTOR_ACCESS:
    LevelObject();
    Sprite* sprite;
    b2Body* body;
    bool remove;
public:
    virtual std::string getDescription() const override
    {
        return "LevelObject";
    }
    virtual int getZ() const
    {
        return 1;
    }
    
    Sprite* getSprite()
    {
        return sprite;
    }
    
    b2Body* getBody() {return body;}
    
    virtual ~LevelObject();
    virtual void interpolate(float alpha) {};
    virtual void update(float dt) override {};
    virtual void setProperties(ValueMap& props);
    virtual void addSprite() {};
    virtual void initPhysics(b2World* world);
    virtual b2BodyDef* createBody(float x, float y);
    virtual b2PolygonShape* createRectangularShape(float width, float height);
    virtual b2CircleShape* createCircleShape(float radius);
    virtual b2FixtureDef* createFixture(b2Shape* shape);
    
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) {return false;};
    virtual bool OnContactEnd(LevelObject* other) {return false;};
    virtual void savePreviousStates() {}
    virtual void launch() {};
    
  
    

};


#endif /* LevelObject_hpp */
