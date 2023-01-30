#include "CurTain.h"

CCurTain::CCurTain(float x, float y) : CGameObject(x, y)
{
	vy = -CURTAIN_VY;
	time_curtain_up = GetTickCount64();
}

void CCurTain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - time_curtain_up > TIME_CURTAIN_UP)
	{
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCurTain::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniID = 0;
	animations->Get(ID_ANI_CURTAIN)->Render(x, y);
	RenderBoundingBox();
}

void CCurTain::OnNoCollision(DWORD dt) 
{
	x += vx * dt;
	y += vy * dt;
}

void CCurTain::SetState(int state) {
	switch (state)
	{
	case CURTAIN_STATE_UP:
		
	default:
		break;
	}
	CGameObject::SetState(state);
}