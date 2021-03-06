#pragma once
#include "Image.h"
#include "CameraEvent.h"

class CameraManager : public SingletonBase<CameraManager>
{
private:
	vector<CameraEvent*> _eventList;

	float _offsetL, _offsetT; // 카메라 LEFT, TOP을 그리기 시작할 윈도우 위치 
	
	float _L, _T; // 카메라 LEFT, TOP 절대 좌표이며 이를 기준으로 그려짐
	float _x, _y; // 카메라 중점 좌표
	float _width, _height; // 카메라 너비, 높이 값

	// 기본값
	float _originMinL, _originMaxL;
	float _originMinT, _originMaxT;
	float _originMinX, _originMaxX;
	float _originMinY, _originMaxY;

	// zoom으로 인한 계산을 위해
	float _minL, _maxL; // Left 좌표의 가능한 범위
	float _minT, _maxT; // Top 좌표의 가능한 범위
	float _minX, _maxX; // x 좌표의 가능한 범위
	float _minY, _maxY; // y 좌표의 가능한 범위

public:
	CameraManager();
	~CameraManager();

	HRESULT init();
	void release();
\
	// for Event
	void processEvent(float elapsedTime);
	void render();
	void pushShakeEvent(float power, float remainTime);
	void pushMoveEvnet(Vector2 targetPos, float moveTime, float waitTime);
	void pushFillEvnet(vector<FloatRect> fillRects, float waitTime, float enterTime, float displayTime, float closeTime, COLORREF color);

	void setConfig(float offsetL, float offsetT, float width, float height, float minL, float minT, float maxL, float maxT);
	void setConfigCenter(float x, float y, float width, float height, float minX, float minY, float maxX, float maxY);
	float getL();
	float getT();
	Vector2 getLT();
	float getX();
	float getY();
	Vector2 getXY();
	void setL(float newL);
	void setT(float newT);
	void setLT(Vector2 newLT);
	void setX(float newX);
	void setY(float newY);
	void setXY(Vector2 newXY);
	void movePivot(float offsetX, float offsetY);
	void movePivot(Vector2 offsetXY);

	float getRelativeX(float left, float ratio = 1.0);
	LONG getRelativeX(LONG left, float ratio = 1.0);
	float getRelativeY(float top, float ratio = 1.0);
	LONG getRelativeY(LONG top, float ratio = 1.0);
	POINT getRelativePt(POINT pt, float ratio = 1.0);
	Vector2 getRelativeV2(Vector2 vec2, float ratio = 1.0);
	FloatRect getRelativeFR(FloatRect rc, float ratio = 1.0);

	float getAbsoluteX(float left);
	LONG getAbsoluteX(LONG left);
	float getAbsoluteY(float top);
	LONG getAbsoluteY(LONG top);
	POINT getAbsolutePt(POINT pt);
	Vector2 getAbsoluteV2(Vector2 vec2);
	FloatRect getAbsoluteFR(FloatRect rc);

	// FOR DEBUG
	void drawLine(Vector2 start, Vector2 end);

	void rectangle(FloatRect rect, D2D1::ColorF::Enum color, float alpha, float strokeWidth);

	void render(Image* img, Vector2 center, bool bisymmetry = false);
	void render(Image* img, Vector2 center, Vector2 size, bool bisymmetry = false);
	void render(Image* img, Vector2 center, Vector2 sourLT, Vector2 sourSize, bool bisymmetry = false);
	void render(Image* img, Vector2 center, Vector2 size, Vector2 sourLT, Vector2 sourSize, bool bisymmetry = false);

	void frameRender(Image* img, Vector2 center, int frameX, int frameY, bool bisymmetry = false);

	void aniRender(Image* img, Vector2 center, Animation* ani, bool bisymmetry = false);
	void aniRender(Image* img, Vector2 center, Vector2 size, Animation* ani, bool bisymmetry = false);

	

	
};
