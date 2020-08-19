#pragma once
class DamageInfo
{
public:
	float damage = 0;
	float trueDamage = 0;
	bool isCritical = false; // ũ��Ƽ���� �߻��ߴ�
	bool isEvade = false; // ȸ���Ͽ���
	bool isBlock = false; // ����Ͽ���

public:
	DamageInfo() : damage(0), trueDamage(0), isCritical(false) {}
	DamageInfo(float damage, float trueDamage, bool isCritical) :
		damage(damage), trueDamage(trueDamage), isCritical(isCritical) {}
};

