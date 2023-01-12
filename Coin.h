#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

//ANIMATION
#define ID_ANI_COIN_BRICK 11001
#define ID_ANI_COIN_AROUND_SMALL 11000
#define ID_ANI_COIN_AROUND_BIG 11002

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
#define COIN_DISTANCE_DOWN 5

//PROPERTY
#define MAX_VY 0.07f
#define COIN_Y_ADJUST 20

//TYPE
#define COIN_TYPE_IN_BRICK 1
#define COIN_TYPE_TURN_AROUND_SMALL 2
#define COIN_TYPE_TURN_AROUND_BIG 3

//TIME
#define COIN_UP_TIMEOUT 400
#define COIN_DOWN_TIMEOUT 200


class CCoin : public CGameObject 
{
	float start_y;
	int type;
	ULONGLONG time_coin_up;
	ULONGLONG time_coin_down;
	bool isSummonScore;
public:
	CCoin(float x, float y, int type) : CGameObject(x, y) 
	{
		time_coin_up = 0;
		time_coin_down = 0;
		start_y = y;
		this->type = type;
		isSummonScore = false;
	}
	void OnNoCollision(DWORD dt);
	void SetState(int state);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void SummonScore();
};