#include "IntroBackGround.h"
#include "Game.h"
#include "debug.h"
#include "IntroScene.h"
#include "CurTain.h"

void CIntroBackGround::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	if (isScene1 && GetTickCount64() - time_change_scene > TIME_BACKGROUND_CHANGE_SCENE_1)
	{
		isScene1 = false;
		isScene2 = true;
		time_change_scene = GetTickCount64();
		SummonCurtain();
	}

	if (isScene2 && GetTickCount64() - time_change_scene > TIME_BACKGROUND_CHANGE_SCENE_2)
	{
		isScene2 = false;
		time_change_scene = 0;
	}
}

void CIntroBackGround::Render() 
{
	CAnimations* animations = CAnimations::GetInstance();
	if (isScene1)
	{
		animations->Get(ID_ANI_INTRO_BACKGROUND_SCENE_ONE)->Render(x, y);
	}
	else if (isScene2)
	{
		
		animations->Get(ID_ANI_INTRO_BACKGROUND_SCENE_TWO)->Render(x, y);
	}
	else
	{
		animations->Get(ID_ANI_INTRO_BACKGROUND)->Render(x, y);
		animations->Get(ID_ANI_INTRO_BACKGROUND_NUMBER_THREE)->Render(x + 4, y + 6);
		if (!isKeyUp)
		{
			animations->Get(ID_ANI_INTRO_BACKGROUND_ARROW)->Render(x - 55, y + 36);
		}
		else
		{
			animations->Get(ID_ANI_INTRO_BACKGROUND_ARROW)->Render(x - 55, y + 52);
		}
	}
}

void CIntroBackGround::SetState(int state) {
	switch (state)
	{
	case INTRO_BACKGROUND_STATE_ARROW_UP:
		DebugOut(L"oke");
		break;
	case INTRO_BACKGROUND_STATE_ARROW_DOWN:
	{
		LPINTROSCENE scene = (LPINTROSCENE)CGame::GetInstance()->GetCurrentScene();
		CCurTain* curtain = new CCurTain(x, y - 26);
		scene->CreateObject(curtain);
		break;
	}
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CIntroBackGround::SummonCurtain() 
{
	LPINTROSCENE scene = (LPINTROSCENE)CGame::GetInstance()->GetCurrentScene();
	CCurTain* curtain = new CCurTain(x, y - 26);
	scene->CreateObject(curtain);
}