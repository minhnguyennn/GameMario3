#pragma once

//BBOX
#define PIPELINE_BBOX_HIDDEN_WIDTH		32
#define PIPELINE_BBOX_HIDDEN_HEIGHT		194
#define PIPELINE_BBOX_BIG_WIDTH			32
#define PIPELINE_BBOX_BIG_HEIGHT		48
#define PIPELINE_BBOX_SMALL_WIDTH		32
#define PIPELINE_BBOX_SMALL_HEIGHT		32

//DISTANCE
#define PIPELINE_DISTANCE_GREEN	3
#define PIPELINE_DISTANCE_RED	6

//ANIMATION
#define ID_ANI_SMALL_PIPELINE	6210
#define ID_ANI_BIG_PIPELINE		6200
#define ID_ANI_HIDDEN_PIPELINE		6211
#define ID_ANI_BLACK_PIPELINE_GO_UP		6212

//TYPE SUMMON PLANT
#define PIPELINE_TYPE_GREEN			1
#define PIPELINE_TYPE_RED			2
#define PIPELINE_TYPE_PIRANHA		3
#define PIPELINE_PLANT_ENOUGH		4

//TYPE PINELINE
#define PIPELINE_TYPE_SMALL			1
#define PIPELINE_TYPE_BIG			2
#define PIPELINE_TYPE_BIG_HIDDEN	3
#define PIPELINE_TYPE_SMALL_HIDDEN	4
#define PIPELINE_TYPE_BLACK_GO_UP	5

#include "GameObject.h"
#include "Data.h"
class CPipeline : public CGameObject
{
	int type_summon_plant;
	int type_pineline;
public:
	CPipeline(float x, float y, int type_summon_plant, int type_pineline) : CGameObject(x, y) 
	{
		this->type_summon_plant = type_summon_plant;
		this->type_pineline = type_pineline;
		SummonVenusFireTrap();
	}
	void Render();
	int IsCollidable() { return 0; }
	int IsBlocking() 
	{ 
		if (CData::GetInstance()->GetIsMarioGoPipeline()) return 0;
		else return 1; 
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SummonVenusFireTrap();
	int GetType() { return type_pineline; }
};