#include "SampleKeyEventHandler.h"
#include "debug.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	if (mario->GetDisableKey()) return;
	switch (KeyCode)
	{
	case DIK_A:

		if (!mario->GetIsRunning() && mario->GetIsOnPlatform() && mario->GetLevel() == MARIO_LEVEL_FIRE)
		{
			mario->SummonFireBalls();
		}
		else if (mario->GetLevel() == MARIO_LEVEL_RACCOON)
		{
			mario->SetState(MARIO_STATE_ATTACK);
		}
		break;
	case DIK_DOWN:
	{
		if (mario->GetLevel() == MARIO_LEVEL_RACCOON && mario->GetIsCollisionPipeline()) 
			mario->SetState(MARIO_STATE_GO_DOWN);
		else 
			mario->SetState(MARIO_STATE_SIT);
		break;
	}
	case DIK_S:
	{
		if (mario->IsMaxPower() && mario->GetLevel() == MARIO_LEVEL_RACCOON) mario->SetState(MARIO_STATE_FLYING);
		else if (mario->GetVY() > 0) mario->SetState(MARIO_STATE_FALL_SLOWLY);
		else mario->SetState(MARIO_STATE_JUMP);
		break;
	}
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
	case DIK_6:
		mario->SetPosition(POSITION_BEGIN_MAP_X, POSITION_BEGIN_MAP_Y);
		break;
	case DIK_7:
		mario->SetPosition(POSITION_MIDDLE_MAP_X, POSITION_MIDDLE_MAP_Y);
		break;
	case DIK_8:
		mario->SetPosition(POSITION_END_MAP_X, POSITION_END_MAP_Y);
		break;
	case DIK_9:
		mario->SetPosition(POSITION_HIDDEN_MAP_X, POSITION_HIDDEN_MAP_Y); // To Hidden Map
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
	if (mario->GetDisableKey()) return;

	switch (KeyCode)
	{
	case DIK_A:
		//if (mario->GetIsFlying()) break;
		if (mario->GetIsHolding())
		{
			mario->SetState(MARIO_STATE_RELEASE_HOLDING);
			mario->MarioThrowKoopaFunction();
		}
		else if (mario->GetIsRunning())
		{
			mario->SetIsRunning(false);
		}
		break;
	case DIK_S:
		if(mario->GetIsFlying()) mario->SetState(MARIO_STATE_RELEASE_FLYING);
		else mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetDisableKey()) return;
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A)) mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A)) mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		if (game->IsKeyDown(DIK_S) && mario->GetIsCollisionPipeline()) mario->SetState(MARIO_STATE_GO_UP);
	}
	else 
	{
		if (mario->GetVX()) mario->SetState(MARIO_STATE_DECELERATION);
		else mario->SetState(MARIO_STATE_IDLE);
	}
}