// ASCII art generated from http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20

#include <iostream>
#include <Windows.h>
#include <unordered_set>
#include <thread>
#include <chrono>
#include "config.hpp"         // Constants for game settings
#include "ScreenData.hpp"     // ScreenData class declaration
#include "MapData.cpp"        // Initializes levels and loads them into an array called Levels[]
#include "sliding_puzzle.hpp" // Function declarations

int main()
{
	// Array of utf16 characters to fill screen
	//wchar_t* screen = new wchar_t[screenWidth * screenHeight];
	//screen[screenWidth * screenHeight - 1] = '\0';
	ScreenData Screen(screenWidth, screenHeight);

	// Handles creating the console buffer so it won't scroll
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	// Data about the current level
	std::wstring map;
	int playerPosition;
	int winLocation;
	int currentLevel = 1;
	int moveCount = 0;

	// Contains all characters that will stop movement
	std::unordered_set <char> walls;
	walls.insert(wall);
	walls.insert(breakable);
	walls.insert(breaking);

	// Initializes map, playerPosition, and winLocation with data from current level
	MapData currentMap = Levels[currentLevel - 1];
	loadMap(currentMap, playerPosition, winLocation, Screen);

	int previousPosition = playerPosition;

	// Prevents changing direction mid-move
	Control controls;
	controls.enable();

	bool newLevel = false;

	GameState gameState = i;

	// Game loop
	while (!GetAsyncKeyState(0x1B)) // 'esc' key
	{
		// Fill screen with blanks
		for (int i = 0; i < Screen.width * screenHeight - 1; i++)
			Screen.display[i] = ' ';

		// Draw title
		for (int y = 0; y < titleHeight; y++)
		{
			for (int x = 0; x < titleWidth; x++)
			{
				Screen.display[(titleY * Screen.width + titleX) + (screenWidth * y) + x] = title[y][x];
			}
		}
		
		// Draw game board
		currentMap.draw(Screen);

		// Draw player's starting position
		Screen.display[playerPosition] = playerSprite;

		// Draw current level and move count
		printDisplay(currentLevel, levelDisplay, 5, levelX, levelY, Screen);
		printDisplay(moveCount, moveDisplay, 6, moveX, moveY, Screen);
		printMessage(L"Move:    WASD", moveX, moveY + 4, Screen);
		printMessage(L"Reset:   R", moveX, moveY + 5, Screen);
		printMessage(L"Exit:    Esc", moveX, moveY + 6, Screen);

		// Controls
		if (GetAsyncKeyState(0x41) && controls.enabledLeft) // 'a' key
		{
			gameState = l;
			controls.disable('a');
			if (walls.find(Screen.display[playerPosition + gameState]) == walls.end()) moveCount++;
		}

		if (GetAsyncKeyState(0x44) && controls.enabledRight) // 'd' key
		{
			gameState = r;
			controls.disable('d');
			if (walls.find(Screen.display[playerPosition + gameState]) == walls.end()) moveCount++;
		}

		if (GetAsyncKeyState(0x57) && controls.enabledUp) // 'w' key
		{
			gameState = u;
			controls.disable('w');
			if (walls.find(Screen.display[playerPosition + gameState]) == walls.end()) moveCount++;
		}

		if (GetAsyncKeyState(0x53) && controls.enabledDown) // 's' key
		{
			gameState = d;
			controls.disable('s');
			if (walls.find(Screen.display[playerPosition + gameState]) == walls.end()) moveCount++;
		}

		if (GetAsyncKeyState(0x52)) // 'r' key  --  reset level. Allowed regardless of control state
		{
			gameState = i;
			controls.enable();
			moveCount = 0;
			currentMap = Levels[currentLevel - 1];
			loadMap(currentMap, playerPosition, winLocation, Screen);
		}

		// Check for winning state
		if (playerPosition == winLocation)
		{
			gameState = i;
			moveCount = 0;
			currentLevel++;
			newLevel = true;
			controls.disable('n');

			if (currentLevel <= levelCount)
			{
				currentMap = Levels[currentLevel - 1];
				loadMap(currentMap, playerPosition, winLocation, Screen);
			}
			else break;
		}
		// Update according to game state
		if (walls.find(Screen.display[playerPosition + gameState]) != walls.end())
		{
			if (Screen.display[playerPosition + gameState] == breakable && previousPosition != playerPosition)
			{
				currentMap.mapLines[mapWidth * (((playerPosition + gameState - ((playerPosition + gameState) % Screen.width)) / Screen.width) - boardY) + ((playerPosition + gameState) % Screen.width - boardX)] = breaking;
				previousPosition = playerPosition;
			}
			else if (Screen.display[playerPosition + gameState] == breaking && previousPosition != playerPosition)
			{
				currentMap.mapLines[mapWidth * (((playerPosition + gameState - ((playerPosition + gameState) % Screen.width)) / Screen.width) - boardY) + ((playerPosition + gameState) % Screen.width - boardX)] = ' ';
				previousPosition = playerPosition;

				switch (gameState)
				{
				case u:
					controls.enabledUp = false;
					break;
				case d:
					controls.enabledDown = false;
					break;
				case r:
					controls.enabledRight = false;
					break;
				case l:
					controls.enabledLeft = false;
					break;
				}
			}
			gameState = i;
		}
		else
		{
			Screen.display[playerPosition] = ' ';
			Screen.display[playerPosition + gameState] = playerSprite;
			previousPosition = playerPosition;
			playerPosition += gameState;

			// Vertical speed doubled to account for font size being taller than it is wide
			// TODO: detect terminal font's height/width ratio and calculate appropriate multiplier automatically
			if (gameState == u || gameState == d)
				std::this_thread::sleep_for(std::chrono::milliseconds(gameSpeed * 2));
			else
				std::this_thread::sleep_for(std::chrono::milliseconds(gameSpeed));
		}

		// Return control to player
		if (gameState == i)
		{
			controls.enable();
		}

		// Draw screen to console. Fourth argument is the coordinates being written to, {0, 0} prevents scrolling
		WriteConsoleOutputCharacter(hConsole, Screen.display, Screen.width * screenHeight, { 0, 0 }, &dwBytesWritten);
	}

	std::cout << "Thanks for playing!" << std::endl;

	return 0;
}

void loadMap(MapData currentLevel, int& playerPosition, int& winLocation, ScreenData Screen)
{
	playerPosition = (boardY * Screen.width) + boardX + (Screen.width * currentLevel.getPlayerPosition()[1] + currentLevel.getPlayerPosition()[0]);
	winLocation = (boardY * Screen.width) + boardX + (Screen.width * currentLevel.getWinLocation()[1] + currentLevel.getWinLocation()[0]);
}

void printDisplay(int count, const std::wstring display, int length, int dispX, int dispY, ScreenData& Screen)
{
	if (count != 999)
	{
		for (int i = 0; i < length; i++)
		{
			Screen.display[Screen.width * dispY + dispX + i] = display[i];
		}
		for (int j = length; j < 7; j++)
		{
			Screen.display[Screen.width * dispY + dispX + j] = ' ';
		}
		Screen.display[Screen.width * dispY + dispX + 7] = (count < 100) ? ' ' : '0' + ((count - count % 100) / 100) % 100;
		Screen.display[Screen.width * dispY + dispX + 8] = (count < 10) ? ' ' : '0' + ((count - count % 10) / 10) % 10;
		Screen.display[Screen.width * dispY + dispX + 9] = '0' + count % 10;
	}
}

void printMessage(const std::wstring message, int dispX, int dispY, ScreenData& Screen)
{
	int i = 0;
	while (message[i] != '\0')
	{
		Screen.display[Screen.width * dispY + dispX + i] = message[i];
		i++;
	}
}