#pragma once

#include "GameObject.h"

//ANIMATION
#define ID_ANI_CARD_BOX_RANDOM 11200
#define ID_ANI_FLOWER_CARD 11201
#define ID_ANI_STAR_CARD 11202
#define ID_ANI_MUSHROOM_CARD 11203

//BBOX
#define CARD_BOX_BBOX_WIDTH 16
#define CARD_BOX_BBOX_HEIGHT 16

//STATE
#define CARD_BOX_STATE_UP	1
#define CARD_BOX_STATE_SUMMON 2
#define CARD_BOX_STATE_RANDOM 3

//PROPERTY
#define	CARD_BOX_SPEED_Y	0.1f

//TIME
#define CARD_BOX_UP_TIMEOUT	1000

//DRAW
#define CARD_BOX_DRAW_FLOWER 1
#define CARD_BOX_DRAW_STAR 2
#define CARD_BOX_DRAW_MUSHROOM 3

class CCardBox : public CGameObject 
{
	int random_card_box;
	bool isUp;
	bool isRandom;
	bool isFlower;
	bool isStar;
	bool isMushRoom;
	ULONGLONG time_line;
public:
	CCardBox(float x, float y) : CGameObject(x, y)
	{
		time_line = 0;
		isUp = false;
		isRandom = true;
		isFlower = false;
		isStar = false;
		isMushRoom = false;
		random_card_box = 0;
	}
	void OnNoCollision(DWORD dt);
	void SetState(int state);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; };
	bool CountDownTimer(int time);
	int SetupRandomCardBox();
};