#pragma once

class Animation
{
public:
	using vFrameList = vector<POINT>;	//�ִϸ��̼� ������ �����
	using vPlayList = vector<int>;	//�ִϸ��̼� �÷��� �ε��� �����

private:
	int _frameNum;	//�ִϸ��̼� ������ ����

	vFrameList	_frameList;
	vPlayList	_playList;

	int _frameWidth;		//������ ����ũ��
	int _frameHeight;		//������ ����ũ��

	BOOL _loop;				//�ִϸ��̼� ���� ����

	float _frameUpdateSec;	//������ ����ð�
	float _elapsedSec;		//��Ÿ Ÿ��

	DWORD _nowPlayIndex;	//���� �÷��� �ε���
	BOOL _play;				//�ִϸ��̼� �������

	void*						_obj;

public:
	Animation();
	~Animation();

	// �̹��� ���α���, �̹��� ���α���, �̹��� ���������� ��, �̹��� ���������� ��
	HRESULT init(int totalW, int totalH, int frameNumWidth, int frameNumHeight);
	void release();

	//����Ʈ �ִϸ��̼�
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);

	//�迭 �ִϸ��̼�
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);

	//���� �ִϸ��̼�
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);


	void setFPS(int framePerSec);

	void frameUpdate(float elapsedTime);

	void start();
	void stop();
	void pause();
	void resume();

	inline BOOL isPlay() { return _play; }
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }

	inline int getPlayIndex() { return _nowPlayIndex;}
};

