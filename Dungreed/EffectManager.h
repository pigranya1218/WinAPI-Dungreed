#pragma once
#include "SingletonBase.h"

class Effect;

class EffectManager : public SingletonBase<EffectManager>
{
private:
	using vEffects = vector<Effect*>;
	using mEffects = map<string, vEffects>;

private:
	mEffects _totalEffect;

public:
	EffectManager();
	~EffectManager();

	void init();
	void release();
	void update();
	void render();

	void addEffect(string effectName, const char* imageName, int fps, int buffer);

	/*void play(string effectName, int x, int y);
	void play(string effectName, int x, int y, int width, int height);*/

	void playZ(string effectName, Vector2 pos, float scale);

};

