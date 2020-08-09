#include "stdafx.h"
#include "Camera.h"
#include "CameraShakeEvent.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

HRESULT Camera::init()
{
	return S_OK;
}

void Camera::release()
{
}

void Camera::processEvent()
{
	if (_eventQueue.empty()) return;

	_eventQueue.front()->processEvent();
	if (_eventQueue.front()->getRemainTime() <= 0)
	{
		delete _eventQueue.front();
		_eventQueue.pop();
	}
}

void Camera::pushShakeEvent(float power, float shakePerTime, float remainTime)
{
	CameraShakeEvent* event = new CameraShakeEvent(power, shakePerTime, remainTime);
	_eventQueue.push(event);
}

void Camera::setConfig(float offsetL, float offsetT, float width, float height, float minL, float minT, float maxL, float maxT)
{
	_offsetL = offsetL;
	_offsetT = offsetT;
	_L = minL;
	_T = minT;
	_width = width;
	_height = height;
	_originMinL = _minL = minL;
	_originMinT = _minT = minT;
	_originMaxL = _maxL = maxL;
	_originMaxT = _maxT = maxT;

	_x = _L + (_width / 2);
	_y = _T + (_height / 2);
	_originMinX = _minX = _minL + (_width / 2);
	_originMinY = _minY = _minT + (_height / 2);
	_originMaxX = _maxX = _maxL + (_width / 2);
	_originMaxY = _maxY = _maxT + (_height / 2);
}

void Camera::setConfigCenter(float x, float y, float width, float height, float minX, float minY, float maxX, float maxY)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_originMinX = _minX = minX;
	_originMinY = _minY = minY;
	_originMaxX = _maxX = maxX;
	_originMaxY = _maxY = maxY;

	_L = _x - (width / 2);
	_T = _y - (height / 2);
	_originMinL = _minL = _minX - (width / 2);
	_originMinT = _minT = _minY - (height / 2);
	_originMaxL = _maxL = _maxX - (width / 2);
	_originMaxT = _maxT = _minY - (height / 2);
}

float Camera::getL()
{
	return _L;
}

float Camera::getT()
{
	return _T;
}

Vector2 Camera::getLT()
{
	return Vector2(_L, _T);
}

float Camera::getX()
{
	return _x;
}

float Camera::getY()
{
	return _y;
}

Vector2 Camera::getXY()
{
	return Vector2(_x, _y);
}

void Camera::setL(float newL)
{
	newL = min(_maxL, newL);
	newL = max(_minL, newL);
	_L = floor(newL);
	_x = _L + (_width / 2);
}

void Camera::setT(float newT)
{
	newT = min(_maxT, newT);
	newT = max(_minT, newT);
	_T = floor(newT);
	_y = _T + (_height / 2);
}

void Camera::setLT(Vector2 newLT)
{
	setL(newLT.x);
	setT(newLT.y);
}

void Camera::setX(float newX)
{
	newX = min(_maxX, newX);
	newX = max(_minX, newX);
	_x = floor(newX);
	_L = _x - (_width / 2);
}

void Camera::setY(float newY)
{
	newY = min(_maxY, newY);
	newY = max(_minY, newY);
	_y = floor(newY);
	_T = _y - (_height / 2);
}

void Camera::setXY(Vector2 newXY)
{
	setX(newXY.x);
	setY(newXY.y);
}

void Camera::movePivot(float offsetX, float offsetY)
{
	setL(_L + offsetX);
	setT(_T + offsetY);
}

void Camera::movePivot(Vector2 offsetXY)
{
	setL(_L + offsetXY.x);
	setT(_T + offsetXY.y);
}

float Camera::getRelativeX(float left)
{
	float newL = _offsetL + left - _L;
	return newL;
}

LONG Camera::getRelativeX(LONG left)
{
	LONG newL = _offsetL + left - _L;
	return newL;
}

float Camera::getRelativeY(float top)
{
	float newT = _offsetT + top - _T;
	return  newT;
}

LONG Camera::getRelativeY(LONG top)
{
	LONG newT = _offsetT + top - _T;
	return  newT;
}

POINT Camera::getRelativePt(POINT pt)
{
	POINT result;
	result.x = getRelativeX(pt.x);
	result.y = getRelativeY(pt.y);
	return result;
}

Vector2 Camera::getRelativeV2(Vector2 vec2)
{
	return Vector2(getRelativeX(vec2.x), getRelativeY(vec2.y));
}

FloatRect Camera::getRelativeFR(FloatRect rc)
{
	float left = getRelativeX(rc.left);
	float top = getRelativeY(rc.top);
	float right = getRelativeX(rc.right);
	float bottom = getRelativeY(rc.bottom);

	return FloatRect(left, top,
		right, bottom);
}

float Camera::getAbsoluteX(float left)
{
	float newL = -_offsetL + _L + left;
	return newL;
}

LONG Camera::getAbsoluteX(LONG left)
{
	LONG newL = -_offsetL + _L + left;
	return newL;
}

float Camera::getAbsoluteY(float top)
{
	float newT = -_offsetT + _T + top;
	return newT;
}

LONG Camera::getAbsoluteY(LONG top)
{
	LONG newT = -_offsetT + _T + top;
	return newT;
}

POINT Camera::getAbsolutePt(POINT pt)
{
	POINT result;
	result.x = getAbsoluteX(pt.x);
	result.y = getAbsoluteY(pt.y);
	return result;
}

Vector2 Camera::getAbsoluteV2(Vector2 vec2)
{
	return Vector2(getAbsoluteX(vec2.x), getAbsoluteY(vec2.y));
}

FloatRect Camera::getAbsoluteFR(FloatRect rc)
{
	return FloatRect(getAbsoluteX(rc.left), getAbsoluteY(rc.top),
		getAbsoluteX(rc.right), getAbsoluteY(rc.bottom));
}

void Camera::drawLine(Vector2 start, Vector2 end)
{
	D2D_RENDERER->drawLine(getRelativeV2(start), getRelativeV2(end));
}

void Camera::rectangle(FloatRect rect, D2D1::ColorF::Enum color, float alpha, float strokeWidth)
{
	FloatRect relativeRc = getRelativeFR(rect);
	D2D_RENDERER->drawRectangle(relativeRc, color, alpha, strokeWidth);
}

void Camera::render(Image * img, Vector2 center, bool bisymmetry)
{
	Vector2 drawPos = getRelativeV2(center);
	img->render(drawPos, bisymmetry);
}

void Camera::render(Image * img, Vector2 center, Vector2 sourLT, Vector2 sourSize, bool bisymmetry)
{
	Vector2 drawPos = getRelativeV2(center);
	img->render(drawPos, sourLT, sourSize, bisymmetry);
}


void Camera::frameRender(Image * img, Vector2 center, int frameX, int frameY, bool bisymmetry)
{
	Vector2 drawPos = getRelativeV2(center);
	img->frameRender(drawPos, frameX, frameY, bisymmetry);
}

void Camera::aniRender(Image * img, Vector2 center, Animation * ani, bool bisymmetry)
{
	Vector2 drawPos = getRelativeV2(center);
	img->aniRender(drawPos, ani, bisymmetry);
}

