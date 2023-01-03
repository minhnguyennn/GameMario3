#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

//ANIMATION
#define ID_ANI_COIN_AROUND 11000
#define ID_ANI_COIN_BRICK 11001

//BBOX
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

//STATE
#define COIN_STATE_IDLE 0
#define COIN_STATE_MOVE_UP 1
#define COIN_STATE_DELETE 2
#define COIN_STATE_MOVE_DOWN 3

//DISTANCE
#define COIN_DISTANCE_UP 40
#define COIN_DISTANCE_DOWN 20

//PROPERTY
#define MAX_VY 0.07f
#define COIN_Y_ADJUST 20

//TYPE
#define COIN_TYPE_IN_BRICK 1
#define COIN_TYPE_TURN_AROUND 2

class CCoin : public CGameObject 
{
	float start_y;
	float coppy_x;
	float coppy_y;
	int type;
public:
	CCoin(float x, float y, int type) : CGameObject(x, y) 
	{
		SetState(COIN_STATE_IDLE);
		start_y = y;
		this->type = type;
	}
	void OnNoCollision(DWORD dt);
	void SetState(int state);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void SummonAndMovePoint();
	void SetCoppyPosition(float coppy_x, float coppy_y) { this->coppy_x = coppy_x, this->coppy_y = coppy_y; }
};