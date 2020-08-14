#include "stdafx.h"
#include "CostumeUI.h"
#include "Player.h"
#include "Costume.h"

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
	for (int i = 0; i < 7; i++)
	{
		//�� ��Ʈ ��ġ ����
		if (i > 0)
		{
			_costumeCell[i].cellRect = FloatRect(360 * i, 162, 360 * i + 360, WINSIZEY - 202);
		}
		if (i < 5)
		{
			//���� �̹��� �Ҵ�
			_costumeCell[i].costumeSample = IMAGE_MANAGER->findImage("UI/COSTUME/" + to_string(i));
		}
	}

	//_costumeCell[0].text = L""
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
	
	//�ڽ�Ƭ �� (ī�޶� ���� �ʿ�)
	for (int i = 0; i < 7; i++)
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
			//����
			D2D_RENDERER->renderTextField(20, WINSIZEY - 200, _costumeCell[i].text, D2D1::ColorF::White, 20,
				WINSIZEX, WINSIZEY, 1.0f, DWRITE_TEXT_ALIGNMENT_LEADING, L"�ձٸ��", 0.f);
		}

		//�ڽ�Ƭ ���� �̹���
		if (i > 4) continue;
		_costumeCell[i].costumeSample->setScale(5);
		_costumeCell[i].costumeSample->render(Vector2(_costumeCell[i].cellRect.getCenter().getIntX(), _costumeCell[i].cellRect.getCenter().getIntY() + 131), false); 
		
		//_costumeCell[i].costumeSample->render(_costumeCell[i].cellRect.getCenter(), false);
		/*D2D_RENDERER->drawRectangle(_costumeCell[i].cellRect, D2D1::ColorF::Enum::Red, 1.0f, 3.0f);
		D2D_RENDERER->drawRectangle(FloatRect(_costumeCell[i].cellRect.getCenter(), _costumeCell[i].costumeSample->getSize(), PIVOT::CENTER), D2D1::ColorF::Enum::Red, 1.0f, 3.0f);*/
	}
	
	_costumeBaseDownImg->render(Vector2(WINSIZEX / 2, WINSIZEY - 100), Vector2(WINSIZEX, 200));
}
