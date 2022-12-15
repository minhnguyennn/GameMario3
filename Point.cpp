#include "Point.h"
#include "debug.h"


void CPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	if (!checkObjectInCamera()) return;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPoint::Render()
{
	if (!checkObjectInCamera()) return;
	CAnimations* animations = CAnimations::GetInstance();
	if (POINT_TYPE_100) 
	{
		animations->Get(ID_ANI_100_POINT)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CPoint::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - POINT_BBOX_WIDTH / 2;
	t = y - POINT_BBOX_HEIGHT / 2;
	r = l + POINT_BBOX_WIDTH;
	b = t + POINT_BBOX_HEIGHT;
}

void CPoint::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CPoint::SetState(int state)
{
	switch (state)
	{
	case POINT_STATE_MOVE_DOWN:
		vy = POINT_MOVE_SPEED;
		break;
	case POINT_STATE_MOVE_UP:
		vy = -POINT_MOVE_SPEED;
		break;
	case POINT_STATE_IDLE:
		vy = 0;
		break;
	case POINT_STATE_ADD_100:
		AdditionPoint();
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CPoint::AdditionPoint() 
{
	number_point = number_point + 100;
	//DebugOutTitle(L"Point: %d", number_point);
}


