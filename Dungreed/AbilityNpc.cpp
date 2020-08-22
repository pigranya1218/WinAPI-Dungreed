#include "AbilityNpc.h"

void AbilityNpc::init(Vector2 pos, DIRECTION direction)
{
	_type = NPC_TYPE::ABILITY;
	_mapIcon = IMAGE_MANAGER->findImage("UI/MAP/ICON_NPC");
}

void AbilityNpc::release()
{
}

void AbilityNpc::update(float timeElapsed)
{
}

void AbilityNpc::interaction()
{
}

void AbilityNpc::render()
{
}

void AbilityNpc::clickMenu(int menuIndex)
{
}
