#pragma once

class  GameScene;

class UIManager
{
private:
	GameScene* _gameScene;

public:
	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; }

	void init();
	void release();
	void update(float const elaspedTime);
	void render();
};

