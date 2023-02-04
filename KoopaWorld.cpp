#include "KoopaWorld.h"

CKoopaWorld::CKoopaWorld(float x, float y) : CGameObject(x, y)
{
	vx = KOOPA_WORLD_SPEED;
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
	//RenderBoundingBox();
}

void CKoopaWorld::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}