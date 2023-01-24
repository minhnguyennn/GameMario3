#pragma once
#include "GameObject.h"

#define ID_ANI_INTRO_BACKGROUND_INVISIBLE	100100
#define ID_ANI_INTRO_BACKGROUND				100101

class CIntroBackGround : public CGameObject
{
private:
public:
	CIntroBackGround(float x, float y) : CGameObject(x, y) 
	{

	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};