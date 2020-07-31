#pragma once

enum class LINEAR_VALUE_TYPE
{
	UP, // 선분의 위에 있음
	ON, // 선분 위에 얹혀있음
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
	SynthesizePublic(float, a, A); // x 기울기
	SynthesizePublic(float, b, B); // y 절편

public:
	LinearFunc() {}
	LinearFunc(float a, float b) :a(a), b(b) {}
	LinearFunc(Vector2 start, Vector2 end);

	LINEAR_VALUE_TYPE getValueType(float x, float y);
	
	float getX(float y) { return (y - b) / a; }
	float getY(float x) { return a * x + b; }

public:
	static LinearFunc getLinearFuncFromPoints(Vector2 start, Vector2 end);
};
