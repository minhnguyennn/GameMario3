#pragma once
#define QUESIONBRICK_BBOX_WIDTH 16
#define QUESIONBRICK_BBOX_HEIGHT 16

#define ID_ANI_QUESTIONBRICK 10100
#define ID_ANI_QUESTIONBRICK_UNBOX 10101

#define SPEED_QUESTION_BRICK 0.07f

#define QUESTION_STATE_IDLE 1
#define QUESTION_STATE_MOVE_UP 2
#define QUESTION_STATE_MOVE_DOWN 3
#define QUESTION_STATE_UNBOX 4

#define DISTANCE_MAX 5

#include "GameObject.h"
class CQuestionBrick : public CGameObject
{

	float start_y;
	BOOL unbox;
public:
	CQuestionBrick(float x, float y) : CGameObject(x, y) {
		SetState(QUESTION_STATE_IDLE);
		start_y = y;
	}
	void SetState(int state);
	void OnNoCollision(DWORD dt);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsCollidable() { return 0; }
	int IsBlocking() { return 1; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

