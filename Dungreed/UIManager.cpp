#include "stdafx.h"
#include "UIManager.h"
#include "Player.h"
#include "StageManager.h"
#include "Item.h"

void UIManager::setPlayer(Player * player)
{
	_player = player;
	_inventoryUI.setPlayer(player);
	_statUI.setPlayer(player);
	_costumeUI.setPlayer(player);
	_restaurantUI.setPlayer(player);
	_abilityUI.setPlayer(player);
}

void UIManager::init()
{
	_isActive = false;

	// HP BAR
	_hpUI.hpBgImg = IMAGE_MANAGER->findImage("UI/PLAYER_LIFE_BG");
	_hpUI.hpFrameImg = IMAGE_MANAGER->findImage("UI/PLAYER_LIFE_FRAME");
	_hpUI.hpBarImg = IMAGE_MANAGER->findImage("UI/PLAYER_LIFE_BAR");
	_hpUI.hpWaveImg = IMAGE_MANAGER->findImage("UI/PLAYER_LIFE_WAVE");
	_hpUI.hpBg = FloatRect(20, 20, 390, 100);
	_hpUI.hpLevel = FloatRect(20, 20, 135, 100);
	_hpUI.hpBar = FloatRect(120, 30, 390, 90);

	_hpUI.hpAni = new Animation;
	_hpUI.hpAni->init(_hpUI.hpWaveImg->getWidth(), _hpUI.hpWaveImg->getHeight(), _hpUI.hpWaveImg->getMaxFrameX(), _hpUI.hpWaveImg->getMaxFrameY());
	_hpUI.hpAni->setFPS(15);
	_hpUI.hpAni->setDefPlayFrame(false, true);
	_hpUI.hpAni->start();

	_hpUI.dashOutsideImg = IMAGE_MANAGER->findImage("UI/DASH_OUTSIDE");
	_hpUI.dashInsideImg = IMAGE_MANAGER->findImage("UI/DASH_INSIDE");
	_hpUI.dashGaugeImg = IMAGE_MANAGER->findImage("UI/DASH_GAUGE");
	_hpUI.dashFirstCenter = Vector2(50, 125);

	// GOLD UI
	_goldUI.img = IMAGE_MANAGER->findImage("UI/GOLD");
	_goldUI.ani = new Animation;
	_goldUI.ani->init(_goldUI.img->getWidth(), _goldUI.img->getHeight(), _goldUI.img->getMaxFrameX(), _goldUI.img->getMaxFrameY());
	_goldUI.ani->setDefPlayFrame(false, true);
	_goldUI.ani->setFPS(15);
	_goldUI.ani->start();
	_goldUI.imgRc = FloatRect(30, 796, 56, 822);
	_goldUI.textRc = FloatRect(80, 798, 200, 821);
	_goldUI.fontSize = 23;

	// SATIETY UI
	_satietyUI.img = IMAGE_MANAGER->findImage("UI/FOOD");
	_satietyUI.imgRc = FloatRect(20, 835, 70, 880);
	_satietyUI.textRc = FloatRect(80, 837, 200, 850);
	_satietyUI.fontSize = 23;
	_satietyProgress.progressRc = FloatRect(80, 860, 200, 870);

	// WEAPON UI
	_weaponUI.bgImg = IMAGE_MANAGER->findImage("UI/WEAPON_BG");
	_weaponUI.frontBaseCenter = Vector2(1480, 820);
	_weaponUI.backBaseCenter = Vector2(1500, 800);
	_weaponUI.frontIndexRc = FloatRect(50, 20, 60, 40);
	_weaponUI.frontBulletRc = FloatRect(-80, 18, 80, 42);
	_weaponUI.move = Vector2(0, 0);
	_weaponUI.moveSpeed = 80;
	_weaponUI.viewIndex = 0;

	// MAP UI
	_mapUI.headerImg = IMAGE_MANAGER->findImage("UI/MAP/HEADER");
	_mapUI.bodyImg = IMAGE_MANAGER->findImage("UI/MAP/BODY");
	_mapUI.nameImg = IMAGE_MANAGER->findImage("UI/MAP/NAME_BG");
	_mapUI.roomImg = IMAGE_MANAGER->findImage("UI/MAP/ROOM");
	_mapUI.titleRc = FloatRect(Vector2(960, 770), Vector2(600, 100), PIVOT::CENTER);

	_mapUI.infos[0].text = L"당신의 위치";
	_mapUI.infos[1].text = L"다음층으로 가는 길";
	_mapUI.infos[2].text = L"비밀통로";
	_mapUI.infos[3].text = L"상점";
	_mapUI.infos[4].text = L"음식점";

	_mapUI.infos[1].img = IMAGE_MANAGER->findImage("UI/MAP/ICON_EXIT");
	_mapUI.infos[2].img = IMAGE_MANAGER->findImage("UI/MAP/ICON_WORM");
	_mapUI.infos[3].img = IMAGE_MANAGER->findImage("UI/MAP/ICON_SHOP");
	_mapUI.infos[4].img = IMAGE_MANAGER->findImage("UI/MAP/ICON_FOOD");

	for (int i = 0; i < 5; i++)
	{
		_mapUI.infos[i].fontSize = 28;
		_mapUI.infos[i].imgRc = FloatRect(Vector2(210, 650 + 36 * i), Vector2(40, 40), PIVOT::CENTER);
		_mapUI.infos[i].textRc = FloatRect(Vector2(390, 650 + 36 * i), Vector2(300, 40), PIVOT::CENTER);
	}

	// DIALOGUE UI
	_dialogueUI.init();

	// INVENTORY UI
	_inventoryUI.init();

	// STATUS UI
	_statUI.init();

	// COSTUME UI
	_costumeUI.init();

	// RESTAURANT UI
	_restaurantUI.init();

	// ABILITY UI
	_abilityUI.init();
}

void UIManager::release()
{
	_inventoryUI.release();
	_statUI.release();
	_costumeUI.release();
	_restaurantUI.release();
	_abilityUI.release();
}

void UIManager::update(float const elapsedTime)
{
	// Damage UI update
	for (int i = 0; i < _damageUI.size();)
	{
		tagDamageUI damageUI = _damageUI[i];
		if (_damageUI[i].remainTimes < 0)
		{
			if (_damageUI[i].alpha == 0)
			{
				_damageUI.erase(_damageUI.begin() + i);
				continue;
			}
			else
			{
				_damageUI[i].alpha = max(0, _damageUI[i].alpha - elapsedTime * 2.5);
			}
		}
		else
		{
			_damageUI[i].pos.y -= elapsedTime * 40;
			_damageUI[i].remainTimes -= elapsedTime;
		}
		i++;

	}

	// HP bar animation
	_hpUI.hpAni->frameUpdate(elapsedTime);

	// Gold icon animation
	_goldUI.ani->frameUpdate(elapsedTime);

	// Weapon change animation
	if (_player->getWeaponIndex() != _weaponUI.viewIndex)
	{
		_weaponUI.move.x = min(20, _weaponUI.move.x + _weaponUI.moveSpeed * elapsedTime);
		_weaponUI.move.y = max(-20, _weaponUI.move.y - _weaponUI.moveSpeed * elapsedTime);
		if (_weaponUI.move.x == 20)
		{
			_weaponUI.move.x = 0;
			_weaponUI.move.y = 0;
			_weaponUI.viewIndex = _player->getWeaponIndex();
		}
	}

	// Map Open
	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::MAP)))
	{
		_mapUI.isShow = !_mapUI.isShow;
	}

	if (KEY_MANAGER->isOnceKeyUp(CONFIG_MANAGER->getKey(ACTION_TYPE::MAP)))
	{
		_mapUI.isShow = false;
		_mapUI.offset = Vector2(0, 0);
		_mapUI.isDrag = false;
		_mapUI.twinkleDelay = 0;
		_mapUI.gate = nullptr;
	}

	if(_mapUI.isShow)
	{
		_mapUI.twinkleDelay += elapsedTime;
		if (_mapUI.twinkleDelay > 0.5)
		{
			_mapUI.twinkleDelay = 0;
			_mapUI.fillCurrRoom = !_mapUI.fillCurrRoom;
		}
		if (_mapUI.gate != nullptr && KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::ATTACK)))
		{
			int centerX = WINSIZEX / 2 + _mapUI.offset.x;
			int centerY = 450 + _mapUI.offset.y;

			// 방 및 아이콘 그리기
			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					if (_mapUI.currIndex.x == x && _mapUI.currIndex.y == y) continue;
					if (_mapUI.uiMap[x][y].exist)
					{
						int offsetX = (x - _mapUI.currIndex.x) * (30 + 114);
						int offsetY = (y - _mapUI.currIndex.y) * (30 + 114);
						for (int i = 0; i < _mapUI.uiMap[x][y].npcs.size(); i++)
						{
							FloatRect relativeRc = FloatRect(Vector2(centerX + offsetX + _mapUI.uiMap[x][y].npcs[i].center.x, centerY + offsetY + _mapUI.uiMap[x][y].npcs[i].center.y), Vector2(34, 28), PIVOT::CENTER);
							if (_mapUI.uiMap[x][y].npcs[i].type == NPC_TYPE::GATE && relativeRc.ptInRect(_ptMouse))
							{
								_mapUI.gate->move(Vector2(x, y));
								_mapUI.isShow = false;
								_mapUI.offset = Vector2(0, 0);
								_mapUI.isDrag = false;
								_mapUI.twinkleDelay = 0;
								_mapUI.gate = nullptr;
								return;
							}
						}
					}
				}
			}
		}
		else if (KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::ATTACK)))
		{
			_mapUI.offset.x += _ptMouse.x - _mapUI.lastMoustpt.x;
			_mapUI.offset.y += _ptMouse.y - _mapUI.lastMoustpt.y;
		}
		_mapUI.lastMoustpt = _ptMouse;

		
	}

	// Inventory Open
	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::INVENTORY)))
	{
		// toggle
		_inventoryUI.setActive(!_inventoryUI.isActive());
	}
	// Status Open
	if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::STAT)))
	{
		_statUI.setActive(!_statUI.isActive());
	}
	// Boutique(CostumeUI) Open
	if (KEY_MANAGER->isOnceKeyDown(VK_F1))
	{
		_costumeUI.setActive(!_costumeUI.isActive());
	}
	// Restaurant Open
	if (KEY_MANAGER->isOnceKeyDown(VK_F2))
	{
		_restaurantUI.setActive(!_restaurantUI.isActive());
	}
	// TrainingHouse(Ability) Open
	if (KEY_MANAGER->isOnceKeyDown(VK_F3))
	{
		_abilityUI.setActive(!_abilityUI.isActive());
	}

	bool isClose = false;
	if (KEY_MANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		isClose = true;
	}

	if (_mapUI.isShow)
	{
		if (isClose)
		{
			_mapUI.isShow = false;
			isClose = false;
		}
	}

	if (_dialogueUI.isActive())
	{
		if (isClose)
		{
			_dialogueUI.setActive(false);
			isClose = false;
		}
		else
		{
			_dialogueUI.update(elapsedTime);
		}
	}
	if (_inventoryUI.isActive())
	{
		if (isClose)
		{
			_inventoryUI.setActive(false);
			isClose = false;
		}
		else
		{
			_inventoryUI.update(elapsedTime);
		}
	}
	if (_statUI.isActive())
	{
		if (isClose)
		{
			_statUI.setActive(false);
			isClose = false;
		}
		else
		{
			_statUI.update(elapsedTime);
		}
	}
	if (_costumeUI.isActive())
	{
		if (isClose)
		{
			_costumeUI.setActive(false);
			isClose = false;
		}
		else
		{
			_costumeUI.update(elapsedTime);
		}
	}
	if (_restaurantUI.isActive())
	{
		if (isClose)
		{
			_restaurantUI.setActive(false);
			isClose = false;
		}
		else
		{
			_restaurantUI.update(elapsedTime);
		}
	}
	if (_abilityUI.isActive())
	{
		if (isClose)
		{
			_abilityUI.setActive(false);
			isClose = false;
		}
		else
		{
			_abilityUI.update(elapsedTime);
		}
	}

	_isActive = false;
	_isActive |= _mapUI.isShow;
	_isActive |= _dialogueUI.isActive();
	_isActive |= _inventoryUI.isActive();
	_isActive |= _statUI.isActive();
	_isActive |= _costumeUI.isActive();
	_isActive |= _restaurantUI.isActive();
	_isActive |= _abilityUI.isActive();
}

void UIManager::render()
{
	if (_isActive)
	{

	}
	{
		// DAMAGE UI
		for (int i = 0; i < _damageUI.size(); i++)
		{
			switch (_damageUI[i].type)
			{
			case 0: // 대미지 입음
			{
				D2D_RENDERER->renderTextField(CAMERA->getRelativeX(_damageUI[i].pos.x - 50), CAMERA->getRelativeY(_damageUI[i].pos.y),
					to_wstring(static_cast<int>(_damageUI[i].value)), _damageUI[i].textColor, _damageUI[i].fontSize,
					100, _damageUI[i].fontSize, _damageUI[i].alpha, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aa카시오페아");
			}
			break;
			case 1: // 회피
			{
				D2D_RENDERER->renderTextField(CAMERA->getRelativeX(_damageUI[i].pos.x - 100), CAMERA->getRelativeY(_damageUI[i].pos.y),
					L"EVADE", _damageUI[i].textColor, _damageUI[i].fontSize,
					200, _damageUI[i].fontSize, _damageUI[i].alpha, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aa카시오페아");
			}
			break;
			case 2: // 블록
			{
				D2D_RENDERER->renderTextField(CAMERA->getRelativeX(_damageUI[i].pos.x - 100), CAMERA->getRelativeY(_damageUI[i].pos.y),
					L"BLOCK", _damageUI[i].textColor, _damageUI[i].fontSize,
					200, _damageUI[i].fontSize, _damageUI[i].alpha, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aa카시오페아");
			}
			break;
			}
			
		}

		// ENEMY HP UI
		for (int i = 0; i < _enemyHpUI.size(); i++)
		{
			FloatRect bg = FloatRect(_enemyHpUI[i].pos, Vector2(64, 20), PIVOT::CENTER);
			FloatRect gage = FloatRect(_enemyHpUI[i].pos, Vector2(60, 16), PIVOT::CENTER);
			gage.right = gage.left + (_enemyHpUI[i].currHp / _enemyHpUI[i].maxHp) * gage.getWidth();
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(bg), 16, 15, 28, 1);
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(gage), 133, 14, 0, 1);
		}
		_enemyHpUI.clear();

		// PLAYER HPBAR
		_hpUI.hpBgImg->render(_hpUI.hpBg.getCenter(), _hpUI.hpBg.getSize());
		float hpRatio = (static_cast<float>(_player->getCurrHp()) / _player->getMaxHp());
		float width = (_hpUI.hpBar.getSize().x) * hpRatio;
		if (FLOAT_EQUAL(hpRatio, 1) || FLOAT_EQUAL(hpRatio, 0))
		{
			FloatRect hpBar = FloatRect(_hpUI.hpBar.left, _hpUI.hpBar.top, _hpUI.hpBar.left + width, _hpUI.hpBar.bottom);
			_hpUI.hpBarImg->render(hpBar.getCenter(), hpBar.getSize());
		}
		else
		{
			FloatRect hpBar = FloatRect(_hpUI.hpBar.left, _hpUI.hpBar.top, max(_hpUI.hpBar.left + 1, _hpUI.hpBar.left + width - 14), _hpUI.hpBar.bottom);
			_hpUI.hpBarImg->render(hpBar.getCenter(), hpBar.getSize());
			FloatRect hpWave = FloatRect(hpBar.right - 1, hpBar.top, hpBar.right + 14, hpBar.bottom);
			_hpUI.hpWaveImg->aniRender(hpWave.getCenter(), hpWave.getSize(), _hpUI.hpAni);
		}
				
		_hpUI.hpFrameImg->render(_hpUI.hpBg.getCenter(), _hpUI.hpBg.getSize());
		D2D_RENDERER->renderTextField(_hpUI.hpLevel.left, _hpUI.hpLevel.top, to_wstring(_player->getLevel()), RGB(255, 255, 255), 
			45, _hpUI.hpLevel.getSize().x, _hpUI.hpLevel.getSize().y, 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aa카시오페아");
		D2D_RENDERER->renderTextField(_hpUI.hpBar.left, _hpUI.hpBar.top, (to_wstring(_player->getCurrHp()) + L"/" + to_wstring(_player->getMaxHp())), RGB(255, 255, 255),
			40, _hpUI.hpBar.getSize().x, _hpUI.hpBar.getSize().y, 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aa카시오페아");

		for (int i = 0; i < _player->getMaxDash(); i++)
		{
			Vector2 dashCenter = _hpUI.dashFirstCenter;
			if (i > 0)
			{
				dashCenter.x += _hpUI.dashOutsideImg->getWidth() * 2.5 + _hpUI.dashInsideImg->getWidth() * 2.5;
				if (i > 1)
				{
					dashCenter.x += _hpUI.dashInsideImg->getWidth() * 5 * (i - 1);
				}
				if (i == _player->getMaxDash() - 1)
				{
					dashCenter.x -= _hpUI.dashInsideImg->getWidth() * 2.5;
					dashCenter.x += _hpUI.dashOutsideImg->getWidth() * 2.5;
				}
			}
			if (i == 0)
			{
				_hpUI.dashOutsideImg->setScale(5);
				_hpUI.dashOutsideImg->render(dashCenter);
			}
			else if (i == _player->getMaxDash() - 1)
			{
				_hpUI.dashOutsideImg->setScale(5);
				_hpUI.dashOutsideImg->render(dashCenter, true);
			}
			else
			{
				_hpUI.dashInsideImg->setScale(5);
				_hpUI.dashInsideImg->render(dashCenter);
			}
			
			if ((i + 1) <= _player->getCurrDash())
			{
				if (i == 0)
				{
					dashCenter.x += 5;
				}
				else if (i == _player->getMaxDash() - 1)
				{
					dashCenter.x -= 5;
				}
				_hpUI.dashGaugeImg->setScale(5);
				_hpUI.dashGaugeImg->render(dashCenter);
			}
		}

		// PLAYER GOLD
		_goldUI.img->aniRender(_goldUI.imgRc.getCenter(), _goldUI.imgRc.getSize(), _goldUI.ani);
		D2D_RENDERER->renderTextField(_goldUI.textRc.left, _goldUI.textRc.top, to_wstring(_player->getGold()) + L"G", RGB(255, 255, 255),
			_goldUI.fontSize, _goldUI.textRc.getSize().x, _goldUI.textRc.getSize().y, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아");

		// PLAYER SATIETY
		_satietyUI.img->render(_satietyUI.imgRc.getCenter(), _satietyUI.imgRc.getSize());
		D2D_RENDERER->renderTextField(_satietyUI.textRc.left, _satietyUI.textRc.top, to_wstring(_player->getSatiety()) + L" / " + to_wstring(_player->getMaxSatiety()), RGB(255, 255, 255),
			_satietyUI.fontSize, _satietyUI.textRc.getSize().x, _satietyUI.textRc.getSize().y, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아");
		D2D_RENDERER->fillRectangle(_satietyProgress.progressRc, 34, 32, 52, 1);
		FloatRect satietyGauge = _satietyProgress.progressRc;
		satietyGauge.right = satietyGauge.left + (static_cast<float>(_player->getSatiety()) / _player->getMaxSatiety()) * satietyGauge.getSize().x;
		D2D_RENDERER->fillRectangle(satietyGauge, 255, 206, 78, 1);
	
		// PLAYER WEAPON
		if (_weaponUI.move.x <= 10)
		{
			_weaponUI.bgImg->setScale(5);
			_weaponUI.bgImg->render(_weaponUI.backBaseCenter - _weaponUI.move);
			_weaponUI.bgImg->setScale(5);
			_weaponUI.bgImg->render(_weaponUI.frontBaseCenter + _weaponUI.move);
			for (int i = 0; i <= _weaponUI.viewIndex; i++)
			{
				FloatRect drawRc = FloatRect(_weaponUI.frontBaseCenter + _weaponUI.move + _weaponUI.frontIndexRc.getCenter(), _weaponUI.frontIndexRc.getSize(), PIVOT::CENTER);
				drawRc.left -= i * _weaponUI.frontIndexRc.getSize().x;
				drawRc.right -= i * _weaponUI.frontIndexRc.getSize().x;

				D2D_RENDERER->fillRectangle(drawRc, 255, 255, 255, 1);
				D2D_RENDERER->drawRectangle(drawRc, 34, 32, 52, 1, 5);
			}

			{
				if (_player->getWeapon(_weaponUI.viewIndex) != nullptr)
				{
					FloatRect bulletRc = FloatRect(_weaponUI.frontBaseCenter + _weaponUI.move + _weaponUI.frontBulletRc.getCenter(), _weaponUI.frontBulletRc.getSize(), PIVOT::CENTER);
					D2D_RENDERER->renderTextField(bulletRc.left, bulletRc.top, _player->getWeapon(_weaponUI.viewIndex)->getBulletUI(), RGB(255, 255, 255),
						bulletRc.getHeight(), bulletRc.getWidth(), bulletRc.getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aa카시오페아");
				}
			}

			Vector2 weaponPos = Vector2(_weaponUI.frontBaseCenter + _weaponUI.move);
			weaponPos.x -= 10;
			if (_player->getWeaponImg(_weaponUI.viewIndex) != nullptr)
			{
				_player->getWeaponImg(_weaponUI.viewIndex)->setScale(4);
				_player->getWeaponImg(_weaponUI.viewIndex)->render(weaponPos);
			}

			{
				if (_player->getWeapon(_weaponUI.viewIndex) != nullptr)
				{
					float ratio = _player->getWeapon(_weaponUI.viewIndex)->getBulletRatio();
					if(!FLOAT_EQUAL(0, ratio))
					{
						FloatRect blank = FloatRect(_weaponUI.frontBaseCenter - _weaponUI.move, Vector2(_weaponUI.bgImg->getWidth() * 5.f, _weaponUI.bgImg->getHeight() * 5.f), PIVOT::CENTER);
						FloatRect bulletReloadRc = blank;
						bulletReloadRc.right = blank.right - ratio * blank.getWidth();
						D2D_RENDERER->fillRectangle(bulletReloadRc, D2D1::ColorF::Enum::Black, 0.5);
					}
				}
			}
			
		}
		else if (_weaponUI.move.x >= 10)
		{
			_weaponUI.bgImg->setScale(5);
			_weaponUI.bgImg->render(_weaponUI.frontBaseCenter + _weaponUI.move);
			_weaponUI.bgImg->setScale(5);
			_weaponUI.bgImg->render(_weaponUI.backBaseCenter - _weaponUI.move);
			for (int i = 0; i <= _player->getWeaponIndex(); i++)
			{
				FloatRect drawRc = FloatRect(_weaponUI.backBaseCenter - _weaponUI.move + _weaponUI.frontIndexRc.getCenter(), _weaponUI.frontIndexRc.getSize(), PIVOT::CENTER);
				drawRc.left -= i * _weaponUI.frontIndexRc.getSize().x;
				drawRc.right -= i * _weaponUI.frontIndexRc.getSize().x;

				D2D_RENDERER->fillRectangle(drawRc, 255, 255, 255, 1);
				D2D_RENDERER->drawRectangle(drawRc, 34, 32, 52, 1, 5);
			}

			{
				if (_player->getWeapon(_player->getWeaponIndex()) != nullptr)
				{
					FloatRect bulletRc = FloatRect(_weaponUI.frontBaseCenter + _weaponUI.move + _weaponUI.frontBulletRc.getCenter(), _weaponUI.frontBulletRc.getSize(), PIVOT::CENTER);
					D2D_RENDERER->renderTextField(bulletRc.left, bulletRc.top, _player->getWeapon(_player->getWeaponIndex())->getBulletUI(), RGB(255, 255, 255),
						bulletRc.getHeight(), bulletRc.getWidth(), bulletRc.getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aa카시오페아");
				}
			}

			Vector2 weaponPos = Vector2(_weaponUI.backBaseCenter - _weaponUI.move);
			weaponPos.x -= 10;
			if (_player->getWeaponImg(_player->getWeaponIndex()) != nullptr)
			{
				_player->getWeaponImg(_player->getWeaponIndex())->setScale(4);
				_player->getWeaponImg(_player->getWeaponIndex())->render(weaponPos);
			}
		}

		// Minimap UI
		{
			Vector2 playerPos = _player->getPosition() / 16;

			int offsetX = 1400;
			int offsetY = 90;
			
			int rectOffsetX = offsetX - playerPos.x;
			int rectOffsetY = offsetY - playerPos.y;
			for (int i = 0; i < _miniMapUI.collisionRect.size(); i++)
			{
				FloatRect drawRc = _miniMapUI.collisionRect[i];
			
				drawRc.left += rectOffsetX;
				drawRc.right += rectOffsetX;
				drawRc.top += rectOffsetY;
				drawRc.bottom += rectOffsetY;

				D2D_RENDERER->fillRectangle(drawRc, 192, 193, 195, 1);
			}
			for (int i = 0; i < _miniMapUI.doorRect.size(); i++)
			{
				FloatRect drawRc = _miniMapUI.doorRect[i];

				drawRc.left += rectOffsetX;
				drawRc.right += rectOffsetX;
				drawRc.top += rectOffsetY;
				drawRc.bottom += rectOffsetY;

				D2D_RENDERER->fillRectangle(drawRc, 7, 209, 17, 1);
			}
		
			// ENEMY
			vector<Vector2> enemies = _miniMapUI.enemyMgr->getAllEnemyPos();
			for (int i = 0; i < enemies.size(); i++)
			{
				Vector2 renderPos;
				Vector2 enemyPos = enemies[i] / 16;
				renderPos.x = offsetX + (enemyPos.x - playerPos.x);
				renderPos.y = offsetY + (enemyPos.y - playerPos.y);
				D2D_RENDERER->fillRectangle(FloatRect(renderPos, Vector2(4, 4), PIVOT::CENTER), 255, 97, 82, 1);
				D2D_RENDERER->drawRectangle(FloatRect(renderPos, Vector2(7, 7), PIVOT::CENTER), D2D1::ColorF::Enum::Black, 1, 3);
			}

			// PLAYER			
			D2D_RENDERER->fillRectangle(FloatRect(Vector2(offsetX, offsetY), Vector2(4, 4), PIVOT::CENTER), 84, 144, 255, 1);
			D2D_RENDERER->drawRectangle(FloatRect(Vector2(offsetX, offsetY), Vector2(7, 7), PIVOT::CENTER), D2D1::ColorF::Enum::Black, 1, 3);
		}
		
		// Map UI
		if (_mapUI.isShow)
		{
			D2D_RENDERER->fillRectangle(FloatRect(Vector2(0, 0), Vector2(WINSIZEX, WINSIZEY), PIVOT::LEFT_TOP), 33, 31, 50, 1);
			
			int centerX = WINSIZEX / 2 + _mapUI.offset.x;
			int centerY = 450 + _mapUI.offset.y;

			// 현재 방 깜빡이기
			if (_mapUI.fillCurrRoom)
			{
				D2D_RENDERER->drawRectangle(FloatRect(Vector2(centerX, centerY), Vector2(109, 109), PIVOT::CENTER), 84, 144, 255, 1, 5);
			}

			int selectGateX = -1;
			int selectGateY = -1;
			Vector2 selectCenter;
			// 방 및 아이콘 그리기
			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					if (_mapUI.uiMap[x][y].exist)
					{
						int offsetX = (x - _mapUI.currIndex.x) * (30 + 114);
						int offsetY = (y - _mapUI.currIndex.y) * (30 + 114);
						_mapUI.roomImg->render(Vector2(centerX + offsetX, centerY + offsetY), Vector2(114, 114));

						for (int i = 0; i < _mapUI.uiMap[x][y].npcs.size(); i++)
						{
							FloatRect relativeRc = FloatRect(Vector2(centerX + offsetX + _mapUI.uiMap[x][y].npcs[i].center.x, centerY + offsetY + _mapUI.uiMap[x][y].npcs[i].center.y), Vector2(34, 28), PIVOT::CENTER);
							if (_mapUI.uiMap[x][y].npcs[i].type == NPC_TYPE::GATE && relativeRc.ptInRect(_ptMouse))
							{
								IMAGE_MANAGER->findImage("UI/MAP/ICON_WORM_SELECTED")->render(relativeRc.getCenter(), relativeRc.getSize());
								selectGateX = x;
								selectGateY = y;
								selectCenter = relativeRc.getCenter();
							}
							else
							{
								_mapUI.uiMap[x][y].npcs[i].img->render(relativeRc.getCenter(), relativeRc.getSize());
							}
						}
					}
				}
			}

			// 방을 잇는 선분 그리기
			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					if (_mapUI.uiMap[x][y].exist)
					{
						int offsetX = (x - _mapUI.currIndex.x) * (30 + 114);
						int offsetY = (y - _mapUI.currIndex.y) * (30 + 114);
						if (_mapUI.uiMap[x][y].isConnect[2]) // 우
						{
							FloatRect rc = FloatRect(centerX + offsetX + 48, centerY + offsetY - 3, centerX + offsetX + 48 + 30 + 18, centerY + offsetY + 3);
							D2D_RENDERER->fillRectangle(rc, 255, 255, 255, 1);
						}
						if (_mapUI.uiMap[x][y].isConnect[3]) // 하
						{
							FloatRect rc = FloatRect(centerX + offsetX - 3, centerY + offsetY + 48, centerX + offsetX + 3, centerY + offsetY + 48 + 30 + 18);
							D2D_RENDERER->fillRectangle(rc, 255, 255, 255, 1);
						}
					}
				}
			}
		
			// 게이트 사이의 퍼런 선분을 연결해야할 때
			if (selectGateX != -1 && (selectGateX != _mapUI.currIndex.x || selectGateY != _mapUI.currIndex.y) && _mapUI.gate != nullptr)
			{
				// 현재의 방
				for (int i = 0; i < _mapUI.uiMap[_mapUI.currIndex.x][_mapUI.currIndex.y].npcs.size(); i++)
				{
					if (_mapUI.uiMap[_mapUI.currIndex.x][_mapUI.currIndex.y].npcs[i].type == NPC_TYPE::GATE)
					{
						D2D_RENDERER->drawLine(Vector2(centerX + _mapUI.uiMap[_mapUI.currIndex.x][_mapUI.currIndex.y].npcs[i].center.x, centerY + _mapUI.uiMap[_mapUI.currIndex.x][_mapUI.currIndex.y].npcs[i].center.y), 
							selectCenter, 45, 255, 244, 1, 6);
						break;
					}
				}
			}


			D2D_RENDERER->fillRectangle(FloatRect(0, 0, WINSIZEX, 190), 33, 31, 50, 1);
			D2D_RENDERER->fillRectangle(FloatRect(0, 850, WINSIZEX, 900), 33, 31, 50, 1);
			D2D_RENDERER->fillRectangle(FloatRect(0, 0, 165, WINSIZEY), 33, 31, 50, 1);
			D2D_RENDERER->fillRectangle(FloatRect(1435, 0, WINSIZEX, WINSIZEY), 33, 31, 50, 1);

			_mapUI.headerImg->render(Vector2(WINSIZEX / 2, 90), Vector2(WINSIZEX, 160));
			_mapUI.bodyImg->render(Vector2(WINSIZEX / 2, WINSIZEY / 2 + 70), Vector2(1300, 660));
			
			_mapUI.nameImg->render(_mapUI.titleRc.getCenter());
			D2D_RENDERER->renderTextField(_mapUI.titleRc.left, _mapUI.titleRc.top, TTYONE_UTIL::stringTOwsting(_mapUI.stageTitle), RGB(255, 234, 168),
				45, _mapUI.titleRc.getWidth(), _mapUI.titleRc.getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER);
		
			D2D_RENDERER->fillRectangle(FloatRect(_mapUI.infos[0].imgRc.getCenter(), Vector2(16, 16), PIVOT::CENTER), 84, 144, 255, 1);
			D2D_RENDERER->renderTextField(_mapUI.infos[0].textRc.left, _mapUI.infos[0].textRc.top, _mapUI.infos[0].text, RGB(255, 255, 255), _mapUI.infos[0].fontSize,
				_mapUI.infos[0].textRc.getWidth(), _mapUI.infos[0].textRc.getHeight());
			for (int i = 1; i < 5; i++)
			{
				_mapUI.infos[i].img->render(_mapUI.infos[i].imgRc.getCenter(), _mapUI.infos[i].imgRc.getSize());
				D2D_RENDERER->renderTextField(_mapUI.infos[i].textRc.left, _mapUI.infos[i].textRc.top, _mapUI.infos[i].text, RGB(255, 255, 255), _mapUI.infos[i].fontSize,
					_mapUI.infos[i].textRc.getWidth(), _mapUI.infos[i].textRc.getHeight());
			}
		}


		// Dialogue UI
		if (_dialogueUI.isActive())
		{
			_dialogueUI.render();
		}

		// Inventory UI 
		if (_inventoryUI.isActive())
		{
			_inventoryUI.render();
		}

		// StatUI
		if (_statUI.isActive())
		{
			_statUI.render();
		}

		// CostumeUI
		if (_costumeUI.isActive())
		{
			_costumeUI.render();
		}

		// RestaurantUI
		if (_restaurantUI.isActive())
		{
			_restaurantUI.render();
		}

		// AbilityUI
		if (_abilityUI.isActive())
		{
			_abilityUI.render();
		}
	}
}

void UIManager::setMiniMap(vector<FloatRect> groundRect, vector<LinearFunc> groundLine, vector<LinearFunc> platformLine, vector<DoorObject*> doors, EnemyManager* enemyManager, NpcManager* npcManager, ObjectManager* objectManager)
{
	_miniMapUI.collisionRect.clear();
	_miniMapUI.doorRect.clear();
	for (int i = 0; i < groundRect.size(); i++)
	{
		FloatRect miniMapRc = groundRect[i];
		miniMapRc.left /= 16;
		miniMapRc.top /= 16;
		miniMapRc.right /= 16;
		miniMapRc.bottom /= 16;
		_miniMapUI.collisionRect.push_back(miniMapRc);
	}
	for (int i = 0; i < groundLine.size(); i++) // 대각선 땅
	{
		LinearFunc line = groundLine[i];
		for (int x = line.getRangeX().x; x < line.getRangeX().y; x += 64)
		{
			FloatRect miniMapRc = FloatRect(Vector2(x + 32, int(line.getY(x + 32))), Vector2(64, 64), PIVOT::CENTER);
			miniMapRc.left /= 16;
			miniMapRc.top /= 16;
			miniMapRc.right /= 16;
			miniMapRc.bottom /= 16;
			_miniMapUI.collisionRect.push_back(miniMapRc);
		}
	}
	for (int i = 0; i < platformLine.size(); i++) // 대각선 땅
	{
		LinearFunc line = platformLine[i];
		if (line.a == 0) // 수평 선
		{
			FloatRect miniMapRc = FloatRect(line.getRangeX().x, line.getY(line.getRangeX().x), line.getRangeX().y, line.getY(line.getRangeX().x) + 64);
			miniMapRc.left /= 16;
			miniMapRc.top /= 16;
			miniMapRc.right /= 16;
			miniMapRc.bottom /= 16;
			_miniMapUI.collisionRect.push_back(miniMapRc);
		}
		else // 대각선
		{
			for (int x = line.getRangeX().x; x < line.getRangeX().y; x += 64)
			{
				FloatRect miniMapRc = FloatRect(Vector2(x + 32, int(line.getY(x + 32))), Vector2(64, 64), PIVOT::CENTER);
				miniMapRc.left /= 16;
				miniMapRc.top /= 16;
				miniMapRc.right /= 16;
				miniMapRc.bottom /= 16;
				_miniMapUI.collisionRect.push_back(miniMapRc);
			}
		}
	}

	for (int i = 0; i < doors.size(); i++)
	{
		if (doors[i] != nullptr)
		{
			FloatRect miniMapRc = FloatRect(doors[i]->getPosition(), doors[i]->getSize(), PIVOT::CENTER);
			miniMapRc.left /= 16;
			miniMapRc.top /= 16;
			miniMapRc.right /= 16;
			miniMapRc.bottom /= 16;
			_miniMapUI.doorRect.push_back(miniMapRc);
		}
		
	}

	_miniMapUI.enemyMgr = enemyManager;
	_miniMapUI.npcMgr = npcManager;
	_miniMapUI.objectMgr = objectManager;
}

void UIManager::setMap(vector<vector<Stage*>> stageMap, string stageName)
{
	_mapUI.stageMap = stageMap;
	_mapUI.stageTitle = stageName;

	_mapUI.uiMap.resize(4);
	for (int i = 0; i < 4; i++)
	{
		_mapUI.uiMap[i].resize(4);
	}

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (stageMap[x][y] == nullptr)
			{
				_mapUI.uiMap[x][y].exist = false;
			}
			else
			{
				_mapUI.uiMap[x][y].exist = true;
				_mapUI.uiMap[x][y].visible = true;
				_mapUI.uiMap[x][y].rc = FloatRect(Vector2(-30 + (30 + 114) * (x), -30 + (30 + 114) * y), Vector2(114, 114), PIVOT::LEFT_TOP);
				_mapUI.uiMap[x][y].isConnect.resize(4);
				vector<bool> isWall = _mapUI.stageMap[x][y]->getWall();
				for (int dir = 0; dir < 4; dir++)
				{
					_mapUI.uiMap[x][y].isConnect[dir] = !isWall[dir];
				}

				vector<tagShowNpc> npcInfos = stageMap[x][y]->getNpcInfos();
				for (int i = 0; i < npcInfos.size(); i++)
				{
					tagNpcIcon npcIcon;
					npcIcon.img = npcInfos[i].icon;
					if (npcInfos.size() == 1)
					{
						npcIcon.center = Vector2(0, 0);
					}
					else // 2일 때
					{
						npcIcon.center = Vector2(-18 + 36 * i, 0);
					}
					npcIcon.type = npcInfos[i].type;
					_mapUI.uiMap[x][y].npcs.push_back(npcIcon);
				}
			}
		}
	}

}

void UIManager::setCurrentMapIndex(Vector2 currIndex)
{
	_mapUI.currIndex = currIndex;
	_mapUI.uiMap[currIndex.x][currIndex.y].visible = true;
}

void UIManager::showDamage(DamageInfo damage, Vector2 pos)
{
	
	if (damage.isEvade)
	{
		tagDamageUI damageUI;
		damageUI.pos = pos;
		damageUI.alpha = 1;
		damageUI.remainTimes = 1; damageUI.type = 1;
		damageUI.fontSize = 35;
		damageUI.textColor = RGB(0, 154, 1);
		_damageUI.push_back(damageUI);

	}
	else if (damage.isBlock)
	{
		tagDamageUI damageUI;
		damageUI.pos = pos;
		damageUI.alpha = 1;
		damageUI.remainTimes = 1; damageUI.type = 2;
		damageUI.fontSize = 35;
		damageUI.textColor = RGB(0, 0, 0);
		_damageUI.push_back(damageUI);

	}
	else
	{
		if (damage.damage >= 0)
		{
			tagDamageUI damageUI;
			damageUI.pos = pos;
			damageUI.alpha = 1;
			damageUI.remainTimes = 1; 
			damageUI.type = 0;
			damageUI.value = damage.damage;
			if (damage.isCritical)
			{
				damageUI.fontSize = 35;
				damageUI.textColor = RGB(243, 152, 0);
			}
			else if (damage.damage < 20)
			{
				damageUI.fontSize = 30;
				damageUI.textColor = RGB(222, 222, 0);
			}
			else
			{
				damageUI.fontSize = 30;
				damageUI.textColor = RGB(255, 212, 0);
			}
			_damageUI.push_back(damageUI);
		}

		if (damage.trueDamage > 0)
		{
			tagDamageUI trueDamageUI;
			trueDamageUI.type = 0;
			trueDamageUI.value = damage.trueDamage;
			trueDamageUI.pos = pos;
			trueDamageUI.pos.x += RANDOM->getFromIntTo(-20, 20);
			trueDamageUI.pos.y += RANDOM->getFromIntTo(-10, 10);
			trueDamageUI.remainTimes = 1;
			trueDamageUI.textColor = RGB(255, 255, 255);
			trueDamageUI.fontSize = 30;
			trueDamageUI.alpha = 1;
			_damageUI.push_back(trueDamageUI);
		}
	}

}

void UIManager::showEnemyHp(float maxHp, float curHp, Vector2 pos)
{
	tagEnemyHpUI hpUI;
	hpUI.pos = pos;
	hpUI.maxHp = maxHp;
	hpUI.currHp = curHp;
	_enemyHpUI.push_back(hpUI);
}

