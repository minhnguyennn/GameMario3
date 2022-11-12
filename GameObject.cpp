#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
	state = -1;
	isDeleted = false;
}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l,t,r,b; 

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy; 
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, &rect, BBOX_ALPHA);
}

bool CGameObject::checkObjectInCamera() {
	float cam_x = CGame::GetInstance()->GetCamX();
	float cam_y = CGame::GetInstance()->GetCamY();
	float cam_x_end = cam_x + SCREEN_WIDTH_CAMERA_DRAW;
	float cam_y_end = cam_y + SCREEN_HEIGHT_CAMERA_DRAW;

	if (x <= cam_x || cam_x_end <= x) { return false; }
	if (y <= cam_y || cam_y_end <= y) { return false; }
	return true;
}

CGameObject::~CGameObject()
{

}
