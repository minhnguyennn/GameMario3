#include "QuestionBrick.h"
#include "debug.h"
#include "PlayScene.h"
#include "Game.h"
#include "MushRoom.h"
#include "Coin.h"
#include "Leaf.h"

void CQuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (!unbox) animations->Get(ID_ANI_QUESTIONBRICK)->Render(x, y);
	else animations->Get(ID_ANI_QUESTIONBRICK_UNBOX)->Render(x, y);
	//DebugOut(L"Unbox: %d, state: %d \n", unbox, state);
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
	
	if ((start_y - y) > DISTANCE_MAX)
	{
		SetState(QUESTION_STATE_MOVE_DOWN);
	}

	if ((vy > 0) && (y > start_y)) 
	{
		SetState(QUESTION_STATE_UNBOX);
		SummonItemsFromBrickQuestion();
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CQuestionBrick::SummonItemsFromBrickQuestion() {
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	switch (type)
	{
		case QUESTION_TYPE_ITEM:
		{
			CMushRoom* mush_room = new CMushRoom(x, y);
			scene->CreateObject(mush_room);
			mush_room->SetState(MUSHROOM_STATE_UP);
			break;
		}
		case QUESTION_TYPE_COIN: 
		{
			CCoin* coin = new CCoin(x, y - 20);
			scene->CreateObject(coin);
			coin->SetState(COIN_STATE_MOVE_UP);
			break;
		}
		case QUESTION_TYPE_LEAF:
		{
			CLeaf* leaf = new CLeaf(x, y);
			leaf->SetVY(-0.05f);
			scene->CreateObject(leaf);
			break;
		}
		default:
			break;
	}
}

