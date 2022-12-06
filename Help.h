#pragma once
#include"GameObject.h"

//ANIMATION
#define ID_ANI_HELP		15001

class CHelp : public CGameObject
{
public:
	CHelp(float x, float y) : CGameObject(x, y) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};