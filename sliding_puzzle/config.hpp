#pragma once

// Screen size
constexpr int screenWidth = 120;
constexpr int screenHeight = 30;

// Speed of player movement
constexpr int gameSpeed = 20;

// Map size
constexpr int mapWidth = 25;
constexpr int mapHeight = 25;

// How far down and to the right the game board is drawn
constexpr int boardX = 80;
constexpr int boardY = 3;

// Constants for displaying move count and current level
const std::wstring moveDisplay = L"Moves:";
constexpr int moveX = 8;
constexpr int moveY = 19;
const std::wstring levelDisplay = L"Level";
constexpr int levelX = 8;
constexpr int levelY = 17;

// Number of levels currently written
constexpr int levelCount = 2;

// Wall representation
constexpr char wall = '#';
constexpr char breakable = 'X';
constexpr char breaking = 'x';

// Player representation
constexpr char playerSprite = 'O';

// Title
constexpr int titleX = 20;
constexpr int titleY = 3;
constexpr int titleWidth = 23;
constexpr int titleHeight = 6;
const std::wstring title[] =
{
	LR"(  _____ _ _     _      )",
	LR"( / ____| (_)   | |     )",
	LR"(| (___ | |_  __| | ___ )",
	LR"( \___ \| | |/ _` |/ _ \)",
	LR"( ____) | | | (_| |  __/)",
	LR"(|_____/|_|_|\__,_|\___|)"
};
