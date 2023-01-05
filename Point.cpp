#include "Point.h"
#include "debug.h"

void CPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	if (!checkObjectInCamera()) return;
	if (GetTickCount64() - time_score_fly > POINT_FLY_TIMEOUT)
	{
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPoint::Render()
{
	if (!checkObjectInCamera()) return;
	CAnimations* animations = CAnimations::GetInstance();
	int AniId = 0;
	if (type_point == POINT_TYPE_100) AniId = ID_ANI_100_SCORE;
	else if (type_point == POINT_TYPE_1000) AniId = ID_ANI_1000_SCORE;
	animations->Get(AniId)->Render(x, y);
	//RenderBoundingBox();
}


void CPoint::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CPoint::SetState(int state)
{
	switch (state)
	{
	case POINT_STATE_MOVE_UP:
		vy = -POINT_MOVE_SPEED;
		time_score_fly = GetTickCount64();
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}