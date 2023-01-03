#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

//ANIMATION
#define ID_ANI_BUTTON 11400
#define ID_ANI_BUTTON_PRESSED 11401

//BBOX
#define BUTTON_BBOX_PRESSED_WIDTH 16
#define BUTTON_BBOX_PRESSED_HEIGHT 1

#define BUTTON_BBOX_WIDTH 16
#define BUTTON_BBOX_HEIGHT 12

//STATE
#define BUTTON_STATE_IDLE 0
#define BUTTON_STATE_MOVE_UP 1 

//DISTANCE
#define BUTTON_DISTANCE_UP 15

//PROPERTY
#define BUTTON_MAX_VY 0.07f
#define BUTTON_PRESSED_Y_ADJUST 6

class CButton : public CGameObject
{
	float start_y;
	bool isPressed;
public:
	CButton(float x, float y) : CGameObject(x, y)
	{
		start_y = y;
		isPressed = false;
	}
	void SetIsPressed(bool isPressed) { this->isPressed = isPressed; }
	bool GetIsPressed() { return isPressed; }
	void OnNoCollision(DWORD dt);
	void SetState(int state);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
	int IsCollidable() { return 1; }
};