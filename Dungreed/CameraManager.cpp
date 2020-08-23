#include "stdafx.h"
#include "CameraManager.h"
#include "CameraShakeEvent.h"
#include "CameraMoveEvent.h"
#include "CameraFillEvent.h"

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

HRESULT CameraManager::init()
{
	return S_OK;
}

void CameraManager::release()
{
}

void CameraManager::processEvent(float elapsedTime)
{
	vector<bool> dupEvent(static_cast<int>(CAMERA_EVENT_TYPE::END), false);
	for (int i = 0; i < _eventList.size();)
	{
		if (dupEvent[static_cast<int>(_eventList[i]->getType())])
		{
			i++;
		}
		else
		{
			dupEvent[static_cast<int>(_eventList[i]->getType())] = true;

			_eventList[i]->processEvent(elapsedTime);

			if (_eventList[i]->getRemainTime() <= 0)
			{
				delete _eventList[i];
				_eventList.erase(_eventList.begin() + i);
			}
			else
			{
				i++;
			}
		}
	}
}

void CameraManager::render()
{
	vector<bool> dupEvent(static_cast<int>(CAMERA_EVENT_TYPE::END), false);
	for (int i = 0; i < _eventList.size();)
	{
		if (dupEvent[static_cast<int>(_eventList[i]->getType())])
		{
			i++;
		}
		else
		{
			dupEvent[static_cast<int>(_eventList[i]->getType())] = true;
			_eventList[i]->render();
		}
	}
}

void CameraManager::pushShakeEvent(float power, float remainTime)
{
	CameraShakeEvent* event = new CameraShakeEvent(power, remainTime);
	
	float currRemainTime = remainTime;

	for (int i = 0; i < _eventList.size(); i++)
	{
		if (_eventList[i]->getType() != event->getType()) continue;
		CameraShakeEvent* currEvent = dynamic_cast<CameraShakeEvent*>(_eventList[i]);
		if (currEvent->getPower() < power)
		{
			currEvent->setPower(power);
		}
		currRemainTime -= currEvent->getRemainTime();
	}

	if (currRemainTime > 0)
	{
		event->setRemainTime(currRemainTime);
		_eventList.push_back(event);
	}
	
}

void CameraManager::pushMoveEvnet(Vector2 targetPos, float moveTime, float waitTime)
{
	CameraMoveEvent* event = new CameraMoveEvent(targetPos, moveTime, waitTime);

	_eventList.push_back(event);
}

void CameraManager::pushFillEvnet(vector<FloatRect> fillRects, float waitTime, float enterTime, float displayTime, float closeTime, COLORREF color)
{
	CameraFillEvent* event = new CameraFillEvent(fillRects, waitTime, enterTime, displayTime, closeTime, color);

	_eventList.push_back(event);
}

void CameraManager::setConfig(float offsetL, float offsetT, float width, float height, float minL, float minT, float maxL, float maxT)
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

void CameraManager::setConfigCenter(float x, float y, float width, float height, float minX, float minY, float maxX, float maxY)
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

float CameraManager::getL()
{
	return _L;
}

float CameraManager::getT()
{
	return _T;
}

Vector2 CameraManager::getLT()
{
	return Vector2(_L, _T);
}

float CameraManager::getX()
{
	return _x;
}

float CameraManager::getY()
{
	return _y;
}

Vector2 CameraManager::getXY()
{
	return Vector2(_x, _y);
}

void CameraManager::setL(float newL)
{
	newL = min(_maxL, newL);
	newL = max(_minL, newL);
	_L = floor(newL);
	_x = _L + (_width / 2);
}

void CameraManager::setT(float newT)
{
	newT = min(_maxT, newT);
	newT = max(_minT, newT);
	_T = floor(newT);
	_y = _T + (_height / 2);
}

void CameraManager::setLT(Vector2 newLT)
{
	setL(newLT.x);
	setT(newLT.y);
}

void CameraManager::setX(float newX)
{
	newX = min(_maxX, newX);
	newX = max(_minX, newX);
	_x = floor(newX);
	_L = _x - (_width / 2);
}

void CameraManager::setY(float newY)
{
	newY = min(_maxY, newY);
	newY = max(_minY, newY);
	_y = floor(newY);
	_T = _y - (_height / 2);
}

void CameraManager::setXY(Vector2 newXY)
{
	setX(newXY.x);
	setY(newXY.y);
}

void CameraManager::movePivot(float offsetX, float offsetY)
{
	setL(_L + offsetX);
	setT(_T + offsetY);
}

void CameraManager::movePivot(Vector2 offsetXY)
{
	setL(_L + offsetXY.x);
	setT(_T + offsetXY.y);
}

float CameraManager::getRelativeX(float left, float ratio)
{
	float newL = left + (_offsetL  - _L) * ratio;
	return newL;
}

LONG CameraManager::getRelativeX(LONG left, float ratio)
{
	LONG newL = left + (_offsetL - _L) * ratio;
	return newL;
}

float CameraManager::getRelativeY(float top, float ratio)
{
	float newT = top + (_offsetT - _T) * ratio;
	return  newT;
}

LONG CameraManager::getRelativeY(LONG top, float ratio)
{
	LONG newT = top + (_offsetT - _T) * ratio;
	return  newT;
}

POINT CameraManager::getRelativePt(POINT pt, float ratio)
{
	POINT result;
	result.x = getRelativeX(pt.x, ratio);
	result.y = getRelativeY(pt.y, ratio);
	return result;
}

Vector2 CameraManager::getRelativeV2(Vector2 vec2, float ratio)
{
	return Vector2(getRelativeX(vec2.x, ratio), getRelativeY(vec2.y, ratio));
}

FloatRect CameraManager::getRelativeFR(FloatRect rc, float ratio)
{
	float left = getRelativeX(rc.left, ratio);
	float top = getRelativeY(rc.top, ratio);
	float right = getRelativeX(rc.right, ratio);
	float bottom = getRelativeY(rc.bottom, ratio);

	return FloatRect(left, top,
		right, bottom);
}

float CameraManager::getAbsoluteX(float left)
{
	float newL = -_offsetL + _L + left;
	return newL;
}

LONG CameraManager::getAbsoluteX(LONG left)
{
	LONG newL = -_offsetL + _L + left;
	return newL;
}

float CameraManager::getAbsoluteY(float top)
{
	float newT = -_offsetT + _T + top;
	return newT;
}

LONG CameraManager::getAbsoluteY(LONG top)
{
	LONG newT = -_offsetT + _T + top;
	return newT;
}

POINT CameraManager::getAbsolutePt(POINT pt)
{
	POINT result;
	result.x = getAbsoluteX(pt.x);
	result.y = getAbsoluteY(pt.y);
	return result;
}

Vector2 CameraManager::getAbsoluteV2(Vector2 vec2)
{
	return Vector2(getAbsoluteX(vec2.x), getAbsoluteY(vec2.y));
}

FloatRect CameraManager::getAbsoluteFR(FloatRect rc)
{
	return FloatRect(getAbsoluteX(rc.left), getAbsoluteY(rc.top),
		getAbsoluteX(rc.right), getAbsoluteY(rc.bottom));
}

void CameraManager::drawLine(Vector2 start, Vector2 end)
{
	D2D_RENDERER->drawLine(getRelativeV2(start), getRelativeV2(end));
}

void CameraManager::rectangle(FloatRect rect, D2D1::ColorF::Enum color, float alpha, float strokeWidth)
{
	FloatRect relativeRc = getRelativeFR(rect);
	D2D_RENDERER->drawRectangle(relativeRc, color, alpha, strokeWidth);
}

void CameraManager::render(Image * img, Vector2 center, bool bisymmetry)
{
	Vector2 drawPos = getRelativeV2(center);
	img->render(drawPos, bisymmetry);
}

void CameraManager::render(Image* img, Vector2 center, Vector2 size, bool bisymmetry)
{
	Vector2 drawPos = getRelativeV2(center);
	img->render(drawPos, size, bisymmetry);
}

void CameraManager::render(Image * img, Vector2 center, Vector2 sourLT, Vector2 sourSize, bool bisymmetry)
{
	Vector2 drawPos = getRelativeV2(center);
	img->render(drawPos, sourLT, sourSize, bisymmetry);
}

void CameraManager::render(Image* img, Vector2 center, Vector2 size, Vector2 sourLT, Vector2 sourSize, bool bisymmetry)
{
	Vector2 drawPos = getRelativeV2(center);
	img->render(drawPos, size, sourLT, sourSize, bisymmetry);
}


void CameraManager::frameRender(Image * img, Vector2 center, int frameX, int frameY, bool bisymmetry)
{
	Vector2 drawPos = getRelativeV2(center);
	img->frameRender(drawPos, frameX, frameY, bisymmetry);
}

void CameraManager::aniRender(Image * img, Vector2 center, Animation * ani, bool bisymmetry)
{
	Vector2 drawPos = getRelativeV2(center);
	img->aniRender(drawPos, ani, bisymmetry);
}

void CameraManager::aniRender(Image* img, Vector2 center, Vector2 size, Animation* ani, bool bisymmetry)
{
	Vector2 drawPos = getRelativeV2(center);
	img->aniRender(drawPos, size, ani, bisymmetry);
}


