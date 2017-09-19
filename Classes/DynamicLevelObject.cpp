//
//  DynamicLevelObject.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/09/2017.
//
//

#include "DynamicLevelObject.hpp"
USING_NS_CC;
DynamicLevelObject::DynamicLevelObject() :
previousPosition(Vec2::ZERO),
startPosition(Vec2::ZERO)
{
    
}

bool DynamicLevelObject::isDynamic() const
{
    return true;
}


void DynamicLevelObject::setProperties(cocos2d::ValueMap &props)
{
    super::setProperties(props);
    
// pixelsToMeters? nah -> interpolation workin with sprites not b2Bodies
    previousPosition = startPosition = getPosition();
}

void DynamicLevelObject::savePreviousStates()
{
    previousPosition = Vec2(metersToPixels(body->GetPosition().x), metersToPixels(body->GetPosition().y));
}


void DynamicLevelObject::interpolate(float alpha)
{
    Vec2 target(lerp(previousPosition.x, metersToPixels(body->GetPosition().x), alpha),
                lerp(previousPosition.y, metersToPixels(body->GetPosition().y), alpha));
    
    setPosition(target);
}
