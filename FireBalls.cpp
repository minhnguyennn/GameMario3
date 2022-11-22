#include "FireBalls.h"
#include "debug.h"
#include "PlayScene.h"
#include "Mario.h"
#include "Pipeline.h"

CFireBalls::CFireBalls(float x, float y) :CGameObject(x, y)
{
	//this->ay = FIREBALLS_GRAVITY;
	//this->start_x = x;
	//SetState(FIREBALLS_STATE_MOVE_RIGHT);
}

void CFireBalls::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	//vy += ay * dt;
	// 
	//DebugOut(L"[TEST] start_x: %d\n", x);
	//if (vy < 0) {
	//	if ((x - start_x) > FIREBALLS_DISTANCE_MAX_UP) {
	//		//DebugOut(L"[OK1] \n");
	//		start_x = 0;
	//		SetState(FIREBALLS_STATE_DOWN);
	//	}
	//}

	//if (vy > 0) {
	//	if ((x - start_x) > FIREBALLS_DISTANCE_MAX_UP) {
	//		//DebugOut(L"[OK1] \n");
	//		start_x = 0;
	//		SetState(FIREBALLS_STATE_UP);
	//	}
	//}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFireBalls::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FIREBALLS)->Render(x, y);
	//RenderBoundingBox();
}

void CFireBalls::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIREBALLS_BBOX_WIDTH / 2;
	t = y - FIREBALLS_BBOX_HEIGHT / 2;
	r = l + FIREBALLS_BBOX_WIDTH;
	b = t + FIREBALLS_BBOX_HEIGHT;
}

void CFireBalls::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CFireBalls::SetState(int state)
{
	
	switch (state)
	{
	case FIREBALLS_STATE_DELETE:
	{
		Delete();
		break;
	}
	case FIREBALLS_STATE_RIGHT_BOTTOM:
	{
		vx = FIREBALLS_SPEED_X;
		vy = 0.03f;
		break;
	}
	case FIREBALLS_STATE_LEFT_BOTTOM:
	{
		vx = -FIREBALLS_SPEED_X;
		vy = 0.03f;
		break;
	}
	case FIREBALLS_STATE_MOVE_RIGHT:
	{
		vx = FIREBALLS_SPEED_X;
		vy = 0.01f;
		break;
	}
	case FIREBALLS_STATE_MOVE_LEFT:
	{
		vx = -FIREBALLS_SPEED_X;
		vy = 0.01f;
		break;
	}
	case FIREBALLS_STATE_MOVE_RIGHT_TOP:
	{
		vx = FIREBALLS_SPEED_X;
		vy = -FIREBALLS_SPEED_Y;
		break;
	}
	case FIREBALLS_STATE_MOVE_LEFT_TOP:
	{
		vx = -FIREBALLS_SPEED_X;
		vy = -FIREBALLS_SPEED_Y;
		break;
	}
	default:
		break;
	}
	CGameObject::SetState(state);
}


