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

	/*_bodyDialogue = bodyDialogue;
	_selectDialogue = selectDialogue;*/
}

void DialogueUI::init()
{
	_isActive = false;
	_currElapsedTime = 0;
	_currBodyLen = 0;

	_nameRc = FloatRect(0, WINSIZEY - 290, WINSIZEX, WINSIZEY - 240);
	_bodyRc = FloatRect(0, WINSIZEY - 300, WINSIZEX, WINSIZEY);
}

void DialogueUI::release()
{
}

void DialogueUI::update(float elapsedTime)
{
	while (_currElapsedTime > 0.1f)
	{
		_currElapsedTime -= 0.1f;
		_currBodyLen += 1;
	}
}

void DialogueUI::render()
{
	IMAGE_MANAGER->findImage("UI/DIALOGUE/BASE")->render(Vector2(WINSIZEX * 0.5, WINSIZEY - 150));
	IMAGE_MANAGER->findImage("UI/DIALOGUE/SELECT")->render(Vector2(WINSIZEX - 150, WINSIZEY - 380));

	D2D_RENDERER->renderTextField(_nameRc.left, _nameRc.top, TTYONE_UTIL::stringTOwsting(_nameDialogue), RGB(255, 255, 255), 50, _nameRc.getWidth(), _nameRc.getHeight(),
		1, DWRITE_TEXT_ALIGNMENT_LEADING, L"µÕ±Ù¸ð²Ã");
}
