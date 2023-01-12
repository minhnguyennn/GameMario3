#include "Point.h"
#include "Data.h"
#include "debug.h"

void CPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	if (!checkObjectInCamera()) return;
	if (GetTickCount64() - time_score_fly > POINT_FLY_TIMEOUT)
	{
		StorageScore();
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPoint::Render()
{
	if (!checkObjectInCamera()) return;
	CAnimations* animations = CAnimations::GetInstance();
	int AniId = 0;
	if (type_point == POINT_TYPE_100) AniId = ID_ANI_100_SCORE;
	else if (type_point == POINT_TYPE_200) AniId = ID_ANI_200_SCORE;
	else if (type_point == POINT_TYPE_400) AniId = ID_ANI_400_SCORE;
	else if (type_point == POINT_TYPE_800) AniId = ID_ANI_800_SCORE;
	else if (type_point == POINT_TYPE_1000) AniId = ID_ANI_1000_SCORE;
	else if (type_point == POINT_TYPE_2000) AniId = ID_ANI_2000_SCORE;
	else if (type_point == POINT_TYPE_4000) AniId = ID_ANI_4000_SCORE;
	else if (type_point == POINT_TYPE_8000) AniId = ID_ANI_8000_SCORE;
	else if (type_point == POINT_TYPE_UP) AniId = ID_ANI_1_UP;
	animations->Get(AniId)->Render(x, y);
	//RenderBoundingBox();
}

void CPoint::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CPoint::SetState(int state)
{
	switch (state)
	{
	case POINT_STATE_MOVE_UP:
		vy = -POINT_MOVE_SPEED;
		time_score_fly = GetTickCount64();
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CPoint::StorageScore()
{
	CData* data_game = CData::GetInstance();
	int data_heart = 0;
	int data_coin = 0;
	switch (type_point)
	{
	case POINT_TYPE_UP:
		data_heart = POINT_NUMBER_1UP;
		break;
	case POINT_TYPE_100:
		data_coin = POINT_NUMBER_100;
		break;
	case POINT_TYPE_200:
		data_coin = POINT_NUMBER_200;
		break;
	case POINT_TYPE_1000:
		data_coin = POINT_NUMBER_1000;
		break;
	default:
		break;
	}
	data_game->SetMarioScore(data_game->GetMarioScore() + data_coin);
	data_game->SetMarioHeart(data_game->GetMarioHeart() + data_heart);
}