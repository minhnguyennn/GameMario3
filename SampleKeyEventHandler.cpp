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
	case DIK_A:

		if (mario->GetLevel() == MARIO_LEVEL_FIRE)
		{
			mario->SummonFireBalls();
		}
		else if (mario->GetLevel() == MARIO_LEVEL_RACCOON)
		{
			mario->SetState(MARIO_STATE_ATTACK);
			mario->SummonTail();
		}
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		if (mario->IsMaxPower())
		{
			mario->SetState(MARIO_STATE_FLYING);
		}
		if (mario->GetIsRunning() && mario->GetPower() > 6)
		{			
			mario->SetState(MARIO_STATE_FLYING);
		}
		else if (mario->GetVY() > 0)
		{
			mario->SetState(MARIO_STATE_FALL_SLOWLY);
		}
		else
		{
			mario->SetState(MARIO_STATE_JUMP);
		}
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
	case DIK_6:
		mario->SetPosition(16, 300);		
		break;
	case DIK_7:
		mario->SetPosition(2682, 383);
		break;
	case DIK_9:
		mario->SetPosition(3340, 0); // To Hidden Map
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
	case DIK_A:
		mario->SetState(MARIO_STATE_RELEASE_HOLDING);
		if (!mario->GetIsHolding())
		{
			mario->MarioThrowKoopaFunction();
		}
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		/*if (mario->GetIsFlying()) 
		{
			mario->SetState(MARIO_STATE_RELEASE_FLYING);
		}
		else
		{
			mario->SetState(MARIO_STATE_RELEASE_JUMP);
		}*/
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

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			if (mario->GetIsOnPlatform())
			{
				mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			}
		}
		else
		{
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		}
		else
		{
			mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
	}
	else 
	{
		if (mario->GetVX())
		{
			mario->SetState(MARIO_STATE_DECELERATION);
		}
		else
		{
			mario->SetState(MARIO_STATE_IDLE);
		}
	}
}