#pragma once


#include "GameObject.h"
#include "Animation.h"
#include "QuestionBrick.h"
#include "Animations.h"
#include "Debris.h"
#include "PlayScene.h"
#include "Game.h"

//ANIMATION
#define ID_ANI_BRICK 10000

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
public:
	CBrick(float x, float y, int type) : CGameObject(x, y) 
	{
		this->type = type;
		time_break = 0;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 0; };
	int IsBlocking() { return 1; }
	void SetState(int state);
};