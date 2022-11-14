#include "Brick.h"
#include "QuestionBrick.h"
#include "debug.h"

void CBrick::Render()
{
	int aniId = ID_ANI_BRICK;
	if (type == BRICK_TYPE_NO_BLOCK) {
		DebugOut(L"[OKE]");
		aniId = ID_ANI_BRICK_NO;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (type == BRICK_TYPE_BLOCK) {
		l = x - BRICK_BBOX_WIDTH / 2;
		t = y - BRICK_BBOX_HEIGHT / 2;
		r = l + BRICK_BBOX_WIDTH;
		b = t + BRICK_BBOX_HEIGHT;
	}
	else if (type == BRICK_TYPE_NO_BLOCK) {
		l = x - BRICK_BBOX_NO_BLOCK_WIDTH / 2;
		t = y - BRICK_BBOX_NO_BLOCK_HEIGHT / 2;
		r = l + BRICK_BBOX_NO_BLOCK_WIDTH;
		b = t + BRICK_BBOX_NO_BLOCK_HEIGHT;
	}
	
}                                                                                                                                                                                                                                                                                                                                                                                  