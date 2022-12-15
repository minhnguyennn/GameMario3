#pragma once
#include "GameObject.h"

#define ID_ANI_COURSE_CLEAR 11300
#define ID_ANI_YOU_GOT_A_CARD 11301

class CAutomation : public CGameObject
{
public:
	CAutomation(float x, float y) : CGameObject(x, y) {}
	void SetState(int state);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
};

