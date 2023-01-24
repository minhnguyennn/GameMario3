#include "IntroBackGround.h"
#include "Game.h"
#include "debug.h"

void CIntroBackGround::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	DebugOutTitle(L"isup: %d", isKeyUp);
}

void CIntroBackGround::Render() 
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_INTRO_BACKGROUND)->Render(x, y);
	if (!isKeyUp)
	{
		animations->Get(ID_ANI_INTRO_BACKGROUND_ARROW)->Render(x - 55, y + 55);
	}
	else
	{
		animations->Get(ID_ANI_INTRO_BACKGROUND_ARROW)->Render(x - 55, y + 71);
	}
}

void CIntroBackGround::SetState(int state) {
	switch (state)
	{
	case INTRO_BACKGROUND_STATE_ARROW_UP:
		DebugOut(L"oke");
		break;
	case INTRO_BACKGROUND_STATE_ARROW_DOWN:
		isKeyUp = false;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}