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

	// INVENTORY UI
	_inventoryUI.init();

	// STATUS UI
	_statUI.init();

	// COSTUME UI
	_costumeUI.init();
}

void UIManager::release()
{
	_inventoryUI.release();
	_statUI.release();
	_costumeUI.release();
}

void UIManager::update(float const elaspedTime)
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
				_damageUI[i].alpha = max(0, _damageUI[i].alpha - elaspedTime * 2);
			}
		}
		else
		{
			_damageUI[i].pos.y -= elaspedTime * 40;
			_damageUI[i].remainTimes -= elaspedTime;
		}
		i++;

	}

	// HP bar animation
	_hpUI.hpAni->frameUpdate(elaspedTime);

	// Gold icon animation
	_goldUI.ani->frameUpdate(elaspedTime);

	// Weapon change animation
	if (_player->getWeaponIndex() != _weaponUI.viewIndex)
	{
		_weaponUI.move.x = min(20, _weaponUI.move.x + _weaponUI.moveSpeed * elaspedTime);
		_weaponUI.move.y = max(-20, _weaponUI.move.y - _weaponUI.moveSpeed * elaspedTime);
		if (_weaponUI.move.x == 20)
		{
			_weaponUI.move.x = 0;
			_weaponUI.move.y = 0;
			_weaponUI.viewIndex = _player->getWeaponIndex();
		}
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

	

	bool isClose = false;
	if (KEY_MANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		isClose = true;
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
			_inventoryUI.update(elaspedTime);
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
			_statUI.update(elaspedTime);
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
			_costumeUI.update(elaspedTime);
		}
	}

	_isActive = false;
	_isActive |= _inventoryUI.isActive();
	_isActive |= _statUI.isActive();
	_isActive |= _costumeUI.isActive();
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
			D2D_RENDERER->renderTextField(CAMERA->getRelativeX(_damageUI[i].pos.x - 50), CAMERA->getRelativeY(_damageUI[i].pos.y), 
				to_wstring(static_cast<int>(_damageUI[i].value)), _damageUI[i].textColor, _damageUI[i].fontSize,
				100, _damageUI[i].fontSize, _damageUI[i].alpha, DWRITE_TEXT_ALIGNMENT_CENTER, L"Alagard");
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
		if (FLOAT_EQUAL(hpRatio, 1))
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
			45, _hpUI.hpLevel.getSize().x, _hpUI.hpLevel.getSize().y, 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Alagard");
		D2D_RENDERER->renderTextField(_hpUI.hpBar.left, _hpUI.hpBar.top, (to_wstring(_player->getCurrHp()) + L"/" + to_wstring(_player->getMaxHp())), RGB(255, 255, 255),
			40, _hpUI.hpBar.getSize().x, _hpUI.hpBar.getSize().y, 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Alagard");

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
			_goldUI.fontSize, _goldUI.textRc.getSize().x, _goldUI.textRc.getSize().y, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Alagard");

		// PLAYER SATIETY
		_satietyUI.img->render(_satietyUI.imgRc.getCenter(), _satietyUI.imgRc.getSize());
		D2D_RENDERER->renderTextField(_satietyUI.textRc.left, _satietyUI.textRc.top, to_wstring(_player->getSatiety()) + L" / " + to_wstring(_player->getMaxSatiety()), RGB(255, 255, 255),
			_satietyUI.fontSize, _satietyUI.textRc.getSize().x, _satietyUI.textRc.getSize().y, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Alagard");
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
						bulletRc.getHeight(), bulletRc.getWidth(), bulletRc.getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Alagard");
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
						bulletRc.getHeight(), bulletRc.getWidth(), bulletRc.getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Alagard");
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
	}
}

void UIManager::showDamage(DamageInfo damage, Vector2 pos)
{
	tagDamageUI damageUI;
	damageUI.value = damage.damage;
	damageUI.pos = pos;
	damageUI.remainTimes = 1;
	damageUI.fontSize = 30;
	if (damage.isCritical)
	{
		damageUI.fontSize = 35;
		damageUI.textColor = RGB(243, 152, 0);
	}
	else if (damage.damage < 20)
	{
		damageUI.fontSize = 30;
		damageUI.textColor = RGB(255, 255, 255);
	}
	else
	{
		damageUI.fontSize = 30; 
		damageUI.textColor = RGB(255, 212, 0);
	}
	damageUI.alpha = 1;
	_damageUI.push_back(damageUI);

	if (damage.trueDamage != 0)
	{
		tagDamageUI trueDamageUI;
		trueDamageUI.value = damage.trueDamage;
		trueDamageUI.pos = pos;
		trueDamageUI.pos.x += 10;
		trueDamageUI.pos.y += 10;
		trueDamageUI.remainTimes = 1;
		trueDamageUI.textColor = RGB(255, 255, 255);
		trueDamageUI.alpha = 1;
		_damageUI.push_back(trueDamageUI);
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
