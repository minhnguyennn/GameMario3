#include "HUD.h"
#include"Game.h"
#include"Sprites.h"
#include"Mario.h"



void CHUD::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_HUD_BA_BLACK)->Render(x, y);
}

CHUD::CHUD(float x, float y)
{
	this->x = x;
	this->y = y;
}
