#include "KoopaWorld.h"

CKoopaWorld::CKoopaWorld(float x, float y) : CGameObject(x, y)
{
	vx = 0.03f;
	position_start = x;
}

void CKoopaWorld::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	if (vx > 0 && x - position_start > 28)
	{
		vx = -vx;
		position_start = x;
	}

	if (vx < 0 &&  position_start - x> 26)
	{
		vx = -vx;
		position_start = x;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopaWorld::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniID = 0;
	if (vx > 0)
	{
		aniID = ID_ANI_KOOPA_WORLD_RIGHT;
	}
	else
	{
		aniID = ID_ANI_KOOPA_WORLD_LEFT;
	}
	animations->Get(aniID)->Render(x, y);
	RenderBoundingBox();
}

void CKoopaWorld::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MARIO_WORLD_SMALL_BBOX_WIDTH / 2;
	t = y - MARIO_WORLD_SMALL_BBOX_HEIGHT / 2;
	r = l + MARIO_WORLD_SMALL_BBOX_WIDTH;
	b = t + MARIO_WORLD_SMALL_BBOX_HEIGHT;
}

void CKoopaWorld::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CKoopaWorld::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CKoopaWorld::SetState(int state)
{

	/*switch (state)
	{

	default:
		break;
	}*/
	CGameObject::SetState(state);
}
