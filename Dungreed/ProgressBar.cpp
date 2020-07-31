#include "stdafx.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar()
{
}

ProgressBar::~ProgressBar()
{
}

HRESULT ProgressBar::init(string backBarImage, string frontBarImage, const Vector2& pos, const Vector2& angle, float scale)
{
	_backBar = IMAGE_MANAGER->findImage(backBarImage);
	_frontBar = IMAGE_MANAGER->findImage(frontBarImage);

	_pos = pos;
	_angle = angle;
	_scale = scale;

	_width = _backBar->getWidth();
	
	return S_OK;
}

void ProgressBar::release()
{

}

void ProgressBar::update()
{
}

void ProgressBar::render()
{
	_backBar->setScale(_scale);
	_backBar->render(
		_pos, 
		Vector2(0, 0), 
		Vector2((float)_backBar->getWidth(), (float)_backBar->getHeight())
	);			

	_frontBar->setScale(_scale);
	_frontBar->setSkew(Vector2(_width, 0.0f), _angle);
	_frontBar->render(
		_pos,											// 출력할 위치
		Vector2(0, 0),									// 이미지의 시작위치
		Vector2(_width, (float)(_backBar->getHeight()))	// 가져올 길이, 높이
	);
}

void ProgressBar::setGauge(float currentHp, float maxHp)
{
	_width = (currentHp / maxHp) * _backBar->getWidth();
}
