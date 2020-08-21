#include "Npc.h"
#include "NpcManager.h"
#include "UIManager.h"

void Npc::update(float timeElapsed)
{
	Vector2 moveDir(0, 0);
	_force.y += 80 * timeElapsed;
	moveDir.y += _force.y;
	_npcMgr->moveTo(this, moveDir);
	if (_isStand)
	{
		_force.y = 0;
	}

	Vector2 playerPos = _npcMgr->getPlayerPos();
	if (!_isActiveInteraction)
	{
		float distance = TTYONE_UTIL::getDistance(_position.x, _position.y, playerPos.x, playerPos.y);
		if (distance < 200)
		{
			_isClose = true;
		}
		else
		{
			_isClose = false;
		}
	}
	else
	{
	}

	if (_isClose) // 플레이어랑 가까울 때
	{
		if (!_isActiveInteraction && KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::INTERACTION)))
		{
			interaction();
		}
	}
}

void Npc::render()
{
	if (_isClose && !_isActiveInteraction)
	{
		Vector2 renderPos = _position;
		renderPos.y -= 80;
		CONFIG_MANAGER->getKeyImage(CONFIG_MANAGER->getKey(ACTION_TYPE::INTERACTION))->setScale(4);
		CONFIG_MANAGER->getKeyImage(CONFIG_MANAGER->getKey(ACTION_TYPE::INTERACTION))->setAlpha(0.8);
		CONFIG_MANAGER->getKeyImage(CONFIG_MANAGER->getKey(ACTION_TYPE::INTERACTION))->render(CAMERA->getRelativeV2(renderPos));
	}
}
