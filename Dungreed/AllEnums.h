#pragma once

enum class DEBUG_TYPE : unsigned int
{
	END
};

enum class OBJECT_TEAM : unsigned int
{
	PLAYER,
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
