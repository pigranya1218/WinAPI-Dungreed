#pragma once
#include "Stage.h"
#include "MapTool.h"



class VillageStage :public Stage
{
private:
	Image* _BGL;
	Image* _BG1;
	Image* _BG2;
	Image* _floor;
	Image* _dungeonEat;
	Animation* _eatAni;
	//Image* _tileImage;

	
	bool _enter;
	int _currentIndex;

	Vector2 _eatPos;

public:
	virtual void init();
	virtual void release();
	virtual void update(float const elapsedTime);
	virtual void render();

	void enterDungeon();
};

