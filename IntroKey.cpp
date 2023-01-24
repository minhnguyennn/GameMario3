#include "IntroKey.h"
#include "debug.h"
#include "AssetIDs.h"
#include "IntroScene.h"
#include "IntroBackGround.h"
void CIntroKey::OnKeyDown(int KeyCode)
{
	CIntroBackGround* player = (CIntroBackGround*)((LPINTROSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	default:
		break;
	}
}