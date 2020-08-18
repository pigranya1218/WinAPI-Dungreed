#pragma once
class DamageInfo
{
public:
	float damage;
	float trueDamage;

public:
	DamageInfo() : damage(0), trueDamage(0) {}
	DamageInfo(float damage, float trueDamage) :
		damage(damage), trueDamage(trueDamage) {}
};

