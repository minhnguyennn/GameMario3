#pragma once
#include "GameObject.h"

//animation
#define ID_ANI_INTRO_BACKGROUND_INVISIBLE		100100
#define ID_ANI_INTRO_BACKGROUND					100101
#define ID_ANI_INTRO_BACKGROUND_ARROW			100102
#define ID_ANI_INTRO_BACKGROUND_NUMBER_THREE	100103

#define ID_ANI_INTRO_BACKGROUND_SCENE_ONE		100104
#define ID_ANI_INTRO_BACKGROUND_SCENE_TWO		100107

#define ID_ANI_INTRO_BACKGROUND_CURTAIN_BEGIN	100105
#define ID_ANI_INTRO_BACKGROUND_CURTAIN_END		100106

//state
#define INTRO_BACKGROUND_STATE_ARROW_UP			1
#define INTRO_BACKGROUND_STATE_ARROW_DOWN		2

//time
#define TIME_BACKGROUND_CHANGE_SCENE_1			3000
#define TIME_BACKGROUND_CHANGE_SCENE_2			4000

class CIntroBackGround : public CGameObject
{
	bool isKeyUp;
	bool isScene1;
	bool isScene2;
	bool isScene3;

	ULONGLONG time_change_scene;
private:
public:
	CIntroBackGround(float x, float y) : CGameObject(x, y) 
	{
		this->isKeyUp = false;
		this->time_change_scene = GetTickCount64();
		this->isScene1 = true;
		this->isScene2 = false;
		this->isScene3 = false;
	}

	void SetIsKeyUp(bool isKeyUp) { this->isKeyUp = isKeyUp; }
	bool GetIsKeyUp() { return isKeyUp; }

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	void SummonCurtain();
};