#include "QuestionBrick.h"
#include "debug.h"
#include "PlayScene.h"
#include "Game.h"
#include "MushRoom.h"

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
	t = y - QUESIONBRICK_BBOX_HEIGHT /2+1;
	r = l + QUESIONBRICK_BBOX_WIDTH;
	b = t + QUESIONBRICK_BBOX_HEIGHT;
}

void CQuestionBrick::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CQuestionBrick::SetState(int state) {
	switch (state)
	{
	case QUESTION_STATE_IDLE:
		unbox = false;
		vy = 0;
		break;
	case QUESTION_STATE_MOVE_UP:
		vy = -SPEED_QUESTION_BRICK;
		break;
	case QUESTION_STATE_MOVE_DOWN:
		vy = SPEED_QUESTION_BRICK;
		break;
	case QUESTION_STATE_UNBOX:
		y = start_y;
		vy = 0;
		unbox = true;
		break;
	default:
		break;
	}
	CGameObject::SetState(state);

}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	
	if ((start_y - y) > DISTANCE_MAX)
	{
		SetState(QUESTION_STATE_MOVE_DOWN);
	}
	else if ((vy > 0) &&(y>start_y+6)){
		SetState(QUESTION_STATE_UNBOX);
		CMushRoom* mushroom = new CMushRoom(x, y);
		scene->CreateObject(mushroom);
		mushroom->SetState(MUSHROOM_STATE_UP);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

