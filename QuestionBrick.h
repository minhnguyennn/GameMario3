#pragma once
#define QUESIONBRICK_BBOX_WIDTH 16
#define QUESIONBRICK_BBOX_HEIGHT 16
#define ID_ANI_QUESTIONBRICK 10100
#define ID_ANI_QUESTIONBRICK_UNBOX 10101

#define QUESTION_STATE_IDLE 1
#define QUESTION_STATE_MOVE_UP 2
#define QUESTION_STATE_MOVE_DOWN 3
#define QUESTION_STATE_UNBOX 4



#include "GameObject.h"
class CQuestionBrick : public CGameObject
{
	BOOL unbox;
public:
	CQuestionBrick(float x, float y) : CGameObject(x, y) {
		SetState(QUESTION_STATE_IDLE);
	}
	void SetState(int state);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

