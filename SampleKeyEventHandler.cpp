#include "SampleKeyEventHandler.h"
#include "debug.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	switch (KeyCode)
	{
	case DIK_D:
		mario->SetState(MARIO_STATE_FLYING);
		break;
	case DIK_A:
		if(mario->GetLevel()==MARIO_LEVEL_FIRE) mario->SummonFireBalls();
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_FIRE);
		break;
	case DIK_4:
		mario->SetLevel(MARIO_LEVEL_RACCOON);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_D:
		mario->SetState(MARIO_STATE_RELEASE_FLYING);
		break;
	case DIK_A:
		mario->SetIsHolding(false);
		mario->SetIsRunning(false);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_LEFT:
		mario->SetState(MARIO_STATE_DECELERATION);
		break;
	case DIK_RIGHT:
		mario->SetState(MARIO_STATE_DECELERATION);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A)) mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else if (game->IsKeyDown(DIK_DOWN)) mario->SetState(MARIO_STATE_SIT);
		else mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A)) mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else if (game->IsKeyDown(DIK_DOWN)) mario->SetState(MARIO_STATE_SIT);
		else mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else {
		if (!mario->GetVX()) {
		
			mario->SetState(MARIO_STATE_IDLE); 
		}
		else { 
			mario->SetState(MARIO_STATE_DECELERATION); 
		}
	}
}