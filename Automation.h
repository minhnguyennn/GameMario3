#pragma once
#include "GameObject.h"

//ANIMATION
#define ID_ANI_COURSE_CLEAR 11300
#define ID_ANI_YOU_GOT_A_CARD 11301
//card_box
#define ID_ANI_FLLOWER_IN_CARD		11302
#define ID_ANI_MUSHROOM_IN_CARD		11303
#define ID_ANI_STAR_IN_CARD			11304

#define ID_ANI_FLLOWER_2			11322
#define ID_ANI_MUSHROOM_2			11323
#define ID_ANI_STAR_2				11324

//TIME
#define COURSE_CLEAR_TIMEOUT 500
#define COURSE_CARD_BOX_TIMEOUT 1000

//POSITION
#define COURSE_CLEAR_POSITION_X 2682
#define COURSE_CLEAR_POSITION_Y 270
#define AUTOMATION_Y_ADJUST 26
#define AUTOMATION_X_ADJUST 62

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

