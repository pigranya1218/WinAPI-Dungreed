#include "stdafx.h"
#include "CostumeManager.h"
#include "Costume.h"
#include "MetalPlateCos.h"
#include "PickaxCos.h"
#include "BaseCos.h"
#include "AliceCos.h"
#include "RedLotusCos.h"

void CostumeManager::init()
{
	Costume* baseCos = new BaseCos;
	baseCos->init();
	_costumeMap.insert(pair<COSTUME_TYPE, Costume*>(COSTUME_TYPE::BASE, baseCos));

	Costume* metalPlateCos = new MetalPlateCos;
	metalPlateCos->init();
	_costumeMap.insert(pair<COSTUME_TYPE, Costume*>(COSTUME_TYPE::METAL_PLATE, metalPlateCos));

	Costume* pickaxCos = new PickaxCos;
	pickaxCos->init();
	_costumeMap.insert(pair<COSTUME_TYPE, Costume*>(COSTUME_TYPE::PICKAX, pickaxCos));

	Costume* aliceCos = new AliceCos;
	aliceCos->init();
	_costumeMap.insert(pair<COSTUME_TYPE, Costume*>(COSTUME_TYPE::ALICE, aliceCos));

	Costume* redLotusCos = new RedLotusCos;
	redLotusCos->init();
	_costumeMap.insert(pair<COSTUME_TYPE, Costume*>(COSTUME_TYPE::RED_LOTUS, redLotusCos));
}

void CostumeManager::release()
{
	for (auto iter = _costumeMap.begin(); iter != _costumeMap.end(); iter++)
	{
		iter->second->release();
		delete iter->second;
	}
	_costumeMap.clear();
}
