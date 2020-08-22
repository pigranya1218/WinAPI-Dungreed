#include "stdafx.h"
#include "PlayGround.h"

#include "MainScene.h"
#include "GameScene.h"
#include "MapToolScene.h"
#include "MazeScene.h"
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
	// ** PLAYER
	IMAGE_MANAGER->addFrameImage("PLAYER/DASH_DUST", L"resources/images/Effect/Dash/DustEffect.png", 6, 1);
	EFFECT_MANAGER->addEffect("PLAYER/DASH_DUST_EFFECT", "PLAYER/DASH_DUST", 30, 10);
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

	IMAGE_MANAGER->addImage("UI/WARNING_LEFT", L"resources/images/gameScene/ui/RedWarningOnHit_0.png");
	IMAGE_MANAGER->addImage("UI/WARNING_RIGHT", L"resources/images/gameScene/ui/RedWarningOnHit_1.png");
	// *** DIALOGUE
	IMAGE_MANAGER->addImage("UI/DIALOGUE/BASE", L"resources/images/gameScene/ui/dialogue/dialogue_body.png");
	IMAGE_MANAGER->addImage("UI/DIALOGUE/SELECT", L"resources/images/gameScene/ui/dialogue/dialogue_select.png");
	IMAGE_MANAGER->addImage("UI/DIALOGUE/SELECT_SELECTED", L"resources/images/gameScene/ui/dialogue/dialogue_select_on.png");
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
	IMAGE_MANAGER->addImage("UI/INVENTORY/INVEN_INFO", L"resources/images/gameScene/ui/inventory/info.png");
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
	IMAGE_MANAGER->addImage("UI/COSTUME/BASE", L"resources/images/gameScene/ui/boutique(costume)/costumeSample/base_sample.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/METAL_PLATE", L"resources/images/gameScene/ui/boutique(costume)/costumeSample/metal_sample.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/ALICE", L"resources/images/gameScene/ui/boutique(costume)/costumeSample/alice_sample.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/RED_LOTUS", L"resources/images/gameScene/ui/boutique(costume)/costumeSample/redLotus_sample.png");
	IMAGE_MANAGER->addImage("UI/COSTUME/PICKAX", L"resources/images/gameScene/ui/boutique(costume)/costumeSample/pickax_sample.png");
	// *** RESTAURANT(FOODS SHOP)
	IMAGE_MANAGER->addImage("UI/RESTAURANT/BASE_LABEL", L"resources/images/gameScene/ui/restaurant/Label.png");
	IMAGE_MANAGER->addImage("UI/RESTAURANT/BASE", L"resources/images/gameScene/ui/restaurant/Base_0.png");
	IMAGE_MANAGER->addImage("UI/RESTAURANT/BASE2", L"resources/images/gameScene/ui/restaurant/Base_3.png");
	IMAGE_MANAGER->addImage("UI/RESTAURANT/LIFE_BASE_BACK", L"resources/images/gameScene/ui/restaurant/RestaurantLifeBaseBack.png");
	IMAGE_MANAGER->addImage("UI/RESTAURANT/LIFE_BASE", L"resources/images/gameScene/ui/restaurant/RestaurantLifeBase.png");
	IMAGE_MANAGER->addImage("UI/RESTAURANT/MENU_GOLD", L"resources/images/gameScene/ui/restaurant/RestaurantMenu.png");
	IMAGE_MANAGER->addImage("UI/RESTAURANT/MENU_GOLD_SELECTED", L"resources/images/gameScene/ui/restaurant/RestaurantMenu_Selected.png");
	IMAGE_MANAGER->addImage("UI/RESTAURANT/MENU", L"resources/images/gameScene/ui/restaurant/RestaurantMenu_Withoutmoney_RESIZE.png");
	IMAGE_MANAGER->addImage("UI/RESTAURANT/MENU_SELECTED", L"resources/images/gameScene/ui/restaurant/RestaurantMenu_Withoutmoney_Selected_RESIZE.png");
	IMAGE_MANAGER->addImage("UI/RESTAURANT/THANKYOU_KR", L"resources/images/gameScene/ui/restaurant/ThankYouKorean.png");
	IMAGE_MANAGER->addImage("UI/RESTAURANT/GOLD_ICON", L"resources/images/gameScene/ui/restaurant/GoldCoin0.png");
	IMAGE_MANAGER->addImage("UI/RESTAURANT/SATIETY_ICON", L"resources/images/gameScene/ui/restaurant/SatietyRate.png");
	IMAGE_MANAGER->addImage("UI/RESTAURANT/HEAL_ICON", L"resources/images/gameScene/ui/restaurant/HealRate.png");
	IMAGE_MANAGER->addFrameImage("UI/RESTAURANT/TABLE", L"resources/images/gameScene/ui/restaurant/RestaurantTable3Frame.png", 3, 1);
	IMAGE_MANAGER->addImage("UI/RESTAURANT/GAUGE_BASE", L"resources/images/gameScene/ui/restaurant/AltarGaugeBase.png");
	// **** FOODS
	// ***** NORMAL
	IMAGE_MANAGER->addImage("FOOD/BREAD", L"resources/images/gameScene/ui/restaurant/foods/01_Bread.png");
	IMAGE_MANAGER->addImage("FOOD/EGG_FRIED", L"resources/images/gameScene/ui/restaurant/foods/02_FriedEgg.png");
	IMAGE_MANAGER->addImage("FOOD/GRILLED_MUSHROOM", L"resources/images/gameScene/ui/restaurant/foods/03_GrilledMushroom.png");
	IMAGE_MANAGER->addImage("FOOD/TOMATO_SOUP", L"resources/images/gameScene/ui/restaurant/foods/04_TamatoSoup.png");
	// ***** RARE
	IMAGE_MANAGER->addImage("FOOD/GRIFFIN_EGG_OMELETTE", L"resources/images/gameScene/ui/restaurant/foods/13_GriffonEggOmelette.png");
	IMAGE_MANAGER->addImage("FOOD/RASPBERRY_COOKIE", L"resources/images/gameScene/ui/restaurant/foods/12_RaspberryCookie.png");
	IMAGE_MANAGER->addImage("FOOD/SPARKLING_WATER", L"resources/images/gameScene/ui/restaurant/foods/26_SparklingWater.png");
	IMAGE_MANAGER->addImage("FOOD/STRAWBERRY_PIE", L"resources/images/gameScene/ui/restaurant/foods/18_StrawberryPie.png");
	// *** ABILITY
	IMAGE_MANAGER->addImage("UI/ABILITY/LABEL", L"resources/images/gameScene/ui/ability/AbilityTItle.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/BASE_WRATH", L"resources/images/gameScene/ui/ability/AbilityBackground_Wrath.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/BASE_SWIFTNESS", L"resources/images/gameScene/ui/ability/AbilityBackground_Swiftness.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/BASE_PATIENCE", L"resources/images/gameScene/ui/ability/AbilityBackground_Patience.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/BASE_ARCANE", L"resources/images/gameScene/ui/ability/AbilityBackground_Arcane.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/BASE_GREED", L"resources/images/gameScene/ui/ability/AbilityBackground_Greed.png");

	IMAGE_MANAGER->addImage("UI/ABILITY/BUTTON_WRATH", L"resources/images/gameScene/ui/ability/AbilityBackgroundButton_Wrath.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/BUTTON_SWIFTNESS", L"resources/images/gameScene/ui/ability/AbilityBackgroundButton_Swiftness.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/BUTTON_PATIENCE", L"resources/images/gameScene/ui/ability/AbilityBackgroundButton_Patience.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/BUTTON_ARCANE", L"resources/images/gameScene/ui/ability/AbilityBackgroundButton_Arcane.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/BUTTON_GREED", L"resources/images/gameScene/ui/ability/AbilityBackgroundButton_Greed.png");

	IMAGE_MANAGER->addImage("UI/ABILITY/BUTTON_WRATH_DISABLE", L"resources/images/gameScene/ui/ability/AbilityBackgroundButtonDisable_Wrath.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/BUTTON_SWIFTNESS_DISABLE", L"resources/images/gameScene/ui/ability/AbilityBackgroundButtonDisable_Swiftness.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/BUTTON_PATIENCE_DISABLE", L"resources/images/gameScene/ui/ability/AbilityBackgroundButtonDisable_Patience.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/BUTTON_ARCANE_DISABLE", L"resources/images/gameScene/ui/ability/AbilityBackgroundButtonDisable_Arcane.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/BUTTON_GREED_DISABLE", L"resources/images/gameScene/ui/ability/AbilityBackgroundButtonDisable_Greed.png");
	// **** ICON
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_WRATH1_ABLE", L"resources/images/gameScene/ui/ability/icon/Wrath1_able.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_WRATH1_ABLE_SELECTED", L"resources/images/gameScene/ui/ability/icon/Wrath1_able_selected.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_WRATH1_DISABLE", L"resources/images/gameScene/ui/ability/icon/Wrath1_disable.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_WRATH2_ABLE", L"resources/images/gameScene/ui/ability/icon/Wrath2_able.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_WRATH2_ABLE_SELECTED", L"resources/images/gameScene/ui/ability/icon/Wrath2_able_selected.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_WRATH2_DISABLE", L"resources/images/gameScene/ui/ability/icon/Wrath2_disable.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_WRATH3_ABLE", L"resources/images/gameScene/ui/ability/icon/Wrath3_able.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_WRATH3_ABLE_SELECTED", L"resources/images/gameScene/ui/ability/icon/Wrath3_able_selected.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_WRATH3_DISABLE", L"resources/images/gameScene/ui/ability/icon/Wrath3_disable.png");

	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_SWIFTNESS1_ABLE", L"resources/images/gameScene/ui/ability/icon/Swiftness1_able.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_SWIFTNESS1_ABLE_SELECTED", L"resources/images/gameScene/ui/ability/icon/Swiftness1_able_selected.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_SWIFTNESS1_DISABLE", L"resources/images/gameScene/ui/ability/icon/Swiftness1_disable.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_SWIFTNESS2_ABLE", L"resources/images/gameScene/ui/ability/icon/Swiftness2_able.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_SWIFTNESS2_ABLE_SELECTED", L"resources/images/gameScene/ui/ability/icon/Swiftness2_able_selected.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_SWIFTNESS2_DISABLE", L"resources/images/gameScene/ui/ability/icon/Swiftness2_disable.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_SWIFTNESS3_ABLE", L"resources/images/gameScene/ui/ability/icon/Swiftness3_able.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_SWIFTNESS3_ABLE_SELECTED", L"resources/images/gameScene/ui/ability/icon/Swiftness3_able_selected.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_SWIFTNESS3_DISABLE", L"resources/images/gameScene/ui/ability/icon/Swiftness3_disable.png");

	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_PATIENCE1_ABLE", L"resources/images/gameScene/ui/ability/icon/Patience1_able.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_PATIENCE1_ABLE_SELECTED", L"resources/images/gameScene/ui/ability/icon/Patience1_able_selected.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_PATIENCE1_DISABLE", L"resources/images/gameScene/ui/ability/icon/Patience1_disable.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_PATIENCE2_ABLE", L"resources/images/gameScene/ui/ability/icon/Patience2_able.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_PATIENCE2_ABLE_SELECTED", L"resources/images/gameScene/ui/ability/icon/Patience2_able_selected.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_PATIENCE2_DISABLE", L"resources/images/gameScene/ui/ability/icon/Patience2_disable.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_PATIENCE3_ABLE", L"resources/images/gameScene/ui/ability/icon/Patience3_able.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_PATIENCE3_ABLE_SELECTED", L"resources/images/gameScene/ui/ability/icon/Patience3_able_selected.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_PATIENCE3_DISABLE", L"resources/images/gameScene/ui/ability/icon/Patience3_disable.png");

	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_ARCANE1_ABLE", L"resources/images/gameScene/ui/ability/icon/Arcane1_able.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_ARCANE1_ABLE_SELECTED", L"resources/images/gameScene/ui/ability/icon/Arcane1_able_selected.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_ARCANE1_DISABLE", L"resources/images/gameScene/ui/ability/icon/Arcane1_disable.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_ARCANE2_ABLE", L"resources/images/gameScene/ui/ability/icon/Arcane2_able.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_ARCANE2_ABLE_SELECTED", L"resources/images/gameScene/ui/ability/icon/Arcane2_able_selected.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_ARCANE2_DISABLE", L"resources/images/gameScene/ui/ability/icon/Arcane2_disable.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_ARCANE3_ABLE", L"resources/images/gameScene/ui/ability/icon/Arcane3_able.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_ARCANE3_ABLE_SELECTED", L"resources/images/gameScene/ui/ability/icon/Arcane3_able_selected.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_ARCANE3_DISABLE", L"resources/images/gameScene/ui/ability/icon/Arcane3_disable.png");

	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_GREED1_ABLE", L"resources/images/gameScene/ui/ability/icon/Greed1_able.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_GREED1_ABLE_SELECTED", L"resources/images/gameScene/ui/ability/icon/Greed1_able_selected.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_GREED1_DISABLE", L"resources/images/gameScene/ui/ability/icon/Greed1_disable.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_GREED2_ABLE", L"resources/images/gameScene/ui/ability/icon/Greed2_able.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_GREED2_ABLE_SELECTED", L"resources/images/gameScene/ui/ability/icon/Greed2_able_selected.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_GREED2_DISABLE", L"resources/images/gameScene/ui/ability/icon/Greed2_disable.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_GREED3_ABLE", L"resources/images/gameScene/ui/ability/icon/Greed3_able.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_GREED3_ABLE_SELECTED", L"resources/images/gameScene/ui/ability/icon/Greed3_able_selected.png");
	IMAGE_MANAGER->addImage("UI/ABILITY/ICON_GREED3_DISABLE", L"resources/images/gameScene/ui/ability/icon/Greed3_disable.png");

	IMAGE_MANAGER->addFrameImage("UI/ABILITY/CLICK_EFFECT", L"resources/images/gameScene/ui/ability/click/ClickEffect.png", 12, 1);
	EFFECT_MANAGER->addEffect("UI/ABILITY/EFFECT_click", "UI/ABILITY/CLICK_EFFECT", 30, 10);

	// *** MAP
	IMAGE_MANAGER->addImage("UI/MAP/HEADER", L"resources/images/gameScene/ui/map/MapBase 1_0.png");
	IMAGE_MANAGER->addImage("UI/MAP/BODY", L"resources/images/gameScene/ui/map/MapBase 1_1.png");
	IMAGE_MANAGER->addImage("UI/MAP/NAME_BG", L"resources/images/gameScene/ui/map/MapName.png");
	IMAGE_MANAGER->addImage("UI/MAP/ROOM", L"resources/images/gameScene/ui/map/room.png");
	IMAGE_MANAGER->addImage("UI/MAP/ICON_FOOD", L"resources/images/gameScene/ui/map/Food.png");
	IMAGE_MANAGER->addImage("UI/MAP/ICON_SHOP", L"resources/images/gameScene/ui/map/Shop.png");
	IMAGE_MANAGER->addImage("UI/MAP/ICON_WORM", L"resources/images/gameScene/ui/map/Worm.png");
	IMAGE_MANAGER->addImage("UI/MAP/ICON_WORM_SELECTED", L"resources/images/gameScene/ui/map/Worm_Selected.png");
	IMAGE_MANAGER->addImage("UI/MAP/ICON_EXIT", L"resources/images/gameScene/ui/map/Exit.png");
	IMAGE_MANAGER->addImage("UI/MAP/ICON_ENTRANCE", L"resources/images/gameScene/ui/map/Enterance.png");
	IMAGE_MANAGER->addImage("UI/MAP/ICON_CHEST", L"resources/images/gameScene/ui/map/Chest.png");
	IMAGE_MANAGER->addImage("UI/MAP/ICON_NPC", L"resources/images/gameScene/ui/map/MiniMapNPC.png");

	// ** NPC
	IMAGE_MANAGER->addFrameImage("NPC_RESTAURANT", L"resources/images/gameScene/npc/restaurant.png", 6, 1);
	IMAGE_MANAGER->addFrameImage("NPC_SHOP", L"resources/images/gameScene/npc/shop.png", 4, 1);
	IMAGE_MANAGER->addFrameImage("NPC_ABILITY", L"resources/images/gameScene/npc/Ability.png", 6, 1);
	IMAGE_MANAGER->addFrameImage("NPC_GATE_IDLE", L"resources/images/gameScene/npc/gate_idle.png", 9, 1);
	IMAGE_MANAGER->addFrameImage("NPC_GATE_EAT", L"resources/images/gameScene/npc/gate_eat.png", 4, 1);
	IMAGE_MANAGER->addFrameImage("NPC_ENTRANCE", L"resources/images/gameScene/npc/Door1.png", 10, 1);
	IMAGE_MANAGER->addFrameImage("NPC_EXIT", L"resources/images/gameScene/npc/Door1.png", 10, 1);
	IMAGE_MANAGER->addImage("NPC_CHEST_BASIC", L"resources/images/gameScene/npc/BasicTresureClosed.png");
	IMAGE_MANAGER->addImage("NPC_CHEST_BASIC_OPEN", L"resources/images/gameScene/npc/BasicTresureOpened.png");
	IMAGE_MANAGER->addImage("NPC_CHEST_BLUE", L"resources/images/gameScene/npc/BlueTresureClosed.png");
	IMAGE_MANAGER->addImage("NPC_CHEST_BLUE_OPEN", L"resources/images/gameScene/npc/BlueTresureOpened.png");
	IMAGE_MANAGER->addImage("NPC_CHEST_YELLOW", L"resources/images/gameScene/npc/YellowTresureClosed.png");
	IMAGE_MANAGER->addImage("NPC_CHEST_YELLOW_OPEN", L"resources/images/gameScene/npc/YellowTresureOpened.png");
	IMAGE_MANAGER->addImage("NPC_CHEST_BOSS", L"resources/images/gameScene/npc/BossTresureClosed.png");
	IMAGE_MANAGER->addImage("NPC_CHEST_BOSS_OPEN", L"resources/images/gameScene/npc/BossTresureOpened.png");

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
	IMAGE_MANAGER->addFrameImage("DungeonEat", L"resources/images/Villiage/DungeonEat.png", 28, 1);

	// ** DUNGEON
	IMAGE_MANAGER->addImage("InDungeonShop", L"resources/images/Villiage/InDungeonShop.png");
	IMAGE_MANAGER->addImage("Tavern", L"resources/images/Villiage/Tavern.png");
	IMAGE_MANAGER->addFrameImage("CandleOn1", L"resources/images/Map/CandleOn1.png", 6, 1);
	IMAGE_MANAGER->addFrameImage("CandleOn2", L"resources/images/Map/CandleOn2.png", 6, 1);
	IMAGE_MANAGER->addFrameImage("CandleOn3", L"resources/images/Map/CandleOn3.png", 6, 1);
	IMAGE_MANAGER->addFrameImage("Torch", L"resources/images/Map/torch.png", 7, 1);

	IMAGE_MANAGER->addFrameImage("Die", L"resources/images/Effect/Die/Die.png", 11, 1);
	EFFECT_MANAGER->addEffect("Die_Effect", "Die", 15, 1); //이건 워프이동에도 이용

	// ** OBJECT
	// *** BROKEN
	IMAGE_MANAGER->addImage("OBJECT/BROKEN/BOX", L"resources/images/object/broken/Box0.png");
	IMAGE_MANAGER->addImage("OBJECT/BROKEN/BIG_BOX", L"resources/images/object/broken/BigBox0.png");
	IMAGE_MANAGER->addImage("OBJECT/BROKEN/DRUM", L"resources/images/object/broken/OakDrum0.png");
	// *** PARTICLE
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/BOX_0", L"resources/images/object/broken/BoxParticle0_0.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/BOX_1", L"resources/images/object/broken/BoxParticle0_1.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/BOX_2", L"resources/images/object/broken/BoxParticle0_2.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/BOX_3", L"resources/images/object/broken/BoxParticle0_3.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/BOX_4", L"resources/images/object/broken/BoxParticle0_4.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/BOX_5", L"resources/images/object/broken/BoxParticle0_5.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/BOX_6", L"resources/images/object/broken/BoxParticle0_6.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/BIG_BOX_0", L"resources/images/object/broken/BigBoxParticle0_0.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/BIG_BOX_1", L"resources/images/object/broken/BigBoxParticle0_1.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/BIG_BOX_2", L"resources/images/object/broken/BigBoxParticle0_2.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/BIG_BOX_3", L"resources/images/object/broken/BigBoxParticle0_4.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/BIG_BOX_4", L"resources/images/object/broken/BigBoxParticle0_5.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/BIG_BOX_5", L"resources/images/object/broken/BigBoxParticle0_6.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/DRUM_0", L"resources/images/object/broken/OakDrumParticle0_0.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/DRUM_1", L"resources/images/object/broken/OakDrumParticle0_1.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/DRUM_2", L"resources/images/object/broken/OakDrumParticle0_2.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/DRUM_3", L"resources/images/object/broken/OakDrumParticle0_3.png");
	IMAGE_MANAGER->addImage("OBJECT/PARTICLE/DRUM_4", L"resources/images/object/broken/OakDrumParticle0_4.png");
	// *** GOLD
	IMAGE_MANAGER->addFrameImage("OBJECT/GOLD/COIN", L"resources/images/object/gold/goldCoin.png", 8, 1);
	IMAGE_MANAGER->addFrameImage("OBJECT/GOLD/BULLION", L"resources/images/object/gold/goldBullion.png", 7, 1);
	// *** HP FAIRY
	IMAGE_MANAGER->addFrameImage("OBJECT/HP_FAIRY/MID", L"resources/images/object/hpFairy/midFairy.png", 16, 1);
	// *** DOOR
	IMAGE_MANAGER->addFrameImage("OBJECT/DOOR", L"resources/images/object/door/door.png", 23, 1);
	IMAGE_MANAGER->addImage("OBJECT/DOOR_OPEN_EFFECT", L"resources/images/object/door/openEffect.png");
	IMAGE_MANAGER->addFrameImage("Floor1Door", L"resources/images/Dungeon/Door1.png", 10, 1);

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
	IMAGE_MANAGER->addImage("Lala'sMagicWand02", L"resources/images/weapon/longDistanceWeapon/Lala'sMagicWand02.png");

	IMAGE_MANAGER->addImage("MatchlockGun", L"resources/images/weapon/longDistanceWeapon/MatchlockGun.png");
	IMAGE_MANAGER->addImage("MetalBoomerang", L"resources/images/weapon/longDistanceWeapon/MetalBoomerang.png");
	IMAGE_MANAGER->addImage("OakBow", L"resources/images/weapon/longDistanceWeapon/OakBow.png");
	IMAGE_MANAGER->addImage("GatlingGun", L"resources/images/weapon/longDistanceWeapon/GatlingGun1.png");

	IMAGE_MANAGER->addFrameImage("GatlingGun_Ani", L"resources/images/weapon/longDistanceWeapon/GatlingGunAni.png", 2, 1);
	IMAGE_MANAGER->addFrameImage("Boomerang_Moving", L"resources/images/weapon/longDistanceWeapon/Boomerang_Moving.png", 2, 1);
	IMAGE_MANAGER->addFrameImage("OakBowAni", L"resources/images/weapon/longDistanceWeapon/OakBowAni.png", 6, 1);

	// **** L_WeaponBullet
	IMAGE_MANAGER->addImage("Arrow00", L"resources/images/weapon/longDistanceWeapon/Arrow00.png");
	IMAGE_MANAGER->addFrameImage("GunBullet", L"resources/images/weapon/longDistanceWeapon/Bullet.png", 4, 1);
	IMAGE_MANAGER->addFrameImage("lalaStickBullet", L"resources/images/weapon/longDistanceWeapon/lalaStickBullet.png", 4, 1);

	// **** L_WeaponReload
	IMAGE_MANAGER->addImage("ReloadBar", L"resources/images/weapon/longDistanceWeapon/ReloadBase.png");
	IMAGE_MANAGER->addImage("ReloadHandle", L"resources/images/weapon/longDistanceWeapon/ReloadBar.png");
	IMAGE_MANAGER->addFrameImage("ReloadFinish", L"resources/images/weapon/longDistanceWeapon/effect/Reload.png", 4, 1);

	// **** L_WeaponEffect
	IMAGE_MANAGER->addFrameImage("ArrowHitEffect", L"resources/images/weapon/longDistanceWeapon/effect/ArrowHitEffect.png", 6, 1);
	IMAGE_MANAGER->addFrameImage("BoomerangEffect", L"resources/images/weapon/longDistanceWeapon/effect/BoomerangEffect.png", 12, 1);
	IMAGE_MANAGER->addFrameImage("ChargeEffect", L"resources/images/weapon/longDistanceWeapon/effect/ChargeEffect.png", 8, 1);
	IMAGE_MANAGER->addFrameImage("HecateSmokeFX02", L"resources/images/weapon/longDistanceWeapon/effect/HecateSmokeFX02.png", 10, 1);
	IMAGE_MANAGER->addFrameImage("ShootEffect", L"resources/images/weapon/longDistanceWeapon/effect/ShootEffect.png", 3, 1);
	IMAGE_MANAGER->addFrameImage("ShootEffect01", L"resources/images/weapon/longDistanceWeapon/effect/ShootEffect01.png", 6, 1);
	IMAGE_MANAGER->addFrameImage("ShootEffect02", L"resources/images/weapon/longDistanceWeapon/effect/ShootEffect02.png", 6, 1);
	IMAGE_MANAGER->addFrameImage("lalaStickEffect", L"resources/images/weapon/longDistanceWeapon/effect/lalaStickEffect.png", 7, 1);
	IMAGE_MANAGER->addFrameImage("GatlingGunEffect", L"resources/images/weapon/longDistanceWeapon/effect/GatlingGunEffect.png", 7, 1);

	EFFECT_MANAGER->addEffect("L_Effect_ArrowHit", "ArrowHitEffect", 30, 10);
	EFFECT_MANAGER->addEffect("L_Effect_Boomerang", "BoomerangEffect", 30, 10);
	EFFECT_MANAGER->addEffect("L_Effect_Charge", "ChargeEffect", 30, 10);
	EFFECT_MANAGER->addEffect("L_Effect_HecateSmoke", "HecateSmokeFX02", 10, 10);
	EFFECT_MANAGER->addEffect("L_Effect_Shoot", "ShootEffect", 30, 10);
	EFFECT_MANAGER->addEffect("L_Effect_Shoot01", "ShootEffect01", 30, 10);
	EFFECT_MANAGER->addEffect("L_Effect_Shoot02", "ShootEffect02", 30, 10);
	EFFECT_MANAGER->addEffect("L_Effect_lalaStick", "lalaStickEffect", 30, 10);
	EFFECT_MANAGER->addEffect("L_Effect_Reload", "ReloadFinish", 30, 10);
	EFFECT_MANAGER->addEffect("L_Effect_GatlingGunBullet", "GatlingGunEffect", 30, 10);

	// **** L_test
	IMAGE_MANAGER->addFrameImage("test_OakBowAni", L"resources/images/weapon/longDistanceWeapon/test_OakBowAni.png", 6, 1);
	IMAGE_MANAGER->addFrameImage("ShootEffect_test", L"resources/images/weapon/longDistanceWeapon/effect/ShootEffect_test.png", 3, 1);
	EFFECT_MANAGER->addEffect("L_Effect_Shoot_test", "ShootEffect_test", 30, 10);


	//***MeleeWeapon
	IMAGE_MANAGER->addImage("ShortSpear", L"resources/images/MeleeWeapon/ShortSpear.png");  //숏 스피어
	IMAGE_MANAGER->addImage("ShortSword", L"resources/images/MeleeWeapon/ShortSword.png");  //숏 소드
	IMAGE_MANAGER->addFrameImage("CosmosSword", L"resources/images/MeleeWeapon/CosmosSword.png",12,1);//우주검 
	IMAGE_MANAGER->addImage("KeresScythe", L"resources/images/MeleeWeapon/KeresScythe.png"); // 케레스(칼,창)
	IMAGE_MANAGER->addImage("PickaxeRed", L"resources/images/MeleeWeapon/PickaxeRed.png"); // 붉은 곡괭이
	IMAGE_MANAGER->addImage("PowerKatanaHUD", L"resources/images/MeleeWeapon/PowerKatanaHUD.png"); // 육도가이(카타나)
	IMAGE_MANAGER->addImage("KatanaWhite", L"resources/images/MeleeWeapon/KatanaWhite.png"); // 육도가이 흰색(카타나)
	
	//***MeleeWeaponIcon
	IMAGE_MANAGER->addImage("CosmosSwordIcon", L"resources/images/MeleeWeapon/CosmosSwordIcon.png"); // 우주검 아이콘
	IMAGE_MANAGER->addImage("KeresScytheIcon", L"resources/images/MeleeWeapon/KeresScytheIcon.png"); // 케레스 아이콘
	IMAGE_MANAGER->addImage("TigerPunchIcon", L"resources/images/MeleeWeapon/TigerPunchIcon.png"); // 타이거 펀치 아이콘
	IMAGE_MANAGER->addImage("PickaxeRedIcon", L"resources/images/MeleeWeapon/PickaxeRedIcon.png"); // 붉은 곡괭이 아이콘
	IMAGE_MANAGER->addImage("PowerKatana", L"resources/images/MeleeWeapon/PowerKatana.png"); // 육도가이(카타나) 아이콘
	IMAGE_MANAGER->addImage("QuarterStaffBig", L"resources/images/MeleeWeapon/QuarterStaff_Big.png"); // 박달나무 쌍단봉 아이콘겸 이미지
	IMAGE_MANAGER->addImage("BigPaintBlush", L"resources/images/MeleeWeapon/BigPaintBlush.png"); // 서예용 붓 아이콘겸 이미지
	IMAGE_MANAGER->addImage("Lumber", L"resources/images/MeleeWeapon/Lumber0.png"); // 각목 아이콘겸 이미지
	IMAGE_MANAGER->addImage("Lumber1", L"resources/images/MeleeWeapon/Lumber1.png"); // 부서진 각목 아이콘겸 이미지
	IMAGE_MANAGER->addImage("FluteGreatSword", L"resources/images/MeleeWeapon/FluteGreatSword.png"); // 흑장미칼 아이콘겸 이미지

	//***MeleeWeaponEffect
	IMAGE_MANAGER->addFrameImage("SwingFX", L"resources/images/MeleeWeapon/SwingFX.png", 3, 1);
	IMAGE_MANAGER->addFrameImage("StabFX", L"resources/images/MeleeWeapon/StabFX.png", 4, 1);
	IMAGE_MANAGER->addFrameImage("CosmosSwordFx", L"resources/images/MeleeWeapon/CosmosSwordFx.png",8, 1); 
	IMAGE_MANAGER->addFrameImage("KeresScytheSwingFX", L"resources/images/MeleeWeapon/KeresScytheSwingFX.png",8, 1);
	IMAGE_MANAGER->addFrameImage("TigerPunch", L"resources/images/MeleeWeapon/TigerPunch.png",10,1);
	IMAGE_MANAGER->addFrameImage("RedPickaxeSwing", L"resources/images/MeleeWeapon/RedPickaxeSwing.png",12,1);
	IMAGE_MANAGER->addFrameImage("PowerKatanaEf", L"resources/images/MeleeWeapon/PowerKatanaEf.png",9,1);
	IMAGE_MANAGER->addFrameImage("PaintSwing", L"resources/images/MeleeWeapon/PaintSwing.png",23,1);
	IMAGE_MANAGER->addFrameImage("CosmosSlashFX0", L"resources/images/MeleeWeapon/CosmosSlashFX0.png",7,1);
	
	//***MeleeWeaponSound
	SOUND_MANAGER->addSound("SOUND_katana", "resources/sound/MeleeWeapon/katana.wav", false, false);  // 카타나
	SOUND_MANAGER->addSound("SOUND_katana2", "resources/sound/MeleeWeapon/katana2.wav", false, false);
	SOUND_MANAGER->addSound("SOUND_katana3", "resources/sound/MeleeWeapon/katana3.wav", false, false);
	SOUND_MANAGER->addSound("SOUND_generalAttack", "resources/sound/MeleeWeapon/generalAttack.wav", false, false); // 기본검 공격
	SOUND_MANAGER->addSound("SOUND_swing0", "resources/sound/MeleeWeapon/swing0.wav", false, false); // 우주검 기본 공격
	SOUND_MANAGER->addSound("SOUND_handAttack", "resources/sound/MeleeWeapon/handAttack.wav", false, false); // 맨손 공격
	SOUND_MANAGER->addSound("SOUND_TigerRoar", "resources/sound/MeleeWeapon/TigerRoar.wav", false, false); // 호랑이권법 공격
	SOUND_MANAGER->addSound("SOUND_scythe", "resources/sound/MeleeWeapon/scythe.wav", false, false); // 사이더 공격
	SOUND_MANAGER->addSound("SOUND_PickaxeRed", "resources/sound/MeleeWeapon/PickaxeRed.wav", false, false); // 붉은곡괭이 공격
	SOUND_MANAGER->addSound("SOUND_wujusword", "resources/sound/MeleeWeapon/wujusword.wav", false, false); // 우주검 공격
	SOUND_MANAGER->addSound("SOUND_swing1", "resources/sound/MeleeWeapon/swing1.wav", false, false); // 붓 공격





	EFFECT_MANAGER->addEffect("EFFECT_COSMOSSWING", "CosmosSwordFx", 30, 10); // 우주검 이펙트
	EFFECT_MANAGER->addEffect("EFFECT_COSMOSSLASH", "CosmosSlashFX0", 30, 10);	  // 우주검 피격시 이펙트
	EFFECT_MANAGER->addEffect("EFFECT_SCYTHESWING", "KeresScytheSwingFX", 30, 10); // 낫 이펙트
	EFFECT_MANAGER->addEffect("EFFECT_SWING", "SwingFX", 15, 10); // 일반 휘두르기 이펙트
	EFFECT_MANAGER->addEffect("EFFECT_STAB", "StabFX", 15, 10);	  // 일반 찌르기 이펙트
	EFFECT_MANAGER->addEffect("EFFECT_TIGERPUNCH", "TigerPunch", 20, 10);	  // 타이거펀치 이펙트
	EFFECT_MANAGER->addEffect("EFFECT_REDPICKAXESWING", "RedPickaxeSwing", 30, 10);	  // 붉은곡괭이 이펙트
	EFFECT_MANAGER->addEffect("EFFECT_POWERKATANA", "PowerKatanaEf", 30, 10);	  // 육도가이(카타나) 이펙트
	EFFECT_MANAGER->addEffect("EFFECT_PAINTSWING", "PaintSwing", 15, 10);	  // 서예용 붓 이펙트
	//**** 크리티컬 이펙트
	IMAGE_MANAGER->addFrameImage("EXPowerKatanaSwingFX", L"resources/images/MeleeWeapon/EXPowerKatanaSwingFX.png",10,1); // 카타나 크리티컬
	EFFECT_MANAGER->addEffect("EFFECT_EXKATANAFX", "EXPowerKatanaSwingFX", 30, 10);	  // 카타나 크리티컬 이펙트


	

	// *Accessories
	IMAGE_MANAGER->addImage("SpikeBall", L"resources/images/Accessories/SpikeBall.png");                       // 뾰족공	
	IMAGE_MANAGER->addImage("BloodStoneRing", L"resources/images/Accessories/BloodStoneRing.png");             // 혈석반지	
	IMAGE_MANAGER->addImage("Voluspa", L"resources/images/Accessories/Voluspa.png");                           // 볼루스파
	IMAGE_MANAGER->addImage("Voluspa0", L"resources/images/Accessories/Voluspa0.png");                         // 볼루스파창
	IMAGE_MANAGER->addImage("BombPouch", L"resources/images/Accessories/BombPouch.png");                       // 대쉬폭탄	
	IMAGE_MANAGER->addFrameImage("BombPouch0", L"resources/images/Accessories/BombPouch1.png", 5, 1);          // 대쉬폭탄 프레임이미지
	IMAGE_MANAGER->addFrameImage("BombPouch2", L"resources/images/Accessories/BombPouch2.png", 7, 1);          // 대쉬폭탄 터지는 프레임이미지
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
	IMAGE_MANAGER->addFrameImage("DadBatBulletFX", L"resources/images/Accessories/DadBatBulletFX.png", 11, 1); // 아빠 그린박쥐 공격 충돌 프레임이미지
	IMAGE_MANAGER->addFrameImage("babyGreenBatF", L"resources/images/Accessories/GreenBat0.png", 6, 1);        // 아기 그린박쥐 프레임이미지
	IMAGE_MANAGER->addFrameImage("GreenBatF", L"resources/images/Accessories/GreenBat3.png", 6, 1);            // 그린박쥐 프레임이미지
	IMAGE_MANAGER->addFrameImage("GreenDadBatF", L"resources/images/Accessories/GreenDadBat1.png", 7, 1);      // 아빠 그린박쥐 프레임이미지
	IMAGE_MANAGER->addFrameImage("GreenMomBatF", L"resources/images/Accessories/GreenMomBat2.png", 7, 1);      // 엄마 그린박쥐 프레임이미지
	IMAGE_MANAGER->addImage("HeartOfCosmos", L"resources/images/Accessories/HeartOfCosmos.png");               // 우주심장
	IMAGE_MANAGER->addFrameImage("HeartOfCosmos0", L"resources/images/Accessories/HeartOfCosmos0.png", 20, 1); // 우주심장 공격 프레임
	IMAGE_MANAGER->addFrameImage("HeartOfCosmosF", L"resources/images/Accessories/HeartOfCosmosF.png", 11, 1); // 우주심장 공격 프레임
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
	IMAGE_MANAGER->addImage("Seeri", L"resources/images/Accessories/Seeri.png");                               // 자동공격 인형 아이콘
	IMAGE_MANAGER->addFrameImage("Seeri0", L"resources/images/Accessories/Seeri0.png", 9, 1);                  // 자동공격 인형 프레임 이미지
	IMAGE_MANAGER->addImage("selected", L"resources/images/Accessories/selected.png");                         // 자동공격 인형 조준점
	IMAGE_MANAGER->addImage("SeeriBullet", L"resources/images/Accessories/SeeriBullet.png");                   // 자동공격 인형 탄

	// ** SPECIAL ABILITY
	IMAGE_MANAGER->addFrameImage("ALICE_ABILITY_WARNING", L"resources/images/weapon/specialAbility/alice_warning.png", 4, 1);
	IMAGE_MANAGER->addFrameImage("ALICE_ABILITY", L"resources/images/weapon/specialAbility/alice_safe.png", 1, 1);

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
	IMAGE_MANAGER->addFrameImage("Bat/Bomb/Attack_Begin", L"resources/images/Enemy/Bat/Bomb/attack_begin.png", 6, 3);	// 박쥐 (자폭) 폭발 준비

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
	IMAGE_MANAGER->addImage("Skel/Small/Hand"			, L"resources/images/Enemy/Skel/Small/hand.png"				);	// 작은해골 손
	IMAGE_MANAGER->addFrameImage("Skel/Small/Move"		, L"resources/images/Enemy/Skel/Small/move.png"		, 6, 1	);	// 작은해골 이동
	IMAGE_MANAGER->addFrameImage("Skel/Small/Move_Shot"	, L"resources/images/Enemy/Skel/Small/move_shot.png", 6, 1	);	// 작은해골 이동 피격

	IMAGE_MANAGER->addFrameImage("Skel/Small/Bow"	, L"resources/images/Enemy/Skel/Small/bow.png"		,  6, 1);	// 작은해골 활
	IMAGE_MANAGER->addFrameImage("Skel/Small/Dagger", L"resources/images/Enemy/Skel/Small/dagger.png"	, 12, 1);	// 작은해골 단검
	IMAGE_MANAGER->addFrameImage("Skel/Small/Gsword", L"resources/images/Enemy/Skel/Small/gSword.png"	, 15, 1);	// 작은해골 대검

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

	// * 에너미 이펙트
	IMAGE_MANAGER->addFrameImage("Enemy_Destroy", L"resources/images/Enemy/destroy.png"	, 11, 1);	// 에너미 죽는 이펙트
	IMAGE_MANAGER->addFrameImage("Enemy_Create"	, L"resources/images/Enemy/create.png"	,  5, 3);	// 에너미 소환 이펙트

	EFFECT_MANAGER->addEffect("Enemy_Destroy", "Enemy_Destroy", 15, 80);	// 삭제 이펙트 등록

	// * 에너미 불릿
	IMAGE_MANAGER->addFrameImage("Bat_Explosion", L"resources/images/Enemy/Bat/Bomb/explosion.png", 12, 1);

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
	EFFECT_MANAGER->addEffect("BabyBatBulletFx","BabyBatBulletFx",15,50);
	EFFECT_MANAGER->addEffect("BombPouch2", "BombPouch2", 15, 50);
	EFFECT_MANAGER->addEffect("HeartOfCosmosF", "HeartOfCosmosF", 15, 50);
	EFFECT_MANAGER->addEffect("DemonBootsF", "DemonBoots0", 15, 50);
	EFFECT_MANAGER->addEffect("DadBatBulletFX", "DadBatBulletFX", 15, 50);

	// ** Boss
	// *  Belial
	// *  Head
	IMAGE_MANAGER->addFrameImage("Belial/Head/Idle"			, L"resources/images/boss/Belial/Head/idle.png"			, 10, 1);	// 머리 기본
	IMAGE_MANAGER->addFrameImage("Belial/Head/Idle_Shot"	, L"resources/images/boss/Belial/Head/idle_Shot.png"	, 10, 1);	// 머리 기본 피격
	IMAGE_MANAGER->addFrameImage("Belial/Head/Attack"		, L"resources/images/boss/Belial/Head/attack.png"		, 10, 1);	// 머리 공격
	IMAGE_MANAGER->addFrameImage("Belial/Head/Attack_Shot"	, L"resources/images/boss/Belial/Head/attack_shot.png"	, 10, 1);	// 머리 공격 피격

	// *  Hand
	IMAGE_MANAGER->addFrameImage("Belial/Hand/Idle"		, L"resources/images/boss/Belial/Hand/idle.png"		, 10, 1);	// 손 기본
	IMAGE_MANAGER->addFrameImage("Belial/Hand/Attack"	, L"resources/images/boss/Belial/Hand/attack.png"	, 18, 1);	// 손 공격

	// *  Laser
	IMAGE_MANAGER->addFrameImage("Belial/Laser/Head", L"resources/images/boss/Belial/Laser/head.png", 7, 1);	// 레이저 시작
	IMAGE_MANAGER->addFrameImage("Belial/Laser/Body", L"resources/images/boss/Belial/Laser/body.png", 7, 1);	// 레이저 몸통

	// *  후광
	IMAGE_MANAGER->addFrameImage("Belial/Back/Circle"	, L"resources/images/boss/Belial/Back/circle.png"	, 10, 1);	// 후광 구
	IMAGE_MANAGER->addFrameImage("Belial/Back/Particle"	, L"resources/images/boss/Belial/Back/particle.png"	,  8, 1);	// 이펙트 이미지

	// *  Sword
	IMAGE_MANAGER->addImage("Belial/Sword"		, L"resources/images/boss/Belial/Sword/default.png"	);	// 검 이미지
	IMAGE_MANAGER->addImage("Belial/Sword_Shoot", L"resources/images/boss/Belial/Sword/shoot.png"	);	// 검 이미지 투사체

	IMAGE_MANAGER->addFrameImage("Belial/Sword_Charge"	, L"resources/images/boss/Belial/Sword/charge.png"	, 1, 8);	// 검 이펙트
	IMAGE_MANAGER->addFrameImage("Belial/Sword_Hit"		, L"resources/images/boss/Belial/Sword/hit.png"		, 5, 1);	// 검 충돌 이펙트

	// *  Bullet
	IMAGE_MANAGER->addFrameImage("Belial/Bullet"			, L"resources/images/boss/Belial/bullet.png"	, 2, 1);	// 투사체
	IMAGE_MANAGER->addFrameImage("Belial/Bullet_FX"			, L"resources/images/boss/Belial/bullet_FX.png"	, 8, 1);	// 투사체 이펙트

	// *  Dead
	IMAGE_MANAGER->addImage("Belial/Dead/Head"		, L"resources/images/boss/Belial/Dead/head.png"		 );	// 머리 파편
	IMAGE_MANAGER->addImage("Belial/Dead/Mouth"		, L"resources/images/boss/Belial/Dead/mouth.png"	 );	// 턱 파편
	IMAGE_MANAGER->addImage("Belial/Dead/Particle_1", L"resources/images/boss/Belial/Dead/particle_1.png");	// 파편
	IMAGE_MANAGER->addImage("Belial/Dead/Particle_2", L"resources/images/boss/Belial/Dead/particle_2.png");	// 파편
	IMAGE_MANAGER->addImage("Belial/Dead/Particle_3", L"resources/images/boss/Belial/Dead/particle_3.png");	// 파편
	IMAGE_MANAGER->addImage("Belial/Dead/Particle_4", L"resources/images/boss/Belial/Dead/particle_4.png");	// 파편
	
	EFFECT_MANAGER->addEffect("Belial/Sword_Charge"	, "Belial/Sword_Charge"	, 15, 10);
	EFFECT_MANAGER->addEffect("Belial/Sword_Hit"	, "Belial/Sword_Hit"	, 15, 10);
	EFFECT_MANAGER->addEffect("Belial/Bullet_FX"	, "Belial/Bullet_FX"	, 15, 50);

	// * 니플헤임
	IMAGE_MANAGER->addFrameImage("Niflheim/Idle"	, L"resources/images/boss/Niflheim/idle.png"	,  6, 1);	// 니플헤임 기본
	IMAGE_MANAGER->addFrameImage("Niflheim/Attack_1", L"resources/images/boss/Niflheim/attack.png"	, 11, 1);	// 니플헤임 공격 1
	IMAGE_MANAGER->addFrameImage("Niflheim/Attack_2", L"resources/images/boss/Niflheim/attack_1.png", 11, 1);	// 니플헤임 공격 2
	IMAGE_MANAGER->addFrameImage("Niflheim/Spawn"	, L"resources/images/boss/Niflheim/enter.png"	, 16, 1);	// 니플헤임 등장
	IMAGE_MANAGER->addFrameImage("Niflheim/Die"		, L"resources/images/boss/Niflheim/die.png"		, 30, 1);	// 니플헤임 죽음
	IMAGE_MANAGER->addFrameImage("Niflheim/Pillar"	, L"resources/images/boss/Niflheim/pillar.png"	, 20, 1);	// 니플헤임 얼음기둥
	IMAGE_MANAGER->addFrameImage("Niflheim/Icicle"	, L"resources/images/boss/Niflheim/icicle.png"	, 10, 1);	// 니플헤임 고드름
	IMAGE_MANAGER->addFrameImage("Niflheim/Spear"	, L"resources/images/boss/Niflheim/spear.png"	, 13, 1);	// 니플헤임 얼음창


	SOUND_MANAGER->addSound("GatlingFire", "resources/sounds/weapon/LongDistanceWeapon/GatlingFire.wav", false, false);

	//사운드
	//** PLAYER / UI
	SOUND_MANAGER->addSound("Player/Step1", "resources/sounds/player/step_lth1.wav", false, false);			//플레이어 이동1
	SOUND_MANAGER->addSound("Player/Step2", "resources/sounds/player/step_lth2.wav", false, false);			//플레이어 이동2
	SOUND_MANAGER->addSound("Player/Step3", "resources/sounds/player/step_lth3.wav", false, false);			//플레이어 이동3
	SOUND_MANAGER->addSound("Player/Step4", "resources/sounds/player/step_lth4.wav", false, false);			//플레이어 이동4
	SOUND_MANAGER->addSound("Player/Dash", "resources/sounds/player/dash.wav", false, false);				//대쉬
	SOUND_MANAGER->addSound("Player/Dead", "resources/sounds/player/dead.wav", false, false);				//사망
	SOUND_MANAGER->addSound("Player/GetGold", "resources/sounds/player/gold_collect.wav", false, false);	//수금 (골드 획득)
	SOUND_MANAGER->addSound("Player/GrowAbility", "resources/sounds/player/GrowAbility.wav", false, false);	//특성 해금
	SOUND_MANAGER->addSound("Player/GetFairy", "resources/sounds/player/Get_Fairy.wav", false, false);		//회복스팟 획득
	SOUND_MANAGER->addSound("Player/Hit", "resources/sounds/player/Hit_Player.wav", false, false);			//피격
	SOUND_MANAGER->addSound("Player/Jump", "resources/sounds/player/Jumping.wav", false, false);			//점프
	SOUND_MANAGER->addSound("Player/Swap", "resources/sounds/player/swap.wav", false, false);				//무기 교체
	SOUND_MANAGER->addSound("Player/Inven/Equip", "resources/sounds/player/inventorySounds/Equip.wav", false, false);				//인벤 장비착용
	SOUND_MANAGER->addSound("Player/Inven/GetItem", "resources/sounds/player/inventorySounds/GetItem.wav", false, false);			//인벤 아이템 획득
	SOUND_MANAGER->addSound("Player/Inven/OpenInven", "resources/sounds/player/inventorySounds/OpenInventory.wav", false, false);	//인벤토리 개폐
	SOUND_MANAGER->addSound("Player/Inven/PickUpItem", "resources/sounds/player/inventorySounds/PickUpItem.wav", false, false);		//픽업 아이템

	//** ENEMY
	SOUND_MANAGER->addSound("Enemy/Die", "resources/sound/enemy/public/MonsterDie.wav", false, false);			//사망(공용)
	SOUND_MANAGER->addSound("Enemy/GetHit", "resources/sound/enemy/public/Hit_Monster.wav", false, false);		//피격(공용)
	//* 박쥐
	SOUND_MANAGER->addSound("Bat/Attack", "resources/sound/enemy/bat/monster-sound2_bat.wav", false, false);						//작은 박쥐 공격
	SOUND_MANAGER->addSound("Bat/Die", "resources/sound/enemy/bat/monster-sound8_bat.wav", false, false);							//작은 박쥐 사망
	SOUND_MANAGER->addSound("GiantBat/Attack", "resources/sound/enemy/bat/Bat2.wav", false, false);									//거대 박쥐 공격
	SOUND_MANAGER->addSound("BoomBat/Ready", "resources/sound/enemy/bat/Fantasy_Game_Creature_High_C_Japok.wav", false, false);		//폭발 박쥐 준비
	SOUND_MANAGER->addSound("BoomBat/Explod", "resources/sound/enemy/bat/Explode.wav", false, false);								//폭발 박쥐 폭발
	//*	수녀
	SOUND_MANAGER->addSound("Banshee/Attack", "resources/sound/enemy/banshee/high_pitch_scream_gverb.wav", false, false);			//수녀 공격
	//* 해골들
	SOUND_MANAGER->addSound("Skell/Arrow/Ready", "resources/sound/enemy/skells/bow_crossbow_arrow_draw_stretch1_03.wav", false, false);	//작은  해골 활 준비  공격
	SOUND_MANAGER->addSound("Skell/Arrow/Attack", "resources/sound/enemy/skells/etc-sound0034_Bow.wav", false, false);					//작은  해골 활 발사  공격
	SOUND_MANAGER->addSound("Skell/Small/Attack", "resources/sound/enemy/skells/swish-1.wav", false, false);					   //작은   해골 단검  공격
	SOUND_MANAGER->addSound("Skell/Small_G/Attack", "resources/sound/enemy/skells/swish-6.wav", false, false);					   //작은   해골 대검	  공격
	SOUND_MANAGER->addSound("Skell/Big/Attack", "resources/sound/enemy/skells/swish-5.wav", false, false);						   //거대   해골 일반	  공격
	SOUND_MANAGER->addSound("Skell/ice/blast", "resources/sound/enemy/skells/ice_blast_projectile_spell_02.wav", false, false);	   //아이스 해골 블라스트  공격
	SOUND_MANAGER->addSound("Skell/ice/Attack", "resources/sound/enemy/skells/ice_spell_forming_shards_04.wav", false, false);	   //아이스 해골 일반      공격
	SOUND_MANAGER->addSound("IceSkell/Magic/Attack", "resources/sound/enemy/skells/ice.wav", false, false);						   //아이스 해골 마법사 공격
	//*	벨리알

	//*	니플헤임



	CONFIG_MANAGER->init();
	DATA_MANAGER->init();


	// 모든 씬 SCENE_MANAGER에 
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->addScene("GAME", new GameScene);
	SCENE_MANAGER->addScene("MapTool", new MapToolScene);
	SCENE_MANAGER->addScene("STAGE_MAKE", new MazeScene);
	
	SCENE_MANAGER->changeScene("GAME");	
	
	TIME_MANAGER->init();
	
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
