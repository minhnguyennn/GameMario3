#include "PiranhaPlant.h"
#include"debug.h"
#include "Time.h"

CPiranhaPlant::CPiranhaPlant(float x, float y) :CGameObject(x, y)
{
	this->ay = PPLANT_GRAVITY;
	this->start_y = y;
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

void CPiranhaPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPiranhaPlant*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	//DebugOut(L"[STATE] STATE: %d\n",state);
	//
	if ((start_y - y) > PPLANT_DISTANCE_MAX_UP) {
		//DebugOut(L"[OK1] \n");
		if (state == PPLANT_STATE_UP) {
			SetState(PPLANT_STATE_IDLE);
		}
		else if (state == PPLANT_STATE_IDLE) {
			ChangeStateMotionDown();
		}
	}

	if ((y - start_y) > PPLANT_DISTANCE_MAX_DOWN) {
		//DebugOut(L"[OKE2]\n");
		if (state == PPLANT_STATE_DOWN) {
			SetState(PPLANT_STATE_IDLE);
		}
		else if (state == PPLANT_STATE_IDLE) {
			ChangeStateMotionUp();
		}
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
	case PPLANT_STATE_UP:
		vy = -PPLANT_MOVING_SPEED;
		ay = -PPLANT_GRAVITY;
		break;
	case PPLANT_STATE_DOWN:
		vy = PPLANT_MOVING_SPEED;
		ay = PPLANT_GRAVITY;
		break;
	case PPLANT_STATE_IDLE:
		vy = 0;
		ay = 0;
		time_line = GetTickCount64();
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CPiranhaPlant::ChangeStateMotionDown() {
	if ((GetTickCount64() - time_line) > PPLANT_WAITING_MAX) {
		SetState(PPLANT_STATE_DOWN);
	}
}

void CPiranhaPlant::ChangeStateMotionUp() {
	if ((GetTickCount64() - time_line) > PPLANT_WAITING_MAX) {
		SetState(PPLANT_STATE_UP);
	}
}

