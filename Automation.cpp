#include "Automation.h"

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
	if (CountDownTimer(COURSE_CLEAR_TIMEOUT))
	{
		animations->Get(ID_ANI_YOU_GOT_A_CARD)->Render(x, y + 26);
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