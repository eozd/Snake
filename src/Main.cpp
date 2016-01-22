/*
 * =============================================================================
 *
 *       Filename:  Main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/18/2016 04:09:44 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Esref Ozdemir (esref.ozdemir27@gmail.com)
 *   Organization:  None
 *
 * =============================================================================
 */

#include "Game.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
	int gridNumber = 0;
	const int DefaultGridNumber = 20;
	if (argc < 2) {
		gridNumber = DefaultGridNumber;
	} else if (argc > 2) {
		std::cerr << "Too many arguments!" << std::endl;
		return 1;
	} else {
		gridNumber = std::atoi(argv[1]);
		if (gridNumber <= 0) {
			std::cerr << "Grid number must be positive integer" << std::endl;
			return 1;
		}
	}
	Game game(500, 500, gridNumber);
	game.run();
}
