#pragma once

class MapData
{
private:
	int playerX;
	int playerY;
	int winX;
	int winY;
	int width;
	int height;

	void setLines(std::wstring lines[], int length)
	{
		for (int i = 0; i < length; i++)
			mapLines += lines[i];
	}
public:
	MapData(int playerX, int playerY, int winX, int winY, std::wstring data[], int width, int height)
		: playerX{ playerX }
		, playerY{ playerY }
		, winX{ winX }
		, winY{ winY }
		, width{ width }
		, height{ height }
	{
		setLines(data, height);
	}

	std::wstring mapLines;

	std::wstring getLines()
	{
		return mapLines;
	}
	int* getPlayerPosition()
	{
		int position[2] = { playerX, playerY };
		return position;
	}
	int* getWinLocation()
	{
		int location[2] = { winX, winY };
		return location;
	}
	void draw(ScreenData& Screen)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				Screen.display[(boardY * Screen.width + boardX) + y * Screen.width + x] = (mapLines[y * height + x] == 'W') ? ' ' : mapLines[y * height + x];
			}
		}
	}
};