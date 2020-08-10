#pragma once

class  GameScene;
class Player;
class StageManager;

class UIManager
{
private:
	struct tagPlayerUI // 플레이어 hp, 대쉬카운트, 레벨
	{
		Image* hpBgimg;
		Image* hpFgimg;
		FloatRect hpBg; // hp바 배경
		FloatRect hpFg; // hp바 게이지
		Animation hpAni; // hp바 에니메이션

		FloatRect levelRc; // 레벨 공간

		Image* dashBgImg;
		Image* dashFgImg;
		FloatRect dashBg; // 대쉬 배경
		FloatRect dashFg; // 대쉬 게이지
	};

	struct tagLabelUI // 이미지 + 글 (골드, 포만감, 빠른시작, 빠른이동)
	{
		Image* img;
		FloatRect imgRc;
		wstring text;
		FloatRect textRc;
		int fontSize;
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

