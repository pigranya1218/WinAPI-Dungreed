#pragma once

class Animation
{
public:
	using vFrameList = vector<POINT>;	//애니메이션 프레임 저장용
	using vPlayList = vector<int>;	//애니메이션 플레이 인덱스 저장용

private:
	int _frameNum;	//애니메이션 프레임 갯수

	vFrameList	_frameList;
	vPlayList	_playList;

	int _frameWidth;		//프레임 가로크기
	int _frameHeight;		//프레임 세로크기

	BOOL _loop;				//애니메이션 루프 여부

	float _frameUpdateSec;	//프레임 경과시간
	float _elapsedSec;		//델타 타임

	DWORD _nowPlayIndex;	//현재 플레이 인덱스
	BOOL _play;				//애니메이션 재생여부

	void*						_obj;

public:
	Animation();
	~Animation();

	// 이미지 가로길이, 이미지 세로길이, 이미지 가로프레임 수, 이미지 세로프레임 수
	HRESULT init(int totalW, int totalH, int frameNumWidth, int frameNumHeight);
	void release();

	//디폴트 애니메이션
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);

	//배열 애니메이션
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);

	//구간 애니메이션
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

