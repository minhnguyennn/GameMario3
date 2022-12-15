#pragma once
#include "GameObject.h"

//ANIMATION
#define ID_ANI_COURSE_CLEAR 11300
#define ID_ANI_YOU_GOT_A_CARD 11301
//TIME
#define COURSE_CLEAR_TIMEOUT 1000

class CAutomation : public CGameObject
{
	ULONGLONG time_line;
public:
	CAutomation(float x, float y) : CGameObject(x, y) 
	{
		time_line = GetTickCount64();
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }
	bool CountDownTimer(int time);
};

