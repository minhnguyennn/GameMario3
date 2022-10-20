#include "PiranhaPlant.h"
#include"debug.h"

CPiranhaPlant::CPiranhaPlant(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = PPLANT_GRAVITY;
	die_start = -1;
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
	x += vx * dt;
	y += vy * dt;
};

void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranhaPlant::Render()
{
	int aniId = ID_ANI_PPLANT_MOVING_UP;
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
		break;
	case PPLANT_STATE_DOWN:
		vy = PPLANT_MOVING_SPEED;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}

