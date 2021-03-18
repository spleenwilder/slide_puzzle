#pragma once

class ScreenData
{
public:
	int width;
	int height;
	wchar_t* display;
	ScreenData(int width, int height)
		: width{ width }
		, height{ height }
	{
		display = new wchar_t[width * height];
		display[width * height - 1] = '\0';
	}

	ScreenData(const ScreenData& sd) // copy constructor
	{
		width = sd.width;
		height = sd.height;

		display = new wchar_t[width * height];
		for (int i = 0; i < width * height; i++)
		{
			display[i] = sd.display[i];
		}
	}

	ScreenData& operator=(const ScreenData& other) // copy assignment operator
	{
		if (this != &other)
		{
			width = other.width;
			height = other.height;

			display = new wchar_t[width * height];
			for (int i = 0; i < width * height; i++)
			{
				display[i] = other.display[i];
			}
		}

		return *this;
	}

	ScreenData(ScreenData&& other) noexcept // move constructor
	{
		width = other.width;
		height = other.height;
		display = other.display;

		other.width = 0;
		other.height = 0;
		other.display = nullptr;
	}
	ScreenData& operator=(ScreenData&& other) noexcept // move assignment operator
	{
		if (this != &other)
		{
			delete[] display;

			display = other.display;
			width = other.width;
			height = other.height;

			other.display = nullptr;
			other.width = 0;
			other.height = 0;
		}

		return *this;
	}

	~ScreenData() // destructor
	{
		delete[] display;
	}
};