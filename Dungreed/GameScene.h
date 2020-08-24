#pragma once
#include "GameNode.h"
#include "Player.h"
#include "StageManager.h"
#include "UIManager.h"
#include "GameEvent.h"


class GameScene : public GameNode
{
private:
	float _timeSpeed; // 시간 배속, 1 = 기본 속도

	Player* _player;
	StageManager* _stageMgr;
	UIManager* _uiMgr;

	vector<GameEvent*> _events;
	bool _showPlayer;

public:
	virtual HRESULT init();			// 초기화 전용 함수
	virtual void release();			// 메모리 해제 전용
	virtual void update();			// 연산 전용
	virtual void render();			// 그리기 전용

	// 초기 세팅 관련 함수
	void loadInfo(tagLoadInfo const info);

	// 플레이어 관련 함수
	Vector2 getEnemyPos(Vector2 pos);
	vector<FloatRect> getEnemyRects();
	bool showPlayer() {return _showPlayer;}
	void setShowPlayer(float showPlayer) { _showPlayer = showPlayer; }
	void showDropItem(Item* item);

	// 스테이지 관련 함수
	void moveTo(GameObject* object, Vector2 moveDir);
	void moveRoom(Vector2 dir);
	bool attack(FloatRect* rect, AttackInfo* info);
	bool attack(FloatCircle* circle, AttackInfo* info);
	void attack(Projectile* projectile, AttackInfo* info);

	// UI 관련 함수
	bool isUIActive();
	void showDamage(DamageInfo info, Vector2 pos);


	// EVENT 관련 함수
	void pushR2REvent(COLORREF color, float remainTime);
	void pushTimeRatioEvent(float ratio, float remainTime);
};

