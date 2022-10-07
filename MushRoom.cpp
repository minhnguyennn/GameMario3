#include "MushRoom.h"

CMushRoom::CMushRoom(float x, float y) :CGameObject(x, y)
{
	start_y = y;
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	die_start = -1;
	SetState(MUSHROOM_STATE_UP);
}

void CMushRoom::SetState(int state)
{
	
	switch (state)
	{
	case MUSHROOM_STATE_UP:
		vy = -MUSHROOM_UP_SPEED;
		break;
	case MUSHROOM_STATE_WALKING:
		ay = MUSHROOM_GRAVITY;
		vx = MUSHROOM_WALKING_SPEED;
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
	if(state != MUSHROOM_STATE_UP) vy += ay * dt;

	if ((abs(y-start_y) > DISTANCE_MAX)) {
		SetState(MUSHROOM_STATE_WALKING);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushRoom::Render()
{
	int aniId = ID_ANI_MUSHROOM_RED;
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

