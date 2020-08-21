#include "stdafx.h"
#include "AbilityUI.h"

void AbilityUI::init()
{
	//아이콘 이미지 할당
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

	//각각 어빌리티 창
	for (int i = 0; i < 5; i++)
	{
		_windows[i].baseRc = FloatRect(30 + 310 * i, 180, 330 + 310 * i, 780);
		_windows[i].buttonCir = FloatCircle(Vector2(_windows[i].baseRc.getCenter().x, _windows[i].baseRc.getCenter().y + 250), 30);
		//특성 아이콘을 배치할 렉트
		_windows[i].iconRc[1] = FloatRect(Vector2(_windows[i].baseRc.getCenter().x, _windows[i].baseRc.getCenter().y + 150), Vector2(60, 60), PIVOT::CENTER);
		_windows[i].iconRc[0] = FloatRect(Vector2(_windows[i].baseRc.getCenter().x - 70, _windows[i].baseRc.getCenter().y + 150), Vector2(60, 60), PIVOT::CENTER);
		_windows[i].iconRc[2] = FloatRect(Vector2(_windows[i].baseRc.getCenter().x + 70, _windows[i].baseRc.getCenter().y + 150), Vector2(60, 60), PIVOT::CENTER);
	}

	//렉트
	_bgRc = FloatRect(Vector2(WINSIZEX / 2, WINSIZEY / 2), Vector2(WINSIZEX, WINSIZEY), PIVOT::CENTER);
	_exitRc = FloatRect(WINSIZEX - 150, 40, WINSIZEX - 30, 130);
	_currPointRc = FloatRect(1270, 880, WINSIZEX - 50, WINSIZEY - 100);

	
}

void AbilityUI::release()
{
}

void AbilityUI::update(float elapsedTime)
{

	if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//창닫기
		if (_exitRc.ptInRect(_ptMouse))
		{
			_isActive = false;
		}
	}
}

void AbilityUI::render()
{
	//뒷배경 (반투명)
	D2D_RENDERER->fillRectangle(_bgRc, 34, 32, 52, 0.5); 
	//상단 라벨 띠지
	_labelImg->render(Vector2(WINSIZEX / 2, 80), Vector2(WINSIZEX, 160));
	//창닫기 단추
	if (_exitRc.ptInRect(_ptMouse))
	{
		_exitButtonSelectedImg->render(_exitRc.getCenter(), _exitRc.getSize());
	}
	else
	{
		_exitButtonImg->render(_exitRc.getCenter(), _exitRc.getSize());
	}
	//특성창
	for (int i = 0; i < 5; i++)
	{
		//특성창 배경
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
		//특성 찍기 단추(원형)
		//D2D_RENDERER->drawEllipse(_windows[i].buttonCir.origin, 50, D2D1::ColorF::Magenta, 1);
		Image* btnImg = _wrathButtonImg;
		switch (i)
		{
		case 0:
		{
			btnImg = _wrathButtonImg;
	
			/*
			{
				btnImg = _wrathButtonDisableImg;
			}*/
		}
			break;
		case 1:
		{
			btnImg = _swiftnessButtonImg;

		}
			break;
		case 2:
		{
			btnImg = _patienceButtonImg;

		}
			break;
		case 3:
		{
			btnImg = _arcaneButtonImg;

		}
			break;
		case 4:
		{
			btnImg = _greedButtonImg;

		}
			break;
		}
		btnImg->setScale(5.2);
		btnImg->render(_windows[i].buttonCir.origin, _windows[i].buttonCir.size);
		Image* icon[3][3];
		//특성 아이콘 배치
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
		for (int j = 0; j < 3; j++)
		{
			icon[j][2]->render(_windows[i].iconRc[j].getCenter(), _windows[i].iconRc[j].getSize());		
		}
		//TEST
		//특성 아이콘 렉트 렌더
		for (int j = 0; j < 3; j++)
		{
			D2D_RENDERER->drawRectangle(_windows[i].iconRc[j], D2D1::ColorF::Magenta, 1, 1);
		}
		//icon[0][0]->render(_windows[i].iconRc[0].getCenter(), _windows[i].iconRc->getSize());
	}
	//현재 남은 특성 포인트
	_currPointBack->render(_currPointRc.getCenter(), _currPointRc.getSize());
	_currPointFrame->render(_currPointRc.getCenter(), _currPointRc.getSize());
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
