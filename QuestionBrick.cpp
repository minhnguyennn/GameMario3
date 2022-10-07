#include "QuestionBrick.h"
#include "debug.h"
void CQuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (!unbox) animations->Get(ID_ANI_QUESTIONBRICK)->Render(x, y);
	else animations->Get(ID_ANI_QUESTIONBRICK_UNBOX)->Render(x, y);
	DebugOut(L" unbox %d state %d\n", unbox,state);
	//RenderBoundingBox();
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESIONBRICK_BBOX_WIDTH / 2;
	t = y - QUESIONBRICK_BBOX_HEIGHT / 2;
	r = l + QUESIONBRICK_BBOX_WIDTH;
	b = t + QUESIONBRICK_BBOX_HEIGHT;
}

void CQuestionBrick::SetState(int state) {
	switch (state)
	{
	case QUESTION_STATE_IDLE:
		unbox = false;
		vy = 0;
		break;
	case QUESTION_STATE_MOVE_UP:
		break;
	case QUESTION_STATE_MOVE_DOWN:
		break;
	case QUESTION_STATE_UNBOX:
		unbox = true;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);

}
