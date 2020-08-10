#include "stdafx.h"
#include "PlayGround.h"

#include "MainScene.h"
#include "GameScene.h"
#include "MapToolScene.h"
#include "TestScene.h"
#include "SecondTestScene.h"

#include "Player.h"

#include <string>

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	GameNode::init(true);

	// 모든 이미지 IMAGE_MANAGER에 등록
	// * COMMON IMAGE

	IMAGE_MANAGER->addFrameImage("sampleTile", L"resources/images/Map/tileAtlas.png", 10, 10);
	

	// ** MOUSE CURSOR
	IMAGE_MANAGER->addImage("CURSOR_BASIC", L"resources/images/common/cursor/BasicCursor.png");
	IMAGE_MANAGER->addImage("CURSOR_SHOOTING", L"resources/images/common/cursor/ShootingCursor2.png");

	// ** CONFIG
	IMAGE_MANAGER->addImage("OPTION_HEADER", L"resources/images/common/option/OptionBase2.png");
	IMAGE_MANAGER->addImage("OPTION_BG", L"resources/images/common/option/ScrollRect.png");
	IMAGE_MANAGER->addImage("SCROLL_HEADER", L"resources/images/common/option/ScrollHeader.png");
	IMAGE_MANAGER->addImage("SCROLL_BG", L"resources/images/common/option/ScrollBg.png");
	IMAGE_MANAGER->addImage("KEYMAP_HEADER", L"resources/images/common/option/KeyMappingHead.png");
	IMAGE_MANAGER->addImage("KEYMAP_BUTTON", L"resources/images/common/option/KeyMappingButtonOn.png");
	IMAGE_MANAGER->addImage("KEYMAP_BUTTON_SELECTED", L"resources/images/common/option/KeyMappingButtonSelect.png");

	// ** BUTTON
	IMAGE_MANAGER->addImage("BUTTON_EXIT", L"resources/images/common/button/FullWindowExitButton.png");
	IMAGE_MANAGER->addImage("BUTTON_EXIT_SELECTED", L"resources/images/common/button/FullWindowExitButton_Selected.png");

	// ** KEYBOARD
	// *** DIRECTION
	IMAGE_MANAGER->addImage("KEY_LEFT", L"resources/images/common/key/Keyboard_←.png");
	IMAGE_MANAGER->addImage("KEY_RIGHT", L"resources/images/common/key/Keyboard_→.png");
	IMAGE_MANAGER->addImage("KEY_UP", L"resources/images/common/key/Keyboard_↑.png");
	IMAGE_MANAGER->addImage("KEY_DOWN", L"resources/images/common/key/Keyboard_↓.png");
	// *** NUMBER
	IMAGE_MANAGER->addImage("KEY_0", L"resources/images/common/key/Keyboard_0.png");
	IMAGE_MANAGER->addImage("KEY_1", L"resources/images/common/key/Keyboard_1.png");
	IMAGE_MANAGER->addImage("KEY_2", L"resources/images/common/key/Keyboard_2.png");
	IMAGE_MANAGER->addImage("KEY_3", L"resources/images/common/key/Keyboard_3.png");
	IMAGE_MANAGER->addImage("KEY_4", L"resources/images/common/key/Keyboard_4.png");
	IMAGE_MANAGER->addImage("KEY_5", L"resources/images/common/key/Keyboard_5.png");
	IMAGE_MANAGER->addImage("KEY_6", L"resources/images/common/key/Keyboard_6.png");
	IMAGE_MANAGER->addImage("KEY_7", L"resources/images/common/key/Keyboard_7.png");
	IMAGE_MANAGER->addImage("KEY_8", L"resources/images/common/key/Keyboard_8.png");
	IMAGE_MANAGER->addImage("KEY_9", L"resources/images/common/key/Keyboard_9.png");
	// *** ALPHABET
	IMAGE_MANAGER->addImage("KEY_A", L"resources/images/common/key/Keyboard_A.png");
	IMAGE_MANAGER->addImage("KEY_B", L"resources/images/common/key/Keyboard_B.png");
	IMAGE_MANAGER->addImage("KEY_C", L"resources/images/common/key/Keyboard_C.png");
	IMAGE_MANAGER->addImage("KEY_D", L"resources/images/common/key/Keyboard_D.png");
	IMAGE_MANAGER->addImage("KEY_E", L"resources/images/common/key/Keyboard_E.png");
	IMAGE_MANAGER->addImage("KEY_F", L"resources/images/common/key/Keyboard_F.png");
	IMAGE_MANAGER->addImage("KEY_G", L"resources/images/common/key/Keyboard_G.png");
	IMAGE_MANAGER->addImage("KEY_H", L"resources/images/common/key/Keyboard_H.png");
	IMAGE_MANAGER->addImage("KEY_I", L"resources/images/common/key/Keyboard_I.png");
	IMAGE_MANAGER->addImage("KEY_J", L"resources/images/common/key/Keyboard_J.png");
	IMAGE_MANAGER->addImage("KEY_K", L"resources/images/common/key/Keyboard_K.png");
	IMAGE_MANAGER->addImage("KEY_L", L"resources/images/common/key/Keyboard_L.png");
	IMAGE_MANAGER->addImage("KEY_M", L"resources/images/common/key/Keyboard_M.png");
	IMAGE_MANAGER->addImage("KEY_N", L"resources/images/common/key/Keyboard_N.png");
	IMAGE_MANAGER->addImage("KEY_O", L"resources/images/common/key/Keyboard_O.png");
	IMAGE_MANAGER->addImage("KEY_P", L"resources/images/common/key/Keyboard_P.png");
	IMAGE_MANAGER->addImage("KEY_Q", L"resources/images/common/key/Keyboard_Q.png");
	IMAGE_MANAGER->addImage("KEY_R", L"resources/images/common/key/Keyboard_R.png");
	IMAGE_MANAGER->addImage("KEY_S", L"resources/images/common/key/Keyboard_S.png");
	IMAGE_MANAGER->addImage("KEY_T", L"resources/images/common/key/Keyboard_T.png");
	IMAGE_MANAGER->addImage("KEY_U", L"resources/images/common/key/Keyboard_U.png");
	IMAGE_MANAGER->addImage("KEY_V", L"resources/images/common/key/Keyboard_V.png");
	IMAGE_MANAGER->addImage("KEY_W", L"resources/images/common/key/Keyboard_W.png");
	IMAGE_MANAGER->addImage("KEY_X", L"resources/images/common/key/Keyboard_X.png");
	IMAGE_MANAGER->addImage("KEY_Y", L"resources/images/common/key/Keyboard_Y.png");
	IMAGE_MANAGER->addImage("KEY_Z", L"resources/images/common/key/Keyboard_Z.png");
	// *** SPECIAL KEY
	IMAGE_MANAGER->addImage("KEY_ALT", L"resources/images/common/key/Keyboard_Alt.png");
	IMAGE_MANAGER->addImage("KEY_CTRL", L"resources/images/common/key/Keyboard_Ctrl.png");
	IMAGE_MANAGER->addImage("KEY_ENTER", L"resources/images/common/key/Keyboard_enter.png");
	IMAGE_MANAGER->addImage("KEY_ESC", L"resources/images/common/key/Keyboard_esc.png");
	IMAGE_MANAGER->addImage("KEY_SHIFT", L"resources/images/common/key/Keyboard_Shift.png");
	IMAGE_MANAGER->addImage("KEY_SPACE", L"resources/images/common/key/Keyboard_Space.png");
	IMAGE_MANAGER->addImage("KEY_TAB", L"resources/images/common/key/Keyboard_Tab.png");
	// *** MOUSE
	IMAGE_MANAGER->addImage("KEY_LBUTTON", L"resources/images/common/key/Mouse_L.png");
	IMAGE_MANAGER->addImage("KEY_RBUTTON", L"resources/images/common/key/Mouse_R.png");

	// ** SOUND BAR
	IMAGE_MANAGER->addImage("SOUND_BAR", L"resources/images/common/option/OptionSoundBar.png");
	IMAGE_MANAGER->addImage("SOUND_HANDLE", L"resources/images/common/option/OptionSoundHandle.png");

	// ** DATA MANAGER
	IMAGE_MANAGER->addImage("SLOT", L"resources/images/common/data/SlotBase.png");
	IMAGE_MANAGER->addImage("SLOT_SELECTED", L"resources/images/common/data/SlotBase_Selected.png");
	IMAGE_MANAGER->addImage("SLOT_DELETE", L"resources/images/common/data/SlotDeleteButton.png");
	IMAGE_MANAGER->addImage("SLOT_DELETE_SELECTED", L"resources/images/common/data/SlotDeleteButton_Selected.png");
	IMAGE_MANAGER->addImage("SLOT_NUM_1", L"resources/images/common/data/SlotText1.EN.png");
	IMAGE_MANAGER->addImage("SLOT_NUM_2", L"resources/images/common/data/SlotText2.EN.png");
	IMAGE_MANAGER->addImage("SLOT_NUM_3", L"resources/images/common/data/SlotText3.EN.png");

	// * MAIN SCENE
	IMAGE_MANAGER->addImage("MAIN_SCENE/LOGO", L"resources/images/mainScene/MainLogo.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/COPYRIGHT", L"resources/images/mainScene/Copyright.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/TEAM_LOGO", L"resources/images/mainScene/TeamLogo.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/PLAY_ON", L"resources/images/mainScene/PlayOn_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/PLAY_OFF", L"resources/images/mainScene/PlayOff_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/OPTION_ON", L"resources/images/mainScene/OptionOn_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/OPTION_OFF", L"resources/images/mainScene/OptionOff_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/EXIT_ON", L"resources/images/mainScene/ExitOn_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/EXIT_OFF", L"resources/images/mainScene/ExitOff_Kor.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/FRONT_CLOUD", L"resources/images/mainScene/FrontCloud.png");
	IMAGE_MANAGER->addImage("MAIN_SCENE/BACK_CLOUD", L"resources/images/mainScene/BackCloud.png");
	IMAGE_MANAGER->addFrameImage("MAIN_SCENE/BIRD", L"resources/images/mainScene/bird.png", 8, 1);

	// * STAGE SCENE
	// ** VILLIGE
	IMAGE_MANAGER->addImage("Town_BGL", L"resources/images/Map/BGLayer_0.png");
	IMAGE_MANAGER->addImage("Town_BG", L"resources/images/Map/TownBG_Day.png");
	IMAGE_MANAGER->addImage("Town_BG2", L"resources/images/Map/TownLayer_Day.png");
	IMAGE_MANAGER->addImage("Town_Floor", L"resources/images/Map/TownFloor.png");

	// ** DUNGEON

	// ** PLAYER
	IMAGE_MANAGER->addFrameImage("PLAYER/IDLE", L"resources/images/Characters/Player/player_idle.png", 5, 1);
	IMAGE_MANAGER->addFrameImage("PLAYER/RUN", L"resources/images/Characters/Player/player_run.png", 8, 1);
	IMAGE_MANAGER->addImage("PLAYER/JUMP", L"resources/images/Characters/Player/player_jump.png");
	IMAGE_MANAGER->addImage("PLAYER/DIE", L"resources/images/Characters/Player/player_die.png");

	// ** ENEMY

	// *Weapon

	//**MeleeWeapon
	IMAGE_MANAGER->addImage("ShortSpear", L"resources/images/MeleeWeapon/ShortSpear.png");

	// 모든 씬 SCENE_MANAGER에 등록
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->addScene("GAME", new GameScene);
	SCENE_MANAGER->addScene("MapTool", new MapToolScene);
	SCENE_MANAGER->addScene("SECOND", new SecondTestScene);
	SCENE_MANAGER->changeScene("GAME");	

	TIME_MANAGER->update();

	CONFIG_MANAGER->init();
	DATA_MANAGER->init();
	return S_OK;
}

//메모리 해제
void playGround::release()
{
	GameNode::release();
}

//연산
void playGround::update()
{
	GameNode::update();

	SCENE_MANAGER->update();
	DEBUG_MANAGER->update();
}

//그리기 전용
void playGround::render()
{	
	D2D_RENDERER->beginRender(D2D1::ColorF::White);
	{
		SCENE_MANAGER->render();
	}
	D2D_RENDERER->endRender();
}
