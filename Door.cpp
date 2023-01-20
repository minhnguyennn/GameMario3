#include "Door.h"
#include "WorldScene.h"
#include "MarioWorld.h"

void CDoor::GetBoundingBox(float& l, float& t, float& r, float& b)
{
		l = x - DOOR_BBOX_WIDTH / 2;
		t = y - DOOR_BBOX_HEIGHT / 2;
		r = l + DOOR_BBOX_WIDTH;
		b = t + DOOR_BBOX_HEIGHT;
}

void CDoor::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	LPWORLDSCENE scene = (LPWORLDSCENE)CGame::GetInstance()->GetCurrentScene();
	CMarioWorld* mario_world = (CMarioWorld*)scene->GetPlayer();
	if (isMarioIdle && (GetTickCount64() - time_mario_idle > 70))
	{
		mario_world->SetState(MARIO_WORLD_STATE_IDLE);
		isMarioIdle = false;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CDoor::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = 0;
	if (type == DOOR_TYPE_SPECIAL)
	{
		animations->Get(ID_ANI_DOOR_SPECIAL)->Render(x, y);
	}
	else if (type == DOOR_TYPE_START)
	{
		animations->Get(ID_ANI_DOOR_START)->Render(x, y);
	}
	else if (type == DOOR_TYPE_1)
	{
		animations->Get(ID_ANI_DOOR_1)->Render(x, y);
	}
	else if (type == DOOR_TYPE_2)
	{
		animations->Get(ID_ANI_DOOR_2)->Render(x, y);
	}
	else if (type == DOOR_TYPE_3)
	{
		animations->Get(ID_ANI_DOOR_3)->Render(x, y);
	}
	else if (type == DOOR_TYPE_4)
	{
		animations->Get(ID_ANI_DOOR_4)->Render(x, y);
	}
	else if (type == DOOR_TYPE_5)
	{
		animations->Get(ID_ANI_DOOR_5)->Render(x, y);
	}
	else if (type == DOOR_TYPE_6)
	{
		animations->Get(ID_ANI_DOOR_6)->Render(x, y);
	}
	else
	{
		animations->Get(ID_ANI_YELLOW_NODE)->Render(x, y);
	}
	
	RenderBoundingBox();
}