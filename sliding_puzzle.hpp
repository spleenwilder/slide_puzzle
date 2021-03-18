#pragma once

void loadMap(MapData currentLevel, int& playerPosition, int& winLocation, ScreenData Screen);

void printDisplay(int count, const std::wstring display, int length, int dispX, int dispY, ScreenData& Screen);

void printMessage(const std::wstring message, int dispX, int dispY, ScreenData& Screen);

enum GameState
{
	l = -1,                 // left
	r = 1,                  // right
	u = -screenWidth,       // up
	d = screenWidth,        // down
	i = 0,                  // waiting for player input
};

struct Control
{
	bool enabledUp;
	bool enabledDown;
	bool enabledRight;
	bool enabledLeft;
	
	char disableTrigger;

	void enable()
	{
		if (disableTrigger == 'w')
		{
			if (!GetAsyncKeyState(0x57)) enabledUp = true;
		}
		else if (disableTrigger != 'n') enabledUp = true;

		if (disableTrigger == 's')
		{
			if (!GetAsyncKeyState(0x53)) enabledDown = true;
		}
		else if (disableTrigger != 'n') enabledDown = true;

		if (disableTrigger == 'd')
		{
			if (!GetAsyncKeyState(0x44)) enabledRight = true;
		}
		else if (disableTrigger != 'n') enabledRight = true;

		if (disableTrigger == 'a')
		{
			if (!GetAsyncKeyState(0x41)) enabledLeft = true;
		}
		else if (disableTrigger != 'n') enabledLeft = true;

		if (disableTrigger == 'n') // new level
		{
			if (!GetAsyncKeyState(0x41) && !GetAsyncKeyState(0x44) && !GetAsyncKeyState(0x53) && !GetAsyncKeyState(0x57))
			{
				enabledUp = true;
				enabledDown = true;
				enabledRight = true;
				enabledLeft = true;
			}
		}
	}

	void disable(char key)
	{
		enabledUp = false;
		enabledDown = false;
		enabledRight = false;
		enabledLeft = false;

		disableTrigger = key;
	}
};