#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

//ANIMATION
#define ID_ANI_BRICK 10000
#define ID_ANI_NO_BRICK 10002	

//BBOX
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

//STATE
#define BRICK_STATE_DELETE 1

//TYPE
#define BRICK_TYPE_BLOCK 1
#define BRICK_TYPE_NO_BLOCK 2

class CBrick : public CGameObject 
{
	int type;
	int time_break;
	bool isNoBrick;
public:
	CBrick(float x, float y, int type) : CGameObject(x, y) 
	{
		this->type = type;
		time_break = 0;
		isNoBrick = false;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int GetTypeBrick() { return type; }
	void SetIsNoBrick(bool isNoBrick) { this->isNoBrick = isNoBrick; }
	bool GetIsNoBrick() { return isNoBrick; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 0; };
	int IsBlocking() { return 1; }
	void SetState(int state);
	void SummonDebris();
	void SummonQuestionBrick();
	void SummonCoin();
};