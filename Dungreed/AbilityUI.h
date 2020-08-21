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
		FloatRect baseRc;			//Ư��â ��Ʈ
		FloatRect titleRc;			//Ư���̸� ���� ��Ʈ
		FloatRect pointRc;			//Ư�� ����Ʈ ���� ��Ʈ
		FloatRect statValueRc[2];	//����ϴ� ������ ��ġ�� ���� ��Ʈ
		FloatRect statNameRc[2];	//����ϴ� ������ �̸��� ���� ��Ʈ
		FloatRect iconRc[3];		//Ư�� ������ ��Ʈ
		FloatRect buttonRc;			//�÷��� ����
		FloatCircle buttonCir;		//�÷��� ���� ��Ŭ
	};

private:
	Player* _player;
	
	bool _isActive;

	//�̹���
	//*�� ����
	Image* _labelImg = IMAGE_MANAGER->findImage("UI/ABILITY/LABEL");
	//*���
	Image* _wrathBackImg = IMAGE_MANAGER->findImage("UI/ABILITY/BASE_WRATH");			//�г� ��� �̹���
	Image* _swiftnessBackImg = IMAGE_MANAGER->findImage("UI/ABILITY/BASE_SWIFTNESS");	//�ż� ��� �̹���
	Image* _patienceBackImg = IMAGE_MANAGER->findImage("UI/ABILITY/BASE_PATIENCE");		//�γ� ��� �̹���
	Image* _arcane = IMAGE_MANAGER->findImage("UI/ABILITY/BASE_ARCANE");				//�ź� ��� �̹���
	Image* _greed = IMAGE_MANAGER->findImage("UI/ABILITY/BASE_GREED");					//Ž�� ��� �̹���
	Image* _currPointFrame = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE");
	Image* _currPointBack = IMAGE_MANAGER->findImage("UI/RESTAURANT/LIFE_BASE_BACK");
	//*����
	Image* _exitButtonImg = IMAGE_MANAGER->findImage("BUTTON_EXIT");
	Image* _exitButtonSelectedImg = IMAGE_MANAGER->findImage("BUTTON_EXIT_SELECTED");
	Image* _wrathButtonImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_WRATH");			//�г� ���� �̹���
	Image* _swiftnessButtonImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_SWIFTNESS");	//�г� ���� �̹���
	Image* _patienceButtonImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_PATIENCE");		//�г� ���� �̹���
	Image* _arcaneButtonImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_ARCANE");			//�г� ���� �̹���
	Image* _greedButtonImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_GREED");			//�г� ���� �̹���
	Image* _wrathButtonDisableImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_WRATH_DISABLE");			//�г� ���� ��Ȱ�� �̹���
	Image* _swiftnessButtonDisableImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_SWIFTNESS_DISABLE");	//�г� ���� ��Ȱ�� �̹���
	Image* _patienceButtonDisableImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_PATIENCE_DISABLE");		//�г� ���� ��Ȱ�� �̹���
	Image* _arcaneButtonDisableImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_ARCANE_DISABLE");			//�г� ���� ��Ȱ�� �̹���
	Image* _greedButtonDisableImg = IMAGE_MANAGER->findImage("UI/ABILITY/BUTTON_GREED_DISABLE");			//�г� ���� ��Ȱ�� �̹���
	//*������ ([Ư��1,2,3][able, able_selected, disable])
	Image* _wrathIcon[3][3];	 //�г�
	Image* _swiftnessIcon[3][3]; //�ż�
	Image* _patienceIcon[3][3];	 //�γ�
	Image* _arcaneIcon[3][3];	 //�ź�
	Image* _greedIcon[3][3];	 //Ž��
	//*+���� Ŭ���� ����Ʈ �̹���
	Image* _clickEffectImg = IMAGE_MANAGER->findImage("UI/ABILITY/CLICK_EFFECT");

	//����� ��Ʈ
	FloatRect _bgRc;	//�޹��(���ļ�ġ �̿��Ͽ� ���� ����)
	FloatRect _exitRc;	//â�ݱ� ����
	FloatRect _currPointRc; //���� ���� Ư�� ����Ʈ�� ǥ���� ��Ʈ

	//Ư�� â ����ü
	tagAbilityWindow _windows[5]; //�г�,�ż�,�γ�,�ź�,Ž�� ������ ����

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

