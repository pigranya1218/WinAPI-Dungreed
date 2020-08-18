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
		/*float radian = atan2f(-(rc.getCenter().y - origin.y), (rc.getCenter().x - origin.x));
		if (radian < 0)
		{
			radian += PI;
		}
		if (isInsideRadian(radian))
		{
			return true;
		}*/
		
		// 사각형의 꼭지점들에 대하여 각도 계산
		float calcSup[4][2] = { {-0.5, -0.5}, {0.5, -0.5}, {0.5, 0.5}, {-0.5, 0.5} };
		float radians[4];
		for (int i = 0; i < 4; i++)
		{
			Vector2 point = rc.getCenter();
			point.x += calcSup[i][0] * rc.getWidth();
			point.y += calcSup[i][1] * rc.getHeight();
			radians[i] = atan2f(-(point.y - origin.y), (point.x - origin.x));
			if (radians[i] < 0)
			{
				radians[i] += PI2;
			}
		}
		
		// 특이케이스
		if (radians[0] < PI && radians[3] > 1.5 * PI)
		{
			if (isIntersectRadian(Vector2(radians[3] - PI2, radians[0])))
			{
				return true;
			}
		}
		else
		{
			float minRadian = PI2;
			float maxRadian = 0;
			for (int i = 0; i < 4; i++)
			{
				if (minRadian > radians[i])
				{
					minRadian = radians[i];
				}
				if (maxRadian < radians[i])
				{
					maxRadian = radians[i];
				}
			}
			if(isIntersectRadian(Vector2(minRadian, maxRadian)))
			{
				return true;
			}
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
			if (rangeY.x <= y[i] && y[i] <= rangeY.y)
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
			if (rangeX.x <= x[i] && x[i] <= rangeX.y)
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
	return isInsideRadian(radian, Vector2(startRadian, endRadian));
}

bool FloatCircle::isInsideRadian(float radian, Vector2 radianRange)
{
	float sRadian = radianRange.x;
	float eRadian = radianRange.y;
	sRadian += PI2;
	eRadian += PI2;
	radian += PI2;
	if (sRadian > PI2) sRadian -= PI2;
	if (eRadian > PI2) eRadian -= PI2;
	if (radian > PI2) radian -= PI2;

	if (sRadian <= eRadian) // 정상 판별의 경우
	{
		return (sRadian <= radian && radian <= eRadian);
	}
	else
	{
		return !(eRadian <= radian && radian <= sRadian);
	}

}

bool FloatCircle::isIntersectRadian(Vector2 rangeRadian)
{
	float oppStartRadian = rangeRadian.x;
	float oppEndRadian = rangeRadian.y;
	float sRadian = startRadian;
	float eRadian = endRadian;
	if (isInsideRadian(oppStartRadian, Vector2(sRadian, eRadian)) ||
		isInsideRadian(oppEndRadian, Vector2(sRadian, eRadian)) ||
		isInsideRadian(sRadian, Vector2(oppStartRadian, oppEndRadian)) ||
		isInsideRadian(eRadian, Vector2(oppStartRadian, oppEndRadian)))
	{
		return true;
	}

	return false;
}

void FloatCircle::render(bool useCamera)
{
	Vector2 renderOrigin = origin;
	if (useCamera)
	{
		renderOrigin = CAMERA->getRelativeV2(renderOrigin);
	}
	D2D_RENDERER->drawEllipse(renderOrigin, size, D2D1::ColorF::Enum::Black, 2);
	D2D_RENDERER->drawLine(renderOrigin, Vector2(renderOrigin.x + cosf(startRadian) * size, renderOrigin.y + -sinf(startRadian) * size));
	D2D_RENDERER->drawLine(renderOrigin, Vector2(renderOrigin.x + cosf(endRadian) * size, renderOrigin.y + -sinf(endRadian) * size));
}
