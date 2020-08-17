#include "stdafx.h"
#include "PlayGround.h"

#include "MainScene.h"
#include "GameScene.h"
#include "MapToolScene.h"
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

	IMAGE_MANAGER->addFrameImage("sampleTile1", L"resources/images/Map/tileAtlas3.png", 10, 10);
	IMAGE_MANAGER->addFrameImage("sampleTile2", L"resources/images/Map/iceAtlas.png", 10, 10);
	IMAGE_MANAGER->addFrameImage("sampleTile3", L"resources/images/Map/townAtlas1.png", 10, 10);
	IMAGE_MANAGER->addFrameImage("AniPalette1", L"resources/images/Map/AniPalette1.png", 10, 10);

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
	// ** UI
	IMAGE_MANAGER->addImage("UI/PLAYER_LIFE_BG", L"resources/images/gameScene/ui/PlayerLifeBack.png");
	IMAGE_MANAGER->addImage("UI/PLAYER_LIFE_FRAME", L"resources/images/gameScene/ui/PlayerLifeBase 1.png");
	IMAGE_MANAGER->addImage("UI/PLAYER_LIFE_BAR", L"resources/images/gameScene/ui/LifeBar.png");
	IMAGE_MANAGER->addFrameImage("UI/PLAYER_LIFE_WAVE", L"resources/images/gameScene/ui/LifeWave.png", 7, 1);
	IMAGE_MANAGER->addFrameImage("UI/GOLD", L"resources/images/gameScene/ui/gold.png", 8, 1);
	IMAGE_MANAGER->addImage("UI/FOOD", L"resources/images/gameScene/ui/Food.png");
	IMAGE_MANAGER->addImage("UI/DASH_OUTSIDE", L"resources/images/gameScene/ui/DashCountBase_0.png");
	IMAGE_MANAGER->addImage("UI/DASH_INSIDE", L"resources/images/gameScene/ui/DashBase.png");
	IMAGE_MANAGER->addImage("UI/DASH_GAUGE", L"resources/images/gameScene/ui/DashCount.png");
	IMAGE_MANAGER->addImage("UI/WEAPON_BG", L"resources/images/gameScene/ui/EquippedWeaponBase.png");
	// *** INVENTORY
	IMAGE_MANAGER->addImage("UI/INVENTORY/BASE", L"resources/images/gameScene/ui/inventory/InventoryBase 2.png");
	IMAGE_MANAGER->addImage("UI/INVENTORY/EXIT", L"resources/images/gameScene/ui/inventory/InventoryExit.png");
	IMAGE_MANAGER->addImage("UI/INVENTORY/EXIT_SELECTED", L"resources/images/gameScene/ui/inventory/InventoryExit_Selected.png");
	IMAGE_MANAGER->addImage("UI/INVENTORY/WEAPON_0_SELECTED", L"resources/images/gameScene/ui/inventory/WeaponSelect0.png");
	IMAGE_MANAGER->addImage("UI/INVENTORY/WEAPON_1_SELECTED", L"resources/images/gameScene/ui/inventory/WeaponSelect1.png");
	IMAGE_MANAGER->addImage("UI/INVENTORY/WEAPON_X", L"resources/images/gameScene/ui/inventory/X.png");
	IMAGE_MANAGER->addImage("UI/INVENTORY/WEAPON_SELECTED", L"resources/images/gameScene/ui/inventory/weapon_selected.png");
	IMAGE_MANAGER->addImage("UI/INVENTORY/ACC_ZONE", L"resources/images/gameScene/ui/inventory/accessoryZone.png");
	IMAGE_MANAGER->addImage("UI/INVENTORY/ACC_BASE", L"resources/images/gameScene/ui/inventory/accessory.png");
	IMAGE_MANAGER->addImage("UI/INVENTORY/INVEN_BASE", L"resources/images/gameScene/ui/inventory/inventory.png");
	IMAGE_MANAGER->addImage("UI/INVENTORY/INVEN_BASE_SELECTED", L"resources/images/gameScene/ui/inventory/inventory_select.png");
	// *** STATUS
	IMAGE_MANAGER->addImage("UI/STAT/BASE", L"resources/images/gameScene/ui/status/Base.png");
	IMAGE_MANAGER->addImage("UI/STAT/POW", L"resources/images/gameScene/ui/status/Stat_00_Pow.png");
	IMAGE_MANAGER->addImage("UI/STAT/POW_SELECTED", L"resources/images/gameScene/ui/status/Stat_00_Pow_Selected.png");
	IMAGE_MANAGER->addImage("UI/STAT/DEF", L"resources/images/gameScene/ui/status/Stat_01_Def.png");
	IMAGE_MANAGER->addImage("UI/STAT/DEF_SELECTED", L"resources/images/gameScene/ui/status/Stat_01_Def_Selected.png");
	IMAGE_MANAGER->addImage("UI/STAT/TOUGH", L"resources/images/gameScene/ui/status/Stat_02_Tough.png");
	IMAGE_MANAGER->addImage("UI/STAT/TOUGH_SELECTED", L"resources/images/gameScene/ui/status/Stat_02_Tough_Selected.png");
	IMAGE_MANAGER->addImage("UI/STAT/BLOCK", L"resources/images/gameScene/ui/status/Stat_03_Block.png");
	IMAGE_MANAGER->addImage("UI/STAT/BLOCK_SELECTED", L"resources/images/gameScene/ui/status/Stat_03_Block_Selected.png");
	IMAGE_MANAGER->addImage("UI/STAT/CRITICAL", L"resources/images/gameScene/ui/status/Stat_04_Critical.png");
	IMAGE_MANAGER->addImage("UI/STAT/CRITICAL_SELECTED", L"resources/images/gameScene/ui/status/Stat_04_Critical_Selected.png");
	IMAGE_MANAGER->addImage("UI/STAT/CRITICAL_DAMAGE", L"resources/images/gameScene/ui/status/Stat_05_CriticalDamage.png");
	IMAGE_MANAGER->addImage("UI/STAT/CRITICAL_DAMAGE_SELECTED", L"resources/images/gameScene/ui/status/Stat_05_CriticalDamage_Selected.png");
	IMAGE_MANAGER->addImage("UI/STAT/EVADE", L"resources/images/gameScene/ui/status/Stat_06_Evade.png");
	IMAGE_MANAGER->addImage("UI/STAT/EVADE_SELECTED", L"resources/images/gameScene/ui/status/Stat_06_Evade_Selected.png");
	IMAGE_MANAGER->addImage("UI/STAT/MOVE_SPEED", L"resources/images/gameScene/ui/status/Stat_07_MoveSpeed.png");
	IMAGE_MANAGER->addImage("UI/STAT/MOVE_SPEED_SELECTED", L"resources/images/gameScene/ui/status/Stat_07_MoveSpeed_Selected.png");
	IMAGE_MANAGER->addImage("UI/STAT/ATTACK_SPEED", L"resources/images/gameScene/ui/status/Stat_08_AttackSpeed.png");
	IMAGE_MANAGER->addImage("UI/STAT/ATTACK_SPEED_SELECTED", L"resources/images/gameScene/ui/status/Stat_08_AttackSpeed_Selected.png");
	IMAGE_MANAGER->addImage("UI/STAT/RELOAD", L"resources/images/gameScene/ui/status/Stat_09_Reload.png");
	IMAGE_MANAGER->addImage("UI/STAT/RELOAD_SELECTED", L"resources/images/gameScene/ui/status/Stat_09_Reload_Selected.png");
	IMAGE_MANAGER->addImage("UI/STAT/DASH_DAMAGE", L"resources/images/gameScene/ui/status/Stat_10_DashDamage.png");
	IMAGE_MANAGER->addImage("UI/STAT/DASH_DAMAGE_SELECTED", L"resources/images/gameScene/ui/status/Stat_10_DashDamage_Selected.png");
	IMAGE_MANAGER->addImage("UI/STAT/TRUE_DAMAGE", L"resources/images/gameScene/ui/status/Stat_11_TrueDamage.png");
	IMAGE_MANAGER->addImage("UI/STAT/TRUE_DAMAGE_SELECTED", L"resources/images/gameScene/ui/status/Stat_11_TrueDamage_Selected.png");
	// *** BOUTIQUE(COSTUME)
	IMAGE_MANAGER->addImage("UI/COSTUME/BASE_UP", L"resources/images/gameScene/ui/boutique(costume)/CostumeBase_0.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/BASE_DOWN", L"resources/images/gameScene/ui/boutique(costume)/CostumeBase_1.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/BACK", L"resources/images/gameScene/ui/boutique(costume)/CostumeBack.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/EQUIPPED", L"resources/images/gameScene/ui/boutique(costume)/CostumeEquipped.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/LOCKED", L"resources/images/gameScene/ui/boutique(costume)/CostumeLocked.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/NONE", L"resources/images/gameScene/ui/boutique(costume)/CostumeNone.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/SELECTED", L"resources/images/gameScene/ui/boutique(costume)/CostumeOver.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/SHADOW", L"resources/images/gameScene/ui/boutique(costume)/CostumeShadow.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/UNLOCKED", L"resources/images/gameScene/ui/boutique(costume)/Costumeunlocked.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/0", L"resources/images/gameScene/ui/boutique(costume)/costumeSample/base_sample.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/1", L"resources/images/gameScene/ui/boutique(costume)/costumeSample/metal_sample.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/2", L"resources/images/gameScene/ui/boutique(costume)/costumeSample/alice_sample.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/3", L"resources/images/gameScene/ui/boutique(costume)/costumeSample/redLotus_sample.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/4", L"resources/images/gameScene/ui/boutique(costume)/costumeSample/pickax_sample.png");

	// ** VILLIGE
	IMAGE_MANAGER->addImage("Town_BGL", L"resources/images/Map/BGLayer_0.png");
	//IMAGE_MANAGER->addImage("Town_BGL", L"resources/images/Map/Town_BGL.png");
	IMAGE_MANAGER->addImage("Town_BG", L"resources/images/Map/TownBG_Day.png");
	IMAGE_MANAGER->addImage("Town_BG2", L"resources/images/Map/TownLayer_Day.png");
	IMAGE_MANAGER->addImage("Town_Floor", L"resources/images/Map/TownFloor.png");
	IMAGE_MANAGER->addImage("BlackSmith", L"resources/images/Villiage/BlackSmith.png");
	IMAGE_MANAGER->addImage("BlackSmithDisplay", L"resources/images/Villiage/BlackSmithDisplay.png");
	IMAGE_MANAGER->addImage("Boutique", L"resources/images/Villiage/Boutique.png");
	IMAGE_MANAGER->addImage("Shop", L"resources/images/Villiage/Shop.png");
	IMAGE_MANAGER->addImage("TrainingSchool", L"resources/images/Villiage/TrainingSchool.png");
	IMAGE_MANAGER->addImage("TrainingHouse", L"resources/images/Villiage/TrainingHouse.png");
	IMAGE_MANAGER->addImage("Temple", L"resources/images/Villiage/Temple.png");
	IMAGE_MANAGER->addImage("TempleFront", L"resources/images/Villiage/TempleFront.png");
	IMAGE_MANAGER->addImage("Gunsmith", L"resources/images/Villiage/Gunsmith.png");
	IMAGE_MANAGER->addImage("Target", L"resources/images/Villiage/Target.png");
	IMAGE_MANAGER->addImage("Tree0", L"resources/images/Map/Tree0.png");
	IMAGE_MANAGER->addImage("Tree1", L"resources/images/Map/Tree1.png");
	IMAGE_MANAGER->addImage("Well", L"resources/images/Map/Well.png");

	// ** DUNGEON
	IMAGE_MANAGER->addImage("InDungeonShop", L"resources/images/Villiage/InDungeonShop.png");
	IMAGE_MANAGER->addImage("Tavern", L"resources/images/Villiage/Tavern.png");
	

	// ** COSTUME
	// *** BASE
	IMAGE_MANAGER->addFrameImage("COSTUME/BASE/IDLE", L"resources/images/costumes/base/player_idle.png", 5, 1);
	IMAGE_MANAGER->addFrameImage("COSTUME/BASE/MOVE", L"resources/images/costumes/base/player_run.png", 8, 1);
	IMAGE_MANAGER->addImage("COSTUME/BASE/JUMP", L"resources/images/costumes/base/player_jump.png");
	IMAGE_MANAGER->addImage("COSTUME/BASE/DIE", L"resources/images/costumes/base/player_die.png");

	// *** METAL_PLATE
	IMAGE_MANAGER->addFrameImage("COSTUME/METAL_PLATE/IDLE", L"resources/images/costumes/metalPlate/player_idle.png", 5, 1);
	IMAGE_MANAGER->addFrameImage("COSTUME/METAL_PLATE/MOVE", L"resources/images/costumes/metalPlate/player_run.png", 8, 1);
	IMAGE_MANAGER->addImage("COSTUME/METAL_PLATE/JUMP", L"resources/images/costumes/metalPlate/player_jump.png");
	IMAGE_MANAGER->addImage("COSTUME/METAL_PLATE/DIE", L"resources/images/costumes/metalPlate/player_die.png");

	// *** PICKAX
	IMAGE_MANAGER->addFrameImage("COSTUME/PICKAX/IDLE", L"resources/images/costumes/pickax/player_idle.png", 5, 1);
	IMAGE_MANAGER->addFrameImage("COSTUME/PICKAX/MOVE", L"resources/images/costumes/pickax/player_run.png", 8, 1);
	IMAGE_MANAGER->addImage("COSTUME/PICKAX/JUMP", L"resources/images/costumes/pickax/player_jump.png");
	IMAGE_MANAGER->addImage("COSTUME/PICKAX/DIE", L"resources/images/costumes/pickax/player_die.png");

	// *** ALICE
	IMAGE_MANAGER->addFrameImage("COSTUME/ALICE/IDLE", L"resources/images/costumes/alice/player_idle.png", 5, 1);
	IMAGE_MANAGER->addFrameImage("COSTUME/ALICE/MOVE", L"resources/images/costumes/alice/player_run.png", 6, 1);
	IMAGE_MANAGER->addImage("COSTUME/ALICE/JUMP", L"resources/images/costumes/alice/player_jump.png");
	IMAGE_MANAGER->addImage("COSTUME/ALICE/DIE", L"resources/images/costumes/alice/player_die.png");

	// *** RED_LOTUS
	IMAGE_MANAGER->addFrameImage("COSTUME/RED_LOTUS/IDLE", L"resources/images/costumes/redLotus/player_idle.png", 5, 1);
	IMAGE_MANAGER->addFrameImage("COSTUME/RED_LOTUS/MOVE", L"resources/images/costumes/redLotus/player_run.png", 6, 1);
	IMAGE_MANAGER->addImage("COSTUME/RED_LOTUS/JUMP", L"resources/images/costumes/redLotus/player_jump.png");
	IMAGE_MANAGER->addImage("COSTUME/RED_LOTUS/DIE", L"resources/images/costumes/redLotus/player_die.png");

	// ** WEAPON
	// *** LongDistanceWeapon
	IMAGE_MANAGER->addImage("Lala'sMagicWand", L"resources/images/weapon/longDistanceWeapon/Lala'sMagicWand.png");
	IMAGE_MANAGER->addImage("MatchlockGun", L"resources/images/weapon/longDistanceWeapon/MatchlockGun.png");
	IMAGE_MANAGER->addImage("MetalBoomerang", L"resources/images/weapon/longDistanceWeapon/MetalBoomerang.png");
	IMAGE_MANAGER->addImage("OakBow", L"resources/images/weapon/longDistanceWeapon/OakBow.png");
	
	IMAGE_MANAGER->addFrameImage("Boomerang_Moving", L"resources/images/weapon/longDistanceWeapon/Boomerang_Moving.png", 2, 1);
	IMAGE_MANAGER->addFrameImage("OakBowAni", L"resources/images/weapon/longDistanceWeapon/OakBowAni.png", 6, 1);

	// **** L_test
	IMAGE_MANAGER->addFrameImage("test_OakBowAni", L"resources/images/weapon/longDistanceWeapon/test_OakBowAni.png", 6, 1);

	// **** L_WeaponBullet
	IMAGE_MANAGER->addImage("Arrow00", L"resources/images/weapon/longDistanceWeapon/Arrow00.png");
	IMAGE_MANAGER->addFrameImage("GunBullet", L"resources/images/weapon/longDistanceWeapon/Bullet.png", 4, 1);
	IMAGE_MANAGER->addFrameImage("lalaStickBullet", L"resources/images/weapon/longDistanceWeapon/lalaStickBullet.png", 4, 1);

	// **** L_WeaponEffect
	IMAGE_MANAGER->addFrameImage("ArrowHitEffect", L"resources/images/weapon/longDistanceWeapon/effect/ArrowHitEffect.png", 6, 1);
	IMAGE_MANAGER->addFrameImage("BoomerangEffect", L"resources/images/weapon/longDistanceWeapon/effect/BoomerangEffect.png", 12, 1);
	IMAGE_MANAGER->addFrameImage("ChargeEffect", L"resources/images/weapon/longDistanceWeapon/effect/ChargeEffect.png", 8, 1);
	IMAGE_MANAGER->addFrameImage("HecateSmokeFX02", L"resources/images/weapon/longDistanceWeapon/effect/HecateSmokeFX02.png", 10, 1);
	IMAGE_MANAGER->addFrameImage("ShootEffect", L"resources/images/weapon/longDistanceWeapon/effect/ShootEffect.png", 3, 1);
	IMAGE_MANAGER->addFrameImage("ShootEffect01", L"resources/images/weapon/longDistanceWeapon/effect/ShootEffect01.png", 6, 1);
	IMAGE_MANAGER->addFrameImage("ShootEffect02", L"resources/images/weapon/longDistanceWeapon/effect/ShootEffect02.png", 6, 1);

	EFFECT_MANAGER->addEffect("L_Effect_ArrowHit", "ArrowHitEffect", 30, 10);
	EFFECT_MANAGER->addEffect("L_Effect_Boomerang", "BoomerangEffect", 30, 10);
	EFFECT_MANAGER->addEffect("L_Effect_Charge", "ChargeEffect", 30, 10);
	EFFECT_MANAGER->addEffect("L_Effect_HecateSmoke", "HecateSmokeFX02", 10, 10);
	EFFECT_MANAGER->addEffect("L_Effect_Shoot", "ShootEffect", 30, 10);
	EFFECT_MANAGER->addEffect("L_Effect_Shoot01", "ShootEffect01", 30, 10);
	EFFECT_MANAGER->addEffect("L_Effect_Shoot02", "ShootEffect02", 30, 10);

	// **** L_WeaponReload
	IMAGE_MANAGER->addImage("ReloadBar", L"resources/images/weapon/longDistanceWeapon/ReloadBase.png");
	IMAGE_MANAGER->addImage("ReloadHandle", L"resources/images/weapon/longDistanceWeapon/ReloadBar.png");
	IMAGE_MANAGER->addFrameImage("ReloadFinish", L"resources/images/weapon/longDistanceWeapon/effect/Reload.png", 4, 1);

	//***MeleeWeapon
	IMAGE_MANAGER->addImage("ShortSpear", L"resources/images/MeleeWeapon/ShortSpear.png");
	IMAGE_MANAGER->addImage("ShortSword", L"resources/images/MeleeWeapon/ShortSword.png");
	IMAGE_MANAGER->addFrameImage("CosmosSword", L"resources/images/MeleeWeapon/CosmosSword.png",12,1);	   //우주검 
	IMAGE_MANAGER->addImage("CosmosSword00", L"resources/images/MeleeWeapon/CosmosSword00.png"); // 우주검 아이콘
	IMAGE_MANAGER->addImage("KeresScythe", L"resources/images/MeleeWeapon/KeresScythe.png"); // 사이드
	IMAGE_MANAGER->addImage("MartialArtOfTiger", L"resources/images/MeleeWeapon/MartialArtOfTiger.png"); // 타이거펀치 아이콘
	IMAGE_MANAGER->addImage("PickaxeRed", L"resources/images/MeleeWeapon/PickaxeRed.png"); // 붉은 곡괭이
	


	//***MeleeWeaponEffect
	IMAGE_MANAGER->addFrameImage("SwingFX", L"resources/images/MeleeWeapon/SwingFX.png", 3, 1);
	IMAGE_MANAGER->addFrameImage("StabFX", L"resources/images/MeleeWeapon/StabFX.png", 4, 1);
	IMAGE_MANAGER->addFrameImage("CosmosSwordFx", L"resources/images/MeleeWeapon/CosmosSwordFx.png",8, 1); 
	IMAGE_MANAGER->addFrameImage("KeresScytheSwingFX", L"resources/images/MeleeWeapon/KeresScytheSwingFX.png",8, 1);
	IMAGE_MANAGER->addFrameImage("TigerPunch", L"resources/images/MeleeWeapon/TigerPunch.png",10,1);
	IMAGE_MANAGER->addFrameImage("RedPickaxeSwing", L"resources/images/MeleeWeapon/RedPickaxeSwing.png",12,1);

	EFFECT_MANAGER->addEffect("EFFECT_COSMOSSWING", "CosmosSwordFx", 30, 10); // 우주검 이펙트
	EFFECT_MANAGER->addEffect("EFFECT_SCYTHESWING", "KeresScytheSwingFX", 30, 10); // 낫 이펙트
	EFFECT_MANAGER->addEffect("EFFECT_SWING", "SwingFX", 15, 10); // 일반 휘두르기 이펙트
	EFFECT_MANAGER->addEffect("EFFECT_STAB", "StabFX", 15, 10);	  // 일반 찌르기 이펙트
	EFFECT_MANAGER->addEffect("EFFECT_TIGERPUNCH", "TigerPunch", 30, 10);	  // 타이거펀치 이팩트
	EFFECT_MANAGER->addEffect("EFFECT_REDPICKAXESWING", "RedPickaxeSwing", 30, 10);	  // 붉은곡괭이 이팩트





	// *Accessories
	IMAGE_MANAGER->addImage("SpikeBall", L"resources/images/Accessories/SpikeBall.png");                       // 뾰족공	
	IMAGE_MANAGER->addImage("BloodStoneRing", L"resources/images/Accessories/BloodStoneRing.png");             // 혈석반지	
	IMAGE_MANAGER->addImage("Voluspa", L"resources/images/Accessories/Voluspa.png");                           // 볼루스파
	IMAGE_MANAGER->addImage("Voluspa0", L"resources/images/Accessories/Voluspa0.png");                         // 볼루스파창
	IMAGE_MANAGER->addImage("BombPouch", L"resources/images/Accessories/BombPouch.png");                       // 대쉬폭탄	
	IMAGE_MANAGER->addFrameImage("BombPouch0", L"resources/images/Accessories/BombPouch1.png", 5, 1);          // 대쉬폭탄 프레임이미지
	IMAGE_MANAGER->addFrameImage("BombPouch1", L"resources/images/Accessories/BombPouch2.png", 7, 1);          // 대쉬폭탄 터지는 프레임이미지
	IMAGE_MANAGER->addImage("CarpCoinPurse", L"resources/images/Accessories/CarpCoinPurse.png");               // 잉어모양 동전지갑
	IMAGE_MANAGER->addImage("DaisyRing", L"resources/images/Accessories/DaisyRing.png");                       // 데이지링
	IMAGE_MANAGER->addImage("DemonBoots", L"resources/images/Accessories/DemonBoots.png");                     // 악마부츠
	IMAGE_MANAGER->addFrameImage("DemonBoots0", L"resources/images/Accessories/DemonBoots0.png", 6, 1);        // 악마부츠 프레임이미지
	IMAGE_MANAGER->addImage("MultiBullet", L"resources/images/Accessories/MultiBullet.png");                   // 3갈래총탄
	IMAGE_MANAGER->addImage("GoldenCandy", L"resources/images/Accessories/GoldenCandy.png");                   // 골드캔디
	IMAGE_MANAGER->addImage("babyGreenBat", L"resources/images/Accessories/babyGreenBat.png");                 // 아기 그린박쥐
	IMAGE_MANAGER->addImage("GreenBat", L"resources/images/Accessories/GreenBat.png");                         // 그린박쥐
	IMAGE_MANAGER->addImage("GreenMomBat", L"resources/images/Accessories/GreenMomBat.png");                   // 엄마그린박쥐
	IMAGE_MANAGER->addImage("GreenDadBat", L"resources/images/Accessories/GreenDadBat.png");                   // 아빠그린박쥐
	IMAGE_MANAGER->addFrameImage("BabyBatBulletAt", L"resources/images/Accessories/BabyBatBullet0.png", 5, 1); // 아기 그린박쥐 공격 프레임이미지
	IMAGE_MANAGER->addFrameImage("BabyBatBulletFx", L"resources/images/Accessories/BabyBatBulletFX.png", 7, 1);// 아기 그린박쥐 공격 충돌 프레임이미지
	IMAGE_MANAGER->addFrameImage("babyGreenBatF", L"resources/images/Accessories/GreenBat0.png", 6, 1);        // 아기 그린박쥐 프레임이미지
	IMAGE_MANAGER->addFrameImage("GreenBatF", L"resources/images/Accessories/GreenBat3.png", 6, 1);            // 그린박쥐 프레임이미지
	IMAGE_MANAGER->addFrameImage("GreenDadBatF", L"resources/images/Accessories/GreenDadBat1.png", 7, 1);      // 아빠 그린박쥐 프레임이미지
	IMAGE_MANAGER->addFrameImage("GreenMomBatF", L"resources/images/Accessories/GreenMomBat2.png", 7, 1);      // 엄마 그린박쥐 프레임이미지
	IMAGE_MANAGER->addImage("HeartOfCosmos", L"resources/images/Accessories/HeartOfCosmos.png");               // 우주심장
	IMAGE_MANAGER->addFrameImage("HeartOfCosmos0", L"resources/images/Accessories/HeartOfCosmos0.png", 20, 1); // 우주심장 공격 프레임
	IMAGE_MANAGER->addImage("IceBall", L"resources/images/Accessories/IceBall.png");                           // 얼음공
	IMAGE_MANAGER->addFrameImage("IceBall0", L"resources/images/Accessories/IceBall0.png", 7, 1);              // 얼음공 세트 완성 프레임이미지
	IMAGE_MANAGER->addImage("Jarngreipr", L"resources/images/Accessories/Jarngreipr.png");                     // 야른그레이프르
	IMAGE_MANAGER->addImage("Magnet", L"resources/images/Accessories/Magnet.png");                             // 자석
	IMAGE_MANAGER->addImage("MagnifyingGlass", L"resources/images/Accessories/MagnifyingGlass.png");           // 돋보기
	IMAGE_MANAGER->addImage("MiniEarth", L"resources/images/Accessories/MiniEarth.png");                       // 미니행성
	IMAGE_MANAGER->addFrameImage("MiniEarth0", L"resources/images/Accessories/MiniEarth0.png", 9, 1);          // 미니행성 프레임 이미지
	IMAGE_MANAGER->addImage("SecretMap", L"resources/images/Accessories/SecretMap.png");                       // 비밀맵
	IMAGE_MANAGER->addImage("SilverBullet", L"resources/images/Accessories/SilverBullet.png");                 // 은탄	
	IMAGE_MANAGER->addImage("SpikeBoots", L"resources/images/Accessories/SpikeBoots.png");                     // 가시신발
	IMAGE_MANAGER->addImage("SpringShoes", L"resources/images/Accessories/SpringShoes.png");                   // 점프신발
	IMAGE_MANAGER->addImage("MetalBoots", L"resources/images/Accessories/MetalBoots.png");                     // 강철신발
	IMAGE_MANAGER->addImage("TAANA", L"resources/images/Accessories/TAANA.png");                               // 타나
	IMAGE_MANAGER->addFrameImage("TAANA0", L"resources/images/Accessories/TAANA0.png", 7, 1);                  // 타나 프레임 이미지
	IMAGE_MANAGER->addImage("Watcher", L"resources/images/Accessories/Watcher.png");                           // 주시자
	IMAGE_MANAGER->addFrameImage("Watcher0", L"resources/images/Accessories/Watcher0.png", 7, 1);              // 주시자 프레임 이미지
	IMAGE_MANAGER->addFrameImage("Watcher1", L"resources/images/Accessories/Watcher1.png", 13, 1);             // 주시자 세트 완성 프레임 이미지
	IMAGE_MANAGER->addImage("Wing", L"resources/images/Accessories/Wing.png");                                 // 날개
	IMAGE_MANAGER->addImage("Wing0", L"resources/images/Accessories/Wing0.png");                               // 날개 장착 이미지
	IMAGE_MANAGER->addImage("Wingboots", L"resources/images/Accessories/Wingboots.png");                       // 윙부츠

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
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Idle_Shot"	, L"resources/images/Enemy/Skel/Big_Ice/idle_shot.png"	,  8, 1);	// 해골 얼음기사 기본 피격
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Move"		, L"resources/images/Enemy/Skel/Big_Ice/move.png"		,  6, 1);	// 해골 얼음기사 이동
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Move_Shot"	, L"resources/images/Enemy/Skel/Big_Ice/move_shot.png"	,  6, 1);	// 해골 얼음기사 이동 피격
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Attack"		, L"resources/images/Enemy/Skel/Big_Ice/attack.png"		, 13, 1);	// 해골 얼음기사 공격
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Attack_Shot"	, L"resources/images/Enemy/Skel/Big_Ice/attack_shot.png", 13, 1);	// 해골 얼음기사 공격 피격
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Skill"		, L"resources/images/Enemy/Skel/Big_Ice/Skill.png"		, 12, 1);	// 해골 얼음기사 스킬
	IMAGE_MANAGER->addFrameImage("Skel/Big_Ice/Skill_Shot"	, L"resources/images/Enemy/Skel/Big_Ice/Skill_Shot.png"	, 12, 1);	// 해골 얼음기사 스킬 피격

	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Idle"			, L"resources/images/Enemy/Skel/Big_Normal/idle.png"		, 5, 1);	// 해골 기사 기본
	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Idle_Shot"	, L"resources/images/Enemy/Skel/Big_Normal/idle_Shot.png"	, 5, 1);	// 해골 기사 기본 피격
	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Move"			, L"resources/images/Enemy/Skel/Big_Normal/Move.png"		, 6, 1);	// 해골 기사 이동
	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Move_Shot"	, L"resources/images/Enemy/Skel/Big_Normal/Move_Shot.png"	, 6, 1);	// 해골 기사 이동 피격
	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Attack"		, L"resources/images/Enemy/Skel/Big_Normal/attack.png"		, 12, 1);	// 해골 기사 공격
	IMAGE_MANAGER->addFrameImage("Skel/Big_Normal/Attack_Shot"	, L"resources/images/Enemy/Skel/Big_Normal/attack_shot.png"	, 12, 1);	// 해골 기사 공격 피격

	IMAGE_MANAGER->addFrameImage("Skel/Dog/Idle"		, L"resources/images/Enemy/Skel/Dog/idle.png"		, 5, 1);	// 해골 강아지 기본
	IMAGE_MANAGER->addFrameImage("Skel/Dog/Idle_Shot"	, L"resources/images/Enemy/Skel/Dog/idle_shot.png"	, 5, 1);	// 해골 강아지 기본 피격
	IMAGE_MANAGER->addFrameImage("Skel/Dog/Move"		, L"resources/images/Enemy/Skel/Dog/Move.png"		, 7, 1);	// 해골 강아지 이동
	IMAGE_MANAGER->addFrameImage("Skel/Dog/Move_Shot"	, L"resources/images/Enemy/Skel/Dog/Move_shot.png"	, 7, 1);	// 해골 강아지 이동 피격

	IMAGE_MANAGER->addFrameImage("Skel/Magician_Ice/Idle"		, L"resources/images/Enemy/Skel/Magician_Ice/idle.png"			,  6, 1);	// 해골 얼음마법사 기본
	IMAGE_MANAGER->addFrameImage("Skel/Magician_Ice/Idle_Shot"	, L"resources/images/Enemy/Skel/Magician_Ice/idle_shot.png"		,  6, 1);	// 해골 얼음마법사 기본 피격
	IMAGE_MANAGER->addFrameImage("Skel/Magician_Ice/Attack"		, L"resources/images/Enemy/Skel/Magician_Ice/attack.png"		, 12, 1);	// 해골 얼음마법사 공격
	IMAGE_MANAGER->addFrameImage("Skel/Magician_Ice/Attack_Shot", L"resources/images/Enemy/Skel/Magician_Ice/attack_shot.png"	, 12, 1);	// 해골 얼음마법사 공격 피격
	IMAGE_MANAGER->addFrameImage("Skel/Magician_Ice/Effect"		, L"resources/images/Enemy/Skel/Magician_Ice/ice_crystal.png"	,  7, 3);	// 해골 얼음마법사 공격 이펙트

	IMAGE_MANAGER->addImage("Skel/Small/Idle"			, L"resources/images/Enemy/Skel/Small/idle.png"				);	// 작은해골 기본
	IMAGE_MANAGER->addImage("Skel/Small/Idle_Shot"		, L"resources/images/Enemy/Skel/Small/idle_shot.png"		);	// 작은해골 기본 피격
	IMAGE_MANAGER->addFrameImage("Skel/Small/Move"		, L"resources/images/Enemy/Skel/Small/move.png"		, 6, 1	);	// 작은해골 이동
	IMAGE_MANAGER->addFrameImage("Skel/Small/Move_Shot"	, L"resources/images/Enemy/Skel/Small/move_shot.png", 6, 1	);	// 작은해골 이동 피격

	IMAGE_MANAGER->addImage("Skel/Small/Bow_Idle"		, L"resources/images/Enemy/Skel/Small/Bow/idle.png"			);	// 작은해골 활 기본
	IMAGE_MANAGER->addFrameImage("Skel/Small/Bow_Attack", L"resources/images/Enemy/Skel/Small/Bow/attack.png", 6, 1	);	// 작은해골 활 공격

	// * 미노타우르스
	IMAGE_MANAGER->addFrameImage("Minotaurs/Idle"		, L"resources/images/Enemy/Minotaurs/idle.png"			, 6, 1);	// 미노타우르스 기본
	IMAGE_MANAGER->addFrameImage("Minotaurs/Idle_Shot"	, L"resources/images/Enemy/Minotaurs/idle_shot.png"		, 6, 1);	// 미노타우르스 기본 피격
	IMAGE_MANAGER->addFrameImage("Minotaurs/Attack"		, L"resources/images/Enemy/Minotaurs/attack.png"		, 7, 1);	// 미노타우르스 공격
	IMAGE_MANAGER->addFrameImage("Minotaurs/Attack_Shot", L"resources/images/Enemy/Minotaurs/attack_shot.png"	, 7, 1);	// 미노타우르스 공격 피격
	IMAGE_MANAGER->addFrameImage("Minotaurs/Skill"		, L"resources/images/Enemy/Minotaurs/skill.png"			, 8, 1);	// 미노타우르스 돌진
	IMAGE_MANAGER->addFrameImage("Minotaurs/Skill_Shot"	, L"resources/images/Enemy/Minotaurs/skill_shot.png"	, 8, 1);	// 미노타우르스 돌진 피격
	IMAGE_MANAGER->addFrameImage("Minotaurs/Effect"		, L"resources/images/Enemy/Minotaurs/effect.png"		, 1, 8);	// 미노타우르스 돌진 이펙트

	EFFECT_MANAGER->addEffect("Minotaurs/Effect", "Minotaurs/Effect", 15, 30);

	// * 물소
	IMAGE_MANAGER->addFrameImage("Ovibos/Idle"			, L"resources/images/Enemy/Ovibos/idle.png"			, 9, 1);	// 물소 기본
	IMAGE_MANAGER->addFrameImage("Ovibos/Idle_Shot"		, L"resources/images/Enemy/Ovibos/idle_shot.png"	, 9, 1);	// 물소 기본 피격
	IMAGE_MANAGER->addFrameImage("Ovibos/Attack"		, L"resources/images/Enemy/Ovibos/attack.png"		, 6, 1);	// 물소 공격 
	IMAGE_MANAGER->addFrameImage("Ovibos/Attack_Shot"	, L"resources/images/Enemy/Ovibos/attack_shot.png"	, 6, 1);	// 물소 공격 피격

	// ** BOSS
	// * 니플헤임
	IMAGE_MANAGER->addFrameImage("Niflheim/Idle"	, L"resources/images/boss/Niflheim/idle.png"	,  6, 1);	// 니플헤임 기본
	IMAGE_MANAGER->addFrameImage("Niflheim/Attack_1", L"resources/images/boss/Niflheim/attack.png"	, 11, 1);	// 니플헤임 공격 1
	IMAGE_MANAGER->addFrameImage("Niflheim/Attack_2", L"resources/images/boss/Niflheim/attack_1.png", 11, 1);	// 니플헤임 공격 2
	IMAGE_MANAGER->addFrameImage("Niflheim/Spawn"	, L"resources/images/boss/Niflheim/enter.png"	, 16, 1);	// 니플헤임 등장
	IMAGE_MANAGER->addFrameImage("Niflheim/Die"		, L"resources/images/boss/Niflheim/die.png"		, 30, 1);	// 니플헤임 죽음
	IMAGE_MANAGER->addFrameImage("Niflheim/Pillar"	, L"resources/images/boss/Niflheim/pillar.png"	, 20, 1);	// 니플헤임 얼음기둥
	IMAGE_MANAGER->addFrameImage("Niflheim/Icicle"	, L"resources/images/boss/Niflheim/icicle.png"	, 10, 1);	// 니플헤임 고드름
	IMAGE_MANAGER->addFrameImage("Niflheim/Spear"	, L"resources/images/boss/Niflheim/spear.png"	, 13, 1);	// 니플헤임 얼음창

	// * 에너미 불릿
	IMAGE_MANAGER->addFrameImage("Banshee/Bullet"	, L"resources/images/Enemy/Bullet/note.png"		, 4, 1);	// 수녀 총알
	IMAGE_MANAGER->addFrameImage("Banshee/Bullet_FX", L"resources/images/Enemy/Bullet/note_FX.png"	, 6, 1);	// 수녀 총알 삭제

	EFFECT_MANAGER->addEffect("Banshee/Bullet_FX", "Banshee/Bullet_FX", 15, 50);	// 이펙트 등록

	IMAGE_MANAGER->addImage("IceBullet"			, L"resources/images/Enemy/Bullet/IceBullet.png"		 );	// 얼음 총알
	IMAGE_MANAGER->addFrameImage("IceBullet_FX"	, L"resources/images/Enemy/Bullet/IceBullet_FX.png", 3, 1);	// 얼음 총알 삭제

	EFFECT_MANAGER->addEffect("IceBullet_FX", "IceBullet_FX", 15, 50);
	
	IMAGE_MANAGER->addFrameImage("GiantBullet"		, L"resources/images/Enemy/Bullet/giantBullet.png"		, 5, 1);	// 박쥐 총알 큰 것
	IMAGE_MANAGER->addFrameImage("GiantBullet_FX"	, L"resources/images/Enemy/Bullet/giantBullet_FX.png"	, 7, 1);	// 박쥐 총알 큰 것 삭제 이펙트
	IMAGE_MANAGER->addFrameImage("SmallBullet"		, L"resources/images/Enemy/Bullet/smallBullet.png"		, 5, 1);	// 박쥐 총알 작은 것
	IMAGE_MANAGER->addFrameImage("SmallBullet_FX"	, L"resources/images/Enemy/Bullet/smallBullet_FX.png"	, 7, 1);	// 박쥐 총알 작은 것 삭제 이펙트

	EFFECT_MANAGER->addEffect("GiantBullet_FX", "GiantBullet_FX", 15, 50);
	EFFECT_MANAGER->addEffect("SmallBullet_FX", "SmallBullet_FX", 15, 50);

	CONFIG_MANAGER->init();
	DATA_MANAGER->init();
	TIME_MANAGER->update();

	// 모든 씬 SCENE_MANAGER에 
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->addScene("GAME", new GameScene);
	SCENE_MANAGER->addScene("MapTool", new MapToolScene);
	
	SCENE_MANAGER->changeScene("GAME");	

	
	return S_OK;
}

//메모리 해제
void playGround::release()
{
	GameNode::release();
}

//연산ds
void playGround::update()
{
	GameNode::update();

	SCENE_MANAGER->update();
	DEBUG_MANAGER->update();
	KEY_MANAGER->update();
}

//그리기 전용
void playGround::render()
{	
	D2D_RENDERER->beginRender(D2D1::ColorF::Gray);
	{
		SCENE_MANAGER->render();
	}
	D2D_RENDERER->endRender();
}
