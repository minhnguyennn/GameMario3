#include "CurTain.h"
#include "debug.h"

CCurTain::CCurTain(float x, float y) : CGameObject(x, y)
{
	isLogo = false;
	isCurTain = true;
	isStop = false;

	vy = -CURTAIN_VY;
	time_curtain_up = GetTickCount64();
	time_logo_down = 0;
	this->isVibrate = false;
	this->random = 0;
	this->time_vibrate = 0;
}

void CCurTain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isCurTain && GetTickCount64() - time_curtain_up > TIME_CURTAIN_UP)
	{
		isCurTain = false;
		isLogo = true;
		time_logo_down = GetTickCount64();
		vy = CURTAIN_VY;
	}
	
	if (isLogo && GetTickCount64() - time_logo_down > CURTAIN_TIME_1800)
	{
		isLogo = false;
		isVibrate = true;
		time_vibrate = GetTickCount64();
		vy = 0.0f;
	}

	if (isVibrate)
	{
		random = rand() % CURTAIN_SUM_RANDOM;
	}

	if (isVibrate && GetTickCount64() - time_vibrate > CURTAIN_TIME_1000)
	{
		isVibrate = false;
		isStop = true;
		time_vibrate = GetTickCount64();
	}

	if (isStop && GetTickCount64() - time_vibrate > CURTAIN_TIME_1000)
	{
		isStop = false;
		isDeleted = true;
		return;
	}

	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCurTain::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	
	if (isLogo || isStop)
	{
		animations->Get(ID_ANI_LOGO)->Render(x, y);		
	}
	else if (isVibrate)
	{
		if (random == CURTAIN_NUMBER_RANDOM_0)
			animations->Get(ID_ANI_LOGO)->Render(x, y);
		else if (random == CURTAIN_NUMBER_RANDOM_1)
			animations->Get(ID_ANI_LOGO)->Render(x, y - CURTAIN_ADJUST_Y);
	}
	else animations->Get(ID_ANI_CURTAIN)->Render(x, y);
	
	//RenderBoundingBox();
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