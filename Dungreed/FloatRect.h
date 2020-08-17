#pragma once

#include "AllEnums.h"

class FloatRect final
{
public:
	float left;
	float top;
	float right;
	float bottom;
public:
	FloatRect();
	explicit FloatRect(const float& left, const float& top, const float& right, const float& bottom);
	explicit FloatRect(const int& left, const int& top, const int& right, const int& bottom);
	explicit FloatRect(const Vector2& pos, const Vector2& size, const PIVOT& pivot);
	explicit FloatRect(const RECT& rc);

	const RECT getRect();
	float getWidth();
	float getHeight();
	Vector2 getCenter();
	Vector2 getBottom();
	Vector2 getSize();
	void update(const Vector2& pos, const Vector2& size, const PIVOT& pivot);
	void move(const Vector2& moveValue);
	bool ptInRect(POINT pt) const;
	bool intersectEffect(FloatRect& move);

	const FloatRect& operator=(const RECT& rc);

	static bool intersect(FloatRect rc1, FloatRect rc2);
};

inline FloatRect rectMakePivot(const Vector2& pos, const Vector2& size, const PIVOT& pivot)
{
	FloatRect result;
	switch (pivot)
	{
	case PIVOT::LEFT_TOP:
		result.left = pos.x;
		result.top = pos.y;
		result.right = pos.x + size.x;
		result.bottom = pos.y + size.y;
		return result;
	case PIVOT::CENTER:
		result.left = pos.x - size.x / 2.f;
		result.top = pos.y - size.y / 2.f;
		result.right = pos.x + size.x / 2.f;
		result.bottom = pos.y + size.y / 2.f;
		return result;
	case PIVOT::BOTTOM:
		result.left = pos.x - size.x / 2.f;
		result.top = pos.y - size.y;
		result.right = pos.x + size.x / 2.f;
		result.bottom = pos.y;
		return result;
	}
	return result;
}

