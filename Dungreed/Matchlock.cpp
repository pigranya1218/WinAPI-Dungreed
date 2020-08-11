#include "matchlock.h"
#include "TestScene.h"

Matchlock::Matchlock(Vector2 pos, DIRECTION dir)
{
	_img = IMAGE_MANAGER->findImage("MatchlockGun");
	if (dir == DIRECTION::LEFT)
	{
		_isLeft = true;
		_position = Vector2(pos.x - 30, pos.y + 10);
	}
	if (dir == DIRECTION::RIGHT)
	{
		_isLeft = false;
		_position = Vector2(pos.x + 30, pos.y + 10);
	}

}

Matchlock::~Matchlock()
{
}

void Matchlock::init()
{
}

void Matchlock::update(Vector2 pos, DIRECTION dir)
{
	_position = Vector2(pos.x + 30, pos.y + 20);;
	if (dir == DIRECTION::LEFT)
	{
		_isLeft = true;
		_position = Vector2(pos.x - 30, pos.y + 10);
	}
	if (dir == DIRECTION::RIGHT)
	{
		_isLeft = false;
		_position = Vector2(pos.x + 30, pos.y + 10);
	}


}

void Matchlock::release()
{
}

void Matchlock::render()
{
	_img->setScale(4);

	_img->setAnglePos(Vector2(_img->getSize().x / 3.f, _img->getSize().y / 2.f));

	float _angleTemp;


	if (!_isLeft)
	{
		_img->setAngle(atan2(_ptMouse.y - _position.y, _ptMouse.x - _position.x) * (180 / PI));
		_angleTemp = atan2(_ptMouse.y - _position.y, _ptMouse.x - _position.x) * (180 / PI);
	}
	if (_isLeft)
	{
		_img->setAngle(-atan2(_ptMouse.y - _position.y, _ptMouse.x - _position.x) * (180 / PI) + 180);
		_angleTemp = -atan2(_ptMouse.y - _position.y, _ptMouse.x - _position.x) * (180 / PI);
	}

	//_hand01 = { _position.x  - _angleTemp, _position.y + _angleTemp, _position.x + 5 + _angleTemp, _position.y + 5 - _angleTemp };

	//Vector2 pos = Vector2(_ptMouse.x - _position.x, _ptMouse.y - _position.y).normalize;
	//_img->setAngle();
	_img->render(_position, _isLeft);
	D2D_RENDERER->fillRectangle(_hand01, 0,0,0, 1);

	wstring data = to_wstring(atan2(_ptMouse.y - _position.y, _ptMouse.x - _position.x));
	D2D_RENDERER->renderText(50, 50, data, 30, D2DRenderer::DefaultBrush::Black, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã", 0.0f);
}
