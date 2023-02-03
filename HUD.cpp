#include "HUD.h"
#include"Game.h"
#include"Sprites.h"
#include"Mario.h"
#include"PlayScene.h"
#include"Data.h"
#include"Automation.h"

void CHUD::Render()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	CData* data_game = CData::GetInstance();

	int time_mario = mario->GetTime();
	int power_mario = mario->GetPower();

	int data_score = CData::GetInstance()->GetMarioScore();
	int data_coin = CData::GetInstance()->GetMarioCoin();
	int data_heart = CData::GetInstance()->GetMarioHeart();
	int data_card_box = CData::GetInstance()->GetCardBox();

	CAnimations::GetInstance()->Get(ID_ANI_HUD_BA_BLACK)->Render(x, y);
	CAnimations::GetInstance()->Get(ID_ANI_HUD_TABLE_HUD)->Render(x + 30, y - 7);
	CAnimations::GetInstance()->Get(ID_ANI_HUD_POWER_M)->Render(x - 74, y - 3);

	//Draw card box
	if (data_game->GetNumberTouchCard() == 1) DrawCardBox(data_card_box, x + 86, y - 7);
	else if (data_game->GetNumberTouchCard() == 2)
	{
		DrawCardBox(data_game->GetCardStore1(), x + 86, y - 7);
		DrawCardBox(data_card_box, x + 110, y - 7);
	}
	else if (data_game->GetNumberTouchCard() == 3)
	{
		DrawCardBox(data_game->GetCardStore1(), x + 86, y - 7);
		DrawCardBox(data_game->GetCardStore2(), x + 110, y - 7);
		DrawCardBox(data_card_box, x + 134, y - 7);
	}
	else if (data_game->GetNumberTouchCard() == 4)
	{
		DrawCardBox(data_game->GetCardStore1(), x + 86, y - 7);
		DrawCardBox(data_game->GetCardStore2(), x + 110, y - 7);
		DrawCardBox(data_game->GetCardStore3(), x + 134, y - 7);
	}
	
	//Number map
	DrawNumber(1, x - 45, y - 11);

	//Draw coin
	DrawNumber(data_coin / 10, x + 50, y - 11);
	DrawNumber(data_coin % 10, x + 58, y - 11);

	//Draw heart
	DrawNumber(data_heart / 10, x - 53, y - 2);
	DrawNumber(data_heart % 10, x - 45, y - 2);

	//Draw time
	DrawNumber(time_mario / 100, x + 42, y - 2);
	DrawNumber((time_mario / 10) % 10, x + 50, y - 2);
	DrawNumber(time_mario % 10, x + 58, y - 2);

	//Draw score
	DrawNumber(data_score / 1000000, x - 30, y - 2);
	DrawNumber(data_score / 100000 % 10, x - 22, y - 2);
	DrawNumber(data_score / 10000 % 10, x - 14, y - 2);
	DrawNumber(data_score / 1000 % 10, x - 6, y - 2);
	DrawNumber(data_score / 100 % 10, x + 2, y - 2);
	DrawNumber(data_score / 10 % 10, x + 10, y - 2);
	DrawNumber(data_score / 1 % 10, x + 18, y - 2);

	//Draw power
	DrawPower(power_mario, x - 29, y - 10);
}

void CHUD::DrawCardBox(int card_box, float position_x, float position_y)
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	switch (card_box)
	{
	case 1:
	{
		if (mario->GetIsCollisionCardBox()) 
			CAnimations::GetInstance()->Get(ID_ANI_FLLOWER_2)->Render(position_x, position_y);
		else 
			CAnimations::GetInstance()->Get(ID_ANI_FLLOWER_IN_CARD)->Render(position_x, position_y);
		break;
	}
	case 2:
	{
		if (mario->GetIsCollisionCardBox())
			CAnimations::GetInstance()->Get(ID_ANI_STAR_2)->Render(position_x, position_y);
		else
			CAnimations::GetInstance()->Get(ID_ANI_STAR_IN_CARD)->Render(position_x, position_y);
		break;
	}
	case 3:
	{
		if (mario->GetIsCollisionCardBox())
			CAnimations::GetInstance()->Get(ID_ANI_MUSHROOM_2)->Render(position_x, position_y);
		else
			CAnimations::GetInstance()->Get(ID_ANI_MUSHROOM_IN_CARD)->Render(position_x, position_y);
		break;
	}
	default:
		break;
	}
}

void CHUD::DrawNumber(int number, float position_x, float position_y)
{
	switch (number)
	{
	case 0:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_0)->Render(position_x, position_y);
		break;
	}
	case 1:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_1)->Render(position_x, position_y);
		break;
	}
	case 2:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_2)->Render(position_x, position_y);
		break;
	}
	case 3:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_3)->Render(position_x, position_y);
		break;
	}
	case 4:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_4)->Render(position_x, position_y);
		break;
	}
	case 5:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_5)->Render(position_x, position_y);
		break;
	}
	case 6:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_6)->Render(position_x, position_y);
		break;
	}
	case 7:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_7)->Render(position_x, position_y);
		break;
	}
	case 8:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_8)->Render(position_x, position_y);
		break;
	}
	case 9:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_9)->Render(position_x, position_y);
		break;
	}
	default:
		break;
	}
}

void CHUD::DrawPower(int power, float position_x, float position_y)
{
	switch (power)
	{
	case 1:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x, position_y);
		break;
	}
	case 2:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 8, position_y);
		break;
	}
	case 3:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 8, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 16, position_y);

		break;
	}
	case 4:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 8, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 16, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 24, position_y);

		break;
	}
	case 5:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 8, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 16, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 24, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 32, position_y);

		break;
	}
	case 6:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 8, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 16, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 24, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 32, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 40, position_y);

		break;
	}
	case 7:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 8, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 16, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 24, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 32, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW_POWER)->Render(position_x + 40, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_POWER_P)->Render(position_x + 52, position_y);

		break;
	}
	default:
		
		break;
	}
}

CHUD::CHUD(float x, float y)
{
	this->x = x;
	this->y = y;
}
