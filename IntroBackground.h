#pragma once
#include "GameObject.h"

//animation
#define ID_ANI_INTRO_BACKGROUND_INVISIBLE	100100
#define ID_ANI_INTRO_BACKGROUND				100101
#define ID_ANI_INTRO_BACKGROUND_ARROW		100102

//state
#define INTRO_BACKGROUND_STATE_ARROW_UP			1
#define INTRO_BACKGROUND_STATE_ARROW_DOWN		2

class CIntroBackGround : public CGameObject
{
	bool isKeyUp;
private:
public:
	CIntroBackGround(float x, float y) : CGameObject(x, y) 
	{
		this->isKeyUp = false;
	}

	void SetIsKeyUp(bool isKeyUp) { this->isKeyUp = isKeyUp; }
	bool GetIsKeyUp() { return isKeyUp; }

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};