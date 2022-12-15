#include "FlowerBox.h"
#include "Point.h"
#include "debug.h"
#include "PlayScene.h"
#include "Automation.h"


void CFlowerBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!checkObjectInCamera()) return;
	if (isUp && CountDownTimer(FLOWER_BOX_UP_TIMEOUT))
	{
		SetState(FLOWER_BOX_SUMMON_AUTOMATION);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFlowerBox::Render()
{
	if (!checkObjectInCamera()) return;
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
	case FLOWER_BOX_SUMMON_AUTOMATION:
	{
		isUp = false;
		isDeleted = true;
		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		CAutomation* automation = new CAutomation(x, y);
		scene->CreateObject(automation);
		break;
	}
	case FLOWER_BOX_STATE_UP:
		time_line = GetTickCount64();
		vy = -FLOWER_BOX_SPEED_Y;
		isUp = true;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}

bool CFlowerBox::CountDownTimer(int time)
{
	if (GetTickCount64() - time_line > time)
	{
		return true;
	}
	return false;
}

void CFlowerBox::AutomationFunction()
{
	
}