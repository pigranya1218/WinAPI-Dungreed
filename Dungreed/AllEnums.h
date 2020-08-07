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

enum class DIRECTION : unsigned int
{
	LEFT,
	RIGHT
};

enum class PIVOT : int
{
	LEFT_TOP, 
	CENTER, 
	BOTTOM
};

enum class KEY_TYPE
{
	MOVE_UP = 0, // ���� �̵�
	MOVE_DOWN, // �Ʒ��� �̵�
	MOVE_LEFT, // �������� �̵�
	MOVE_RIGHT, // ���������� �̵�
	ATTACK, // ���� 
	MAIN_SKILL, // ��ų
	SUB_SKILL, // ������ų
	DASH, // �뽬
	RELOAD, // ������
	INVENTORY, // ĳ���� �κ��丮
	MAP, // ���� ����
	STAT, // ĳ���� �ɷ�ġ
	INTERACTION // ��ȣ�ۿ�
};

enum class SOUND_TYPE
{
	BGM, // �����
	EFFECT // ȿ����
};

enum class ITEM_TYPE
{
	ITEM_ACCESSARIES,
	ITEM_WEAPON
};

enum class WEAPON_SIZE
{
	ONE_HAND,
	TWO_HAND
};
