#pragma once

class CostumeManager;
class ItemManager;
class Costume;
class Item;

enum class COSTUME_TYPE;
enum class ITEM_RANK;

struct tagLoadInfo
{
	int playTime; // �� ����
	int highStage; // ���� ���� ������ ��
	int level; // �÷��̾� ����
	int gold; // ������
	// TODO
	int statLevel[5];// �Ʒ��� ���� ����
	// ������ ���� (�ź� 20���� ��ų ���) 
};

class DataManager : public SingletonBase<DataManager>
{
private:
	Image* _exitButton;
	FloatRect _exitRc;

	Image* _slotImg;

	bool _isActive; // �ε� UI�� ��� ������ �����ϴ� �� ����
	tagLoadInfo _loadInfos[3];
	FloatRect _loadRc[3];
	FloatRect _deleteRc[3];
	int _selectedSlot;
	int _selectedDelete;

	CostumeManager* _costumeMgr;
	ItemManager*	_itemMgr;

public:
	void init(); // �ε� ������ �����Ѵٸ� ����
	void update(); // �ε� UI�� ��� ������ �� 
	void render(); // �ε� UI�� ��� ������ ��

	inline void setActive(bool active) { _isActive = active; }
	inline bool isActive() const noexcept { return _isActive; }
	void save(int slot, tagLoadInfo info) {} // �����ϴ� �Լ�

public:
	Costume* getCostume (COSTUME_TYPE type);

	vector<Item*> getRandomItem(ITEM_RANK startRank, ITEM_RANK endRank, int count);
	Item* getItem(int itemCode);
};

