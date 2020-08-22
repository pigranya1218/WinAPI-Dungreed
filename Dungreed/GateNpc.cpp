#include "GateNpc.h"
#include "UIManager.h"
#include "NpcManager.h"
#include "StageManager.h"

void GateNpc::init(Vector2 pos, DIRECTION direction)
{
	_type = NPC_TYPE::GATE;
	_mapIcon = IMAGE_MANAGER->findImage("UI/MAP/ICON_WORM");
	_miniMapIcon = IMAGE_MANAGER->findImage("UI/MAP/ICON_WORM");

	_img = IMAGE_MANAGER->findImage("NPC_GATE_IDLE");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(20);
	_ani->start();

	_position = pos;
	_size = Vector2(50, 120);
	_direction = direction;
	_active = true;

	_isActiveInteraction = false;
	_isClose = false;
	_move = false;
}

void GateNpc::release()
{
	_ani->release();
	delete _ani;
}

void GateNpc::update(float timeElapsed)
{
	


	if (_move && !_ani->isPlay())
	{
		
		
			// 플레이어 이동시키기
			_npcMgr->moveRoom(_roomIndex);

			// 초기화
			_img = IMAGE_MANAGER->findImage("NPC_GATE_IDLE");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setDefPlayFrame(false, true);
			_move = false;
			return;

		
		
	}
	Npc::update(timeElapsed);

	_ani->frameUpdate(timeElapsed);
}

void GateNpc::interaction()
{
	_uiMgr->showMap(this, true);
}

void GateNpc::render()
{
	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));

	Npc::render();
}

void GateNpc::move(Vector2 roomIndex)
{
	_move = true;
	_roomIndex = roomIndex;
	_img = IMAGE_MANAGER->findImage("NPC_GATE_EAT");;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, false);
	_ani->start();

	Vector2 effectScale; 
	effectScale.x = _img->getSize().x * 4;
	effectScale.y = _img->getSize().y * 4;

	EFFECT_MANAGER->play("Die_Effect", CAMERA->getAbsoluteV2(_npcMgr->getPlayerPos()), effectScale);
	
}
