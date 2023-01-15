#include "Pipeline.h"
#include "debug.h"
#include "PlayScene.h"
#include "VenusFireTrap.h"
#include"debug.h"

void CPipeline::Render()
{
	if (!checkObjectInCamera()) return;
	int aniId = 0;
	if (type_pineline == PIPELINE_TYPE_SMALL) aniId = ID_ANI_SMALL_PIPELINE;
	else if (type_pineline == PIPELINE_TYPE_BIG_HIDDEN) aniId = ID_ANI_HIDDEN_PIPELINE;
	else if (type_pineline == PIPELINE_TYPE_SMALL_HIDDEN) aniId = ID_ANI_SMALL_PIPELINE;
	else if (type_pineline == PIPELINE_TYPE_BLACK_GO_UP) aniId = ID_ANI_BLACK_PIPELINE_GO_UP;
	else aniId = ID_ANI_BIG_PIPELINE;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CPipeline::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (type_pineline == PIPELINE_TYPE_BIG)
	{
		l = x - PIPELINE_BBOX_BIG_WIDTH / 2;
		t = y - PIPELINE_BBOX_BIG_HEIGHT / 2;
		r = l + PIPELINE_BBOX_BIG_WIDTH;
		b = t + PIPELINE_BBOX_BIG_HEIGHT;
	}
	else if (type_pineline == PIPELINE_TYPE_BIG_HIDDEN)
	{
		l = x - PIPELINE_BBOX_HIDDEN_WIDTH / 2;
		t = y - PIPELINE_BBOX_HIDDEN_HEIGHT / 2;
		r = l + PIPELINE_BBOX_HIDDEN_WIDTH;
		b = t + PIPELINE_BBOX_HIDDEN_HEIGHT;
	}
	else 
	{
		l = x - PIPELINE_BBOX_SMALL_WIDTH / 2;
		t = y - PIPELINE_BBOX_SMALL_HEIGHT / 2;
		r = l + PIPELINE_BBOX_SMALL_WIDTH;
		b = t + PIPELINE_BBOX_SMALL_HEIGHT;
	}
}

void CPipeline::SummonVenusFireTrap()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	if (type_summon_plant == PIPELINE_TYPE_GREEN) {
		CVenusFireTrap* vft_green = new CVenusFireTrap(x, y, VFTRAP_TYPE_GREEN);
		scene->CreateObject(vft_green);
	}
	else if (type_summon_plant == PIPELINE_TYPE_RED) {
		CVenusFireTrap* vft_red = new CVenusFireTrap(x, y - PIPELINE_DISTANCE_RED, VFTRAP_TYPE_RED);
		scene->CreateObject(vft_red);
	}
	else if (type_summon_plant == PIPELINE_TYPE_PIRANHA)
	{
		CVenusFireTrap* piranha = new CVenusFireTrap(x, y, VFTRAP_TYPE_PIRANHA);
		scene->CreateObject(piranha);
	}
}