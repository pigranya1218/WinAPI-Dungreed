#pragma once

class Player;
class PlayerStat;

enum class ABILITY_ICON : int
{
	ABLE,
	ABLE_SELECTED,
	DISABLE
};

class AbilityUI
{
private:
	struct tagAbilityWindow
	{
		FloatRect baseRc;			//특성창 렉트
		FloatRect titleRc;			//특성이름 적을 렉트
		FloatRect pointRc;			//특성 포인트 적을 렉트
		FloatRect statValueRc[2];	//상승하는 스탯의 수치를 적을 렉트
		FloatRect statNameRc[2];	//상승하는 스탯의 이름을 적을 렉트
		FloatRect iconRc[3];		//특성 아이콘 렉트
		FloatRect buttonRc;			//플러스 단추
		FloatCircle buttonCir;		//플러스 단추 서클
	};

private:
	Player* _player;
	
	bool _isActive;

	//이미지
	//*라벨 띠지
	Image* _labelImg = IMAGE_MANAGER->findImage("UI/ABILITY/LABEL");
	//*배경
	Image* _wrathBackImg = IMAGE_MANAGER->findImage("UI/ABILITY/BASE_WRATH");			//분노 배경 이미지
	Image* _swiftnessBackImg = IMAGE_MANAGER->findImage("UI/ABILITY/BASE_SWIFTNESS");	//신속 배경 이미지
	Image* _patienceBackImg = IMAGE_MANAGER->findImage("UI/ABILITY/BASE_PATIENCE");		//인내 배경 이미지
	Image* _arcane = IMAGE_MANAGER->findImage("UI/ABILITY/BASE_ARCANE");				//신비 배경 이미지
	Image* _greed = IMAGE_MANAGER->findImage("UI/ABILITY/BASE_GREED");					//탐욕 배경 이미지
	Image* _currPointFrame = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE");
	Image* _currPointBack = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE_BACK");
	//*단추
	Image* _exitButtonImg = IMAGE_MANAGER->findImage("BUTTON_EXIT");
	Image* _exitButtonSelectedImg = IMAGE_MANAGER->findImage("BUTTON_EXIT_SELECTED");
	Image* _wrathButtonImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_WRATH");			//분노 단추 이미지
	Image* _swiftnessButtonImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_SWIFTNESS");	//분노 단추 이미지
	Image* _patienceButtonImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_PATIENCE");		//분노 단추 이미지
	Image* _arcaneButtonImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_ARCANE");			//분노 단추 이미지
	Image* _greedButtonImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_GREED");			//분노 단추 이미지
	Image* _wrathButtonDisableImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_WRATH_DISABLE");			//분노 단추 비활성 이미지
	Image* _swiftnessButtonDisableImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_SWIFTNESS_DISABLE");	//분노 단추 비활성 이미지
	Image* _patienceButtonDisableImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_PATIENCE_DISABLE");		//분노 단추 비활성 이미지
	Image* _arcaneButtonDisableImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_ARCANE_DISABLE");			//분노 단추 비활성 이미지
	Image* _greedButtonDisableImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_GREED_DISABLE");			//분노 단추 비활성 이미지
	//*아이콘 ([특성1,2,3][able, able_selected, disable])
	Image* _wrathIcon[3][3];	 //분노
	Image* _swiftnessIcon[3][3]; //신속
	Image* _patienceIcon[3][3];	 //인내
	Image* _arcaneIcon[3][3];	 //신비
	Image* _greedIcon[3][3];	 //탐욕
	//*+단추 클릭시 이펙트 이미지
	Image* _clickEffectImg = IMAGE_MANAGER->findImage("UI/ABILITY/CLICK_EFFECT");

	//사용할 렉트
	FloatRect _bgRc;	//뒷배경(알파수치 이용하여 투명도 조정)
	FloatRect _exitRc;	//창닫기 단추
	FloatRect _currPointRc; //현재 남은 특성 포인트를 표시할 렉트

	//특성 창 구조체
	tagAbilityWindow _windows[5]; //분노,신속,인내,신비,탐욕 순으로 저장

public:
	void setPlayer(Player* player) { _player = player; }

	void init();
	void release();
	void update(float elapsedTime);
	void render();

	bool isActive() const noexcept { return _isActive; }
	void setActive(bool active) { _isActive = active; }

	string getAbilityIconString(ABILITY_ICON type);
};

