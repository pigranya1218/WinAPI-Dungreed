#pragma once

enum class DEBUG_TYPE : unsigned int
{
	END
};

enum class OBJECT_TEAM : int
{
	PLAYER = 0,
	ENEMY
};

enum class ENEMY_TYPE : unsigned int
{
	BANSHEE = 0,		// ����
	BAT_BOMB,			// ���� ����
	BAT_RED,			// ���� ����
	BAT_NORMAL,			// ���� �⺻
	BAT_ICE,			// ���� ����
	BAT_GIANT_RED,		// ���� �Ŵ� ����
	BAT_GIANT_NORMAL,	// ���� �Ŵ� �⺻
	GHOST,				// ����
	LILITH,				// ��ť����
	SKEL_BIG_NORMAL,	// �ذ��� �⺻
	SKEL_BIG_ICE,		// �ذ��� ����
	SKEL_DOG,			// �ذ񰭾���
	SKEL_MAGICIAN_ICE,	// �ذ񸶹��� ����
	SKEL_SMALL_BOW,		// �ذ� �ü�
	SKEL_SMALL_GSWORD,	// �ذ� ���
	SKEL_SMALL_DAGGER,	// �ذ� �ܰ�
	MINOTAURS,			// �̳�Ÿ�츣��
	OVIBOS,				// ������ ����
	BELIAL,				// ������
	NIPLEHEIM			// ��������
};

enum class DIRECTION : unsigned int
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN,
	END
};

enum class PIVOT : int
{
	LEFT_TOP, 
	CENTER, 
	BOTTOM
};

enum class ACTION_TYPE
{
	MOVE_UP = 0, // ���� �̵�
	MOVE_DOWN, // �Ʒ��� �̵�
	MOVE_LEFT, // �������� �̵�
	MOVE_RIGHT, // ���������� �̵�
	JUMP, // ����
	ATTACK, // ���� 
	MAIN_SKILL, // ��ų
	SUB_SKILL, // ������ų
	DASH, // �뽬
	RELOAD, // ������
	INVENTORY, // ĳ���� �κ��丮
	MAP, // ���� ����
	STAT, // ĳ���� �ɷ�ġ
	INTERACTION, // ��ȣ�ۿ�
	CHANGE_WEAPON, // ���� ��ü
	END
};

enum class SOUND_TYPE
{
	BGM, // �����
	EFFECT // ȿ����
};
