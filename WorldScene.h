#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "HudWorld.h"
#include"Map.h"

//POSITION BLACK BACKGROUND OF TABLE HUD
#define WORLDMAP_BLACK_BACKGROUND_ADJUST_X	96
#define WORLDMAP_BLACK_BACKGROUND_ADJUST_Y	193
#define CAM_POSITION_ADJUST	-7

class CWorldScene : public CScene
{
protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;

	CMap* current_map = NULL;
	CHudWorld* hud_world = NULL;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_TILEMAP_DATA(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	CWorldScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	virtual void CreateObject(LPGAMEOBJECT gameobject) 
	{ 
		objects.insert(objects.begin() + 1, gameobject); 
	}

	LPGAMEOBJECT GetPlayer() { return player; }
	vector<LPGAMEOBJECT> GetListObject() { return objects; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CWorldScene* LPWORLDSCENE;

