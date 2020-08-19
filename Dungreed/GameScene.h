#pragma once
#include "GameNode.h"
#include "Player.h"
#include "StageManager.h"
#include "UIManager.h"



class GameScene : public GameNode
{
private:
	float _timeSpeed; // 시간 배속, 1 = 기본 속도

	Player* _player;
	StageManager* _stageMgr;
	UIManager* _uiMgr;

public:
	virtual HRESULT init();			// 초기화 전용 함수
	virtual void release();			// 메모리 해제 전용
	virtual void update();			// 연산 전용
	virtual void render();			// 그리기 전용

	// 초기 세팅 관련 함수
	void loadInfo(tagLoadInfo const info);

	// 플레이어 관련 함수


	// 스테이지 관련 함수
	void moveTo(GameObject* object, Vector2 moveDir);
	void attack(FloatRect* rect, AttackInfo* info);
	void attack(FloatCircle* circle, AttackInfo* info);
	void attack(Projectile* projectile, AttackInfo* info);

	// UI 관련 함수
	bool isUIActive();
	void showDamage(DamageInfo info, Vector2 pos);

};

