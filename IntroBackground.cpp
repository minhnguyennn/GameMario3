#include "IntroBackGround.h"
#include "Game.h"
#include "debug.h"
#include "IntroScene.h"
#include "CurTain.h"
#include "WorldScene.h"
#include "Leaf.h"
#include "Mario.h"
#include "IntroSummonObject.h"
#include "Goomba.h"
#include "MushRoom.h"
#include "IntroKoopa.h"
#include "IntroGoomba.h"
#include "IntroLeaf.h"

void CIntroBackGround::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	if (isSummon && GetTickCount64() - time_change_summon > 500)
	{
		LPINTROSCENE scene = (LPINTROSCENE)CGame::GetInstance()->GetCurrentScene();

		CIntroKoopa* koopa = new CIntroKoopa(x, y - 100, 1, 2);
		scene->CreateObject(koopa);
		koopa->SetState(KOOPA_STATE_CLOSE_SHELL);

		CIntroKoopa* koopa_2 = new CIntroKoopa(x + 40, y - 100, 1, 2);
		scene->CreateObject(koopa_2);
		koopa_2->SetState(KOOPA_STATE_CLOSE_SHELL);

		CIntroGoomba* goomba = new CIntroGoomba(x - 86, y - 100, 1, 1);
		scene->CreateObject(goomba);

		CIntroLeaf* leaf = new CIntroLeaf(x , y - 50);
		scene->CreateObject(leaf);

		isSummon = false;
	}
	if (isScene1 && GetTickCount64() - time_change_scene > 1000)
	{
		isScene1 = false;
		isScene2 = true;
		time_change_scene = GetTickCount64();
		SummonCurtain();
	}
	else if (isScene2 && GetTickCount64() - time_change_scene > TIME_BACKGROUND_CHANGE_SCENE_2)
	{
		isScene2 = false;
		time_change_scene = 0;
		time_change_summon = GetTickCount64();
		isSummon = true;
	} 
	
	if (isWorldScene && GetTickCount64() - time_change_scene > TIME_BACKGROUND_CHANGE_SCENE_3)
	{
		isWorldScene = false;
		CGame::GetInstance()->InitiateSwitchScene(DATA_ID_WORLD_SCENE);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
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
		animations->Get(ID_ANI_INTRO_BACKGROUND_NUMBER_THREE)->Render(x + 4, y + 4);
		if (!isKeyUp)
		{
			if (isWorldScene) animations->Get(ID_ANI_INTRO_BACKGROUND_ARROW_2)->Render(x - 55, y + 36);
			else animations->Get(ID_ANI_INTRO_BACKGROUND_ARROW)->Render(x - 55, y + 36);
		}
		else
		{
			if (isWorldScene) animations->Get(ID_ANI_INTRO_BACKGROUND_ARROW_2)->Render(x - 55, y + 52);
			else animations->Get(ID_ANI_INTRO_BACKGROUND_ARROW)->Render(x - 55, y + 52);
		}
	}
	RenderBoundingBox();
}

void CIntroBackGround::SetState(int state) {
	switch (state)
	{
	case INTRO_BACKGROUND_STATE_ARROW_UP:
	{
		LPINTROSCENE scene = (LPINTROSCENE)CGame::GetInstance()->GetCurrentScene();
		CGoomba* goomba = new CGoomba(x - 40, y - 100, 1, 1);
		scene->CreateObject(goomba);
		break;
	}
	case INTRO_BACKGROUND_STATE_ARROW_DOWN:
	{
		isWorldScene = true;
		time_change_scene = GetTickCount64();
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

	CIntroSummonObject* summon = new CIntroSummonObject(x, y);
	scene->CreateObject(summon);
	summon->SummonMario();
}

void CIntroBackGround::SummonObject()
{
	LPINTROSCENE scene = (LPINTROSCENE)CGame::GetInstance()->GetCurrentScene();
	CLeaf* leaf = new CLeaf(x + 20, y - 100);
	scene->CreateObject(leaf);

	/*CKoopa* koopa = new CKoopa(x + 100, y + 100, 1, 2);
	scene->CreateObject(koopa);
	koopa->SetState(KOOPA_STATE_CLOSE_SHELL);*/


	CIntroKoopa* koopa = new CIntroKoopa(x + 40, y - 100, 1, 2);
	scene->CreateObject(koopa);
	koopa->SetState(KOOPA_STATE_CLOSE_SHELL);

	CGoomba* goomba = new CGoomba(x - 40, y - 100, 1, 1);
	scene->CreateObject(goomba);

	CMushRoom* mush_room_red = new CMushRoom(x - 40, y - 100, 1);
	scene->CreateObject(mush_room_red);

	CMushRoom* mush_room_green = new CMushRoom(x + 40, y - 100, 2);
	scene->CreateObject(mush_room_green);
}