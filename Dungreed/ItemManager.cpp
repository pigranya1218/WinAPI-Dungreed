#include "stdafx.h"
#include "ItemManager.h"
#include "Item.h"

#include "babyGreenBat.h"
#include "bombPouch.h"
#include "daisyRing.h"
#include "DemonBoots.h"
#include "GreenBat.h"
#include "GreenDadBat.h"
#include "GreenMomBat.h"
#include "HeartOfCosmos.h"
#include "IceBall.h"
#include "MagnifyingGlass.h"
#include "MetalBoots.h"
#include "MultiBullet.h"
#include "Seeri.h"
#include "SilverBullet.h"
#include "SpikeBall.h"
#include "Voluspa.h"
#include "watCher.h"
#include "Wingboots.h"

#include "Boomerang.h"
#include "GatlingGun.h"
#include "MagicStick.h"
#include "MatchLockGun.h"
#include "OakBow.h"

#include "BigPaintBlush.h"
#include "CosmosSword.h"
#include "KeresScythe.h"
#include "MartialArtOfTiger.h"
#include "PickaxeRed.h"
#include "PowerKatana.h"
#include "Punch.h"
#include "QuarterStaffBig.h"
#include "ShortSpear.h"
#include "ShortSword.h"

void ItemManager::init()
{
	Item* BabyGreenBat = new babyGreenBat;
	BabyGreenBat->init();
	_itemMap.insert(pair<int, Item*>(BabyGreenBat->getItemCode(), BabyGreenBat));

	Item* BombPouch = new bombPouch;
	BombPouch->init();
	_itemMap.insert(pair<int, Item*>(BombPouch->getItemCode(), BombPouch));

	Item* daisyRing = new DaisyRing;
	daisyRing->init();
	_itemMap.insert(pair<int, Item*>(daisyRing->getItemCode(), daisyRing));

	Item* demonBoots = new DemonBoots;
	demonBoots->init();
	_itemMap.insert(pair<int, Item*>(demonBoots->getItemCode(), demonBoots));

	Item* greenBat = new GreenBat;
	greenBat->init();
	_itemMap.insert(pair<int, Item*>(greenBat->getItemCode(), greenBat));

	Item* greenDadBat = new GreenDadBat;
	greenDadBat->init();
	_itemMap.insert(pair<int, Item*>(greenDadBat->getItemCode(), greenDadBat));

	Item* greenMomBat = new GreenMomBat;
	greenMomBat->init();
	_itemMap.insert(pair<int, Item*>(greenMomBat->getItemCode(), greenMomBat));

	Item* heartOfCosmos = new HeartOfCosmos;
	heartOfCosmos->init();
	_itemMap.insert(pair<int, Item*>(heartOfCosmos->getItemCode(), heartOfCosmos));

	Item* iceBall = new IceBall;
	iceBall->init();
	_itemMap.insert(pair<int, Item*>(iceBall->getItemCode(), iceBall));

	Item* magnifyingGlass = new MagnifyingGlass;
	magnifyingGlass->init();
	_itemMap.insert(pair<int, Item*>(magnifyingGlass->getItemCode(), magnifyingGlass));

	Item* metalBoots = new MetalBoots;
	metalBoots->init();
	_itemMap.insert(pair<int, Item*>(metalBoots->getItemCode(), metalBoots));

	Item* multiBullet = new MultiBullet;
	multiBullet->init();
	_itemMap.insert(pair<int, Item*>(multiBullet->getItemCode(), multiBullet));

	Item* seeri = new Seeri;
	seeri->init();
	_itemMap.insert(pair<int, Item*>(seeri->getItemCode(), seeri));

	Item* silverBullet = new SilverBullet;
	silverBullet->init();
	_itemMap.insert(pair<int, Item*>(silverBullet->getItemCode(), silverBullet));

	Item* spikeBall = new SpikeBall;
	spikeBall->init();
	_itemMap.insert(pair<int, Item*>(spikeBall->getItemCode(), spikeBall));

	Item* voluspa = new Voluspa;
	voluspa->init();
	_itemMap.insert(pair<int, Item*>(voluspa->getItemCode(), voluspa));

	Item* WatCher = new watCher;
	WatCher->init();
	_itemMap.insert(pair<int, Item*>(WatCher->getItemCode(), WatCher));

	Item* wingboots = new Wingboots;
	wingboots->init();
	_itemMap.insert(pair<int, Item*>(wingboots->getItemCode(), wingboots));

	Item* boomerang = new Boomerang;
	boomerang->init();
	_itemMap.insert(pair<int, Item*>(boomerang->getItemCode(), boomerang));

	Item* gatlingGun = new GatlingGun;
	gatlingGun->init();
	_itemMap.insert(pair<int, Item*>(gatlingGun->getItemCode(), gatlingGun));

	Item* magicStick = new MagicStick;
	magicStick->init();
	_itemMap.insert(pair<int, Item*>(magicStick->getItemCode(), magicStick));

	Item* matchLockGun = new MatchLockGun;
	matchLockGun->init();
	_itemMap.insert(pair<int, Item*>(matchLockGun->getItemCode(), matchLockGun));

	Item* oakBow = new OakBow;
	oakBow->init();
	_itemMap.insert(pair<int, Item*>(oakBow->getItemCode(), oakBow));

	Item* bigPaintBlush = new BigPaintBlush;
	bigPaintBlush->init();
	_itemMap.insert(pair<int, Item*>(bigPaintBlush->getItemCode(), bigPaintBlush));

	Item* cosmosSword = new CosmosSword;
	cosmosSword->init();
	_itemMap.insert(pair<int, Item*>(cosmosSword->getItemCode(), cosmosSword));

	Item* keresScythe = new KeresScythe;
	keresScythe->init();
	_itemMap.insert(pair<int, Item*>(keresScythe->getItemCode(), keresScythe));

	Item* martialArtOfTiger = new MartialArtOfTiger;
	martialArtOfTiger->init();
	_itemMap.insert(pair<int, Item*>(martialArtOfTiger->getItemCode(), martialArtOfTiger));

	Item* pickaxeRed = new PickaxeRed;
	pickaxeRed->init();
	_itemMap.insert(pair<int, Item*>(pickaxeRed->getItemCode(), pickaxeRed));

	Item* powerKatana = new PowerKatana;
	powerKatana->init();
	_itemMap.insert(pair<int, Item*>(powerKatana->getItemCode(), powerKatana));

	Item* punch = new Punch;
	punch->init();
	_itemMap.insert(pair<int, Item*>(punch->getItemCode(), punch));

	Item* quarterStaffBig = new QuarterStaffBig;
	quarterStaffBig->init();
	_itemMap.insert(pair<int, Item*>(quarterStaffBig->getItemCode(), quarterStaffBig));

	Item* shortSpear = new ShortSpear;
	shortSpear->init();
	_itemMap.insert(pair<int, Item*>(shortSpear->getItemCode(), shortSpear));

	Item* shortSword = new ShortSword;
	shortSword->init();
	_itemMap.insert(pair<int, Item*>(shortSword->getItemCode(), shortSword));
}

void ItemManager::release()
{
	for (auto iter = _itemMap.begin(); iter != _itemMap.end(); ++iter)
	{
		iter->second->release();
		SAFE_DELETE(iter->second);
	}
	_itemMap.clear();
}

vector<Item*> ItemManager::getRandomItem(ITEM_RANK startRank, ITEM_RANK endRank, int count)
{
	// 반환할 벡터
	vector<Item*> result;

	// 해당되는 랭크들을 모을 벡터
	vector<Item*> searchRank;

	// 순회하여 벡터에 담는다
	for (auto iter = _itemMap.begin(); iter != _itemMap.end(); ++iter)
	{
		if (startRank <= iter->second->getItemRank() && iter->second->getItemRank() <= endRank)
		{
			searchRank.push_back(iter->second);
		}
	}

	// 카운트만큼
	for (int i = 0; i < count; i++)
	{
		// 랜덤으로 하나를 지정
		int randomNum = RANDOM->getFromIntTo(0, searchRank.size() - 1);

		// 중복 검사
		bool overLap = false;
		for (int j = 0; j < result.size(); j++)
		{
			// 아이템 코드가 같다면
			if (result[j]->getItemCode() == searchRank[randomNum]->getItemCode())
			{
				// 중복
				overLap = true;
				break;
			}
		}
		// 중복이면
		if (overLap)
		{
			// 다시 돌아간다
			--i;
			continue;
		}
		else
		{
			// 반환값에 추가
			result.push_back(searchRank[randomNum]);
		}
	}

	return result;
}

Item* ItemManager::getItem(int itemCode)
{
	return _itemMap.find(itemCode)->second;
}
