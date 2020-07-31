#pragma once
/****************************************************************************
## Vector2 ##
*****************************************************************************/
class Vector2 final
{
public:
	float x;
	float y;
public:
	explicit Vector2();
	explicit Vector2(const float& x, const float& y);
	explicit Vector2(const int& x, const int& y);
	explicit Vector2(const POINT& pt);

	const int getIntX();
	const int getIntY();
	const POINT getPoint();

	Vector2 operator+ (const Vector2& v);
	Vector2 operator- (const Vector2& v);
	void operator+= (const Vector2& v);
	void operator-= (const Vector2& v);
	Vector2 operator* (const float& scalar);
	Vector2 operator/ (const float& scalar);
	const bool operator==(const Vector2& v);
	const bool operator!=(const Vector2& v);
public:
	static Vector2 normalize(const Vector2* const  pVector2);
	static float toRadian(const Vector2* const pVector2);
	static float length(const Vector2* const pVector2);
	static float dot(const Vector2* const pVector2A, const Vector2* const pVector2B);
	static float cross(const Vector2* const pvector2A, const Vector2* const pVector2B);
};

