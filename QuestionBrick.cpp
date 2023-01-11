#include "QuestionBrick.h"
#include "debug.h"
#include "PlayScene.h"
#include "Game.h"
#include "MushRoom.h"
#include "Coin.h"
#include "Leaf.h"
#include "Button.h"
#include "Data.h"

void CQuestionBrick::Render()
{
	if (!checkObjectInCamera()) return;
	CAnimations* animations = CAnimations::GetInstance();
	if (!unbox) animations->Get(ID_ANI_QUESTIONBRICK)->Render(x, y);
	else animations->Get(ID_ANI_QUESTIONBRICK_UNBOX)->Render(x, y);
	//RenderBoundingBox();
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESIONBRICK_BBOX_WIDTH / 2;
	t = y - QUESIONBRICK_BBOX_HEIGHT /2;
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

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	if (!checkObjectInCamera()) return;
	if ((start_y - y) > DISTANCE_MAX_QUESTIONBRICK)
	{
		SetState(QUESTION_STATE_MOVE_DOWN);
	}

	if ((vy > 0) && (y > start_y)) 
	{
		SummonItemsFromBrickQuestion();
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CQuestionBrick::SummonItemsFromBrickQuestion() 
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	SetState(QUESTION_STATE_UNBOX);
	switch (type)
	{
		case QUESTION_TYPE_ITEM:
		{
			if (mario->GetLevel() == MARIO_LEVEL_SMALL) 
			{
				CMushRoom* mush_room = new CMushRoom(x, y, MUSHROOM_TYPE_RED);
				scene->CreateObject(mush_room);
				mush_room->SetState(MUSHROOM_STATE_UP);
			}
			else 
			{
				CLeaf* leaf = new CLeaf(x, y);
				scene->CreateObject(leaf);
			}
			break;
		}
		case QUESTION_TYPE_COIN: 
		{
			CCoin* coin = new CCoin(x, y - COIN_Y_ADJUST, COIN_TYPE_TURN_AROUND);
			scene->CreateObject(coin);
			coin->SetState(COIN_STATE_MOVE_UP);
			CData::GetInstance()->IncreaseCoin();
			break;
		}
		case QUESTION_TYPE_BUTTON:
		{
			if (mario->GetLevel() == MARIO_LEVEL_RACCOON)
			{
				CButton* button = new CButton(x, y);
				scene->CreateObject(button);
				button->SetState(BUTTON_STATE_MOVE_UP);
			}
			break;
		}
		default:
			break;
	}
}