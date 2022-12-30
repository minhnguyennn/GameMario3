#include "Brick.h"
#include "debug.h"
#include "QuestionBrick.h"
#include "Debris.h"
#include "PlayScene.h"
#include "Game.h"

void CBrick::Render()
{
	if (!checkObjectInCamera()) return;
	int aniId = 0;
	if (isNoBrick)
		aniId = ID_ANI_NO_BRICK;
	else
		aniId = ID_ANI_BRICK;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBrick::SetState(int state)
{
	switch (state)
	{
	case BRICK_STATE_DELETE:
	{
		isDeleted = true;
		break;
	}
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CBrick::SummonDebris()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();

	CDebris* left_up = new CDebris(x, y);
	scene->CreateObject(left_up);
	left_up->SetState(DEBRIS_LEFT);

	CDebris* left_down = new CDebris(x, y - DEBRIS_Y_ADJUST);
	scene->CreateObject(left_down);
	left_down->SetState(DEBRIS_LEFT);

	CDebris* right_up = new CDebris(x + DEBRIS_X_ADJUST, y);
	scene->CreateObject(right_up);
	right_up->SetState(DEBRIS_RIGHT);

	CDebris* right_down = new CDebris(x + DEBRIS_X_ADJUST, y - DEBRIS_Y_ADJUST);
	scene->CreateObject(right_down);
	right_down->SetState(DEBRIS_RIGHT);
}

void CBrick::SummonQuestionBrick()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CQuestionBrick* question_brick = new CQuestionBrick(x, y, QUESTION_TYPE_BUTTON);
	scene->CreateObject(question_brick);
}