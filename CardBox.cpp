#include "CardBox.h"
#include "Point.h"
#include "debug.h"
#include "PlayScene.h"
#include "Automation.h"
#include "Data.h"


void CCardBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!checkObjectInCamera()) return;
	if (isRandom) SetupRandomCardBox();
	if (isUp && CountDownTimer(CARD_BOX_UP_TIMEOUT)) SetState(CARD_BOX_STATE_SUMMON);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCardBox::Render()
{
	if (!checkObjectInCamera()) return;
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = 0;
	if (isRandom) aniId = ID_ANI_CARD_BOX_RANDOM;
	else if (isUp && isFlower) aniId = ID_ANI_FLOWER_CARD;
	else if (isUp && isStar) aniId = ID_ANI_STAR_CARD;
	else if (isUp && isMushRoom) aniId = ID_ANI_MUSHROOM_CARD;
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CCardBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CARD_BOX_BBOX_WIDTH / 2;
	t = y - CARD_BOX_BBOX_HEIGHT / 2;
	r = l + CARD_BOX_BBOX_WIDTH;
	b = t + CARD_BOX_BBOX_HEIGHT;
}

void CCardBox::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CCardBox::SetState(int state)
{
	switch (state)
	{
	case CARD_BOX_STATE_SUMMON:
	{
		isUp = false;
		isFlower = false;
		isStar = false;
		isMushRoom = false;
		time_line = 0;
		isDeleted = true;
		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		CAutomation* automation = new CAutomation(COURSE_CLEAR_POSITION_X, COURSE_CLEAR_POSITION_Y);
		scene->CreateObject(automation);
		break;
	}
	case CARD_BOX_STATE_UP:
	{
		CData* data_game = CData::GetInstance();
		if (data_game->GetCardBox() == CARD_BOX_DRAW_FLOWER) isFlower = true;
		else if (data_game->GetCardBox() == CARD_BOX_DRAW_STAR) isStar = true;
		else if (data_game->GetCardBox() == CARD_BOX_DRAW_MUSHROOM) isMushRoom = true;
		time_line = GetTickCount64();
		vy = -CARD_BOX_SPEED_Y;
		isUp = true;
		isRandom = false;
		break;
	}
	default:
		break;
	}
	CGameObject::SetState(state);
}

bool CCardBox::CountDownTimer(int time)
{
	if (GetTickCount64() - time_line > time)
	{
		return true;
	}
	return false;
}

int CCardBox::SetupRandomCardBox()
{
	random_card_box = rand() % CARD_BOX_NUMBER_RANDOM_3;
	if (random_card_box == CARD_BOX_NUMBER_RANDOM_0) return CARD_BOX_DRAW_FLOWER;
	else if (random_card_box == CARD_BOX_NUMBER_RANDOM_1) return CARD_BOX_DRAW_STAR;
	else if (random_card_box == CARD_BOX_NUMBER_RANDOM_2) return CARD_BOX_DRAW_MUSHROOM;
	else return 0;
}