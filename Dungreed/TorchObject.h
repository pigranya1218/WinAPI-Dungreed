#pragma once
#include "Object.h"
class TorchObject :
    public Object
{
	

private:
	
	Image* _img;
	Animation* _ani;

public:
	void init( Vector2 pos);
	virtual void release() override;
	virtual void update(float elapsedTime) override;
	virtual void render() override;
};

