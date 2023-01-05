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
	int AniId = 0;
	if (isCoin)
		AniId = ID_ANI_BRICK_COIN;
	else
		AniId = ID_ANI_BRICK;
	CAnimations::GetInstance()->Get(AniId)->Render(x, y);
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
	
	CountDownConvertCoin();
	bool isConvert = CData::GetInstance()->GetIsConvertBrick();
	if (isConvert) isCoin = true;
	else isCoin = false;
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

void CBrick::CountDownConvertCoin()
{
	if (CData::GetInstance()->GetIsConvertBrick())
	{
		if (time_convert > 0)
		{
			if (GetTickCount64() - time_count_down > BRICK_TIME_COUTDOWN)
			{
				time_convert--;
				time_count_down = GetTickCount64();
			}
		}
		else
		{
			CData::GetInstance()->SetIsConvertBrick(false);
		}
	}
}

void CBrick::SummonCoin()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CCoin* coin = new CCoin(x, y, COIN_TYPE_IN_BRICK);
	scene->CreateObject(coin);
}