#pragma once
#include "GameObject.h"

class Image;
class Animation;

class Effect : public GameObject
{
protected:
	Image*		_effectImage;
	Animation*	_effectAnimation;
	bool		_isRunning;
	float		_elapsedTime;
	float		_scale;

public:
	Effect();
	~Effect();

	virtual void init(Image* effectImage, int fps);
	virtual void release();
	virtual void update();
	virtual void render();

	//void startEffect(int x, int y);
	//void startEffect(int x, int y, int width, int height);
	void startEffectZ(Vector2 pos, float scale);

	virtual void killEffect();

	bool getIsRunning() { return _isRunning; }
};
