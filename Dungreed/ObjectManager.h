#pragma once
#include "Object.h"

class Stage;
class Player;

class ObjectManager
{
private:
	Stage* _stage;
	Player* _player;
	vector<Object*> _objects;

public:
	void setStage(Stage* stage) { _stage = stage; }
	void setPlayer(Player* player) { _player = player; }

	void init();
	void release();
	void update(float const elapsedTime);
	void render();

	bool isHit(FloatRect* rect, AttackInfo* info);
	bool isHit(FloatCircle* circle, AttackInfo* info);
	bool isHit(Projectile* projectile, bool isOnceCollision);

	void moveTo(GameObject* gameObject, Vector2 moveDir, bool checkCollisionGround = true, bool checkCollisionPlatform = true);
	
	void spawnObject(int objectCode, Vector2 pos);
	void pushObject(Object* object);
	Player* getPlayer() { return _player; }
};

