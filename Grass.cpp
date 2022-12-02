#include "Grass.h"

CGrass::CGrass(float x, float y) : CGameObject(x, y)
{

}

void CGrass::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGrass::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_GRASS)->Render(x, y);
	RenderBoundingBox();
}

void CGrass::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MARIO_WORLD_SMALL_BBOX_WIDTH / 2;
	t = y - MARIO_WORLD_SMALL_BBOX_HEIGHT / 2;
	r = l + MARIO_WORLD_SMALL_BBOX_WIDTH;
	b = t + MARIO_WORLD_SMALL_BBOX_HEIGHT;
}

void CGrass::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CGrass::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CGrass::SetState(int state)
{

	/*switch (state)
	{

	default:
		break;
	}*/
	CGameObject::SetState(state);
}
