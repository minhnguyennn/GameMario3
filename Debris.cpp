#include "Debris.h"
#include "debug.h"

void CDebris::Render()
{
	if (!checkObjectInCamera()) return;
	int aniId = ID_ANI_DEBRIS;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CDebris::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!checkObjectInCamera()) return;
	vy += ay * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void  CDebris::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CDebris::SetState(int state)
{
	switch(state)
	{
	case DEBRIS_LEFT:
	{
		vx = -DEBRIS_VX;
		vy = -DEBRIS_VY;
		break;
	}
	case DEBRIS_RIGHT:
	{
		vx = DEBRIS_VX;
		vy = -DEBRIS_VY;
		break;
	}
	default:
		break;
	}
	CGameObject::SetState(state);
}