#include "IntroBackGround.h"
#include "Game.h"
#include "debug.h"

void CIntroBackGround::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{

}

void CIntroBackGround::Render() 
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_INTRO_BACKGROUND)->Render(x, y);
	RenderBoundingBox();
}

void CIntroBackGround::SetState(int state) {
	switch (state)
	{
	default:
		break;
	}
	CGameObject::SetState(state);
}