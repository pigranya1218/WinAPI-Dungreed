#include "stdafx.h"
#include "UIManager.h"
#include "Player.h"
#include "StageManager.h"

void UIManager::init()
{
	_isActive = false;

	// HP BAR
	_hpUI.hpBgImg = IMAGE_MANAGER->findImage("UI/PLAYER_LIFE_BG");
	_hpUI.hpFrameImg = IMAGE_MANAGER->findImage("UI/PLAYER_LIFE_FRAME");
	_hpUI.hpBarImg = IMAGE_MANAGER->findImage("UI/PLAYER_LIFE_BAR");
	_hpUI.hpWaveImg = IMAGE_MANAGER->findImage("UI/PLAYER_LIFE_WAVE");
	_hpUI.hpBg = FloatRect(20, 20, 390, 100);
	_hpUI.hpLevel = FloatRect(20, 20, 130, 100);
	_hpUI.hpBar = FloatRect(120, 30, 390, 90);

	_hpUI.hpAni = new Animation;
	_hpUI.hpAni->init(_hpUI.hpWaveImg->getWidth(), _hpUI.hpWaveImg->getHeight(), _hpUI.hpWaveImg->getMaxFrameX(), _hpUI.hpWaveImg->getMaxFrameY());
	_hpUI.hpAni->setFPS(15);
	_hpUI.hpAni->setDefPlayFrame(false, true);
	_hpUI.hpAni->start();

	// GOLD UI
	_goldUI.img = IMAGE_MANAGER->findImage("UI/GOLD");
	_goldUI.ani = new Animation;
	_goldUI.ani->init(_goldUI.img->getWidth(), _goldUI.img->getHeight(), _goldUI.img->getMaxFrameX(), _goldUI.img->getMaxFrameY());
	_goldUI.ani->setDefPlayFrame(false, true);
	_goldUI.ani->setFPS(15);
	_goldUI.ani->start();
	_goldUI.imgRc = FloatRect(30, 796, 56, 822);
	_goldUI.textRc = FloatRect(80, 795, 200, 821);
	_goldUI.fontSize = 26;

	// SATIETY UI
	_satietyUI.img = IMAGE_MANAGER->findImage("UI/FOOD");
	_satietyUI.imgRc = FloatRect(20, 835, 70, 880);
	_satietyUI.textRc = FloatRect(80, 835, 200, 850);
	_satietyUI.fontSize = 25;
	_satietyProgress.progressRc = FloatRect(80, 860, 200, 870);

}

void UIManager::release()
{
}

void UIManager::update(float const elaspedTime)
{
	_hpUI.hpAni->frameUpdate(elaspedTime);
	_goldUI.ani->frameUpdate(elaspedTime);
}

void UIManager::render()
{
	if (_isActive)
	{

	}
	else // ±âº» UI
	{
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
		
		if (!FLOAT_EQUAL(width, _hpUI.hpBar.getSize().x))
		{
			
		}
		_hpUI.hpFrameImg->render(_hpUI.hpBg.getCenter(), _hpUI.hpBg.getSize());
		D2D_RENDERER->renderTextField(_hpUI.hpLevel.left, _hpUI.hpLevel.top, to_wstring(_player->getLevel()), RGB(255, 255, 255), 
			45, _hpUI.hpLevel.getSize().x, _hpUI.hpLevel.getSize().y, 1, DWRITE_TEXT_ALIGNMENT_CENTER);
		D2D_RENDERER->renderTextField(_hpUI.hpBar.left, _hpUI.hpBar.top, (to_wstring(_player->getCurrHp()) + L"/" + to_wstring(_player->getMaxHp())), RGB(255, 255, 255),
			40, _hpUI.hpBar.getSize().x, _hpUI.hpBar.getSize().y, 1, DWRITE_TEXT_ALIGNMENT_CENTER);

		// PLAYER GOLD
		_goldUI.img->aniRender(_goldUI.imgRc.getCenter(), _goldUI.imgRc.getSize(), _goldUI.ani);
		D2D_RENDERER->renderTextField(_goldUI.textRc.left, _goldUI.textRc.top, to_wstring(_player->getGold()) + L" ¿ø", RGB(255, 255, 255),
			_goldUI.fontSize, _goldUI.textRc.getSize().x, _goldUI.textRc.getSize().y, 1);

		// PLAYER SATIETY
		_satietyUI.img->render(_satietyUI.imgRc.getCenter(), _satietyUI.imgRc.getSize());
		D2D_RENDERER->renderTextField(_satietyUI.textRc.left, _satietyUI.textRc.top, to_wstring(_player->getSatiety()) + L" / " + to_wstring(_player->getMaxSatiety()), RGB(255, 255, 255),
			_satietyUI.fontSize, _satietyUI.textRc.getSize().x, _satietyUI.textRc.getSize().y, 1);
		D2D_RENDERER->fillRectangle(_satietyProgress.progressRc, 34, 32, 52, 1);
		FloatRect satietyGauge = _satietyProgress.progressRc;
		satietyGauge.right = satietyGauge.left + (static_cast<float>(_player->getSatiety()) / _player->getMaxSatiety()) * satietyGauge.getSize().x;
		D2D_RENDERER->fillRectangle(satietyGauge, 255, 206, 78, 1);
	}
}
