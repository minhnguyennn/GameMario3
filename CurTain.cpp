#include "CurTain.h"

CCurTain::CCurTain(float x, float y) : CGameObject(x, y)
{
	isLogo = false;
	vy = -CURTAIN_VY;
	time_curtain_up = GetTickCount64();
}

void CCurTain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isLogo && GetTickCount64() - time_curtain_up > TIME_CURTAIN_UP)
	{
		SetState(LOGO_STATE_DOWN);
	}
	else if (isLogo && GetTickCount64() - time_curtain_up > TIME_CURTAIN_UP)
	{
		isLogo = false;
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
	if (isLogo) aniID = ID_ANI_LOGO;
	else aniID = ID_ANI_CURTAIN;
	animations->Get(aniID)->Render(x, y);
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
	case LOGO_STATE_DOWN:
		isLogo = true;
		vy = CURTAIN_VY;
		time_curtain_up = GetTickCount64();
	default:
		break;
	}
	CGameObject::SetState(state);
}