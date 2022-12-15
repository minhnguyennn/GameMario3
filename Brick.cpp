#include "Brick.h"
#include "QuestionBrick.h"
#include "debug.h"

void CBrick::Render()
{
	if (!checkObjectInCamera()) return;
	int aniId = ID_ANI_BRICK;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}