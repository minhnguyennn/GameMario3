#include "KoopaWorld.h"

CKoopaWorld::CKoopaWorld(float x, float y) : CGameObject(x, y)
{
	vx = 0.03f;
	time_line = GetTickCount64();
}

void CKoopaWorld::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	if (GetTickCount64() - time_line > KOOPA_WORLD_WALKING_TIMEOUT)
	{
		time_line = GetTickCount64();
		vx = -vx;
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
