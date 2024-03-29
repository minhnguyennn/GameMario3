#include "WorldKeyEvent.h"
#include "debug.h"
#include "Game.h"
#include "MarioWorld.h"
#include "WorldScene.h"
#include "debug.h"
#include "Data.h"

void CWorldKeyEvent::OnKeyDown(int KeyCode)
{
	////DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMarioWorld* mario_world = (CMarioWorld*)((LPWORLDSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (!mario_world->GetIsDelay()) return;
	switch (KeyCode)
	{
	case DIK_W:
		if (!mario_world->GetIsRedArrow() && CData::GetInstance()->GetMarioHeart() < 1)
		{
			mario_world->SetState(MARIO_WORLD_STATE_GO_PLAYSCENE_RESET);
		}
		else if (CData::GetInstance()->GetMarioHeart() < 1)
		{
			mario_world->SetState(MARIO_WORLD_STATE_GO_INTRO_SCENE);
		}
		break;
	case DIK_S:
		if (mario_world->GetIsCollisionDoor()) mario_world->SetState(MARIO_WORLD_STATE_GO_PLAYSCENE);
		break;
	case DIK_UP:
		if (CData::GetInstance()->GetMarioHeart() < 1) mario_world->SetIsRedArrow(false);
		else
		{
			if (!mario_world->GetIsGoTop()) break;
			mario_world->SetState(MARIO_WORLD_STATE_UP);
		}
		break;
	case DIK_DOWN:
		if (CData::GetInstance()->GetMarioHeart() < 1) mario_world->SetIsRedArrow(true);
		else
		{
			if (!mario_world->GetIsGoBottom()) break;
			mario_world->SetState(MARIO_WORLD_STATE_DOWN);
		}
		break;
	case DIK_LEFT:
		if (!mario_world->GetIsGoLeft() || CData::GetInstance()->GetMarioHeart() < 1) break;
		mario_world->SetState(MARIO_WORLD_STATE_LEFT);
		break;
	case DIK_RIGHT:
		if (!mario_world->GetIsGoRight() || CData::GetInstance()->GetMarioHeart() < 1) break;
		mario_world->SetState(MARIO_WORLD_STATE_RIGHT);
		break;
	}
}

void CWorldKeyEvent::OnKeyUp(int KeyCode)
{
	////DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	//CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	//switch (KeyCode)
	//{
	//case DIK_A:
	//	mario->SetIsHolding(false);
	//	mario->SetIsRunning(false);
	//	break;
	//case DIK_S:
	//	if (mario->GetState() == MARIO_STATE_FLYING)
	//	{
	//		mario->SetState(MARIO_STATE_RELEASE_FLYING);
	//	}
	//	else
	//	{
	//		mario->SetState(MARIO_STATE_RELEASE_JUMP);
	//	}
	//	break;
	//case DIK_DOWN:
	//	mario->SetState(MARIO_STATE_SIT_RELEASE);
	//	break;
	//	/*case DIK_LEFT:
	//		mario->SetState(MARIO_STATE_DECELERATION);
	//		break;
	//	case DIK_RIGHT:
	//		mario->SetState(MARIO_STATE_DECELERATION);
	//		break;*/
	//}
}

void CWorldKeyEvent::KeyState(BYTE* states)
{
	//LPGAME game = CGame::GetInstance();
	//CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	//if (game->IsKeyDown(DIK_RIGHT))
	//{
	//	if (game->IsKeyDown(DIK_A))
	//	{
	//		mario->SetState(MARIO_STATE_RUNNING_RIGHT);
	//	}
	//	/*else if (game->IsKeyDown(DIK_DOWN))
	//	{
	//		mario->SetState(MARIO_STATE_SIT);
	//	}*/
	//	else
	//	{
	//		mario->SetState(MARIO_STATE_WALKING_RIGHT);
	//	}
	//}
	//else if (game->IsKeyDown(DIK_LEFT))
	//{
	//	if (game->IsKeyDown(DIK_A))
	//	{
	//		mario->SetState(MARIO_STATE_RUNNING_LEFT);
	//	}
	//	/*	else if (game->IsKeyDown(DIK_DOWN))
	//		{
	//			mario->SetState(MARIO_STATE_SIT);
	//		}*/
	//	else
	//	{
	//		mario->SetState(MARIO_STATE_WALKING_LEFT);
	//	}
	//}
	//else
	//{
	//	mario->SetState(MARIO_STATE_IDLE);
	//	/*if (!mario->GetVX())
	//	{
	//		mario->SetState(MARIO_STATE_IDLE);
	//	}
	//	else
	//	{
	//		mario->SetState(MARIO_STATE_DECELERATION);
	//	}*/
	//}


}