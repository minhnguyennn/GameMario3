#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Data.h"

//ANIMATION
#define ID_ANI_BRICK 10000
#define ID_ANI_BRICK_COIN 10003

//BBOX
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

//STATE
#define BRICK_STATE_DELETE 1
#define BRICK_STATE_COIN	2
#define BRICK_STATE_BRICK	3

//TYPE
#define BRICK_TYPE_NO_BLOCK 1
#define BRICK_TYPE_BUTTON 2
#define BRICK_TYPE_MUSHROOM 3

//TIME
#define BRICK_TIME_COUTDOWN		1000
#define BRICK_CONVERT_TIMEOUT	7
#define BRICK_Y_ADJUST			1

//random
#define BRICK_RANDOM_SUM	2
#define BRICK_RANDOM_0		0
#define BRICK_RANDOM_1		1

class CBrick : public CGameObject 
{
	int type;
	int time_convert;
	int random;
	
	ULONGLONG time_count_down;
	ULONGLONG time_coin;

	bool isCoin;
	bool isBrick;
public:
	CBrick(float x, float y, int type) : CGameObject(x, y) 
	{
		this->type = type;
		random = 0;

		isCoin = false;
		isBrick = false;

		time_convert = 7;
		time_coin = 0;
		time_count_down = 0;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	bool GetIsCoin() { return isCoin; }
	int GetTypeBrick() { return type; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() 
	{ 
		if (isCoin)
			return 1;
		else
			return 0; 
	};
	int IsBlocking() 
	{ 
		if (CData::GetInstance()->GetIsCoin())
			return 0;
		else
			return 1;
	}
	void SetState(int state);
	void SummonDebris();
	void SummonQuestionBrick(int type_question_brick);
	void CountDownConvertCoin();
	void SummonCoin();
};