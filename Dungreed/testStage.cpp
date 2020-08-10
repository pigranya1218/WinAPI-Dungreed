#include "TestStage.h"

void TestStage::init()
{
	Stage::init();
	_collisions.push_back({LinearFunc::getLinearFuncFromPoints(Vector2(0, 800), Vector2(WINSIZEX, 800)), LINEAR_VALUE_TYPE::DOWN});
}

void TestStage::release()
{
	Stage::release();
}

void TestStage::update(float const elapsedTime)
{
	Stage::update(elapsedTime);
}

void TestStage::render()
{
	for (int i = 0; i < _collisions.size(); i++)
	{
		D2D_RENDERER->drawLine(_collisions[i].func.getStart(), _collisions[i].func.getEnd());
	}

	Stage::render();

}
