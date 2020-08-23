#pragma once

class CostumeManager;
class ItemManager;
class Costume;
class Item;

enum class COSTUME_TYPE;
enum class ITEM_RANK;

struct tagLoadInfo
{
	int playTime; // 분 단위
	int highStage; // 가장 높이 도달한 층
	int level; // 플레이어 레벨
	int gold; // 소지금
	// TODO
	int statLevel[5];// 훈련장 스탯 정보
	// 장착한 무기 (신비 20레벨 스킬 대비) 
};

class DataManager : public SingletonBase<DataManager>
{
private:
	Image* _exitButton;
	FloatRect _exitRc;

	Image* _slotImg;

	bool _isActive; // 로드 UI를 띄울 것인지 결정하는 불 변수
	tagLoadInfo _loadInfos[3];
	FloatRect _loadRc[3];
	FloatRect _deleteRc[3];
	int _selectedSlot;
	int _selectedDelete;

	CostumeManager* _costumeMgr;
	ItemManager*	_itemMgr;

public:
	void init(); // 로드 데이터 존재한다면 읽음
	void update(); // 로드 UI를 띄운 상태일 때 
	void render(); // 로드 UI를 띄운 상태일 때

	inline void setActive(bool active) { _isActive = active; }
	inline bool isActive() const noexcept { return _isActive; }
	void save(int slot, tagLoadInfo info) {} // 저장하는 함수

public:
	Costume* getCostume (COSTUME_TYPE type);

	vector<Item*> getRandomItem(ITEM_RANK startRank, ITEM_RANK endRank, int count);
	Item* getItem(int itemCode);
};

