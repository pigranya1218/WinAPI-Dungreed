#pragma once
#include "Image.h"
#include "CameraEvent.h"

class Camera
{
private:
	queue<CameraEvent*> _eventQueue;

	float _offsetL, _offsetT; // ī�޶� LEFT, TOP�� �׸��� ������ ������ ��ġ 
	
	float _L, _T; // ī�޶� LEFT, TOP ���� ��ǥ�̸� �̸� �������� �׷���
	float _x, _y; // ī�޶� ���� ��ǥ
	float _width, _height; // ī�޶� �ʺ�, ���� ��

	// �⺻��
	float _originMinL, _originMaxL;
	float _originMinT, _originMaxT;
	float _originMinX, _originMaxX;
	float _originMinY, _originMaxY;

	// zoom���� ���� ����� ����
	float _minL, _maxL; // Left ��ǥ�� ������ ����
	float _minT, _maxT; // Top ��ǥ�� ������ ����
	float _minX, _maxX; // x ��ǥ�� ������ ����
	float _minY, _maxY; // y ��ǥ�� ������ ����

public:
	Camera();
	~Camera();

	HRESULT init();
	void release();
	void processEvent();
	void pushShakeEvent(float power, float shakePerTime, float remainTime);

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

	float getRelativeX(float left);
	LONG getRelativeX(LONG left);
	float getRelativeY(float top);
	LONG getRelativeY(LONG top);
	POINT getRelativePt(POINT pt);
	Vector2 getRelativeV2(Vector2 vec2);
	FloatRect getRelativeFR(FloatRect rc);

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
	void render(Image* img, Vector2 center, Vector2 sourLT, Vector2 sourSize, bool bisymmetry = false);

	void frameRender(Image* img, Vector2 center, int frameX, int frameY, bool bisymmetry = false);

	void aniRender(Image* img, Vector2 center, Animation* ani, bool bisymmetry = false);
	
};