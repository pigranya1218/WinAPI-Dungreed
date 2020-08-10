#include "TestScene.h"

HRESULT TestScene::init()
{

	playerx = WINSIZEX / 2;
	playery = WINSIZEY / 2;

	x = 0;
	y = 0;

	angle = PI / 2;
	speed = 1.5f;

	RC[0] = FloatRect(Vector2(playerx + x, playery + y), Vector2(25, 25), PIVOT::CENTER);

	RC[1] = FloatRect(Vector2(playerx , playery ), Vector2(50, 50), PIVOT::CENTER);




	// 에너미 테스트입니다.
	_em = new EnemyManager;
	_em->init();
	_em->setScene(this);
	_em->spawn(Vector2(WINSIZEX / 2, WINSIZEY / 2), ENEMY_TYPE::BAT_RED);




	return S_OK;
}

void TestScene::release()
{
}

void TestScene::update()
{
	// 에너미 테스트입니다.
	_em->update();



	if (KEY_MANAGER->isStayKeyDown(VK_LEFT))
	{
		playerx -= 4;
	}
	if (KEY_MANAGER->isStayKeyDown(VK_RIGHT))
	{
		playerx += 4;
	}
	if (KEY_MANAGER->isStayKeyDown(VK_UP))
	{
		playery -= 4;
	}
	if (KEY_MANAGER->isStayKeyDown(VK_DOWN))
	{
		playery += 4;
	}


	angle += 0.033f;
	x = cosf(angle)*speed * 80; // 30이 공전 반지름 이라 늘리면 거리가늘어남
	y = -sinf(angle)*speed * 80;


	RC[0] = FloatRect(Vector2(playerx + x, playery + y), Vector2(25, 25), PIVOT::CENTER);

	RC[1] = FloatRect(Vector2(playerx, playery), Vector2(50, 50), PIVOT::CENTER);

	
}

void TestScene::render()
{
	Rectangle(_hdc, RC[0].left, RC[0].top, RC[0].right, RC[0].bottom);
	Rectangle(_hdc, RC[1].left, RC[1].top, RC[1].right, RC[1].bottom);


	// 에머니 테스트입니다.
	_em->render();
}

void TestScene::moveGameObject(GameObject * gObject, Vector2& movePos)
{
	if (gObject->getRect().left <= 0)
	{
		FloatRect temp(0.0f, gObject->getRect().getSize().x, gObject->getRect().top, gObject->getRect().bottom);

		movePos = temp.getCenter();
	}
}

