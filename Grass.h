#pragma once
#include"GameObject.h"
//ANIMATION
#define ID_ANI_GRASS		15000
class CGrass : public CGameObject
{
public:
	CGrass(float x, float y) : CGameObject(x, y) {}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};