#pragma once
#include "Object.h"

// 부셔질 수 있는 물체
class BrokenObject :
    public Object
{
private:
	string _fileName;
	Image* _img;

	Vector2 _force; // 받고 있는 힘

private:
	Image* getImage();
	Vector2 getObjectSize();
	void respawnParticle();
	void respawnGold();
	void respawnHpFairy();

public:
	void init(int ObjectCode, Vector2 pos);
	virtual void update(float elapsedTime) override;
	virtual void render() override;

	virtual bool hitEffect(FloatRect* rect, AttackInfo* info) override;
	virtual bool hitEffect(FloatCircle* circle, AttackInfo* info) override;
	virtual bool hitEffect(Projectile* projectile) override;
};

