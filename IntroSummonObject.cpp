#include "IntroSummonObject.h"
#include "IntroScene.h"
#include "Mario.h"

CIntroSummonObject::CIntroSummonObject(float x, float y) : CGameObject(x, y)
{
	this->time_mario_jump = GetTickCount64();
	this->isMarioJump = false;
}

void CIntroSummonObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CIntroSummonObject::Render()
{

	//RenderBoundingBox();
}

void CIntroSummonObject::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CIntroSummonObject::SetState(int state) 
{
	switch (state)
	{
	case INTRO_SUMMON_STATE_MARIO:
	{
		LPINTROSCENE scene = (LPINTROSCENE)CGame::GetInstance()->GetCurrentScene();
		CMario* mario_green = new CMario(x - 120, y + 56);
		scene->CreateObject(mario_green);
		mario_green->SetState(MARIO_STATE_WALKING_RIGHT);
		mario_green->SetIsMarioGreen(true);
	}
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CIntroSummonObject::SummonMario()
{
	LPINTROSCENE scene = (LPINTROSCENE)CGame::GetInstance()->GetCurrentScene();

	CMario* mario = new CMario(x + 120, y + 56);
	scene->CreateObject(mario);
	mario->SetChangeLevel(MARIO_LEVEL_BIG);
	mario->SetState(MARIO_STATE_AUTO_WALK_LEFT);
	
	CMario* mario_green = new CMario(x - 120, y + 56);
	scene->CreateObject(mario_green);
	mario_green->SetState(MARIO_STATE_WALKING_RIGHT);
	mario_green->SetIsMarioGreen(true);
	mario_green->SetState(MARIO_STATE_AUTO_JUMP);
}