#pragma once
#include "Npc.h"

class DialogueUI
{
private:
	bool _isActive;
	
	Npc* _npc; // ���� ��ȭâ�� �� NPC

	wstring _nameDialogue;
	wstring _bodyDialogue;
	vector<wstring> _selectDialogue;

	FloatRect _nameRc;
	FloatRect _bodyRc;
	vector<FloatRect> _selectRc;
	float _currElapsedTime;
	int _currBodyLen;

	bool _finishBody;

public:
	bool isActive() const noexcept { return _isActive; }
	void setActive(bool active) { _isActive = active; }

	void startDialogue(Npc* npc);

	void init();
	void release();
	void update(float elapsedTime);
	void render();
};

