#include "stdafx.h"
#include "Animation.h"


Animation::Animation()
	: _frameNum(0),
	_frameWidth(0),
	_frameHeight(0),
	_loop(FALSE),
	_frameUpdateSec(0),
	_elapsedSec(0),
	_nowPlayIndex(0),
	_play(FALSE)
{
}


Animation::~Animation()
{
}

HRESULT Animation::init(int totalW, int totalH, int frameNumWidth, int frameNumHeight)
{
	//�ִϸ��̼� ���� �� ������ ���
	_frameWidth = totalW / frameNumWidth;
	//�ִϸ��̼� ���� �� ������ ���
	_frameHeight = totalH / frameNumHeight;

	//�� �ִϸ��̼� �������� �� ������ ���
	_frameNum = frameNumWidth * frameNumHeight;

	_frameList.clear();

	for (int i = 0; i < frameNumHeight; ++i)
	{
		for (int j = 0; j < frameNumWidth; ++j)
		{
			POINT framePos;

			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			_frameList.push_back(framePos);
		}
	}

	return S_OK;
}

void Animation::release()
{
}

void Animation::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	_obj = NULL;

	_loop = loop;
	_playList.clear();

	if (reverse)
	{
		if (_loop)
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}

			for (int i = _frameNum - 1; i >= 0; --i)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}

			for (int i = _frameNum - 1; i >= 0; --i)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		if (_loop)
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = 0; i < _frameNum; ++i)
			{
				_playList.push_back(i);
			}
		}
	}

}

void Animation::setPlayFrame(int * playArr, int arrLen, BOOL loop)
{
	_obj = NULL;

	_loop = loop;

	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}

}


void Animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	_obj = NULL;

	_loop = loop;

	_playList.clear();

	if (start == end)
	{
		_playList.clear();
		stop();
		return;
	}

	if (start > end)
	{
		if (reverse)
		{
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
			}
		}
	}
	else
	{
		if (reverse)
		{
			if (_loop)
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; --i)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; --i)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}
			}
		}
	}


}

void Animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

void Animation::frameUpdate(float elapsedTime)
{
	if (_play)
	{
		_elapsedSec += elapsedTime;

		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;

			_nowPlayIndex++;

			if (_nowPlayIndex == _playList.size())
			{
				if (_loop) _nowPlayIndex = 0;
				else
				{
					_nowPlayIndex--;
					_play = FALSE;
				}
			}
		}
	}

}

void Animation::start()
{
	_play = TRUE;
	_nowPlayIndex = 0;
}

void Animation::stop()
{
	_play = FALSE;
	_nowPlayIndex = 0;
}

void Animation::pause()
{
	_play = FALSE;
}

void Animation::resume()
{
	_play = TRUE;
}
