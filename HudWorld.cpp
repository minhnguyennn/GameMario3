#include "HudWorld.h"
#include"Game.h"
#include"Sprites.h"
#include"Mario.h"
#include"MarioWorld.h"
#include"PlayScene.h"
#include"Data.h"
#include"Automation.h"
#include"WorldScene.h"

CHudWorld::CHudWorld(float x, float y)
{
	this->x = x;
	this->y = y;
}

void CHudWorld::Render()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();

	LPWORLDSCENE world_scene = (LPWORLDSCENE)CGame::GetInstance()->GetCurrentScene();
	CMarioWorld* mario_world = (CMarioWorld*)world_scene->GetPlayer();

	CData* data_game = CData::GetInstance();

	int data_score = CData::GetInstance()->GetMarioScore();
	int data_coin = CData::GetInstance()->GetMarioCoin();
	int data_heart = CData::GetInstance()->GetMarioHeart();
	int data_card_box = CData::GetInstance()->GetCardBox();
	int data_time = CData::GetInstance()->GetMarioTime();

	CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_BA_BLACK)->Render(x, y);
	CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_TABLE_HUD)->Render(x + 30, y - 7);
	CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_POWER_M)->Render(x - 74, y - 3);

	if (!mario_world->GetIsDelay() && data_heart > 3)
	{
		CAnimations::GetInstance()->Get(ID_ANI_INFOR_BOARD_BEGIN)->Render(x + 30, y - 110);
		DrawNumber(data_heart % 10, x + 70, y - 100);
		DrawNumber(1, x + 50, y - 120);
	}
	else
	{
		mario_world->SetIsDelay(true);
	}
	
	if (data_heart < 1)
	{
		CAnimations::GetInstance()->Get(ID_ANI_INFOR_BOARD_END)->Render(x + 30, y - 110);
		if (!mario_world->GetIsRedArrow()) CAnimations::GetInstance()->Get(ID_ANI_INFOR_BOARD_ARROW)->Render(x + 12, y - 98);
		else CAnimations::GetInstance()->Get(ID_ANI_INFOR_BOARD_ARROW)->Render(x + 12, y - 90);
	}

	//Number map
	DrawNumber(1, x - 45, y - 11);

	//Draw coin
	DrawNumber(data_coin / 10, x + 50, y - 11);
	DrawNumber(data_coin % 10, x + 58, y - 11);

	//Draw heart
	DrawNumber(data_heart / 10, x - 53, y - 2);
	DrawNumber(data_heart % 10, x - 45, y - 2);

	//Draw score
	DrawNumber(data_score / 1000000, x - 30, y - 2);
	DrawNumber(data_score / 100000 % 10, x - 22, y - 2);
	DrawNumber(data_score / 10000 % 10, x - 14, y - 2);
	DrawNumber(data_score / 1000 % 10, x - 6, y - 2);
	DrawNumber(data_score / 100 % 10, x + 2, y - 2);
	DrawNumber(data_score / 10 % 10, x + 10, y - 2);
	DrawNumber(data_score / 1 % 10, x + 18, y - 2);

	//Draw time
	DrawNumber(data_time / 100, x + 42, y - 2);
	DrawNumber((data_time / 10) % 10, x + 50, y - 2);
	DrawNumber(data_time % 10, x + 58, y - 2);

	//Draw card box
	DrawCardBox(data_game->GetCardStore1(), x + 86, y - 7);
	DrawCardBox(data_game->GetCardStore2(), x + 110, y - 7);
	DrawCardBox(data_game->GetCardStore3(), x + 134, y - 7);
	

	//Draw coin
	//DrawNumber(coin_mario / 10, x + 50, y - 11);
	//DrawNumber(coin_mario % 10, x + 58, y - 11);

	////Draw heart
	//DrawNumber(heart_mario / 10, x - 53, y - 2);
	//DrawNumber(heart_mario % 10, x - 45, y - 2);

	//Draw time
	/*DrawNumber(time_mario / 100, x + 42, y - 2);
	DrawNumber((time_mario / 10) % 10, x + 50, y - 2);
	DrawNumber(time_mario % 10, x + 58, y - 2);*/

	//Draw score
	/*DrawNumber(score_mario / 1000000, x - 30, y - 2);
	DrawNumber(score_mario / 100000 % 10, x - 22, y - 2);
	DrawNumber(score_mario / 10000 % 10, x - 14, y - 2);
	DrawNumber(score_mario / 1000 % 10, x - 6, y - 2);
	DrawNumber(score_mario / 100 % 10, x + 2, y - 2);
	DrawNumber(score_mario / 10 % 10, x + 10, y - 2);
	DrawNumber(score_mario / 1 % 10, x + 18, y - 2);*/

	//Draw power
	/*DrawPower(power_mario, x - 29, y - 10);*/



	//DrawNumber(power_mario, x - 30, y - 8);

}

void CHudWorld::DrawCardBox(int card_box, float position_x, float position_y)
{
	switch (card_box)
	{
	case 1:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_FLLOWER_IN_CARD)->Render(position_x, position_y);
		break;
	}
	case 2:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_STAR_IN_CARD)->Render(position_x, position_y);
		break;
	}
	case 3:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_MUSHROOM_IN_CARD)->Render(position_x, position_y);
		break;
	}
	default:
		break;
	}
}

void CHudWorld::DrawNumber(int number, float position_x, float position_y)
{
	switch (number)
	{
	case 0:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_0)->Render(position_x, position_y);
		break;
	}
	case 1:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_1)->Render(position_x, position_y);
		break;
	}
	case 2:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_2)->Render(position_x, position_y);
		break;
	}
	case 3:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_3)->Render(position_x, position_y);
		break;
	}
	case 4:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_4)->Render(position_x, position_y);
		break;
	}
	case 5:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_5)->Render(position_x, position_y);
		break;
	}
	case 6:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_6)->Render(position_x, position_y);
		break;
	}
	case 7:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_7)->Render(position_x, position_y);
		break;
	}
	case 8:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_8)->Render(position_x, position_y);
		break;
	}
	case 9:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_9)->Render(position_x, position_y);
		break;
	}
	default:
		break;
	}
}

void CHudWorld::DrawPower(int power, float position_x, float position_y)
{
	switch (power)
	{
	case 1:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x, position_y);
		break;
	}
	case 2:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 8, position_y);

		break;
	}
	case 3:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 8, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 16, position_y);

		break;
	}
	case 4:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 8, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 16, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 24, position_y);

		break;
	}
	case 5:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 8, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 16, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 24, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 32, position_y);

		break;
	}
	case 6:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 8, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 16, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 24, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 32, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 40, position_y);

		break;
	}
	case 7:
	{
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 8, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 16, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 24, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 32, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_ARROW_POWER)->Render(position_x + 40, position_y);
		CAnimations::GetInstance()->Get(ID_ANI_HUD_WORLD_POWER_P)->Render(position_x + 52, position_y);

		break;
	}
	default:
		break;
	}
}