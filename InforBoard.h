#pragma once
#include"GameObject.h"
//ANIMATION
#define ID_ANI_GOSH_BOX		15008
//BBOX
#define GOSH_BOX_BBOX_WIDTH 16
#define GOSH_BOX_BBOX_HEIGHT 16
class CInforBoard : public CGameObject
{
public:
	CInforBoard(float x, float y) : CGameObject(x, y) {}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; };
};

