#pragma once
#include"debug.h"
#include"GameObject.h"

#define DATA_MARIO_HEART				4
#define DATA_MARIO_TIME_OUTMAP			7
#define DATA_MARIO_SCORE_ADJUST			50
#define DATA_MARIO_COIN_MAX				99
#define DATA_MARIO_HEART_MAX			99
#define DATA_FLOWER_CARD_BOX			1
#define DATA_STAR_CARD_BOX				2
#define DATA_MUSHROOM_CARD_BOX			3
#define DATA_SCORE_FOR_ONE_TIME			50
#define DATA_SUM_THREE_SIMILAR_FLOWER	3
#define DATA_SUM_THREE_SIMILAR_STAR		6
#define DATA_SUM_THREE_SIMILAR_MUSHROOM 9
#define DATA_SUM_THREE_DIFFERENT_CARD	6
#define DATA_SUM_TWO_SIMILAR_CARD		2
#define DATA_NUMBER_INCREASE_HEART_1	1
#define DATA_NUMBER_INCREASE_HEART_5	5
#define DATA_NUMBER_INCREASE_HEART_3	3
#define DATA_ID_PLAY_SCENE				5

class CData
{
	static CData* __instance;
	bool isConvertBrick;
	int card_box;

	int number_touch_card_box;
	int card_store_1;
	int card_store_2;
	int card_store_3;

	bool mario_go_down;
	bool mario_go_pipeline;
	bool mario_go_up;
	bool isDrawCardBox;
	bool isGoBackWorldMap;
	bool isResetGame;

	int mario_score;
	int mario_heart;
	int mario_coin;
	int mario_time;
public:
	CData()
	{
		this->isConvertBrick = false;
		this->mario_go_down = false;
		this->mario_go_up = false;
		this->mario_go_pipeline = false;
		this->isDrawCardBox = false;
		this->isGoBackWorldMap = false;
		this->isResetGame = false;
		
		this->card_box = 0;
		this->mario_score = 0;
		this->mario_coin = 0;

		this->number_touch_card_box = 0;
		this->card_store_1 = 0;
		this->card_store_2 = 0;
		this->card_store_3 = 0;
		
		//this->mario_heart = DATA_MARIO_HEART;
		this->mario_heart = 0;
		this->mario_time = 0;
	};
	void SetIsResetGame(bool isResetGame) { this->isResetGame = isResetGame; }
	bool GetIsResetGame() { return isResetGame; }

	void SetIsGoBackWorldMap(bool isGoBackWorldMap) { this->isGoBackWorldMap = isGoBackWorldMap; }
	bool GetIsGoBackWorldMap() { return isGoBackWorldMap; }

	int GetNumberTouchCard() { return number_touch_card_box; }

	void SetCardStore1(int card_store_1) { this->card_store_1 = card_store_1; }
	int GetCardStore1() { return card_store_1; }

	void SetCardStore2(int card_store_2) { this->card_store_2 = card_store_2; }
	int GetCardStore2() { return card_store_2; }

	void SetCardStore3(int card_store_3) { this->card_store_3 = card_store_3; }
	int GetCardStore3() { return card_store_3; }

	void SetIsDrawCardBox(bool isDrawCardBox) { this->isDrawCardBox = isDrawCardBox; }
	bool GetIsDrawCardBox() { return isDrawCardBox; }

	void SetIsMarioGoPipeline(bool mario_go_pipeline) { this->mario_go_pipeline = mario_go_pipeline; }
	bool GetIsMarioGoPipeline() { return mario_go_pipeline; }

	void SetIsMarioGoUp(bool mario_go_up) { this->mario_go_up = mario_go_up; }
	bool GetIsMarioGoUp() { return mario_go_up; }

	void SetIsMarioGoDown(bool mario_go_down) { this->mario_go_down = mario_go_down; }
	bool GetIsMarioGoDown() { return mario_go_down; }

	void SetIsConvertBrick(bool isConvertBrick) { this->isConvertBrick = isConvertBrick; }
	bool GetIsConvertBrick() { return isConvertBrick; }

	void SetCardBox(int card_box) { this->card_box = card_box; }
	int GetCardBox() { return card_box; }

	void SetMarioScore(int mario_score) { this->mario_score = mario_score; }
	int GetMarioScore() { return mario_score; }

	void SetMarioHeart(int mario_heart) { this->mario_heart = mario_heart; }
	int GetMarioHeart() { return mario_heart; }

	void SetMarioTime(int mario_time) { this->mario_time = mario_time; }
	int GetMarioTime() { return mario_time; }

	void SetMarioCoin(int mario_coin) { this->mario_coin = mario_coin; }
	int GetMarioCoin() { return mario_coin; }

	void IncreaseCoin() { mario_coin++; }
	void IncreaseHeart() { mario_heart++; }
	void DecreaseHeart() { mario_heart--; }
	void IncreaseNumberTouchCard() { number_touch_card_box++; }
	void IncreaseScore() { mario_score += DATA_MARIO_SCORE_ADJUST; }

	void SumCardBox() 
	{ 
		int sum_card_box = card_store_1 + card_store_2 + card_store_3;
		int sum_2_card = card_store_1 + card_store_2;
		//DebugOutTitle(L"sum_card_box: %d and card_store_1: %d and card_store_2: %d and card_store_3: %d", sum_card_box, card_store_1, card_store_2, card_store_3);
		if ((sum_2_card % DATA_SUM_TWO_SIMILAR_CARD == 0) && (sum_card_box == DATA_SUM_THREE_SIMILAR_FLOWER || sum_card_box == DATA_SUM_THREE_SIMILAR_STAR || sum_card_box == DATA_SUM_THREE_SIMILAR_MUSHROOM))
		{
			mario_heart += DATA_NUMBER_INCREASE_HEART_5;
		}
		else if (sum_card_box == DATA_SUM_THREE_DIFFERENT_CARD)
		{
			mario_heart += DATA_NUMBER_INCREASE_HEART_1;
		}
		else
		{
			mario_heart += DATA_NUMBER_INCREASE_HEART_3;
		}
	}

	void CaculationScoreTimeout(int time) 
	{ 
		mario_score += time * DATA_SCORE_FOR_ONE_TIME;
	}

	void ResetGame()
	{
		this->isResetGame = true;
		this->isConvertBrick = false;
		this->mario_go_down = false;
		this->mario_go_up = false;
		this->mario_go_pipeline = false;
		this->isDrawCardBox = false;
		this->isGoBackWorldMap = false;

		this->card_box = 0;
		this->mario_score = 0;
		this->mario_coin = 0;

		this->number_touch_card_box = 0;
		this->card_store_1 = 0;
		this->card_store_2 = 0;
		this->card_store_3 = 0;

		this->mario_heart = 4;
		this->mario_time = 0;
	}

	static CData* GetInstance();
	~CData() {};
};