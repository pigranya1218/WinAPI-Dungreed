#pragma once


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

	bool _isActive; // �ε� UI�� ��� ������ �����ϴ� �� ����
	tagLoadInfo _loadInfos[3];
	FloatRect _loadRc[3];

public:
	void init(); // �ε� ������ �����Ѵٸ� ����
	void update(); // �ε� UI�� ��� ������ �� 
	void render(); // �ε� UI�� ��� ������ ��

	inline void setActive(bool active) { _isActive = active; }
	inline bool isActive() const noexcept { return _isActive; }
	void save(int slot, tagLoadInfo info) {} // �����ϴ� �Լ�
};

