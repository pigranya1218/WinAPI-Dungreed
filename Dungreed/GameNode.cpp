#include "stdafx.h"
#include "GameNode.h"


GameNode::GameNode()
{
}


GameNode::~GameNode()
{
}

HRESULT GameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		KEY_MANAGER->init();
		TIME_MANAGER->init();
		EFFECT_MANAGER->init();
		SOUND_MANAGER->init();
		SCENE_MANAGER->init();
		DEBUG_MANAGER->init();
	}


	return S_OK;
}

void GameNode::release()
{
	if (_managerInit)
	{
		KEY_MANAGER->release();
		KEY_MANAGER->releaseSingleton();

		IMAGE_MANAGER->releaseSingleton();

		TIME_MANAGER->release();
		TIME_MANAGER->releaseSingleton();

		EFFECT_MANAGER->release();
		EFFECT_MANAGER->releaseSingleton();

		SOUND_MANAGER->release();
		SOUND_MANAGER->releaseSingleton();

		SCENE_MANAGER->release();
		SCENE_MANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update()
{

}

void GameNode::render()
{

}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HWND - �ڵ�޽���
	//UINT - �޽��� �߻� ��ȣ
	//WPARAM - Ű���� �Է� �� ���콺 Ŭ�� �޽��� ����
	//LPARAM - ���콺 ��ǥ ����

	PAINTSTRUCT ps;
	HDC         hdc;

	switch (iMessage)
	{

	case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>(LOWORD(lParam));
		_ptMouse.y = static_cast<float>(HIWORD(lParam));
		break;

	case WM_KEYDOWN:
	{
		/*switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}*/
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}