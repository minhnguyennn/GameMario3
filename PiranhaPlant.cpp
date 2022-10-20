#include "PiranhaPlant.h"
#include"debug.h"

CPiranhaPlant::CPiranhaPlant(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = PPLANT_GRAVITY;
	this->start_y = y;
	SetState(PPLANT_STATE_IDLE);
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PPLANT_BBOX_WIDTH / 2;
	top = y - PPLANT_BBOX_HEIGHT / 2;
	right = left + PPLANT_BBOX_WIDTH;
	bottom = top + PPLANT_BBOX_HEIGHT;
}

void CPiranhaPlant::OnNoCollision(DWORD dt)
{
	y += vy * dt;
};

void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	if (state == PPLANT_STATE_IDLE) {
		SetState(PPLANT_STATE_UP);
	}
	if ((start_y - y) > 32) {
		DebugOut(L"[OKE]\n");
		SetState(PPLANT_STATE_IDLE);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranhaPlant::Render()
{
	int aniId = ID_ANI_PPLANT_MOVING_UP_LEFT;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CPiranhaPlant::SetState(int state)
{
	switch (state)
	{
	case PPLANT_STATE_IDLE:
		vy = 0;
		
		break;
	case PPLANT_STATE_UP:
		vy = -PPLANT_MOVING_SPEED;
		ay = -PPLANT_GRAVITY;
		break;
	case PPLANT_STATE_DOWN:
		vy = PPLANT_MOVING_SPEED;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}

