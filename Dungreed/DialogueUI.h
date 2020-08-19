#pragma once
#include "Npc.h"

class DialogueUI
{
private:
	bool _isActive;
	
	Npc* _npc; // 현재 대화창을 연 NPC

	string _nameDialogue;
	string _bodyDialogue;
	vector<string> _selectDialogue;

	FloatRect _nameRc;
	FloatRect _bodyRc;
	vector<FloatRect> _selectRc;
	float _currElapsedTime;
	int _currBodyLen;

public:
	bool isActive() const noexcept { return _isActive; }
	void setActive(bool active) { _isActive = active; }

	void startDialogue(Npc* npc);

	void init();
	void release();
	void update(float elapsedTime);
	void render();
};

