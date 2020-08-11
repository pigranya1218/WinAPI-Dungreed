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
	float		_angle;

public:
	Effect();
	~Effect();

	virtual void init() {}
	virtual void init(Image* effectImage, int fps);
	virtual void release() override;
	virtual void update(float elapsedTime) override;
	virtual void render() override;

	void startEffect(Vector2 pos, float angle);
	void startEffect(Vector2 pos, Vector2 size, float angle);

	virtual void killEffect();

	bool getIsRunning() const { return _isRunning; }
};
