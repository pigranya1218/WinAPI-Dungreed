#pragma once
#include "GameNode.h"

class ProgressBar : public GameNode
{
private:
	Image*	_frontBar;	// �� �̹���
	Image*	_backBar;	// �� �̹���
	Vector2 _pos;		// ��ǥ
	Vector2 _angle;		// ���� ���� X, Y
	float	_width;		// ����� ����
	float	_scale;		// ������ ��

public:
	ProgressBar();
	~ProgressBar();

	// �� �̹���, �� �̹���, �����ǥ, ���� X, Y ����
	HRESULT init(string backBarImage, string frontBarImage, const Vector2& pos, const Vector2& angle = Vector2(0.0f, 0.0f), float scale = 1.0f);
	void release();
	void update();
	void render();
	
	void setGauge(float currentHp, float maxHp);


};

