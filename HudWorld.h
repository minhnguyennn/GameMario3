#pragma once
//point
#define ID_ANI_HUD_WORLD_0	12
#define ID_ANI_HUD_WORLD_1	11
#define ID_ANI_HUD_WORLD_2	21
#define ID_ANI_HUD_WORLD_3	31
#define ID_ANI_HUD_WORLD_4	42
#define ID_ANI_HUD_WORLD_5	52
#define ID_ANI_HUD_WORLD_6	62
#define ID_ANI_HUD_WORLD_7	71
#define ID_ANI_HUD_WORLD_8	81
#define ID_ANI_HUD_WORLD_9	91

//background black
#define ID_ANI_HUD_WORLD_BA_BLACK		102

//table_hud
#define ID_ANI_HUD_WORLD_TABLE_HUD	107

//arrow_power
#define ID_ANI_HUD_WORLD_ARROW_POWER	53

//power_M
#define ID_ANI_HUD_WORLD_POWER_M		43

//power_P
#define ID_ANI_HUD_WORLD_POWER_P		63

class CHudWorld
{
private:
	float x;
	float y;
public:
	CHudWorld(float x, float y);
	void DrawNumber(int number, float position_x, float position_y);
	void DrawPower(int power, float position_x, float position_y);
	void Render();
};

