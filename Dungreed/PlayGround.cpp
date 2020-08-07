#include "stdafx.h"
#include "PlayGround.h"

#include "MainScene.h"

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
	// ** MOUSE CURSOR
	IMAGE_MANAGER->addImage("CURSOR_BASIC", L"resources/images/common/cursor/BasicCursor.png");
	IMAGE_MANAGER->addImage("CURSOR_SHOOTING", L"resources/images/common/cursor/ShootingCursor2.png");

	// ** CONFIG
	IMAGE_MANAGER->addImage("OPTION_HEADER", L"resources/images/common/option/OptionBase2.png");
	IMAGE_MANAGER->addImage("OPTION_BG", L"resources/images/common/option/ScrollRect.png");

	// ** BUTTON
	IMAGE_MANAGER->addImage("BUTTON_EXIT", L"resources/images/common/button/FullWindowExitButton.png");
	IMAGE_MANAGER->addImage("BUTTON_EXIT_SELECTED", L"resources/images/common/button/FullWindowExitButton_Selected.png");

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

	// ** DUNGEON

	// ** ENEMY
	// * 수녀
	IMAGE_MANAGER->addFrameImage("Banshee/Idle"			, L"resources/images/Enemy/Banshee/idle.png"		, 6, 1);	// 기본
	IMAGE_MANAGER->addFrameImage("Banshee/Idle_Shot"	, L"resources/images/Enemy/Banshee/idle_shot.png"	, 6, 1);	// 기본 피격
	IMAGE_MANAGER->addFrameImage("Banshee/Attack"		, L"resources/images/Enemy/Banshee/attack.png"		, 6, 1);	// 공격
	IMAGE_MANAGER->addFrameImage("Banshee/Attack_Shot"	, L"resources/images/Enemy/Banshee/attack_shot.png"	, 6, 1);	// 공격 피격

	// * 박쥐
	IMAGE_MANAGER->addFrameImage("Bat/Ice/Move"			, L"resources/images/Enemy/Bat/Ice/move.png"		,  6, 1);	// 박쥐 (얼음) 이동
	IMAGE_MANAGER->addFrameImage("Bat/Ice/Move_Shot"	, L"resources/images/Enemy/Bat/Ice/move_shot.png"	,  6, 1);	// 박쥐 (얼음) 이동 피격
	IMAGE_MANAGER->addFrameImage("Bat/Ice/Attack"		, L"resources/images/Enemy/Bat/Ice/attack.png"		, 10, 1);	// 박쥐 (얼음) 공격
	IMAGE_MANAGER->addFrameImage("Bat/Ice/Attack_Shot"	, L"resources/images/Enemy/Bat/Ice/attack_shot.png"	, 10, 1);	// 박쥐 (얼음) 공격 피격

	IMAGE_MANAGER->addFrameImage("Bat/Red/Move"			, L"resources/images/Enemy/Bat/Red/move.png"		,  6, 1);	// 박쥐 (빨강) 이동
	IMAGE_MANAGER->addFrameImage("Bat/Red/Move_Shot"	, L"resources/images/Enemy/Bat/Red/move_shot.png"	,  6, 1);	// 박쥐 (빨강) 이동 피격
	IMAGE_MANAGER->addFrameImage("Bat/Red/Attack"		, L"resources/images/Enemy/Bat/Red/attack.png"		, 10, 1);	// 박쥐 (빨강) 공격
	IMAGE_MANAGER->addFrameImage("Bat/Red/Attack_Shot"	, L"resources/images/Enemy/Bat/Red/attack_shot.png"	, 10, 1);	// 박쥐 (빨강) 공격 피격

	IMAGE_MANAGER->addFrameImage("Bat/Normal/Move"		, L"resources/images/Enemy/Bat/Normal/move.png"		, 6, 1);	// 박쥐 (기본) 이동
	IMAGE_MANAGER->addFrameImage("Bat/Normal/Move_Shot"	, L"resources/images/Enemy/Bat/Normal/move_shot.png", 6, 1);	// 박쥐 (기본) 이동 피격

	IMAGE_MANAGER->addFrameImage("Bat/Bomb/Move"		, L"resources/images/Enemy/Bat/Bomb/move.png"		 , 6, 1);	// 박쥐 (자폭) 이동
	IMAGE_MANAGER->addFrameImage("Bat/Bomb/Move_Shot"	, L"resources/images/Enemy/Bat/Bomb/move_shot.png"	 , 6, 1);	// 박쥐 (자폭) 이동 피격
	IMAGE_MANAGER->addFrameImage("Bat/Bomb/attack_Begin", L"resources/images/Enemy/Bat/Bomb/attack_begin.png", 6, 3);	// 박쥐 (자폭) 폭발 준비

	IMAGE_MANAGER->addFrameImage("Bat/Giant_Normal/Idle"		, L"resources/images/Enemy/Bat/Giant_Normal/idle.png"		,  7, 1);	// 박쥐 (거대 기본) 기본
	IMAGE_MANAGER->addFrameImage("Bat/Giant_Normal/Idle_Shot"	, L"resources/images/Enemy/Bat/Giant_Normal/idle_shot.png"	,  7, 1);	// 박쥐 (거대 기본) 기본 피격
	IMAGE_MANAGER->addFrameImage("Bat/Giant_Normal/Attack"		, L"resources/images/Enemy/Bat/Giant_Normal/attack.png"		, 10, 1);	// 박쥐 (거대 기본) 공격
	IMAGE_MANAGER->addFrameImage("Bat/Giant_Normal/Attack_Shot"	, L"resources/images/Enemy/Bat/Giant_Normal/attack_shot.png", 10, 1);	// 박쥐 (거대 기본) 공격 피격

	IMAGE_MANAGER->addFrameImage("Bat/Giant_Red/Idle"			, L"resources/images/Enemy/Bat/Giant_Red/idle.png"			,  7, 1);	// 박쥐 (거대 빨강) 기본
	IMAGE_MANAGER->addFrameImage("Bat/Giant_Red/Idle_Shot"		, L"resources/images/Enemy/Bat/Giant_Red/idle_shot.png"		,  7, 1);	// 박쥐 (거대 빨강) 기본 피격
	IMAGE_MANAGER->addFrameImage("Bat/Giant_Red/Attack"			, L"resources/images/Enemy/Bat/Giant_Red/attack.png"		, 10, 1);	// 박쥐 (거대 빨강) 공격
	IMAGE_MANAGER->addFrameImage("Bat/Giant_Red/Attack_Shot"	, L"resources/images/Enemy/Bat/Giant_Red/attack_shot.png"	, 10, 1);	// 박쥐 (거대 빨강) 공격 피격

	// * 유령
	IMAGE_MANAGER->addFrameImage("Ghost/Move"		, L"resources/images/Enemy/Ghost/move.png"			, 6, 1);	// 유령 이동
	IMAGE_MANAGER->addFrameImage("Ghost/Move_Shot"	, L"resources/images/Enemy/Ghost/move_shot.png"		, 6, 1);	// 유령 이동 피격
	IMAGE_MANAGER->addFrameImage("Ghost/Attack"		, L"resources/images/Enemy/Ghost/attack.png"		, 3, 1);	// 유령 공격
	IMAGE_MANAGER->addFrameImage("Ghost/Attack_Shot", L"resources/images/Enemy/Ghost/attack_shot.png"	, 3, 1);	// 유령 공격 피격

	// * 서큐버스
	IMAGE_MANAGER->addFrameImage("Lilith/Idle"		, L"resources/images/Enemy/Lilith/idle.png"			, 12, 1);	// 리리스 기본
	IMAGE_MANAGER->addFrameImage("Lilith/Idle_Shot"	, L"resources/images/Enemy/Lilith/idle_shot.png"	, 12, 1);	// 리리스 기본 피격
	IMAGE_MANAGER->addFrameImage("Lilith/Move"		, L"resources/images/Enemy/Lilith/move.png"			,  6, 1);	// 리리스 이동
	IMAGE_MANAGER->addFrameImage("Lilith/Move_Shot"	, L"resources/images/Enemy/Lilith/move_shot.png"	,  6, 1);	// 리리스 이동 피격
	IMAGE_MANAGER->addImage("Lilith/attack"		, L"resources/images/Enemy/Lilith/attack.png"		);				// 리리스 공격
	IMAGE_MANAGER->addImage("Lilith/attack_Shot", L"resources/images/Enemy/Lilith/attack_Shot.png"	);				// 리리스 공격 피격

	// * 해골
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Idle"		, L"resources/images/Enemy/Skel/Big_Ice/idle.png"		,  8, 1);	// 해골 얼음기사 기본
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Idle_Shot"	, L"resources/images/Enemy/Skel/Big_Ice/idle_Shot.png"	,  8, 1);	// 해골 얼음기사 기본 피격
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Move"		, L"resources/images/Enemy/Skel/Big_Ice/Move.png"		,  6, 1);	// 해골 얼음기사 이동
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Move_Shot"	, L"resources/images/Enemy/Skel/Big_Ice/Move_Shot.png"	,  6, 1);	// 해골 얼음기사 이동 피격
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Skill"		, L"resources/images/Enemy/Skel/Big_Ice/Skill.png"		, 12, 1);	// 해골 얼음기사 스킬
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Skill_Shot"	, L"resources/images/Enemy/Skel/Big_Ice/Skill_Shot.png"	, 12, 1);	// 해골 얼음기사 스킬 피격

	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Idle"		, L"resources/images/Enemy/Skel/Big_Normal/idle.png"		, 5, 1);	// 해골 기사 기본
	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Idle_Shot", L"resources/images/Enemy/Skel/Big_Normal/idle_Shot.png"	, 5, 1);	// 해골 기사 기본 피격
	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Move"		, L"resources/images/Enemy/Skel/Big_Normal/Move.png"		, 6, 1);	// 해골 기사 이동
	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Move_Shot", L"resources/images/Enemy/Skel/Big_Normal/Move_Shot.png"	, 6, 1);	// 해골 기사 이동 피격

	IMAGE_MANAGER->addFrameImage("Skel/Dog/Idle"		, L"resources/images/Enemy/Skel/Dog/idle.png"		, 5, 1);	// 해골 강아지 기본
	IMAGE_MANAGER->addFrameImage("Skel/Dog/Idle_Shot"	, L"resources/images/Enemy/Skel/Dog/idle_shot.png"	, 5, 1);	// 해골 강아지 기본 피격
	IMAGE_MANAGER->addFrameImage("Skel/Dog/Move"		, L"resources/images/Enemy/Skel/Dog/Move.png"		, 7, 1);	// 해골 강아지 이동
	IMAGE_MANAGER->addFrameImage("Skel/Dog/Move_Shot"	, L"resources/images/Enemy/Skel/Dog/Move_shot.png"	, 7, 1);	// 해골 강아지 이동 피격

	IMAGE_MANAGER->addFrameImage("Skel/Magician_Ice/Idle"		, L"resources/images/Enemy/Skel/Magician_Ice/idle.png"			,  6, 1);	// 해골 얼음마법사 기본
	IMAGE_MANAGER->addFrameImage("Skel/Magician_Ice/Idle_Shot"	, L"resources/images/Enemy/Skel/Magician_Ice/idle_shot.png"		,  6, 1);	// 해골 얼음마법사 기본 피격
	IMAGE_MANAGER->addFrameImage("Skel/Magician_Ice/Attack"		, L"resources/images/Enemy/Skel/Magician_Ice/attack.png"		, 12, 1);	// 해골 얼음마법사 공격
	IMAGE_MANAGER->addFrameImage("Skel/Magician_Ice/Attack_Shot", L"resources/images/Enemy/Skel/Magician_Ice/attack_shot.png"	, 12, 1);	// 해골 얼음마법사 공격 피격






	// 모든 씬 SCENE_MANAGER에 등록
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->changeScene("MAIN");	

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
	D2D_RENDERER->beginRender(D2D1::ColorF::Black);
	{
		SCENE_MANAGER->render();
	}
	D2D_RENDERER->endRender();
}
