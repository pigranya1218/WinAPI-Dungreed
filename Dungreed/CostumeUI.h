#pragma once

class Player;
class PlayerStat;
class Costume;
class MetalPlateCos;
class AliceCos;
class RedLotusCos;
class PickaxCos;

enum class COSTUME_TYPE;

class CostumeUI
{
private:
	Player*			_player;
	Costume*		_costume;
	MetalPlateCos*	_metalPlateCos;
	AliceCos*		_aliceCos;
	RedLotusCos*	_redLotusCos;
	PickaxCos*		_pickaxCos;

	COSTUME_TYPE	_cosType;

	bool _isActive;

	Image* _costumeBaseUpImg = IMAGE_MANAGER->findImage("UI/COSTUME/BASE_UP");
	Image* _costumeBaseDownImg = IMAGE_MANAGER->findImage("UI/COSTUME/BASE_DOWN");
	Image* _exitBtn = IMAGE_MANAGER->findImage("BUTTON_EXIT");
	Image* _exitBtnSelected = IMAGE_MANAGER->findImage("BUTTON_EXIT_SELECTED");
	FloatRect _exitRc;
	FloatRect _midRc;
	//Vector2 _winCenter = Vector2(WINSIZEX / 2, WINSIZEY / 2);
private:
	struct tagCostumeCell
	{
		Image* costumeBackImg = IMAGE_MANAGER->findImage("UI/COSTUME/BACK");
		Image* costumeShadowImg = IMAGE_MANAGER->findImage("UI/COSTUME/SHADOW");
		Image* costumeNoneImg = IMAGE_MANAGER->findImage("UI/COSTUME/NONE");

		Image* costumeEquippedImg = IMAGE_MANAGER->findImage("UI/COSTUME/EQUIPPED");
		Image* costumeLockedImg = IMAGE_MANAGER->findImage("UI/COSTUME/LOCKED");
		Image* costumeUnlockedImg = IMAGE_MANAGER->findImage("UI/COSTUME/UNLOCKED");
		
		Image* costumeSelectedImg = IMAGE_MANAGER->findImage("UI/COSTUME/SELECTED");

		FloatRect cellRect;

		// 코스튬 샘플 이미지
		Image* costumeSample;
		// 코스튬 이름
		wstring cosTitle;
		// 코스튬 개요 
		wstring cosSummary;
		// 코스튬 상세내용
		wstring cosDetails;
		// 코스튬 변동 스탯
		PlayerStat* differStat;

	};

	tagCostumeCell _costumeCell[7];
public:
	void setPlayer(Player* player) { _player = player; }

	void init();
	void release();
	void update(float elapsedTime);
	void render();

	bool isActive() const noexcept { return _isActive; }
	void setActive(bool active) { _isActive = active; }
};

