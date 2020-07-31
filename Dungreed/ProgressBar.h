#pragma once
#include "GameNode.h"

class ProgressBar : public GameNode
{
private:
	Image*	_frontBar;	// 앞 이미지
	Image*	_backBar;	// 뒤 이미지
	Vector2 _pos;		// 좌표
	Vector2 _angle;		// 꺾을 각도 X, Y
	float	_width;		// 출력할 길이
	float	_scale;		// 스케일 값

public:
	ProgressBar();
	~ProgressBar();

	// 뒤 이미지, 앞 이미지, 출력좌표, 꺾을 X, Y 각도
	HRESULT init(string backBarImage, string frontBarImage, const Vector2& pos, const Vector2& angle = Vector2(0.0f, 0.0f), float scale = 1.0f);
	void release();
	void update();
	void render();
	
	void setGauge(float currentHp, float maxHp);


};

