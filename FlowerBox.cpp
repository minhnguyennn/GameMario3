#include "FlowerBox.h"
#include "Point.h"
#include "debug.h"
#include "PlayScene.h"


void CFlowerBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFlowerBox::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = 0;
	if (isUp)
	{
		aniId = ID_ANI_FLOWER_BOX_UP;
	}
	else
	{
		aniId = ID_ANI_FLOWER_BOX;
	}
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CFlowerBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FLOWER_BOX_BBOX_WIDTH / 2;
	t = y - FLOWER_BOX_BBOX_HEIGHT / 2;
	r = l + FLOWER_BOX_BBOX_WIDTH;
	b = t + FLOWER_BOX_BBOX_HEIGHT;
}

void CFlowerBox::OnNoCollision(DWORD dt) 
{
	x += vx * dt;
	y += vy * dt;
}

void CFlowerBox::SetState(int state)
{
	switch (state)
	{
	case FLOWER_BOX_STATE_UP:
		vy = -FLOWER_BOX_SPEED_Y;
		isUp = true;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}