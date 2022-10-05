#include "QuestionBrick.h"

void CQuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_QUESTIONBRICK)->Render(x, y);
	//RenderBoundingBox();
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESIONBRICK_BBOX_WIDTH / 2;
	t = y - QUESIONBRICK_BBOX_HEIGHT / 2;
	r = l + QUESIONBRICK_BBOX_WIDTH;
	b = t + QUESIONBRICK_BBOX_HEIGHT;
}
