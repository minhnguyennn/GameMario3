#pragma once

//BBOX
#define QUESIONBRICK_BBOX_WIDTH 16
#define QUESIONBRICK_BBOX_HEIGHT 16

//ANIMATION
#define ID_ANI_QUESTIONBRICK 10100
#define ID_ANI_QUESTIONBRICK_UNBOX 10101

//PROPERTY
#define SPEED_QUESTION_BRICK 0.1f
#define DISTANCE_MAX_QUESTIONBRICK 6

//STATE
#define QUESTION_STATE_IDLE 1
#define QUESTION_STATE_MOVE_UP 2
#define QUESTION_STATE_MOVE_DOWN 3
#define QUESTION_STATE_UNBOX 4

//TYPE
#define QUESTION_TYPE_COIN 1
#define QUESTION_TYPE_ITEM 2
#define QUESTION_TYPE_MUSHROOM_GREEN 3
#define QUESTION_TYPE_BUTTON 4

#include "GameObject.h"
class CQuestionBrick : public CGameObject
{
	int type;
	float start_y;
	BOOL unbox;
public:
	CQuestionBrick(float x, float y, int type) : CGameObject(x, y) {
		SetState(QUESTION_STATE_IDLE);
		start_y = y;
		this->type = type;
		if (type == QUESTION_TYPE_BUTTON) this->SummonItemsFromBrickQuestion();
	}
	void SetState(int state);
	void OnNoCollision(DWORD dt);
	void Render();
	void SummonItemsFromBrickQuestion();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 1; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

