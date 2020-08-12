#include "CostumeManager.h"
#include "MetalPlateCos.h"
#include "PickaxCos.h"
#include "DefaultCos.h"

void CostumeManager::init()
{
	_costumeMap.insert(pair<COSTUME_TYPE, Costume*>(COSTUME_TYPE::DEFAULT, new DefaultCos));
	_costumeMap.insert(pair<COSTUME_TYPE, Costume*>(COSTUME_TYPE::METAL_PLATE, new MetalPlateCos));
	_costumeMap.insert(pair<COSTUME_TYPE, Costume*>(COSTUME_TYPE::PICKAX, new PickaxCos));
}

void CostumeManager::release()
{
}

void CostumeManager::update()
{
	// _costume->getCostume();
	
}

void CostumeManager::render()
{
}
