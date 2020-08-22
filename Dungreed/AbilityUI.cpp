#include "stdafx.h"
#include "AbilityUI.h"
#include "Player.h"
#include <sstream>
#include <iomanip>

void AbilityUI::init()
{
	_currAbilityPoint = 30;

	//������ �̹��� �Ҵ�
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ABILITY_ICON type = static_cast<ABILITY_ICON>(j);
			_wrathIcon[i][j] = IMAGE_MANAGER->findImage("UI/ABILITY/ICON_WRATH" + to_string(i + 1) + "_" + getAbilityIconString(type));
			_swiftnessIcon[i][j] = IMAGE_MANAGER->findImage("UI/ABILITY/ICON_SWIFTNESS" + to_string(i + 1) + "_" + getAbilityIconString(type));
			_patienceIcon[i][j] = IMAGE_MANAGER->findImage("UI/ABILITY/ICON_PATIENCE" + to_string(i + 1) + "_" + getAbilityIconString(type));
			_arcaneIcon[i][j] = IMAGE_MANAGER->findImage("UI/ABILITY/ICON_ARCANE" + to_string(i + 1) + "_" + getAbilityIconString(type));
			_greedIcon[i][j] = IMAGE_MANAGER->findImage("UI/ABILITY/ICON_GREED" + to_string(i + 1) + "_" + getAbilityIconString(type));
		}
	}

	//���� �����Ƽ â
	for (int i = 0; i < 5; i++)
	{
		_windows[i].baseRc = FloatRect(30 + 310 * i, 180, 330 + 310 * i, 780);
		_windows[i].buttonCir = FloatCircle(Vector2(_windows[i].baseRc.getCenter().x, _windows[i].baseRc.getCenter().y + 250), 50);
		//Ư�� �������� ��ġ�� ��Ʈ
		_windows[i].iconRc[1] = FloatRect(Vector2(_windows[i].baseRc.getCenter().x, _windows[i].baseRc.getCenter().y + 150), Vector2(60, 60), PIVOT::CENTER);
		_windows[i].iconRc[0] = FloatRect(Vector2(_windows[i].baseRc.getCenter().x - 70, _windows[i].baseRc.getCenter().y + 150), Vector2(60, 60), PIVOT::CENTER);
		_windows[i].iconRc[2] = FloatRect(Vector2(_windows[i].baseRc.getCenter().x + 70, _windows[i].baseRc.getCenter().y + 150), Vector2(60, 60), PIVOT::CENTER);
		//Ư�� �̸��� ������ ��Ʈ
		_windows[i].titleRc = FloatRect(Vector2(_windows[i].baseRc.getCenter().x, _windows[i].baseRc.getCenter().y - 120), Vector2(120, 70), PIVOT::CENTER);
		//Ư�� ����Ʈ�� ������ ��Ʈ
		_windows[i].pointRc = FloatRect(Vector2(_windows[i].baseRc.getCenter().x, _windows[i].baseRc.getCenter().y - 60), Vector2(80, 60), PIVOT::CENTER);
		//Ư�� ����Ʈ ��ġ �ʱ�ȭ
		_windows[i].abilityPoint = 0;
		//���� ��ġ�� ������ ��Ʈ
		_windows[i].statValueRc[0] = FloatRect(Vector2(_windows[i].baseRc.getCenter().x - 60, _windows[i].baseRc.getCenter().y + 80), Vector2(50, 40), PIVOT::CENTER);
		if (i == 1 || i == 3)
		{
			_windows[i].statValueRc[1] = FloatRect(Vector2(_windows[i].baseRc.getCenter().x - 60, _windows[i].baseRc.getCenter().y + 40), Vector2(50, 40), PIVOT::CENTER);
		}
		//���� �̸��� ������ ��Ʈ
		_windows[i].statNameRc[0] = FloatRect(Vector2(_windows[i].baseRc.getCenter().x + 35, _windows[i].baseRc.getCenter().y + 80), Vector2(140, 40), PIVOT::CENTER);
		if (i == 1 || i == 3)
		{
			_windows[i].statNameRc[1] = FloatRect(Vector2(_windows[i].baseRc.getCenter().x + 35, _windows[i].baseRc.getCenter().y + 40), Vector2(140, 40), PIVOT::CENTER);
		}
	}

	//��Ʈ
	_bgRc = FloatRect(Vector2(WINSIZEX / 2, WINSIZEY / 2), Vector2(WINSIZEX, WINSIZEY), PIVOT::CENTER);
	_exitRc = FloatRect(WINSIZEX - 150, 40, WINSIZEX - 30, 130);
	_currPointRc = FloatRect(1270, 800, WINSIZEX - 50, WINSIZEY - 20);
	_abilityInitRc = FloatRect(1100, 830, 1150, WINSIZEY - 20);
	_abilityInitTextRc = FloatRect(1150, 830, 1250, WINSIZEY - 20);

	//���� Ŭ�� ����Ʈ
	_effectImg = IMAGE_MANAGER->findImage("UI/ABILITY/CLICK_EFFECT");
	_effectAni = new Animation;
	_effectAni->init(_effectImg->getWidth(), _effectImg->getHeight(), _effectImg->getMaxFrameX(), _effectImg->getMaxFrameY());
	_effectAni->setDefPlayFrame(false, false);
	_effectAni->setFPS(25);
}

void AbilityUI::release()
{
	_effectAni->release();
	delete _effectAni;
}

void AbilityUI::update(float elapsedTime)
{

	if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//â�ݱ�
		if (_exitRc.ptInRect(_ptMouse))
		{
			_isActive = false;
		}
		//Ư�� ���
		for (int i = 0; i < 5; i++)
		{
			if (_windows[i].buttonCir.ptInCircle(_ptMouse) && _windows[i].abilityPoint < 20 && _currAbilityPoint > 0)
			{
				_currAbilityPoint -= 1;
				_windows[i].abilityPoint += 1;
				//--- �г� �ż� �γ� �ź� Ž�� --- ������ Ư���� �ø� ������ ���� ��ġ ����
				if (i == 0)	//�г�
				{
					_abilityStat.power = _windows[i].abilityPoint * 2;
				}
				else if (i == 1)	//�ż�
				{
					_abilityStat.attackSpeed = _windows[i].abilityPoint * 0.5;
					_abilityStat.moveSpeed = _windows[i].abilityPoint * 0.5;
				}
				else if (i == 2)	//�γ�
				{
					_abilityStat.defense = _windows[i].abilityPoint * 1.5;
				}
				else if (i == 3)	//�ź�
				{
					_abilityStat.criticalChance = _windows[i].abilityPoint * 0.5;
					_abilityStat.evasion = _windows[i].abilityPoint * 0.5;
				}
				else if (i == 4)	//Ž��
				{
					_abilityStat.maxHp = _windows[i].abilityPoint * 2;
				}

				_effectPos = _windows[i].buttonCir.origin;
				_effectAni->start();

				_player->setAbilityStat(_abilityStat);
			}
		}
	}

	//Ư�� �ʱ�ȭ
	if (KEY_MANAGER->isOnceKeyDown('R'))
	{
		_currAbilityPoint = 30;
		for (int i = 0; i < 5; i++)
		{
			_windows[i].abilityPoint = 0;
		}
		_abilityStat = PlayerStat();
		_player->setAbilityStat(_abilityStat);
	}

	_effectAni->frameUpdate(elapsedTime);
}

void AbilityUI::render()
{
	//�޹�� (������)
	D2D_RENDERER->fillRectangle(_bgRc, 34, 32, 52, 0.5); 
	//��� �� ����
	_labelImg->render(Vector2(WINSIZEX / 2, 80), Vector2(WINSIZEX, 160));
	//â�ݱ� ����
	if (_exitRc.ptInRect(_ptMouse))
	{
		_exitButtonSelectedImg->render(_exitRc.getCenter(), _exitRc.getSize());
	}
	else
	{
		_exitButtonImg->render(_exitRc.getCenter(), _exitRc.getSize());
	}
	//Ư��â
	for (int i = 0; i < 5; i++)
	{
		//Ư��â ���
		D2D_RENDERER->drawRectangle(_windows[i].baseRc, D2D1::ColorF::Magenta, 1, 1);
		Image* backImg = _wrathBackImg;
		switch (i)
		{
		case 0:
			backImg = _wrathBackImg;
			break;
		case 1:
			backImg = _swiftnessBackImg;
			break;
		case 2:
			backImg = _patienceBackImg;
			break;
		case 3:
			backImg = _arcane;
			break;
		case 4:
			backImg = _greed;
			break;
		}
		if (i == 0) backImg->render(_windows[i].baseRc.getCenter(), Vector2(_windows[i].baseRc.getSize().x + 45, _windows[i].baseRc.getSize().y));
		else if (i == 1) backImg->render(Vector2(_windows[i].baseRc.getCenter().x, _windows[i].baseRc.getCenter().y - 10), Vector2(_windows[i].baseRc.getSize().x, _windows[i].baseRc.getSize().y + 20));
		else backImg->render(_windows[i].baseRc.getCenter(), _windows[i].baseRc.getSize());
		//Ư�� ��� ����(����)
		//D2D_RENDERER->drawEllipse(_windows[i].buttonCir.origin, 50, D2D1::ColorF::Magenta, 1);
		Image* btnImg = _wrathButtonImg;
		switch (i)
		{
		case 0:
		{
			if (_windows[i].buttonCir.ptInCircle(_ptMouse) && _windows[i].abilityPoint < 20 && _currAbilityPoint > 0)
			{
				btnImg = _wrathButtonImg;
			}
			else
			{
				btnImg = _wrathButtonDisableImg;
			}
		}
			break;
		case 1:
		{
			if (_windows[i].buttonCir.ptInCircle(_ptMouse) && _windows[i].abilityPoint < 20 && _currAbilityPoint > 0)
			{
				btnImg = _swiftnessButtonImg;
			}
			else
			{
				btnImg = _swiftnessButtonDisableImg;
			}
		}
			break;
		case 2:
		{
			if (_windows[i].buttonCir.ptInCircle(_ptMouse) && _windows[i].abilityPoint < 20 && _currAbilityPoint > 0)
			{
				btnImg = _patienceButtonImg;
			}
			else
			{
				btnImg = _patienceButtonDisableImg;
			}
		}
			break;
		case 3:
		{
			if (_windows[i].buttonCir.ptInCircle(_ptMouse) && _windows[i].abilityPoint < 20 && _currAbilityPoint > 0)
			{
				btnImg = _arcaneButtonImg;
			}
			else
			{
				btnImg = _arcaneButtonDisableImg;
			}
		}
			break;
		case 4:
		{
			if (_windows[i].buttonCir.ptInCircle(_ptMouse) && _windows[i].abilityPoint < 20 && _currAbilityPoint > 0)
			{
				btnImg = _greedButtonImg;
			}
			else
			{
				btnImg = _greedButtonDisableImg;
			}
		}
			break;
		}
		btnImg->setScale(5.2);
		btnImg->render(_windows[i].buttonCir.origin, _windows[i].buttonCir.size);
		
		//���� ��ġ ��ȭ ǥ��
		D2D_RENDERER->drawRectangle(_windows[i].statValueRc[0], D2D1::ColorF::Magenta, 1, 1);
		D2D_RENDERER->drawRectangle(_windows[i].statNameRc[0], D2D1::ColorF::Magenta, 1, 1);
		if (i == 1 || i == 3)
		{
			D2D_RENDERER->drawRectangle(_windows[i].statValueRc[1], D2D1::ColorF::Magenta, 1, 1);
			D2D_RENDERER->drawRectangle(_windows[i].statNameRc[1], D2D1::ColorF::Magenta, 1, 1);
		}
		int power = (int)_abilityStat.power;
		float attackSpeed = _abilityStat.attackSpeed;
		float moveSpeed = _abilityStat.moveSpeed;
		float defense = _abilityStat.defense;
		float criChan = _abilityStat.criticalChance;
		float evasion = _abilityStat.evasion;
		int maxHp = _abilityStat.maxHp;
		int pre = 0;
		stringstream str1;
		stringstream str2;
		wstring wstr0 = TTYONE_UTIL::stringTOwsting(_abilityStat.getStatString(STAT_TYPE::POW, false));
		wstring wstr1_0 = TTYONE_UTIL::stringTOwsting(_abilityStat.getStatString(STAT_TYPE::ATTACK_SPEED, false));
		wstring wstr1_1 = TTYONE_UTIL::stringTOwsting(_abilityStat.getStatString(STAT_TYPE::MOVE_SPEED, false));
		wstring wstr2 = TTYONE_UTIL::stringTOwsting(_abilityStat.getStatString(STAT_TYPE::DEF, false));
		wstring wstr3_0 = TTYONE_UTIL::stringTOwsting(_abilityStat.getStatString(STAT_TYPE::EVADE, false));
		wstring wstr3_1 = TTYONE_UTIL::stringTOwsting(_abilityStat.getStatString(STAT_TYPE::CRITICAL, false));
		wstring wstr4 = TTYONE_UTIL::stringTOwsting(_abilityStat.getStatString(STAT_TYPE::MAX_HP, false));
		switch (i)
		{
		case 0:
			D2D_RENDERER->renderTextField(_windows[i].statValueRc[0].left, _windows[i].statValueRc[0].top, L"+" + to_wstring(power),
			 RGB(0, 255, 0), 25, _windows[i].statValueRc[0].getWidth(), _windows[i].statValueRc[0].getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aaī�ÿ����");
			D2D_RENDERER->renderTextField(_windows[i].statNameRc[0].left, _windows[i].statNameRc[0].top, L"+" + wstr0, D2D1::ColorF::White, 25, _windows[i].statNameRc[0].getWidth(), _windows[i].statNameRc[0].getHeight(),
				1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aaī�ÿ����");
			break;
		case 1:
			if (attackSpeed - (int)attackSpeed == 0) pre = 0;
			else pre = 1;
			str1 << fixed << setprecision(pre) << attackSpeed;
			str2 << fixed << setprecision(pre) << moveSpeed;
			D2D_RENDERER->renderTextField(_windows[i].statValueRc[0].left, _windows[i].statValueRc[0].top, L"+" + TTYONE_UTIL::stringTOwsting(str1.str()),
				RGB(0, 255, 0), 25, _windows[i].statValueRc[0].getWidth(), _windows[i].statValueRc[0].getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aaī�ÿ����");
			D2D_RENDERER->renderTextField(_windows[i].statValueRc[1].left, _windows[i].statValueRc[1].top, L"+" + TTYONE_UTIL::stringTOwsting(str2.str()),
				RGB(0, 255, 0), 25, _windows[i].statValueRc[1].getWidth(), _windows[i].statValueRc[1].getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aaī�ÿ����");
			D2D_RENDERER->renderTextField(_windows[i].statNameRc[0].left, _windows[i].statNameRc[0].top, wstr1_0, D2D1::ColorF::White, 25, _windows[i].statNameRc[0].getWidth(), _windows[i].statNameRc[0].getHeight(),
				1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aaī�ÿ����");
			D2D_RENDERER->renderTextField(_windows[i].statNameRc[1].left, _windows[i].statNameRc[1].top, wstr1_1, D2D1::ColorF::White, 25, _windows[i].statNameRc[1].getWidth(), _windows[i].statNameRc[1].getHeight(),
				1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aaī�ÿ����");
			break;
		case 2:
			if (defense - (int)defense == 0) pre = 0;
			else pre = 1;
			str1 << fixed << setprecision(pre) << defense;
			D2D_RENDERER->renderTextField(_windows[i].statValueRc[0].left, _windows[i].statValueRc[0].top, L"+" + TTYONE_UTIL::stringTOwsting(str1.str()),
				RGB(0, 255, 0), 25, _windows[i].statValueRc[0].getWidth(), _windows[i].statValueRc[0].getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aaī�ÿ����");
			D2D_RENDERER->renderTextField(_windows[i].statNameRc[0].left, _windows[i].statNameRc[0].top, wstr2, D2D1::ColorF::White, 25, _windows[i].statNameRc[0].getWidth(), _windows[i].statNameRc[0].getHeight(),
				1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aaī�ÿ����");
			break;
		case 3:
			if (evasion - (int)evasion == 0) pre = 0;
			else pre = 1;
			str1 << fixed << setprecision(pre) << evasion;
			str2 << fixed << setprecision(pre) << criChan;
			D2D_RENDERER->renderTextField(_windows[i].statValueRc[0].left, _windows[i].statValueRc[0].top, L"+" + TTYONE_UTIL::stringTOwsting(str1.str()),
				RGB(0, 255, 0), 25, _windows[i].statValueRc[0].getWidth(), _windows[i].statValueRc[0].getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aaī�ÿ����");
			D2D_RENDERER->renderTextField(_windows[i].statValueRc[1].left, _windows[i].statValueRc[1].top, L"+" + TTYONE_UTIL::stringTOwsting(str2.str()),
				RGB(0, 255, 0), 25, _windows[i].statValueRc[1].getWidth(), _windows[i].statValueRc[1].getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aaī�ÿ����");
			D2D_RENDERER->renderTextField(_windows[i].statNameRc[0].left, _windows[i].statNameRc[0].top, wstr3_0, D2D1::ColorF::White, 25, _windows[i].statNameRc[0].getWidth(), _windows[i].statNameRc[0].getHeight(),
				1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aaī�ÿ����");
			D2D_RENDERER->renderTextField(_windows[i].statNameRc[1].left, _windows[i].statNameRc[1].top, wstr3_1, D2D1::ColorF::White, 25, _windows[i].statNameRc[1].getWidth(), _windows[i].statNameRc[1].getHeight(),
				1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aaī�ÿ����");
			break;
		case 4:
			D2D_RENDERER->renderTextField(_windows[i].statValueRc[0].left, _windows[i].statValueRc[0].top, L"+" + to_wstring(maxHp),
				RGB(0, 255, 0), 25, _windows[i].statValueRc[0].getWidth(), _windows[i].statValueRc[0].getHeight(), 1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aaī�ÿ����");
			D2D_RENDERER->renderTextField(_windows[i].statNameRc[0].left, _windows[i].statNameRc[0].top, wstr4, D2D1::ColorF::White, 25, _windows[i].statNameRc[0].getWidth(), _windows[i].statNameRc[0].getHeight(),
				1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aaī�ÿ����");
			break;
		}


		Image* icon[3][3];
		//Ư�� ������ ��ġ
		switch (i)
		{
		case 0:
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					icon[j][k] = _wrathIcon[j][k];
				}
			}
			break;
		case 1:
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					icon[j][k] = _swiftnessIcon[j][k];
				}
			}
			break;
		case 2:
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					icon[j][k] = _patienceIcon[j][k];
				}
			}
			break;
		case 3:
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					icon[j][k] = _arcaneIcon[j][k];
				}
			}
			break;
		case 4:
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					icon[j][k] = _greedIcon[j][k];
				}
			}
			break;
		}
		//Ư�� ������
		for (int j = 0; j < 3; j++)
		{
			// j (0~2) : Ȱ��ȭ �Ǵ� Ư���� ȿ�� 1~3
			int k;
			if (j == 0)
			{
				if (_windows[i].abilityPoint < 5) k = 2;
				else
				{
					k = 0;
					if (_windows[i].iconRc[j].ptInRect(_ptMouse))
					{
						k = 1;
					}
				}
				icon[j][k]->render(_windows[i].iconRc[j].getCenter(), _windows[i].iconRc[j].getSize());
			}
			else if (j == 1)
			{
				if (_windows[i].abilityPoint < 10) k = 2;
				else
				{ 
					k = 0; 
					if (_windows[i].iconRc[j].ptInRect(_ptMouse))
					{
						k = 1;
					}
				}
				icon[j][k]->render(_windows[i].iconRc[j].getCenter(), _windows[i].iconRc[j].getSize());
			}
			else
			{
				if (_windows[i].abilityPoint < 20) k = 2;
				else
				{
					k = 0;
					if (_windows[i].iconRc[j].ptInRect(_ptMouse))
					{
						k = 1;
					}
				}
				icon[j][k]->render(_windows[i].iconRc[j].getCenter(), _windows[i].iconRc[j].getSize());
			}	
		}
		//Ư�� ������ ��Ʈ 
		for (int j = 0; j < 3; j++)
		{
			//D2D_RENDERER->drawRectangle(_windows[i].iconRc[j], D2D1::ColorF::Magenta, 1, 1);
			//��Ʈ ���� 5, 10, 20 ǥ��
			wstring text;
			if (j == 0) text = L"5";
			else if(j == 1) text = L"10";
			else if (j == 2) text = L"20";
			D2D_RENDERER->renderTextField(_windows[i].iconRc[j].left, _windows[i].iconRc[j].top - 40, text, D2D1::ColorF::White, 12, _windows[i].iconRc[j].getWidth(), _windows[i].iconRc[j].getHeight(), 1,
				DWRITE_TEXT_ALIGNMENT_CENTER, L"Aaī�ÿ����");
		}
		//Ư�� �̸� 
		wstring title[5] = { L"�г�", L"�ż�", L"�γ�", L"�ź�", L"Ž��" };
		//D2D_RENDERER->drawRectangle(_windows[i].titleRc, D2D1::ColorF::Magenta, 1, 1);
		D2D_RENDERER->renderTextField(_windows[i].titleRc.left, _windows[i].titleRc.top, title[i], D2D1::ColorF::White, 50, _windows[i].titleRc.getWidth(), _windows[i].titleRc.getHeight(), 1,
			DWRITE_TEXT_ALIGNMENT_CENTER, L"Aaī�ÿ����");
		//Ư�� ����Ʈ
		//D2D_RENDERER->drawRectangle(_windows[i].pointRc, D2D1::ColorF::Magenta, 1, 1);
		int r, g, b;
		if (i == 0) r = 210, g = 130, b = 112;
		else if (i == 1) r = 181, g = 227, b = 204;
		else if (i == 2) r = 176, g = 182, b = 194;
		else if (i == 3) r = 160, g = 177, b = 210;
		else if (i == 4) r = 225, g = 183, b = 98;
		D2D_RENDERER->renderTextField(_windows[i].pointRc.left, _windows[i].pointRc.top, to_wstring(_windows[i].abilityPoint), RGB(r, g, b), 50, _windows[i].pointRc.getWidth(), _windows[i].pointRc.getHeight(),
			1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Alagard");
	}
	//Ư�� �ʱ�ȭ
	//D2D_RENDERER->drawRectangle(_abilityInitRc, D2D1::ColorF::Magenta, 1, 1);
	//D2D_RENDERER->drawRectangle(_abilityInitTextRc, D2D1::ColorF::Magenta, 1, 1);
	_abilityInitImg->render(_abilityInitRc.getCenter(), _abilityInitRc.getSize());
	D2D_RENDERER->renderTextField(_abilityInitTextRc.left, _abilityInitTextRc.top, L"�ʱ�ȭ", D2D1::ColorF::White, 30, _abilityInitTextRc.getWidth(), _abilityInitTextRc.getHeight(), 1,
		DWRITE_TEXT_ALIGNMENT_CENTER, L"Aaī�ÿ����");
	//���� ���� Ư�� ����Ʈ
	_currPointBack->render(_currPointRc.getCenter(), _currPointRc.getSize());
	_currPointFrame->render(_currPointRc.getCenter(), _currPointRc.getSize());
	//D2D_RENDERER->drawRectangle(_currPointRc, D2D1::ColorF::Magenta, 1, 1);
	D2D_RENDERER->renderTextField(_currPointRc.left, _currPointRc.top, L"���� ����Ʈ : " + to_wstring(_currAbilityPoint), D2D1::ColorF::White, 30, _currPointRc.getWidth(), _currPointRc.getHeight(), 1,
		DWRITE_TEXT_ALIGNMENT_CENTER, L"Aaī�ÿ����", 0);
	//D2D_RENDERER->renderText(_currPointRc.left + 30, _currPointRc.top - 50, L"���� ����Ʈ : " + to_wstring(_currAbilityPoint), 20, D2DRenderer::DefaultBrush::White, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aaī�ÿ����", 0);

	if (_effectAni->isPlay())
	{
		_effectImg->aniRender(_effectPos, Vector2(110, 110), _effectAni);
	}
}

string AbilityUI::getAbilityIconString(ABILITY_ICON type)
{
	switch (type)
	{
	case ABILITY_ICON::ABLE:
		return "ABLE";
		break;
	case ABILITY_ICON::ABLE_SELECTED:
		return "ABLE_SELECTED";
		break;
	case ABILITY_ICON::DISABLE:
		return "DISABLE";
		break;
	}
}
