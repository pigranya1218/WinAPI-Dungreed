#include "stdafx.h"
#include "FloatCircle.h"

bool FloatCircle::intersect(FloatRect rc)
{
	POINT circleCenter = { origin.x, origin.y };
	if (rc.ptInRect(circleCenter)) // 호의 중점이 사각형 안에 있는 경우 (원이 더 작은 경우)
	{
		// 무조건 교차함
		return true;
	}

	// (원이 큰 경우)
	if (TTYONE_UTIL::getDistance(rc.getCenter().x, rc.getCenter().y, origin.x, origin.y) < size)
	{
		float radian = atan2f(-(rc.getCenter().y - origin.y), (rc.getCenter().x - origin.x));
		if (radian < 0)
		{
			radian += PI;
		}
		if (isInsideRadian(radian))
		{
			return true;
		}
	}
	// 사각형의 모서리와 교차점 비교 (원과 사각형의 크기가 비슷한 경우)
	else if (isCollisionX(rc.left, Vector2(rc.top, rc.bottom)) || isCollisionX(rc.right, Vector2(rc.top, rc.bottom)) || isCollisionY(rc.top, Vector2(rc.left, rc.right)) || isCollisionY(rc.bottom, Vector2(rc.left, rc.right)))
	{
		return true;
	}

	
	return false;
}

bool FloatCircle::isCollisionX(float x, Vector2 rangeY)
{
	if (origin.x - size <= x && x <= origin.x + size)
	{
		float result = sqrt(size * size - (x - origin.x) * (x - origin.x));
		if (result < 0) return false;
		result = sqrt(result);
		float y[2] = { result + origin.y, -result + origin.y };
		bool isCollision = false;
		for (int i = 0; i < 2; i++)
		{
			//if (rangeY.x <= y[i] && y[i] <= rangeY.y)
			{
				float radian = atan2f(-(y[i] - origin.y), (x - origin.x));
				if (radian < 0)
				{
					radian += PI2;
				}
				isCollision |= isInsideRadian(radian);
			}
		}

		return isCollision;
	}
	return false;
}

bool FloatCircle::isCollisionY(float y, Vector2 rangeX)
{
	if (origin.y - size <= y && y <= origin.y + size)
	{
		float result = size * size - (y - origin.y) * (y - origin.y);
		if (result < 0) return false;
		result = sqrt(result);
		float x[2] = { result + origin.x, -result + origin.x };
		bool isCollision = false;
		for (int i = 0; i < 2; i++)
		{
			//if (rangeX.x <= x[i] && x[i] <= rangeX.y)
			{
				float radian = atan2f(-(y - origin.y), (x[i] - origin.x));
				if (radian < 0)
				{
					radian += PI2;
				}
				isCollision |= isInsideRadian(radian);
			}
		}

		return isCollision;
	}
	return false;
}

bool FloatCircle::isInsideRadian(float radian)
{
	float sRadian = startRadian;
	float eRadian = endRadian;
	if (sRadian < 0)
	{
		sRadian += PI2;
		eRadian += PI2;
		radian += PI2;
	}

	return (sRadian <= radian && radian <= eRadian);
}
