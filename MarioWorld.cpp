#include "MarioWorld.h"

CMarioWorld::CMarioWorld(float x, float y) :CGameObject(x, y)
{
	
}

void CMarioWorld::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMarioWorld::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	//animations->Get(ID_ANI_TAIL)->Render(x, y);
	RenderBoundingBox();
}

void CMarioWorld::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	/*l = x - TAIL_BBOX_WIDTH / 2;
	t = y - TAIL_BBOX_HEIGHT / 2;
	r = l + TAIL_BBOX_WIDTH;
	b = t + TAIL_BBOX_HEIGHT;*/
}

void CMarioWorld::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CMarioWorld::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}


void CMarioWorld::SetState(int state)
{

	switch (state)
	{
	
	default:
		break;
	}
	CGameObject::SetState(state);
}
