#include "Brick.h"
#include "debug.h"
#include "QuestionBrick.h"
#include "PlayScene.h"
#include "Game.h"
#include "Debris.h"
#include "Coin.h"
#include "Data.h"

void CBrick::Render()
{
	if (!checkObjectInCamera()) return;
	if (isBrick)
	{
		if (random == BRICK_RANDOM_0)
			CAnimations::GetInstance()->Get(ID_ANI_BRICK)->Render(x, y);
		else if (random == BRICK_RANDOM_1)
			CAnimations::GetInstance()->Get(ID_ANI_BRICK)->Render(x, y - BRICK_Y_ADJUST);
	}
	else if (CData::GetInstance()->GetIsCoin()) CAnimations::GetInstance()->Get(ID_ANI_BRICK_COIN)->Render(x, y);
	else CAnimations::GetInstance()->Get(ID_ANI_BRICK)->Render(x, y);
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
	bool isConvert = CData::GetInstance()->GetIsConvertBrick();
	if (isConvert) isBrick = true;
	else isBrick = false;
	/*if (isConvert) isCoin = true;
	else isCoin = false;*/
	CountDownConvertCoin();
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

void CBrick::SummonQuestionBrick(int type_question_brick)
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CQuestionBrick* question_brick = new CQuestionBrick(x, y, type_question_brick);
	scene->CreateObject(question_brick);
	question_brick->SummonItemsFromBrickQuestion();
}

void CBrick::CountDownConvertCoin()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	if (isBrick)
	{
		random = rand() % BRICK_RANDOM_SUM;
	}
	if (CData::GetInstance()->GetIsConvertBrick() && (GetTickCount64() - mario->GetTimeCollisionButton() > BRICK_TIME_COUTDOWN))
	{
		mario->SetTimeCollisionButton(0);
		CData::GetInstance()->SetIsConvertBrick(false);
		CData::GetInstance()->SetIsCoin(true);
	}
	if (CData::GetInstance()->GetIsCoin())
	{
		if (time_convert > 0)
		{
			if (GetTickCount64() - time_count_down > BRICK_TIME_COUTDOWN)
			{
				isCoin = true;
				time_convert--;
				time_count_down = GetTickCount64();
			}
		}
		else
		{
			isCoin = false;
			CData::GetInstance()->SetIsCoin(false);
		}
	}
}

void CBrick::SummonCoin()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CCoin* coin = new CCoin(x, y, COIN_TYPE_IN_BRICK);
	scene->CreateObject(coin);
}