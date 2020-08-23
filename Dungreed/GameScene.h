#pragma once
#include "GameNode.h"
#include "Player.h"
#include "StageManager.h"
#include "UIManager.h"
#include "GameEvent.h"


class GameScene : public GameNode
{
private:
	float _timeSpeed; // �ð� ���, 1 = �⺻ �ӵ�

	Player* _player;
	StageManager* _stageMgr;
	UIManager* _uiMgr;

	vector<GameEvent*> _events;
	bool _showPlayer;

public:
	virtual HRESULT init();			// �ʱ�ȭ ���� �Լ�
	virtual void release();			// �޸� ���� ����
	virtual void update();			// ���� ����
	virtual void render();			// �׸��� ����

	// �ʱ� ���� ���� �Լ�
	void loadInfo(tagLoadInfo const info);

	// �÷��̾� ���� �Լ�
	Vector2 getEnemyPos(Vector2 pos);
	vector<FloatRect> getEnemyRects();
	bool showPlayer() {return _showPlayer;}
	void setShowPlayer(float showPlayer) { _showPlayer = showPlayer; }
	void showDropItem(Item* item);

	// �������� ���� �Լ�
	void moveTo(GameObject* object, Vector2 moveDir);
	void moveRoom(Vector2 dir);
	bool attack(FloatRect* rect, AttackInfo* info);
	bool attack(FloatCircle* circle, AttackInfo* info);
	void attack(Projectile* projectile, AttackInfo* info);

	// UI ���� �Լ�
	bool isUIActive();
	void showDamage(DamageInfo info, Vector2 pos);


	// EVENT ���� �Լ�
	void pushR2REvent(COLORREF color, float remainTime);
	void pushTimeRatioEvent(float ratio, float remainTime);
};

