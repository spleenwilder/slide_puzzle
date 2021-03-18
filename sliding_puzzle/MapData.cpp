// Draw a new level using the template at the bottom.
// Winning location should be an edge, and should be marked with a 'W'
// Add it to the game by creating a MapData instance and adding it to the array of levels

#include "MapData.hpp" // MapData class declaration

// Level 1

std::wstring level1[25] =
{
	L"#########################",
	L"####                #####",
	L"##                  #####",
	L"#          #####        #",
	L"#    ###   #####        #",
	L"########                #",
	L"########                #",
	L"###                     #",
	L"###                     #",
	L"###             #########",
	L"#               #########",
	L"#                       W",
	L"###     #################",
	L"###     #################",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#              #####    #",
	L"####           #####    #",
	L"####                    #",
	L"####                    #",
	L"########     #####      #",
	L"########     #####      #",
	L"########                #",
	L"#########################"
};

MapData Level1(22, 15, 24, 11, level1, mapWidth, mapHeight);

// Level 2

std::wstring level2[25] =
{
	L"############W############",
	L"####    ####            #",
	L"##      #### #######    #",
	L"##       ### #     #    #",
	L"#        ### #     #    #",
	L"#         ## #X         #",
	L"###XXXXXXX## ####     ###",
	L"###          ####     ###",
	L"###      ########     ###",
	L"#        ###            #",
	L"#      #####      #     #",
	L"#      ############     #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#####       #########   #",
	L"#####       #########   #",
	L"#           ##          #",
	L"#                       #",
	L"#                  ######",
	L"#                  ######",
	L"#                  ######",
	L"#####           #########",
	L"#####           #########",
	L"#########################"
};

MapData Level2(1, 4, 12, 0, level2, mapWidth, mapHeight);

// Array holding all levels
MapData Levels[] = { Level1, Level2 };

/*

Empty template level

std::wstring level_[25] =
{
	L"#########################",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#                       #",
	L"#########################"
};

*/
