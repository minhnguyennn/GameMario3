#include "VenusFireTrap.h"
#include"debug.h"
#include "Time.h"

CVenusFireTrap::CVenusFireTrap(float x, float y) :CGameObject(x, y)
{
	this->ay = VFTRAP_GRAVITY;
	this->start_y = y;
	SetState(VFTRAP_STATE_UP);
}

void CVenusFireTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - VFTRAP_BBOX_WIDTH / 2;
	top = y - VFTRAP_BBOX_HEIGHT / 2;
	right = left + VFTRAP_BBOX_WIDTH;
	bottom = top + VFTRAP_BBOX_HEIGHT;
}

void CVenusFireTrap::OnNoCollision(DWORD dt)
{
	y += vy * dt;
};

void CVenusFireTrap::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CVenusFireTrap*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	//DebugOut(L"[STATE] STATE: %d\n",state);
	//
	if ((start_y - y) > VFTRAP_DISTANCE_MAX_UP) {
		//DebugOut(L"[OK1] \n");
		if (state == VFTRAP_STATE_UP) {
			SetState(VFTRAP_STATE_IDLE);
		}
		else if (state == VFTRAP_STATE_IDLE) {
			ChangeStateMotionDown();
		}
	}

	if ((y - start_y) > VFTRAP_DISTANCE_MAX_DOWN) {
		//DebugOut(L"[OKE2]\n");
		if (state == VFTRAP_STATE_DOWN) {
			SetState(VFTRAP_STATE_IDLE);
		}
		else if (state == VFTRAP_STATE_IDLE) {
			ChangeStateMotionUp();
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CVenusFireTrap::Render()
{
	int aniId = ID_ANI_VFTRAP_MOVING_UP_LEFT;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CVenusFireTrap::SetState(int state)
{
	switch (state)
	{
	case VFTRAP_STATE_UP:
		vy = -VFTRAP_MOVING_SPEED;
		ay = -VFTRAP_GRAVITY;
		break;
	case VFTRAP_STATE_DOWN:
		vy = VFTRAP_MOVING_SPEED;
		ay = VFTRAP_GRAVITY;
		break;
	case VFTRAP_STATE_IDLE:
		vy = 0;
		ay = 0;
		time_line = GetTickCount64();
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CVenusFireTrap::ChangeStateMotionDown() {
	if ((GetTickCount64() - time_line) > VFTRAP_WAITING_MAX) {
		SetState(VFTRAP_STATE_DOWN);
	}
}

void CVenusFireTrap::ChangeStateMotionUp() {
	if ((GetTickCount64() - time_line) > VFTRAP_WAITING_MAX) {
		SetState(VFTRAP_STATE_UP);
	}
}

