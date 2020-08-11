#pragma once

class  GameScene;
class Player;
class StageManager;

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

		Image* dashBgImg;
		Image* dashFgImg;
		FloatRect dashBg; // 대쉬 배경
		FloatRect dashFg; // 대쉬 게이지
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
		FloatRect currRc;
		FloatRect swapRc;
	};

	struct tagSkillUI // 현재 스킬
	{

	};

	struct tagMiniMap // 미니맵
	{
		FloatRect miniMapRc;
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

public:
	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; }
	void setPlayer(Player* player) { _player = player; }
	void setStageManager(StageManager* stageMgr) { _stageMgr = stageMgr; }

	void init();
	void release();
	void update(float const elaspedTime);
	void render();

	bool isActive() const noexcept { return _isActive; }
};

