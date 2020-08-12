#include "stdafx.h"
#include "EffectManager.h"
#include "Effect.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::init()
{
}

void EffectManager::release()
{
	for (auto iter = _totalEffect.begin(); iter != _totalEffect.end(); iter++)
	{
		vEffects effects = iter->second;
		for (int i = 0; i < effects.size(); i++)
		{
			effects[i]->release();
			delete effects[i];
		}
		effects.clear();
	}
}

void EffectManager::update(float elapsedTime)
{
	for (auto iter = _totalEffect.begin(); iter != _totalEffect.end(); iter++)
	{
		vEffects effects = iter->second;
		for (int i = 0; i < effects.size(); i++)
		{
			effects[i]->update(elapsedTime);
		}
	}
}

void EffectManager::render()
{
	for (auto iter = _totalEffect.begin(); iter != _totalEffect.end(); iter++)
	{
		vEffects effects = iter->second;
		for (int i = 0; i < effects.size(); i++)
		{
			effects[i]->render();
		}
	}
}

void EffectManager::addEffect(string effectName, const char * imageName, int fps, int buffer)
{
	Image* img;
	vEffects vEffectBuffer;

	if (IMAGE_MANAGER->findImage(imageName))
	{
		img = IMAGE_MANAGER->findImage(imageName);
	}
	else
	{
		return;
	}

	for (int i = 0; i < buffer; ++i)
	{
		vEffectBuffer.push_back(new Effect);
		vEffectBuffer[i]->init(img, fps);
	}

	_totalEffect.insert(pair<string, vEffects>(effectName, vEffectBuffer));
}

void EffectManager::play(string effectName, Vector2 pos, float angle)
{
	for (auto iter = _totalEffect.begin(); iter != _totalEffect.end(); iter++)
	{
		if (iter->first != effectName) continue;
		vEffects effects = iter->second;
		for (int i = 0; i < effects.size(); i++)
		{
			if (effects[i]->getIsRunning()) continue;
			effects[i]->startEffect(pos, angle);
			return;
		}
	}
}

void EffectManager::play(string effectName, Vector2 pos, Vector2 size, float angle)
{
	for (auto iter = _totalEffect.begin(); iter != _totalEffect.end(); iter++)
	{
		if (iter->first != effectName) continue;
		vEffects effects = iter->second;
		for (int i = 0; i < effects.size(); i++)
		{
			if (effects[i]->getIsRunning()) continue;
			effects[i]->startEffect(pos, size, angle);
			return;
		}
	}
}

