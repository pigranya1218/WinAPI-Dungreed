#pragma once

class  GameScene;
class Player;

class UIManager
{
private:
	GameScene* _gameScene;
	Player* _player;

public:
	void setGameScene(GameScene* gameScene) { _gameScene = gameScene; }
	void setPlayer(Player* player) { _player = player; }

	void init();
	void release();
	void update(float const elaspedTime);
	void render();
};

