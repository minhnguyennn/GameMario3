#include "MarioWorld.h"

CMarioWorld::CMarioWorld(float x, float y) :CGameObject(x, y)
{
	
}

void CMarioWorld::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMarioWorld::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_SMALL_MARIO_WORLD)->Render(x, y);
	RenderBoundingBox();
}

void CMarioWorld::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MARIO_WORLD_SMALL_BBOX_WIDTH / 2;
	t = y - MARIO_WORLD_SMALL_BBOX_HEIGHT / 2;
	r = l + MARIO_WORLD_SMALL_BBOX_WIDTH;
	b = t + MARIO_WORLD_SMALL_BBOX_HEIGHT;
}

void CMarioWorld::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CMarioWorld::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->nx != 0 && e->obj->IsBlocking()) 
	{
		vx = 0;
	}
}

void CMarioWorld::SetState(int state)
{

	switch (state)
	{

	case MARIO_WORLD_STATE_UP:
		vy = -0.1f;
		vx = 0;
		break;
	case MARIO_WORLD_STATE_DOWN:
		vy = 0.1f;
		vx = 0;
		break;
	case MARIO_WORLD_STATE_RIGHT:
		vy = 0;
		vx = 0.1f;
		break;
	case MARIO_WORLD_STATE_LEFT:
		vy = 0;
		vx = -0.1f;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}
