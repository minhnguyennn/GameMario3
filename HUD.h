#pragma once
//point
#define ID_ANI_HUD_0	10
#define ID_ANI_HUD_1	1
#define ID_ANI_HUD_2	2
#define ID_ANI_HUD_3	3
#define ID_ANI_HUD_4	4
#define ID_ANI_HUD_5	5
#define ID_ANI_HUD_6	6
#define ID_ANI_HUD_7	7
#define ID_ANI_HUD_8	8
#define ID_ANI_HUD_9	9

//background black
#define ID_ANI_HUD_BA_BLACK		101

//table_hud
#define ID_ANI_HUD_TABLE_HUD	100

//arrow_power
#define ID_ANI_HUD_ARROW_POWER	50

//power_M
#define ID_ANI_HUD_POWER_M		40

//power_P
#define ID_ANI_HUD_POWER_P		60

class CHUD 
{
private:
	float x;
	float y;
public:
	CHUD(float x, float y);
	void DrawNumber(int number, float position_x, float position_y);
	void DrawPower(int power, float position_x, float position_y);
	void Render();
};