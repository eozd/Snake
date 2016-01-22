#ifndef GAME_HPP
#define GAME_HPP
/*
 * =============================================================================
 *
 *       Filename:  Game.hpp
 *
 *    Description:  Main Game class handling the main game loop
 *
 *        Version:  1.0
 *        Created:  01/18/2016 04:10:24 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Esref Ozdemir (esref.ozdemir27@gmail.com)
 *   Organization:  None
 *
 * =============================================================================
 */

#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Board.hpp"

class Game
{
public:
	Game(const int width, const int height, const int numOfGrids);
	Game(const Game&) = delete;
	Game(const Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(const Game&&) = delete;

	void run();
private:
	void update(); //updates the game state
	void render(); //renders the objects to the screen
	void handleEvents(); //handles all events
	//pressed = true ==> pressed; pressed = false ==> released
	void handleKeyEvents(const sf::Keyboard::Key key, const bool pressed);
	/**
	  * Finds a new random position for the give Piece object within the
	  * boundaries of width and height of the board.
	  */
	void findRandomPosition(Piece&);
private:
	//CONSTANTS
	const float mGridSize; //Length of a single edge of a grid.
	const int mNumOfGrids; //Number of grids in one edge of the Board.
	const size_t mInitialSnakeSize; //How many grids Snake will be at the begin
	const double mSecondsBetweenSteps; //How many seconds between each "tick"
private:
	//MEMBERS
	sf::RenderWindow mWindow; //main rendering window
	Board mBoard; //Object representing the Board. It handles how the Board is
				  //drawn and the stuff related to the width and height of the
				  //Board
	Snake mSnake; //Snake object
	Piece mPiece; //Piece object that the Snake is trying to eat
	int mScore; //Score of the player
};
#endif
