#include "stdafx.h"
#include "DialogueUI.h"
#include "Npc.h"

void DialogueUI::startDialogue(Npc* npc)
{
	_isActive = true;
	_currElapsedTime = 0;
	_currBodyLen = 0;
	_npc = npc;
	_nameDialogue = npc->getName();
	_bodyDialogue = npc->getBodyDialogue();
	_selectDialogue = npc->getSelectDialogues();
	_selectDialogue.push_back(L"아무것도");
	_selectRc.clear();
	for (int i = 0; i < _selectDialogue.size(); i++)
	{
		_selectRc.push_back(FloatRect(WINSIZEX - 300, WINSIZEY - 429 + 50 * i, WINSIZEX, WINSIZEY - 429 + (50 * (i + 1))));
	}

	_finishBody = false;

	/*_bodyDialogue = bodyDialogue;
	_selectDialogue = selectDialogue;*/
}

void DialogueUI::init()
{
	_isActive = false;
	_currElapsedTime = 0;
	_currBodyLen = 0;

	_nameRc = FloatRect(50, WINSIZEY - 270, WINSIZEX, WINSIZEY - 200);
	_bodyRc = FloatRect(50, WINSIZEY - 180, WINSIZEX, WINSIZEY - 140);
	
}

void DialogueUI::release()
{
}

void DialogueUI::update(float elapsedTime)
{
	if (!_finishBody)
	{
		_currElapsedTime += elapsedTime;

		while (_currElapsedTime > 0.07f)
		{
			_currElapsedTime -= 0.07f;
			_currBodyLen += 1;
		}

		if (_currBodyLen >= _bodyDialogue.size())
		{
			_finishBody = true;
		}

		if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::ATTACK)))
		{
			_finishBody = true;
			_currBodyLen = _bodyDialogue.size();
		}
	}
	else
	{
		if (KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::ATTACK)))
		{
			for (int i = 0; i < _selectRc.size(); i++)
			{
				if (_selectRc[i].ptInRect(_ptMouse))
				{
					if (i != _selectRc.size() - 1)
					{
						_npc->clickMenu(i);
					}
					_npc->setActiveInteraction(false);
					_isActive = false;
					break;
				}
			}
		}
	}
}

void DialogueUI::render()
{
	IMAGE_MANAGER->findImage("UI/DIALOGUE/BASE")->render(Vector2(WINSIZEX * 0.5, WINSIZEY - 150));

	D2D_RENDERER->renderTextField(_nameRc.left, _nameRc.top, _nameDialogue, RGB(255, 178, 144), _nameRc.getHeight(), _nameRc.getWidth(), _nameRc.getHeight(),
		1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아");
	D2D_RENDERER->renderTextField(_bodyRc.left, _bodyRc.top, _bodyDialogue.substr(0, _currBodyLen), 
		RGB(255, 255, 255), 35, _bodyRc.getWidth(), _bodyRc.getHeight(),
		1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아");

	if (_finishBody)
	{
		IMAGE_MANAGER->findImage("UI/DIALOGUE/SELECT")->render(Vector2(WINSIZEX - 150, WINSIZEY - 380));

		for (int i = 0; i < _selectRc.size(); i++)
		{
			if (_selectRc[i].ptInRect(_ptMouse))
			{
				IMAGE_MANAGER->findImage("UI/DIALOGUE/SELECT_SELECTED")->render(_selectRc[i].getCenter());
			}
		}

		for (int i = 0; i < _selectDialogue.size(); i++)
		{
			D2D_RENDERER->renderTextField(_selectRc[i].left, _selectRc[i].top, _selectDialogue[i],
				RGB(255, 255, 255), 35, _selectRc[i].getWidth(), _selectRc[i].getHeight(),
				1, DWRITE_TEXT_ALIGNMENT_CENTER, L"Aa카시오페아");
		}


	}
}
