#include <iostream>
#include <fstream>
#include "AssetIDs.h"
#include "WorldScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include"debug.h"
#include "HUD.h"
#include "MarioWorld.h"
#include "WorldKeyEvent.h"
#include "MarioWorld.h"
#include "Grass.h"
#include "GoshBox.h"
#include "KoopaWorld.h"
#include "Help.h"
#include "Door.h"

using namespace std;

CWorldScene::CWorldScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	player = NULL;
	key_handler = new CWorldKeyEvent(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_TILEMAP 3

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2


#define MAX_SCENE_LINE 1024

void CWorldScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CWorldScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CWorldScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (unsigned int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CWorldScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO_WORLD:
	{
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMarioWorld(x, y);
		player = (CMarioWorld*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	}
	case OBJECT_TYPE_GRASS_WORLD:
	{
		obj = new CGrass(x, y);
		break;
	}
	case OBJECT_TYPE_KOOPA_WORLD:
	{
		obj = new CKoopaWorld(x, y);
		break;
	}
	case OBJECT_TYPE_HELP_WORLD:
	{
		obj = new CHelp(x, y);
		break;
	}
	case OBJECT_TYPE_DOOR_WORLD:
	{
		int type = (int)atof(tokens[3].c_str());
		obj = new CDoor(x, y, type);
		break;
	}
	case OBJECT_TYPE_GOSH_BOX_WORLD:
	{
		obj = new CGoshBox(x, y);
		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	objects.push_back(obj);
}

void CWorldScene::_ParseSection_TILEMAP_DATA(string line)
{
	int ID, rowMap, columnMap, columnTile, rowTile, totalTiles, startX, startY;
	LPCWSTR path = ToLPCWSTR(line);
	ifstream f;

	f.open(path);
	f >> ID >> rowMap >> columnMap >> rowTile >> columnTile >> totalTiles >> startX >> startY;
	//Init Map Matrix

	int** TileMapData = new int* [rowMap];
	for (int i = 0; i < rowMap; i++)
	{
		TileMapData[i] = new int[columnMap];
		for (int j = 0; j < columnMap; j++)
		{
			f >> TileMapData[i][j];
		}

	}
	f.close();

	current_map = new CMap(ID, rowMap, columnMap, rowTile, columnTile, totalTiles, startX, startY);
	current_map->ExtractTileFromTileSet();
	current_map->SetTileMapData(TileMapData);
}

void CWorldScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CWorldScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[TILEMAP]") { section = SCENE_SECTION_TILEMAP; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; };

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_TILEMAP: _ParseSection_TILEMAP_DATA(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CWorldScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	CGame::GetInstance()->SetCamPos(CAM_POSITION_ADJUST, CAM_POSITION_ADJUST);

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	

	PurgeDeletedObjects();
}

void CWorldScene::Render()
{
	current_map->Render();

	CGame* game = CGame::GetInstance();
	float cam_x = game->GetCamX() + WORLDMAP_BLACK_BACKGROUND_ADJUST_X;
	float cam_y = game->GetCamY() + WORLDMAP_BLACK_BACKGROUND_ADJUST_Y;
	hud_world = new CHudWorld(cam_x, cam_y);

	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	hud_world->Render();
}

/*
*	Clear all objects from this scene
*/
void CWorldScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CWorldScene::Unload()
{

	for (unsigned int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();

	delete current_map;
	current_map = nullptr;

	delete hud_world;
	hud_world = nullptr;

	
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CWorldScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CWorldScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CWorldScene::IsGameObjectDeleted),
		objects.end());
}