#pragma once
class DamageInfo
{
public:
	float damage;
	float trueDamage;
	bool isCritical;

public:
	DamageInfo() : damage(0), trueDamage(0), isCritical(false) {}
	DamageInfo(float damage, float trueDamage, bool isCritical) :
		damage(damage), trueDamage(trueDamage), isCritical(isCritical) {}
};

