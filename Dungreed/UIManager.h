#pragma once
#include "InventoryUI.h"
#include "StatUI.h"
#include "CostumeUI.h"
#include "RestaurantUI.h"
#include "DialogueUI.h"
#include "DamageInfo.h"
#include "LinearFunc.h"
#include "DoorObject.h"

class GameScene;
class Player;
class StageManager;
class EnemyManager;
class NpcManager;
class ObjectManager;

class UIManager
{
private:
	struct tagPlayerUI // 플레이어 hp, 대쉬카운트, 레벨
	{
		Image* hpBgImg; // hp바 배경
		Image* hpFrameImg; // hp바 프레임
		Image* hpBarImg; // hp바 게이지
		Image* hpWaveImg; // hp바 웨이브
		
		FloatRect hpBg; // hp바 배경
		FloatRect hpBar; // hp바 게이지
		FloatRect hpLevel; // 레벨 
		
		Animation* hpAni; // hp바 에니메이션

		FloatRect levelRc; // 레벨 공간

		Image* dashOutsideImg;
		Image* dashInsideImg;
		Image* dashGaugeImg;
		Vector2 dashFirstCenter;
	};

	struct tagLabelUI // 이미지 + 글 (골드, 포만감, 빠른시작, 빠른이동)
	{
		Image* img;
		Animation* ani;
		FloatRect imgRc;
		FloatRect textRc;
		int fontSize;
	};

	struct tagProgressUI
	{
		FloatRect progressRc;
	};

	struct tagWeaponUI // 현재 장착한 무기들
	{
		Image* bgImg;
		Vector2 frontBaseCenter;
		Vector2 backBaseCenter;
		FloatRect frontIndexRc;
		FloatRect frontBulletRc;
		
		float moveSpeed;
		int viewIndex;
		Vector2 move;
	};

	struct tagDamageUI // 대미지에 따른 숫자 표기
	{
		int type; // 0 = damage, 1 = EVADE, 2 = BLOCK
		float value; // 대미지 값
		COLORREF textColor;
		float remainTimes; // 사라지기까지 남은 시간
		float fontSize; // 글자 크기, 크리티컬이냐에 따라 다름
		Vector2 pos; // 그릴 위치
		float alpha;
	};

	struct tagEnemyHpUI // 에너미 체력
	{
		float maxHp;
		float currHp;
		Vector2 pos; // 그릴 위치
	};

	struct tagMiniMap // 미니맵
	{
		vector<FloatRect> collisionRect; // 미니맵에 그려질 땅
		vector<FloatRect> doorRect; // 미니맵에 그려질 문
		EnemyManager* enemyMgr;
		NpcManager* npcMgr;
		ObjectManager* objectMgr;
	};
private:
	GameScene* _gameScene;
	Player* _player;
	StageManager* _stageMgr;

	bool _isActive; // 창이 뜬 경우

	tagPlayerUI _hpUI; // 플레이어 HP
	tagLabelUI	_goldUI; // 플레이어 소지금 라벨
	tagLabelUI	_satietyUI; // 플레이어 포만감 라벨
	tagProgressUI	_satietyProgress; // 플레이어 포만감 프로그레스바
	tagWeaponUI	_weaponUI; // 무기 UI
	tagMiniMap _mapUI; // 미니맵 UI

	vector<tagDamageUI> _damageUI; // 대미지 표기 숫자 UI
	vector<tagEnemyHpUI> _enemyHpUI; // 적 체력바 UI

	DialogueUI _dialogueUI;
	InventoryUI _inventoryUI;
	StatUI _statUI;
	CostumeUI _costumeUI;
	RestaurantUI _restaurantUI;

public:
	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; }
	void setPlayer(Player* player);
	void setStageManager(StageManager* stageMgr) { _stageMgr = stageMgr; }

	void init();
	void release();
	void update(float const elaspedTime);
	void render();

	void setMap(vector<FloatRect> groundRect, vector<LinearFunc> groundLine, vector<LinearFunc> platformLine, vector<DoorObject*> doors, EnemyManager* enemyManager, NpcManager* npcManager, ObjectManager* objectManager);

	bool isActive() const noexcept { return _isActive; }

	void showDamage(DamageInfo damage, Vector2 pos);
	void showEnemyHp(float maxHp, float curHp, Vector2 pos);

	void setDialogue(Npc* npc) { _dialogueUI.startDialogue(npc); }
};

