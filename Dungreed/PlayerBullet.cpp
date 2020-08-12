#include "PlayerBullet.h"

void PlayerBullet::init(Vector2 pos, float angle)
{
	_bulletImg = IMAGE_MANAGER->findImage("GunBullet");
	_bulletCount = 1;
	_shootTermTime = 0.1f;
	_reloadTime = 2.5f;
	_position = pos;
	_angle = angle;

	_ani = new Animation;
	_ani->init(_bulletImg->getWidth(), _bulletImg->getHeight(), 4, 1);
	_ani->setDefPlayFrame(false, false);
	_ani->setFPS(8);
	_ani->start();
}

void PlayerBullet::update(float const elapsedTime)
{
	move();
	_ani->frameUpdate(elapsedTime);
}

void PlayerBullet::release()
{
}

void PlayerBullet::render()
{
	_bulletImg->setAngle(_angle);
	_bulletImg->setScale(4);
	_bulletImg->aniRender(_position, _ani);
	//D2D_RENDERER->drawRectangle(_bulletRect);
	//sprintf_s(_buffer, "current angle : %f", _angle);

	//D2D_RENDERER->renderText(300, 520, to_wstring(_angle), 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã", 0.0f);
	//D2D_RENDERER->renderText(300, 540, to_wstring(_position.x), 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã", 0.0f);
	//D2D_RENDERER->renderText(300, 560, to_wstring(_position.y), 20, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã", 0.0f);
}

void PlayerBullet::fire()
{

}

void PlayerBullet::move()
{
	float _currentAngle = _angle * (PI / 180.0f);
	_position.x += cosf(_currentAngle) * 15;
	_position.y += -sinf(_currentAngle) * 15;
}
