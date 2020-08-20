#include "Object.h"

bool Object::isHit(FloatRect* rect, AttackInfo* info)
{
    return false;
}

bool Object::isHit(FloatCircle* circle, AttackInfo* info)
{
    return false;
}

bool Object::isHit(Projectile* projectile)
{
    return false;
}
