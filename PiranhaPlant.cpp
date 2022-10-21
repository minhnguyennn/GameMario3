#include "PiranhaPlant.h"
#include"debug.h"
#include "Time.h"

CPiranhaPlant::CPiranhaPlant(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = PPLANT_GRAVITY;
	this->start_y = y;
	this->check_state = false;
	SetState(PPLANT_STATE_UP);
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
	if ((start_y - y) > PPLANT_DISTANCE_MAX) {
		if (check_state == false) {
			SetState(PPLANT_STATE_IDLE);
			check_state = true;
		}
		ChangeStateMotion();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranhaPlant::Render()
{
	int aniId = ID_ANI_PPLANT_MOVING_UP_LEFT;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CPiranhaPlant::SetState(int state)
{
	switch (state)
	{
	case PPLANT_STATE_IDLE:
		vy = 0;
		ay = 0;
		time_line = GetTickCount64();
		break;
	case PPLANT_STATE_UP:
		vy = -PPLANT_MOVING_SPEED;
		ay = -PPLANT_GRAVITY;
		break;
	case PPLANT_STATE_DOWN:
		vy = PPLANT_MOVING_SPEED;
		ay = PPLANT_GRAVITY;
		time_line = GetTickCount64();
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CPiranhaPlant::ChangeStateMotion() {

	if ((GetTickCount64() - time_line) > PPLANT_WAITING_MAX) {
		SetState(PPLANT_STATE_DOWN);
	}
}

