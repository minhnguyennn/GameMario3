#include "Point.h"
#include "debug.h"


void CPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	/*DebugOut(L"[TEST] y of coin: %d\n", y);
	if ((start_y - y) > 70)
	{
		SetState(COIN_STATE_MOVE_DOWN);
	}
	if ((vy > 0) && (y > start_y - 50))
	{
		SetState(COIN_STATE_DELETE);
	}*/
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPoint::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (POINT_TYPE_100) {
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
		vy = +0.07;
		break;
	case POINT_STATE_MOVE_UP:
		vy = -0.07f;
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

void CPoint::AdditionPoint() {
	number_point = number_point + 100;
	DebugOutTitle(L"Point: %d", number_point);
}

