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

	virtual void init() {}
	virtual void init(Image* effectImage, int fps);
	virtual void release() override;
	virtual void update(float elapsedTime) override;
	virtual void render() override;

	void startEffect(int x, int y);
	void startEffect(int x, int y, int width, int height);
	//void startEffectZ(Vector2 pos, float scale);

	virtual void killEffect();

	bool getIsRunning() const { return _isRunning; }
};
