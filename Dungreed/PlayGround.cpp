#include "stdafx.h"
#include "PlayGround.h"

#include "MainScene.h"
#include "GameScene.h"
#include "MapToolScene.h"
#include "SecondTestScene.h"

#include "Player.h"

#include <string>

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	GameNode::init(true);

	// ��� �̹��� IMAGE_MANAGER�� ���
	// * COMMON IMAGE

	IMAGE_MANAGER->addFrameImage("sampleTile", L"resources/images/Map/tileAtlas3.png", 10, 10);
	IMAGE_MANAGER->addFrameImage("sampleTile2", L"resources/images/Map/iceAtlas.png", 10, 10);

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
	IMAGE_MANAGER->addImage("KEY_LEFT", L"resources/images/common/key/Keyboard_��.png");
	IMAGE_MANAGER->addImage("KEY_RIGHT", L"resources/images/common/key/Keyboard_��.png");
	IMAGE_MANAGER->addImage("KEY_UP", L"resources/images/common/key/Keyboard_��.png");
	IMAGE_MANAGER->addImage("KEY_DOWN", L"resources/images/common/key/Keyboard_��.png");
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
	// ** UI
	IMAGE_MANAGER->addImage("UI/PLAYER_LIFE_BG", L"resources/images/gameScene/ui/PlayerLifeBack.png");
	IMAGE_MANAGER->addImage("UI/PLAYER_LIFE_FRAME", L"resources/images/gameScene/ui/PlayerLifeBase 1.png");
	IMAGE_MANAGER->addImage("UI/PLAYER_LIFE_BAR", L"resources/images/gameScene/ui/LifeBar.png");
	IMAGE_MANAGER->addFrameImage("UI/PLAYER_LIFE_WAVE", L"resources/images/gameScene/ui/LifeWave.png", 7, 1);
	IMAGE_MANAGER->addFrameImage("UI/GOLD", L"resources/images/gameScene/ui/gold.png", 8, 1);


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
	// * ����
	IMAGE_MANAGER->addFrameImage("Banshee/Idle"			, L"resources/images/Enemy/Banshee/idle.png"		, 6, 1);	// �⺻
	IMAGE_MANAGER->addFrameImage("Banshee/Idle_Shot"	, L"resources/images/Enemy/Banshee/idle_shot.png"	, 6, 1);	// �⺻ �ǰ�
	IMAGE_MANAGER->addFrameImage("Banshee/Attack"		, L"resources/images/Enemy/Banshee/attack.png"		, 6, 1);	// ����
	IMAGE_MANAGER->addFrameImage("Banshee/Attack_Shot"	, L"resources/images/Enemy/Banshee/attack_shot.png"	, 6, 1);	// ���� �ǰ�

	// * ����
	IMAGE_MANAGER->addFrameImage("Bat/Ice/Move"			, L"resources/images/Enemy/Bat/Ice/move.png"		,  6, 1);	// ���� (����) �̵�
	IMAGE_MANAGER->addFrameImage("Bat/Ice/Move_Shot"	, L"resources/images/Enemy/Bat/Ice/move_shot.png"	,  6, 1);	// ���� (����) �̵� �ǰ�
	IMAGE_MANAGER->addFrameImage("Bat/Ice/Attack"		, L"resources/images/Enemy/Bat/Ice/attack.png"		, 10, 1);	// ���� (����) ����
	IMAGE_MANAGER->addFrameImage("Bat/Ice/Attack_Shot"	, L"resources/images/Enemy/Bat/Ice/attack_shot.png"	, 10, 1);	// ���� (����) ���� �ǰ�

	IMAGE_MANAGER->addFrameImage("Bat/Red/Move"			, L"resources/images/Enemy/Bat/Red/move.png"		,  6, 1);	// ���� (����) �̵�
	IMAGE_MANAGER->addFrameImage("Bat/Red/Move_Shot"	, L"resources/images/Enemy/Bat/Red/move_shot.png"	,  6, 1);	// ���� (����) �̵� �ǰ�
	IMAGE_MANAGER->addFrameImage("Bat/Red/Attack"		, L"resources/images/Enemy/Bat/Red/attack.png"		, 10, 1);	// ���� (����) ����
	IMAGE_MANAGER->addFrameImage("Bat/Red/Attack_Shot"	, L"resources/images/Enemy/Bat/Red/attack_shot.png"	, 10, 1);	// ���� (����) ���� �ǰ�

	IMAGE_MANAGER->addFrameImage("Bat/Normal/Move"		, L"resources/images/Enemy/Bat/Normal/move.png"		, 6, 1);	// ���� (�⺻) �̵�
	IMAGE_MANAGER->addFrameImage("Bat/Normal/Move_Shot"	, L"resources/images/Enemy/Bat/Normal/move_shot.png", 6, 1);	// ���� (�⺻) �̵� �ǰ�

	IMAGE_MANAGER->addFrameImage("Bat/Bomb/Move"		, L"resources/images/Enemy/Bat/Bomb/move.png"		 , 6, 1);	// ���� (����) �̵�
	IMAGE_MANAGER->addFrameImage("Bat/Bomb/Move_Shot"	, L"resources/images/Enemy/Bat/Bomb/move_shot.png"	 , 6, 1);	// ���� (����) �̵� �ǰ�
	IMAGE_MANAGER->addFrameImage("Bat/Bomb/attack_Begin", L"resources/images/Enemy/Bat/Bomb/attack_begin.png", 6, 3);	// ���� (����) ���� �غ�
	// ** WEAPON
	// *** LongDistanceWeapon
	IMAGE_MANAGER->addImage("Lala'sMagicWand", L"resources/images/weapon/longDistanceWeapon/Lala'sMagicWand.png");
	IMAGE_MANAGER->addImage("MatchlockGun", L"resources/images/weapon/longDistanceWeapon/MatchlockGun.png");
	IMAGE_MANAGER->addImage("MetalBoomerang", L"resources/images/weapon/longDistanceWeapon/MetalBoomerang.png");
	IMAGE_MANAGER->addImage("OakBow", L"resources/images/weapon/longDistanceWeapon/OakBow.png");

	IMAGE_MANAGER->addFrameImage("Boomerang_Moving", L"resources/images/weapon/longDistanceWeapon/Boomerang_Moving.png", 2, 1);
	IMAGE_MANAGER->addFrameImage("OakBowAni", L"resources/images/weapon/longDistanceWeapon/OakBowAni.png", 6, 1);
	// **** WeaponBullet
	IMAGE_MANAGER->addImage("Arrow00", L"resources/images/weapon/longDistanceWeapon/Arrow00.png");
	IMAGE_MANAGER->addImage("GunBullet", L"resources/images/weapon/longDistanceWeapon/Bullet.png");
	IMAGE_MANAGER->addImage("GunBullet_Big", L"resources/images/weapon/longDistanceWeapon/Bullet_Big.png");
	// **** WeaponEffect
	IMAGE_MANAGER->addFrameImage("ArrowHitEffect", L"resources/images/weapon/longDistanceWeapon/effect/ArrowHitEffect.png", 6, 1);
	IMAGE_MANAGER->addFrameImage("BoomerangEffect", L"resources/images/weapon/longDistanceWeapon/effect/BoomerangEffect.png", 12, 1);
	IMAGE_MANAGER->addFrameImage("ChargeEffect", L"resources/images/weapon/longDistanceWeapon/effect/ChargeEffect.png", 8, 1);
	IMAGE_MANAGER->addFrameImage("HecateSmokeFX02", L"resources/images/weapon/longDistanceWeapon/effect/HecateSmokeFX02.png", 9, 1);
	IMAGE_MANAGER->addFrameImage("ShootEffect", L"resources/images/weapon/longDistanceWeapon/effect/ShootEffect.png", 3, 1);
	IMAGE_MANAGER->addFrameImage("ShootEffect01", L"resources/images/weapon/longDistanceWeapon/effect/ShootEffect01.png", 6, 1);
	IMAGE_MANAGER->addFrameImage("ShootEffect02", L"resources/images/weapon/longDistanceWeapon/effect/ShootEffect02.png", 6, 1);

	//***MeleeWeapon
	IMAGE_MANAGER->addImage("ShortSpear", L"resources/images/MeleeWeapon/ShortSpear.png");
	IMAGE_MANAGER->addImage("ShortSword", L"resources/images/MeleeWeapon/ShortSword.png");
	//***MeleeWeaponEffect
	IMAGE_MANAGER->addFrameImage("SwingFX", L"resources/images/MeleeWeapon/SwingFX.png",3,1);
	IMAGE_MANAGER->addFrameImage("StabFX", L"resources/images/MeleeWeapon/StabFX.png",4,1);






	IMAGE_MANAGER->addFrameImage("Bat/Giant_Normal/Idle"		, L"resources/images/Enemy/Bat/Giant_Normal/idle.png"		,  7, 1);	// ���� (�Ŵ� �⺻) �⺻
	IMAGE_MANAGER->addFrameImage("Bat/Giant_Normal/Idle_Shot"	, L"resources/images/Enemy/Bat/Giant_Normal/idle_shot.png"	,  7, 1);	// ���� (�Ŵ� �⺻) �⺻ �ǰ�
	IMAGE_MANAGER->addFrameImage("Bat/Giant_Normal/Attack"		, L"resources/images/Enemy/Bat/Giant_Normal/attack.png"		, 10, 1);	// ���� (�Ŵ� �⺻) ����
	IMAGE_MANAGER->addFrameImage("Bat/Giant_Normal/Attack_Shot"	, L"resources/images/Enemy/Bat/Giant_Normal/attack_shot.png", 10, 1);	// ���� (�Ŵ� �⺻) ���� �ǰ�

	IMAGE_MANAGER->addFrameImage("Bat/Giant_Red/Idle"			, L"resources/images/Enemy/Bat/Giant_Red/idle.png"			,  7, 1);	// ���� (�Ŵ� ����) �⺻
	IMAGE_MANAGER->addFrameImage("Bat/Giant_Red/Idle_Shot"		, L"resources/images/Enemy/Bat/Giant_Red/idle_shot.png"		,  7, 1);	// ���� (�Ŵ� ����) �⺻ �ǰ�
	IMAGE_MANAGER->addFrameImage("Bat/Giant_Red/Attack"			, L"resources/images/Enemy/Bat/Giant_Red/attack.png"		, 10, 1);	// ���� (�Ŵ� ����) ����
	IMAGE_MANAGER->addFrameImage("Bat/Giant_Red/Attack_Shot"	, L"resources/images/Enemy/Bat/Giant_Red/attack_shot.png"	, 10, 1);	// ���� (�Ŵ� ����) ���� �ǰ�

	// *Accessories
	IMAGE_MANAGER->addImage("SpikeBall", L"resources/images/Accessories/SpikeBall.png");                       // ������	
	IMAGE_MANAGER->addImage("BloodStoneRing", L"resources/images/Accessories/BloodStoneRing.png");             // ��������	
	IMAGE_MANAGER->addImage("Voluspa", L"resources/images/Accessories/Voluspa.png");                           // ���罺��
	IMAGE_MANAGER->addImage("Voluspa0", L"resources/images/Accessories/Voluspa0.png");                         // ���罺��â
	IMAGE_MANAGER->addImage("BombPouch", L"resources/images/Accessories/BombPouch.png");                       // �뽬��ź	
	IMAGE_MANAGER->addFrameImage("BombPouch0", L"resources/images/Accessories/BombPouch0.png", 12, 1);         // �뽬��ź �������̹���
	IMAGE_MANAGER->addImage("CarpCoinPurse", L"resources/images/Accessories/CarpCoinPurse.png");               // �׾��� ��������
	IMAGE_MANAGER->addImage("DaisyRing", L"resources/images/Accessories/DaisyRing.png");                       // ��������
	IMAGE_MANAGER->addImage("DemonBoots", L"resources/images/Accessories/DemonBoots.png");                     // �Ǹ�����
	IMAGE_MANAGER->addFrameImage("DemonBoots0", L"resources/images/Accessories/DemonBoots0.png", 6, 1);        // �Ǹ����� �������̹���
	IMAGE_MANAGER->addImage("MultiBullet", L"resources/images/Accessories/MultiBullet.png");                   // 3������ź
	IMAGE_MANAGER->addImage("GoldenCandy", L"resources/images/Accessories/GoldenCandy.png");                   // ���ĵ��
	IMAGE_MANAGER->addImage("babyGreenBat", L"resources/images/Accessories/babyGreenBat.png");                 // �Ʊ� �׸�����
	IMAGE_MANAGER->addImage("babyuGreenBat", L"resources/images/Accessories/GreenBat.png");                    // �׸�����
	IMAGE_MANAGER->addImage("GreenMomBat", L"resources/images/Accessories/GreenMomBat.png");                   // �����׸�����
	IMAGE_MANAGER->addImage("GreenDadBat", L"resources/images/Accessories/GreenDadBat.png");                   // �ƺ��׸�����
	IMAGE_MANAGER->addFrameImage("BabyBatBulletAt", L"resources/images/Accessories/BabyBatBullet0.png", 5, 1); // �Ʊ� �׸����� ���� �������̹���
	IMAGE_MANAGER->addFrameImage("BabyBatBulletFx", L"resources/images/Accessories/BabyBatBulletFX.png", 7, 1);// �Ʊ� �׸����� ���� �浹 �������̹���
	IMAGE_MANAGER->addFrameImage("babyGreenBatF", L"resources/images/Accessories/GreenBat0.png", 6, 1);        // �Ʊ� �׸����� �������̹���
	IMAGE_MANAGER->addFrameImage("GreenBatF", L"resources/images/Accessories/GreenBat3.png", 6, 1);            // �׸����� �������̹���
	IMAGE_MANAGER->addFrameImage("GreenDadBatF", L"resources/images/Accessories/GreenDadBat1.png", 7, 1);      // �ƺ� �׸����� �������̹���
	IMAGE_MANAGER->addFrameImage("GreenMomBatF", L"resources/images/Accessories/GreenMomBat2.png", 7, 1);      // ���� �׸����� �������̹���
	IMAGE_MANAGER->addImage("HeartOfCosmos", L"resources/images/Accessories/HeartOfCosmos.png");               // ���ֽ���
	IMAGE_MANAGER->addFrameImage("HeartOfCosmos0", L"resources/images/Accessories/HeartOfCosmos0.png", 20, 1); // ���ֽ��� ���� ������
	IMAGE_MANAGER->addImage("IceBall", L"resources/images/Accessories/IceBall.png");                           // ������
	IMAGE_MANAGER->addFrameImage("IceBall0", L"resources/images/Accessories/IceBall0.png", 7, 1);              // ������ ��Ʈ �ϼ� �������̹���
	IMAGE_MANAGER->addImage("Jarngreipr", L"resources/images/Accessories/Jarngreipr.png");                     // �߸��׷�������
	IMAGE_MANAGER->addImage("Magnet", L"resources/images/Accessories/Magnet.png");                             // �ڼ�
	IMAGE_MANAGER->addImage("MagnifyingGlass", L"resources/images/Accessories/MagnifyingGlass.png");           // ������
	IMAGE_MANAGER->addImage("MiniEarth", L"resources/images/Accessories/MiniEarth.png");                       // �̴��༺
	IMAGE_MANAGER->addFrameImage("MiniEarth0", L"resources/images/Accessories/MiniEarth0.png", 9, 1);          // �̴��༺ ������ �̹���
	IMAGE_MANAGER->addImage("SecretMap", L"resources/images/Accessories/SecretMap.png");                       // ��и�
	IMAGE_MANAGER->addImage("SilverBullet", L"resources/images/Accessories/SilverBullet.png");                 // ��ź	
	IMAGE_MANAGER->addImage("SpikeBoots", L"resources/images/Accessories/SpikeBoots.png");                     // ���ýŹ�
	IMAGE_MANAGER->addImage("SpringShoes", L"resources/images/Accessories/SpringShoes.png");                   // �����Ź�
	IMAGE_MANAGER->addImage("MetalBoots", L"resources/images/Accessories/MetalBoots.png");                     // ��ö�Ź�
	IMAGE_MANAGER->addImage("TAANA", L"resources/images/Accessories/TAANA.png");                               // Ÿ��
	IMAGE_MANAGER->addFrameImage("TAANA0", L"resources/images/Accessories/TAANA0.png", 7, 1);                  // Ÿ�� ������ �̹���
	IMAGE_MANAGER->addImage("Watcher", L"resources/images/Accessories/Watcher.png");                           // �ֽ���
	IMAGE_MANAGER->addFrameImage("Watcher0", L"resources/images/Accessories/Watcher0.png", 7, 1);              // �ֽ��� ������ �̹���
	IMAGE_MANAGER->addFrameImage("Watcher1", L"resources/images/Accessories/Watcher1.png", 13, 1);             // �ֽ��� ��Ʈ �ϼ� ������ �̹���
	IMAGE_MANAGER->addImage("Wing", L"resources/images/Accessories/Wing.png");                                 // ����
	IMAGE_MANAGER->addImage("Wing0", L"resources/images/Accessories/Wing0.png");                               // ���� ���� �̹���
	IMAGE_MANAGER->addImage("Wingboots", L"resources/images/Accessories/Wingboots.png");                       // ������
	

	// * ����
	IMAGE_MANAGER->addFrameImage("Ghost/Move"		, L"resources/images/Enemy/Ghost/move.png"			, 6, 1);	// ���� �̵�
	IMAGE_MANAGER->addFrameImage("Ghost/Move_Shot"	, L"resources/images/Enemy/Ghost/move_shot.png"		, 6, 1);	// ���� �̵� �ǰ�
	IMAGE_MANAGER->addFrameImage("Ghost/Attack"		, L"resources/images/Enemy/Ghost/attack.png"		, 3, 1);	// ���� ����
	IMAGE_MANAGER->addFrameImage("Ghost/Attack_Shot", L"resources/images/Enemy/Ghost/attack_shot.png"	, 3, 1);	// ���� ���� �ǰ�

	// * ��ť����
	IMAGE_MANAGER->addFrameImage("Lilith/Idle"		, L"resources/images/Enemy/Lilith/idle.png"			, 12, 1);	// ������ �⺻
	IMAGE_MANAGER->addFrameImage("Lilith/Idle_Shot"	, L"resources/images/Enemy/Lilith/idle_shot.png"	, 12, 1);	// ������ �⺻ �ǰ�
	IMAGE_MANAGER->addFrameImage("Lilith/Move"		, L"resources/images/Enemy/Lilith/move.png"			,  6, 1);	// ������ �̵�
	IMAGE_MANAGER->addFrameImage("Lilith/Move_Shot"	, L"resources/images/Enemy/Lilith/move_shot.png"	,  6, 1);	// ������ �̵� �ǰ�
	IMAGE_MANAGER->addImage("Lilith/attack"		, L"resources/images/Enemy/Lilith/attack.png"		);				// ������ ����
	IMAGE_MANAGER->addImage("Lilith/attack_Shot", L"resources/images/Enemy/Lilith/attack_Shot.png"	);				// ������ ���� �ǰ�

	// * �ذ�
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Idle"		, L"resources/images/Enemy/Skel/Big_Ice/idle.png"		,  8, 1);	// �ذ� ������� �⺻
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Idle_Shot"	, L"resources/images/Enemy/Skel/Big_Ice/idle_shot.png"	,  8, 1);	// �ذ� ������� �⺻ �ǰ�
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Move"		, L"resources/images/Enemy/Skel/Big_Ice/move.png"		,  6, 1);	// �ذ� ������� �̵�
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Move_Shot"	, L"resources/images/Enemy/Skel/Big_Ice/move_shot.png"	,  6, 1);	// �ذ� ������� �̵� �ǰ�
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Attack"		, L"resources/images/Enemy/Skel/Big_Ice/attack.png"		, 13, 1);	// �ذ� ������� ����
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Attack_Shot"	, L"resources/images/Enemy/Skel/Big_Ice/attack_shot.png", 13, 1);	// �ذ� ������� ���� �ǰ�
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Skill"		, L"resources/images/Enemy/Skel/Big_Ice/Skill.png"		, 12, 1);	// �ذ� ������� ��ų
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Skill_Shot"	, L"resources/images/Enemy/Skel/Big_Ice/Skill_Shot.png"	, 12, 1);	// �ذ� ������� ��ų �ǰ�

	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Idle"			, L"resources/images/Enemy/Skel/Big_Normal/idle.png"		, 5, 1);	// �ذ� ��� �⺻
	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Idle_Shot"	, L"resources/images/Enemy/Skel/Big_Normal/idle_Shot.png"	, 5, 1);	// �ذ� ��� �⺻ �ǰ�
	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Move"			, L"resources/images/Enemy/Skel/Big_Normal/Move.png"		, 6, 1);	// �ذ� ��� �̵�
	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Move_Shot"	, L"resources/images/Enemy/Skel/Big_Normal/Move_Shot.png"	, 6, 1);	// �ذ� ��� �̵� �ǰ�
	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Attack"		, L"resources/images/Enemy/Skel/Big_Normal/attack.png"		, 12, 1);	// �ذ� ��� ����
	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Attack_Shot"	, L"resources/images/Enemy/Skel/Big_Normal/attack_shot.png"	, 12, 1);	// �ذ� ��� ���� �ǰ�

	IMAGE_MANAGER->addFrameImage("Skel/Dog/Idle"		, L"resources/images/Enemy/Skel/Dog/idle.png"		, 5, 1);	// �ذ� ������ �⺻
	IMAGE_MANAGER->addFrameImage("Skel/Dog/Idle_Shot"	, L"resources/images/Enemy/Skel/Dog/idle_shot.png"	, 5, 1);	// �ذ� ������ �⺻ �ǰ�
	IMAGE_MANAGER->addFrameImage("Skel/Dog/Move"		, L"resources/images/Enemy/Skel/Dog/Move.png"		, 7, 1);	// �ذ� ������ �̵�
	IMAGE_MANAGER->addFrameImage("Skel/Dog/Move_Shot"	, L"resources/images/Enemy/Skel/Dog/Move_shot.png"	, 7, 1);	// �ذ� ������ �̵� �ǰ�

	IMAGE_MANAGER->addFrameImage("Skel/Magician_Ice/Idle"		, L"resources/images/Enemy/Skel/Magician_Ice/idle.png"			,  6, 1);	// �ذ� ���������� �⺻
	IMAGE_MANAGER->addFrameImage("Skel/Magician_Ice/Idle_Shot"	, L"resources/images/Enemy/Skel/Magician_Ice/idle_shot.png"		,  6, 1);	// �ذ� ���������� �⺻ �ǰ�
	IMAGE_MANAGER->addFrameImage("Skel/Magician_Ice/Attack"		, L"resources/images/Enemy/Skel/Magician_Ice/attack.png"		, 12, 1);	// �ذ� ���������� ����
	IMAGE_MANAGER->addFrameImage("Skel/Magician_Ice/Attack_Shot", L"resources/images/Enemy/Skel/Magician_Ice/attack_shot.png"	, 12, 1);	// �ذ� ���������� ���� �ǰ�

	IMAGE_MANAGER->addFrameImage("test", L"resources/images/Enemy/Skel/Small/move.png", 6,1);

	// * ���ʹ� �Ҹ�
	IMAGE_MANAGER->addFrameImage("Banshee/Bullet"	, L"resources/images/Enemy/Banshee/bullet.png"		, 4, 1);	// ���� �Ѿ�
	IMAGE_MANAGER->addFrameImage("Banshee/Bullet_FX", L"resources/images/Enemy/Banshee/bullet_FX.png"	, 6, 1);	// ���� �Ѿ� ����

	IMAGE_MANAGER->addFrameImage("Bat/Bullet/Small"		, L"resources/images/Enemy/Bat/Bullet/Small/Bullet.png"		, 5, 1);	// ���� �Ѿ� ���� ��
	IMAGE_MANAGER->addFrameImage("Bat/Bullet/Small_FX"	, L"resources/images/Enemy/Bat/Bullet/Small/Bullet_FX.png"	, 7, 1);	// ���� �Ѿ� ���� �� ����




	// ��� �� SCENE_MANAGER�� ���
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

//�޸� ����
void playGround::release()
{
	GameNode::release();
}

//����
void playGround::update()
{
	GameNode::update();

	SCENE_MANAGER->update();
	DEBUG_MANAGER->update();
}

//�׸��� ����
void playGround::render()
{	
	D2D_RENDERER->beginRender(D2D1::ColorF::Gray);
	{
		SCENE_MANAGER->render();
	}
	D2D_RENDERER->endRender();
}
