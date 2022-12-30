#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

//ANIMATION
#define ID_ANI_DEBRIS 10001

//PROPERTY
#define DEBRIS_VX 0.08f
#define DEBRIS_VY 0.25f
#define DEBRIS_AY 0.0005f
#define DEBRIS_Y_ADJUST 14
#define DEBRIS_X_ADJUST 6

//STATE
#define DEBRIS_LEFT 1
#define DEBRIS_RIGHT 2

class CDebris : public CGameObject
{
	float ay;
public:
	CDebris(float x, float y) : CGameObject(x, y) 
	{
		this->ay = DEBRIS_AY;
	};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetIsDeleted(bool isDeleted) { this->isDeleted = isDeleted; }
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsCollidable() { return 0; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void SetState(int state);
};