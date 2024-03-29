#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "HUD.h"
#include"Map.h"
#include "Goomba.h"
//#include "Koopas.h"

#define PLSCENE_MAP_MAX_X	3200

#define PLSCENE_HIDDEN_MAP_MAX_Y_CAM	16
#define PLSCENE_HIDDEN_MAP_MIN_Y_CAM	-8

#define PLSCENE_MIN_X_CAM	0

#define PLSCENE_MAX_X_CAM	2554
#define PLSCENE_MAX_Y_CAM	256
#define PLSCENE_MIN_Y_CAM	0

//POSITION BLACK BACKGROUND OF TABLE HUD
#define BLACK_BACKGROUND_ADJUST_X	100
#define BLACK_BACKGROUND_ADJUST_Y	193



class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					
	CMap* current_map = NULL;
	CMap* hidden_map = NULL;

	CHUD* hud = NULL;
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_TILEMAP_DATA(string line);
	void _ParseSection_HIDDEN_DATA(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual void CreateObject(LPGAMEOBJECT gameobject) {objects.insert(objects.begin() + 1, gameobject); }

	LPGAMEOBJECT GetPlayer() { return player; }
	vector<LPGAMEOBJECT> GetListObject() { return objects; }
	CMap* GetMap() { return current_map; }



	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

