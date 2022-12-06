#include "Door.h"
void CDoor::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
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
	else
	{
		animations->Get(ID_ANI_DOOR_6)->Render(x, y);
	}
	RenderBoundingBox();
}