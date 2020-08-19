#pragma once
class DamageInfo
{
public:
	float damage = 0;
	float trueDamage = 0;
	bool isCritical = false; // 크리티컬이 발생했다
	bool isEvade = false; // 회피하였다
	bool isBlock = false; // 방어하였다

public:
	DamageInfo() : damage(0), trueDamage(0), isCritical(false) {}
	DamageInfo(float damage, float trueDamage, bool isCritical) :
		damage(damage), trueDamage(trueDamage), isCritical(isCritical) {}
};

