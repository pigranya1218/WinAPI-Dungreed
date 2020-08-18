#include "stdafx.h"
#include "CostumeUI.h"
#include "Player.h"
#include "PlayerStat.h"
#include "Costume.h"
#include "MetalPlateCos.h"
#include "AliceCos.h"
#include "RedLotusCos.h"
#include "PickaxCos.h"

void CostumeUI::init()
{
	_isActive = false;
	_cosType = COSTUME_TYPE::ALICE;

	//â�ݱ� ��ư
	_exitRc = FloatRect(WINSIZEX - 150, 40, WINSIZEX - 30, 130);

	//�ߴ� �ڽ�Ƭ ���� ��ũ���� ���� ��Ʈ
	_midRc = FloatRect(0, 160, WINSIZEX, WINSIZEY - 200);

	//costume cell
	//���� ���� ũ�� : 360, ���� ũ��� 162 ~ WINSIZEY - 202
	_costumeCell[0].cellRect = FloatRect(0, 162, 360, WINSIZEY - 202);
	for (int i = 0; i < static_cast<int>(COSTUME_TYPE::END); i++)
	{
		COSTUME_TYPE type = static_cast<COSTUME_TYPE>(i);
		Costume* costume = DATA_MANAGER->getCostume(type);
		//�� ��Ʈ ��ġ ����
		if (i > 0)
		{
			_costumeCell[i].cellRect = FloatRect(360 * i, 162, 360 * i + 360, WINSIZEY - 202);
		}
		if (i < 5)
		{
			//���� �̹��� �Ҵ�
			_costumeCell[i].costumeSample = IMAGE_MANAGER->findImage("UI/COSTUME/" + costume->getCostumeName());
		}

		_costumeCell[i].cosTitle = costume->getTitle();
		_costumeCell[i].cosSummary = costume->getSummary();
		_costumeCell[i].cosDetails = costume->getDetails();
		_costumeCell[i].differStat = costume->getDifferStat();
	
		/*if (_costumeCell[i].differStat != 0)
		{

		}*/

	}

}

void CostumeUI::release()
{
}

void CostumeUI::update(float elapsedTime)
{
	
	if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//â�ݱ�
		if (_exitRc.ptInRect(_ptMouse))
		{
			_isActive = false;
		}
		//�ڽ�Ƭ ����
		for (int i = 0; i < 5; i++)
		{
			if (_costumeCell[i].cellRect.ptInRect(_ptMouse))
			{
				_cosType = COSTUME_TYPE(i);
				_player->setCurrCostume(DATA_MANAGER->getCostume(_cosType));
			}
		}
	}
}

void CostumeUI::render()
{
	_costumeBaseUpImg->render(Vector2(WINSIZEX / 2, 80), Vector2(WINSIZEX, 160));
	//â�ݱ� ��ư
	if (_exitRc.ptInRect(_ptMouse))
	{
		_exitBtnSelected->render(_exitRc.getCenter(), _exitRc.getSize(), false);
	}
	else
	{
		_exitBtn->render(_exitRc.getCenter(), _exitRc.getSize(), false);
	}
	
	D2D_RENDERER->drawRectangle(_midRc, D2D1::ColorF::White, 3, 3);
	_costumeBaseDownImg->render(Vector2(WINSIZEX / 2, WINSIZEY - 100), Vector2(WINSIZEX, 200));
	//�ڽ�Ƭ �� (ī�޶� ���� �ʿ�)
	for (int i = 0; i < static_cast<int>(COSTUME_TYPE::END); i++)
	{
		//�� �޹��
		_costumeCell[i].costumeBackImg->render(_costumeCell[i].cellRect.getCenter(), _costumeCell[i].cellRect.getSize(), false);
		//��/��� ���
		if (i != static_cast<int>(_cosType))
		{
			//_costumeCell[i].costumeUnlockedImg->setScale(5.2);
			_costumeCell[i].costumeUnlockedImg->setSize(Vector2(300, 500));
			_costumeCell[i].costumeUnlockedImg->render(Vector2(_costumeCell[i].cellRect.getCenter().getIntX(), _costumeCell[i].cellRect.getCenter().getIntY() + 10), false);
		}
		//���� �������� �ڽ�Ƭ
		else 
		{
			_costumeCell[i].costumeEquippedImg->setSize(Vector2(300, 500));
			_costumeCell[i].costumeEquippedImg->render(Vector2(_costumeCell[i].cellRect.getCenter().getIntX(), _costumeCell[i].cellRect.getCenter().getIntY() + 10), false);
			//_costumeCell[i].costumeEquippedImg->render(_costumeCell[i].cellRect.getCenter(), false);
		}
		//���� ������ �ڽ�Ƭ
		if (_costumeCell[i].cellRect.ptInRect(_ptMouse))
		{
			_costumeCell[i].costumeSelectedImg->setSize(Vector2(300, 500));
			_costumeCell[i].costumeSelectedImg->render(Vector2(_costumeCell[i].cellRect.getCenter().getIntX(), _costumeCell[i].cellRect.getCenter().getIntY() + 10), false);
			//�ڽ�Ƭ �̸�
			D2D_RENDERER->renderTextField(20, WINSIZEY - 140, _costumeCell[i].cosTitle, D2D1::ColorF::Gold, 45,
				500, 0, 1.f, DWRITE_TEXT_ALIGNMENT_CENTER, L"�ձٸ��", 0.f);
			//�ڽ�Ƭ ����
			D2D_RENDERER->renderTextField(30, WINSIZEY - 80, _costumeCell[i].cosSummary, D2D1::ColorF::White, 25,
				500, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"�ձٸ��", 0.f);
			//�ڽ�Ƭ �󼼳���
			if (_costumeCell[i].cosDetails != L"")
			{
				D2D_RENDERER->renderTextField(530, WINSIZEY - 140, L"��", D2D1::ColorF::White, 25,
					WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"�ձٸ��", 0.f);
				D2D_RENDERER->renderTextField(560, WINSIZEY - 140, _costumeCell[i].cosDetails, D2D1::ColorF::Green, 25,
					WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"�ձٸ��", 0.f);
			}
			//��������
			wstring wstr1, wstr2, wstr3;
			int stat1 = 0;
			int stat2 = 0;
			int stat3 = 0;
			//D2D1::ColorF::Enum color1, color2, color3;
			D2D1::ColorF::Enum color1 =  D2D1::ColorF::White;
			D2D1::ColorF::Enum color2 = D2D1::ColorF::White;
			D2D1::ColorF::Enum color3 = D2D1::ColorF::White;
			if (i > 0)
			{
				if (i == 1)
				{
					stat1 = static_cast<int>(_costumeCell[i].differStat->defense);
					color1 = ((stat1 >= 0) ?  D2D1::ColorF::Green : D2D1::ColorF::Red);
					wstr1 = to_wstring(stat1) + L" " + TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::DEF, false));
					

					stat2 = _costumeCell[i].differStat->maxHp;
					color2 = ((stat2 >= 0) ? D2D1::ColorF::Green : D2D1::ColorF::Red);
					wstr2 = to_wstring(stat2) + L" " + TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::MAX_HP, false));
				}
				if (i == 2)
				{
					stat1 = _costumeCell[i].differStat->maxHp;
					stat1 >= 0 ? color1 = D2D1::ColorF::Green : color1 = D2D1::ColorF::Red;
					wstr1 = to_wstring(stat1) + L" " + TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::MAX_HP, false));

					stat2 = static_cast<int>(_costumeCell[i].differStat->power);
					stat2 >= 0 ? color2 = D2D1::ColorF::Green : color2 = D2D1::ColorF::Red;
					wstr2 = to_wstring(stat2) + L" " + TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::POW, false));
				}
				if (i == 3)
				{
					stat1 = _costumeCell[i].differStat->maxHp;
					stat1 >= 0 ? color1 = D2D1::ColorF::Green : color1 = D2D1::ColorF::Red;
					wstr1 = to_wstring(stat1) + L" " + TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::MAX_HP, false));

					stat2 = static_cast<int>(_costumeCell[i].differStat->evasion);
					stat2 >= 0 ? color2 = D2D1::ColorF::Green : color2 = D2D1::ColorF::Red;
					wstr2 = to_wstring(stat2) + L" " + TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::EVADE, false));
				}
				if (i == 4)
				{
					stat1 = static_cast<int>(_costumeCell[i].differStat->dashDamage);
					stat1 >= 0 ? color1 = D2D1::ColorF::Green : color1 = D2D1::ColorF::Red;
					wstr1 = to_wstring(stat1) + L" " + TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::DASH_DAMAGE, false));

					stat2 = _costumeCell[i].differStat->maxDashCount;
					stat2 >= 0 ? color2 = D2D1::ColorF::Green : color2 = D2D1::ColorF::Red;
					wstr2 = to_wstring(stat2) + L" " + TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::MAX_DASH_COUNT, false));

					stat3 = static_cast<int>(_costumeCell[i].differStat->criticalChance);
					stat3 >= 0 ? color3 = D2D1::ColorF::Green : color3 = D2D1::ColorF::Red;
					wstr3 = to_wstring(stat3) + L" " + TTYONE_UTIL::stringTOwsting(_costumeCell[i].differStat->getStatString(STAT_TYPE::CRITICAL, false));

					D2D_RENDERER->renderTextField(530, WINSIZEY - 50, L"��", D2D1::ColorF::White, 25,
						WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"�ձٸ��", 0.f);
					D2D_RENDERER->renderTextField(560, WINSIZEY - 50, wstr3, color3, 25,
						WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"�ձٸ��", 0.f);
				}
				D2D_RENDERER->renderTextField(530, WINSIZEY - 110, L"��", D2D1::ColorF::White, 25,
					WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"�ձٸ��", 0.f);
				D2D_RENDERER->renderTextField(560, WINSIZEY - 110, wstr1, color1, 25,
					WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"�ձٸ��", 0.f);
				D2D_RENDERER->renderTextField(530, WINSIZEY - 80, L"��", D2D1::ColorF::White, 25,
					WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"�ձٸ��", 0.f);
				D2D_RENDERER->renderTextField(560, WINSIZEY - 80, wstr2, color2, 25,
					WINSIZEX, 0, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"�ձٸ��", 0.f);
			}
		}

		//�ڽ�Ƭ ���� �̹���
		if (i >= static_cast<int>(COSTUME_TYPE::END)) continue;
		_costumeCell[i].costumeSample->setScale(5);
		_costumeCell[i].costumeSample->render(Vector2(_costumeCell[i].cellRect.getCenter().getIntX(), _costumeCell[i].cellRect.getCenter().getIntY() + 131), false); 
		
		//_costumeCell[i].costumeSample->render(_costumeCell[i].cellRect.getCenter(), false);
		/*D2D_RENDERER->drawRectangle(_costumeCell[i].cellRect, D2D1::ColorF::Enum::Red, 1.0f, 3.0f);
		D2D_RENDERER->drawRectangle(FloatRect(_costumeCell[i].cellRect.getCenter(), _costumeCell[i].costumeSample->getSize(), PIVOT::CENTER), D2D1::ColorF::Enum::Red, 1.0f, 3.0f);*/
	}
	
	

}
