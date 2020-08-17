#pragma once
#include "stdafx.h"

enum class LINEAR_VALUE_TYPE
{
	ON, // 선분과 부딪힘
	UP, // 선분의 위에 있음
	DOWN, // 선분의 아래에 있음
	LEFT, // 선분의 왼쪽에 있음 (x = 100 등의 함수 꼴에서만 사용)
	RIGHT // 선분의 오른쪽에 있음 (x = 100 등의 함수 꼴에서만 사용)
};

// 1차 함수, 선분을 기준으로 위아래 어디에 위치하는지 판단하는 메서드 제공
class LinearFunc
{
public:
	static const int INF_A = 987654321;
public:
	SynthesizePublic(Vector2, start, Start); // X의 범위
	SynthesizePublic(Vector2, end, End); // X의 범위
	SynthesizePublic(Vector2, rangeX, RangeX); // X의 범위
	SynthesizePublic(Vector2, rangeY, RangeY); // Y의 범위
	SynthesizePublic(float, a, A); // x 기울기, a = INF_A라면 x = b 꼴의 일차함수이다
	SynthesizePublic(float, b, B); // y 절편, a = INF_A라면 x = b 꼴의 일차함수이다

public:
	LinearFunc() {}
	LinearFunc(Vector2 start, Vector2 end);

	LINEAR_VALUE_TYPE getValueType(float x, float y);
	
	float getX(float y) { return (y - b) / a; }
	float getY(float x) { return a * x + b; }

public:
	// start, end : 선분을 구하기 위한 두 점, rangeX : X의 범위, rangeY : Y의 범위
	static LinearFunc getLinearFuncFromPoints(Vector2 pointA, Vector2 pointB, Vector2 rangeX, Vector2 rangeY);
};;
