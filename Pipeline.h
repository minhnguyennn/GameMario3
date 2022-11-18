#pragma once

//BBOX
#define PIPELINE_BBOX_BIG_WIDTH		31
#define PIPELINE_BBOX_BIG_HEIGHT	47

#define PIPELINE_BBOX_SMALL_WIDTH	31
#define PIPELINE_BBOX_SMALL_HEIGHT	31

//DISTANCE
#define PIPELINE_DISTANCE_GREEN	3
#define PIPELINE_DISTANCE_RED	6

//ANIMATION
#define ID_ANI_SMALL_PIPELINE	6010
#define ID_ANI_BIG_PIPELINE		6000

//TYPE SUMMON PLANT
#define PIPELINE_TYPE_GREEN		1
#define PIPELINE_TYPE_RED		2
#define PIPELINE_TYPE_PIRANHA	3

//TYPE PINELINE
#define PIPELINE_TYPE_SMALL		1
#define PIPELINE_TYPE_BIG		2

#include "GameObject.h"
class CPipeline : public CGameObject
{
	int type_summon_plant;
	int type_pineline;
public:
	CPipeline(float x, float y, int type_summon_plant, int type_pineline) : CGameObject(x, y) {
		this->type_summon_plant = type_summon_plant;
		this->type_pineline = type_pineline;
		SummonVenusFireTrap();
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsCollidable() { return 0; }
	int IsBlocking() { return 1; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SummonVenusFireTrap();
};

