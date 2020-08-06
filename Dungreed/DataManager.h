#pragma once


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

	bool _isActive; // 로드 UI를 띄울 것인지 결정하는 불 변수
	tagLoadInfo _loadInfos[3];
	FloatRect _loadRc[3];

public:
	void init(); // 로드 데이터 존재한다면 읽음
	void update(); // 로드 UI를 띄운 상태일 때 
	void render(); // 로드 UI를 띄운 상태일 때

	inline void setActive(bool active) { _isActive = active; }
	inline bool isActive() const noexcept { return _isActive; }
	void save(int slot, tagLoadInfo info) {} // 저장하는 함수
};

