#include "stdafx.h"
#include "FloatRect.h"


/**************************************************************************************************
## FloatRect::FloatRect ##
**************************************************************************************************/
FloatRect::FloatRect()
	:left(0.f), top(0.f), right(0.f), bottom(0.f) {}

FloatRect::FloatRect(const float& left, const float& top, const float& right, const float& bottom)
	: left(left), top(top), right(right), bottom(bottom) {}

FloatRect::FloatRect(const int& left, const int& top, const int& right, const int& bottom)
	: left((float)left), top((float)top), right((float)right), bottom((float)bottom) {}

FloatRect::FloatRect(const Vector2& pos, const Vector2& size, const Pivot& pivot)
{
	*this = rectMakePivot(pos, size, pivot);
}

FloatRect::FloatRect(const RECT& rc)
	:left((float)rc.left), top((float)rc.top), right((float)rc.right), bottom((float)rc.bottom) {}

/**************************************************************************************************
## FloatRect::GetRect ##
@@ return RECT : LONG형 RECT로 변환 후 반환
**************************************************************************************************/
const RECT FloatRect::getRect()
{
	return { (LONG)left,(LONG)top,(LONG)right,(LONG)bottom };
}
float FloatRect::getWidth()
{
	return right - left;
}
float FloatRect::getHeight()
{
	return bottom - top;
}
/**************************************************************************************************
## FloatRect::GetCenter ##
@@ return Vector2 : 중심 좌표
**************************************************************************************************/
Vector2 FloatRect::getCenter()
{
	return Vector2(left + (right - left) / 2.f, top + (bottom - top) / 2.f);
}
Vector2 FloatRect::getBottom()
{
	return Vector2(left + (right - left) / 2.f, bottom);
}
Vector2 FloatRect::getSize()
{
	return Vector2((right - left), (bottom - top));
}
/**************************************************************************************************
## FloatRect::Update ##
@@ Vector2 pos : 좌표
@@ Vector2 size : 사이즈
@@ Pivot pivot : 피봇

FLOATRECT 정보 갱신
**************************************************************************************************/
void FloatRect::update(const Vector2& pos, const Vector2& size, const Pivot& pivot)
{
	*this = ::rectMakePivot(pos, size, pivot);
}
/**************************************************************************************************
## FloatRect::Move ##
@@ Vector2 moveValue : 이동방향 * 이동량
**************************************************************************************************/
void FloatRect::move(const Vector2& moveValue)
{
	left += moveValue.x;
	right += moveValue.x;
	top += moveValue.y;
	bottom += moveValue.y;
}

/**************************************************************************************************
## FloatRect::operator = ##
@@ RECT rc : RECT
***************************************************************************************************/
const FloatRect& ::FloatRect::operator=(const RECT& rc)
{
	this->left = (float)rc.left;
	this->right = (float)rc.right;
	this->top = (float)rc.top;
	this->bottom = (float)rc.bottom;
	return *this;
}

bool FloatRect::intersect(FloatRect rc1, FloatRect rc2)
{
	if ((rc1.top < rc2.bottom) &&
		(rc1.bottom > rc2.top) &&
		(rc1.left < rc2.right) &&
		(rc1.right > rc2.left))
	{
		return true;
	}
	return false;
}

