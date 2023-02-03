#include "IntroKey.h"
#include "debug.h"
#include "AssetIDs.h"
#include "IntroScene.h"
#include "IntroBackGround.h"
#include "Data.h"

void CIntroKey::OnKeyDown(int KeyCode)
{
	CIntroBackGround* player_intro = (CIntroBackGround*)((LPINTROSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_Q:
		if (player_intro->GetIsKeyUp()) player_intro->SetIsKeyUp(false);
		else player_intro->SetIsKeyUp(true);
		break;
	case DIK_W:
		player_intro->SetState(INTRO_BACKGROUND_STATE_GO_WORLD_MAP);
		CData::GetInstance()->ResetGame();
		break;
	default:
		break;
	}
}