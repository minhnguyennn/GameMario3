#pragma once
#include "GameObject.h"
#include "debug.h"

#define ID_ANI_LEAF 12000

#define LEAF_BBOX_HEIGHT 16
#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT_DIE 7

#define LEAF_GRAVITY 0.00004f
#define LEAF_WALKING_SPEED 0.02f
#define MAX_VY 0.02f

#define	ADJUST_MAX_VX 0.025f
#define ADJUST_AX_WHEN_FALL 0.00001f

#define LEAF_DIE_TIMEOUT 500

#define LEAF_STATE_WALKING 100
#define LEAF_STATE_DIE 200

#define DISTANCE_LEAF_MAX 28

#define ID_ANI_LEAF_WALKING 12300	
#define ID_ANI_LEAF_DIE 12301	
class CLeaf : public CGameObject
{
protected:
	float ax;
	float ay;
	float start_position;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	//virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CLeaf(float x, float y);
	virtual void SetState(int state);
};

