#include "Automation.h"
#include "Data.h"

void CAutomation::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!checkObjectInCamera()) return;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CAutomation::Render()
{
	if (!checkObjectInCamera()) return;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COURSE_CLEAR)->Render(x, y);
	if (CountDownTimer(COURSE_CLEAR_TIMEOUT)) animations->Get(ID_ANI_YOU_GOT_A_CARD)->Render(x, y + AUTOMATION_Y_ADJUST);
	if (CountDownTimer(COURSE_CARD_BOX_TIMEOUT))
	{
		CData* data_game = CData::GetInstance();
		if (data_game->GetCardBox() == DATA_FLOWER_CARD_BOX) 
			animations->Get(ID_ANI_FLLOWER_IN_CARD)->Render(x + AUTOMATION_X_ADJUST, y + AUTOMATION_Y_ADJUST);
		else if (data_game->GetCardBox() == DATA_STAR_CARD_BOX) 
			animations->Get(ID_ANI_STAR_IN_CARD)->Render(x + AUTOMATION_X_ADJUST, y + AUTOMATION_Y_ADJUST);
		else if (data_game->GetCardBox() == DATA_MUSHROOM_CARD_BOX) 
			animations->Get(ID_ANI_MUSHROOM_IN_CARD)->Render(x + AUTOMATION_X_ADJUST, y + AUTOMATION_Y_ADJUST);
	}
	if (CountDownTimer(1500))
	{
		CData::GetInstance()->SetIsDrawCardBox(true);
	}
}

bool CAutomation::CountDownTimer(int time)
{
	if (GetTickCount64() - time_line > time)
	{
		return true;
	}
	return false;
}

