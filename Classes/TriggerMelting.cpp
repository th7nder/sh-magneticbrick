//
//  TriggerMelting.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 01/06/2017.
//
//

#include "TriggerMelting.hpp"

TriggerMelting::TriggerMelting()
{
    
}

TriggerMelting::~TriggerMelting()
{
   
}

TriggerMelting* TriggerMelting::create(GameHandler* handler)
{
    self* ret = new (std::nothrow) self();
    if (ret && ret->init(handler))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}


bool TriggerMelting::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void TriggerMelting::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
    CCASSERT(!props["target"].isNull(), "TriggerMelting without target!");
    target = props["target"].asString();
}




bool TriggerMelting::OnContactBegin(LevelObject *other, b2Body* otherBody)
{

    getParent()->enumerateChildren(target, [](Node* meltingNode) -> bool{
        auto melting = dynamic_cast<MeltingObstacle*>(meltingNode);
        if(melting != nullptr)
        {
            melting->addIce();
        }
        return false;
        
    });
    
    return false;
}



void TriggerMelting::initPhysics(b2World *world)
{
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPositionX(), getPositionY()));
    auto fixture = createFixture(createRectangularShape(size.width, size.height));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}
