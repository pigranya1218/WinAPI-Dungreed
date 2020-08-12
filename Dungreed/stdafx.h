#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <atlconv.h>

#include <vector>
#include <map>
#include <queue>
#include <bitset>
using namespace std;

#include "LibraryHeader.h"
#include "Vector2.h"
#include "FloatRect.h"
#include "FloatCircle.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "Utils.h"
#include "D2DRenderer.h"
#include "Image.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "EffectManager.h"
#include "CameraManager.h"
#include "DebugManager.h"
#include "ConfigManager.h"
#include "DataManager.h"

using namespace TTYONE_UTIL;

// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
#define WINNAME (LPCTSTR)(TEXT("Dungreed"))
#define WINSTARTX	50
#define WINSTARTY	50
#define WINSIZEX	1600
#define WINSIZEY	900
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define RANDOM RandomFunction::getSingleton()
#define KEY_MANAGER KeyManager::getSingleton()
#define IMAGE_MANAGER ImageManager::getSingleton()
#define TIME_MANAGER TimeManager::getSingleton()
#define EFFECT_MANAGER EffectManager::getSingleton()
#define SOUND_MANAGER SoundManager::getSingleton()
#define SCENE_MANAGER SceneManager::getSingleton()
#define D2D_RENDERER D2DRenderer::getSingleton()
#define EFFECT_MANAGER EffectManager::getSingleton()
#define DEBUG_MANAGER DebugManager::getSingleton()
#define CONFIG_MANAGER ConfigManager::getSingleton()
#define DATA_MANAGER DataManager::getSingleton()
#define CAMERA CameraManager::getSingleton()

#define SAFE_DELETE(p)		{if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p)		{if(p) {(p)->release(); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[](p); (p) = NULL;}}
#define NEW_SAFE_RELEASE(p) {if(p){p->Release(); (p) = NULL;}}

#define Synthesize(ValueType,ValueName,FuncName) \
protected: ValueType ValueName;\
public: inline ValueType get##FuncName(void) const{return ValueName;}\
public: inline void set##FuncName(ValueType value){ValueName = value;}

#define SynthesizePublic(ValueType,ValueName,FuncName) \
public: ValueType ValueName;\
public: inline ValueType get##FuncName(void) const{return ValueName;}\
public: inline void set##FuncName(ValueType value){ValueName = value;}

//====================================
// ## 20.05.29 ## Extern ##
//====================================

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
extern HDC			_hdc;