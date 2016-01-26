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
	Game(const unsigned int width, const unsigned int height,
		 const unsigned int numOfGrids);
	Game(const Game&) = delete;
	Game(const Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(const Game&&) = delete;

	void restart();
	void run();
private:
	void update(); //updates the game state
	void render(); //renders the objects to the screen
	void handleKeyEvents();
	/**
	  * Finds a new random position for the give Piece object within the
	  * boundaries of width and height of the board.
	  */
	void findRandomPosition(Piece&);
	void initGameOverText(sf::Text&) const;
private:
	//CONSTANTS
	//How many grids Snake will be at the begin
	const sf::Color BackgroundColor{189, 183, 107};
	const sf::Color SnakeColor{0, 100, 0};
	const sf::Color PieceColor{139, 69, 19};
	const sf::Vector2f InitialSnakePoint{0, 0};
	const size_t InitialSnakeSize{3};
	//How many seconds between each "tick"
	const double SecondsBetweenSteps{0.1};
	const float FPS{10.0f};
	const sf::Time TimePerFrame{sf::seconds(1.0f / FPS)};
	const int ScoreAdd{1};
private:
	enum class State
	{
		Playing,
		Paused,
		GameOver,
	};
	State mGameState{State::Paused}; //current state of the game
	//Object representing the Board. It stores the width, height and grid size
	Board mBoard;
	sf::RenderWindow mWindow; //main rendering window
	sf::Font mFont; //font that will be used throughout the game
	sf::Text mScoreText; //text object for drawing the player score
	Snake mSnake; //Snake object
	Piece mPiece; //Piece object that the Snake is trying to eat
	int mScore{0}; //Score of the player
};
#endif
