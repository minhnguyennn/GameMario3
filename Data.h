#pragma once

#define DATA_MARIO_HEART 4
#define DATA_MARIO_GAME_TIMEOUT 300
#define DATA_MARIO_TIME_OUTMAP 7
#define DATA_MARIO_SCORE_ADJUST 50
#define DATA_MARIO_COIN_MAX 99
#define DATA_MARIO_HEART_MAX 99
#define DATA_FLOWER_CARD_BOX 1
#define DATA_STAR_CARD_BOX 2
#define DATA_MUSHROOM_CARD_BOX 3

class CData
{
	static CData* __instance;
	bool isConvertBrick;
	int card_box;
	bool mario_go_down;
	bool mario_go_pipeline;
	bool mario_go_up;
	bool isDrawCardBox;

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
		

		this->card_box = 0;
		this->mario_score = 0;
		this->mario_coin = 0;
		
		this->mario_heart = DATA_MARIO_HEART;
		this->mario_time = DATA_MARIO_GAME_TIMEOUT;
	};

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
	void IncreaseCardBox() { card_box++; }
	void IncreaseScore() { mario_score += DATA_MARIO_SCORE_ADJUST; }

	static CData* GetInstance();
	~CData() {};
};