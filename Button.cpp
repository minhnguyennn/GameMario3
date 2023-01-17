#include "Button.h"
#include "debug.h"
#include "PlayScene.h"
#include "Game.h"
#include "Brick.h"

void CButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!checkObjectInCamera()) return;
	if ((start_y - y) > BUTTON_DISTANCE_UP)
	{
		SetState(BUTTON_STATE_IDLE);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CButton::Render()
{
	if (!checkObjectInCamera()) return;
	int aniId = 0;
	if (isPressed)
		aniId = ID_ANI_BUTTON_PRESSED;
	else
		aniId = ID_ANI_BUTTON;
	if (isPressed)
		CAnimations::GetInstance()->Get(aniId)->Render(x, y + BUTTON_PRESSED_Y_ADJUST);
	else
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isPressed)
	{
		l = x - BUTTON_BBOX_PRESSED_WIDTH / 2;
		t = y - BUTTON_BBOX_PRESSED_HEIGHT / 2;
		r = l + BUTTON_BBOX_PRESSED_WIDTH;
		b = t + BUTTON_BBOX_PRESSED_HEIGHT;
	}
	else
	{
		l = x - BUTTON_BBOX_WIDTH / 2;
		t = y - BUTTON_BBOX_HEIGHT / 2;
		r = l + BUTTON_BBOX_WIDTH;
		b = t + BUTTON_BBOX_HEIGHT;
	}
}

void CButton::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CButton::SetState(int state)
{
	switch (state)
	{
	case BUTTON_STATE_IDLE:
		vy = 0;
		break;
	case BUTTON_STATE_MOVE_UP:
	{
		vy = -BUTTON_MAX_VY;
		break;
	}
	default:
		break;
	}
	CGameObject::SetState(state);
}
