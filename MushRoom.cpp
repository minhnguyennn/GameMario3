#include "MushRoom.h"
#include"debug.h"



CMushRoom::CMushRoom(float x, float y, int type_mushroom) :CGameObject(x, y)
{
	start_y = y;
	//this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	this->type_mushroom = type_mushroom;
	die_start = -1;
	check = false;
	countDebug = 0;
	//SetState(MUSHROOM_STATE_UP);
}

void CMushRoom::SetState(int state)
{
	switch (state)
	{
	case MUSHROOM_STATE_IDLE:
		ay = 0;
		vx = 0;
		vy = 0;
		count_time_change = GetTickCount64();
		break;
	case MUSHROOM_STATE_UP:
		vy = -MUSHROOM_UP_SPEED;
		break;
	case MUSHROOM_STATE_WALKING:
		ay = MUSHROOM_GRAVITY;
		vx = MUSHROOM_WALKING_SPEED;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CMushRoom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_BBOX_WIDTH / 2;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH;
	b = t + MUSHROOM_BBOX_HEIGHT;
}

void CMushRoom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!checkObjectInCamera()) return;
	if(state != MUSHROOM_STATE_UP) vy += ay * dt;

	if ((start_y - y) > DISTANCE_MAX_MUSHROOM) 
	{
		if (!check) {
			SetState(MUSHROOM_STATE_IDLE);
			check = true;
		}
		else
		{
			SetState(MUSHROOM_STATE_WALKING);
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushRoom::Render()
{
	if (!checkObjectInCamera()) return;
	int aniId = ID_ANI_MUSHROOM_GREEN;
	if (type_mushroom == MUSHROOM_TYPE_RED) {
		aniId = ID_ANI_MUSHROOM_RED;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CMushRoom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushRoom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMushRoom*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CMushRoom::ChangeStateWalking() {
	if ((GetTickCount64() - count_time_change > TIME_HALF_SECOND)) {
		SetState(MUSHROOM_STATE_WALKING);
	}

}