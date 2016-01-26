/*
 * =============================================================================
 *
 *       Filename:  Game.cpp
 *
 *    Description:  Definition of Game class
 *
 *        Version:  1.0
 *        Created:  01/18/2016 04:11:31 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Esref Ozdemir (esref.ozdemir27@gmail.com)
 *   Organization:  None
 *
 * =============================================================================
 */

#include <string>
#include <cstdlib>
#include <iostream>
#include "Game.hpp"
#include "Direction.hpp"

Game::Game(const unsigned int width, const unsigned int height,
		   const unsigned int numOfGrids)
	: mBoard(width, height, numOfGrids)
	, mWindow(sf::VideoMode(width, height + height / numOfGrids),"Snake")
	, mFont()
	, mScoreText()
	, mSnake(InitialSnakePoint, InitialSnakeSize, height / numOfGrids,
			 direction::Right)
	, mPiece(0, 0, height / numOfGrids)
{
	if (width <= 0 || height <= 0 || width != height) {
		throw std::invalid_argument("Window must be square");
	}
	if (!mFont.loadFromFile("assets/Inconsolata.otf")) {
		throw std::runtime_error("Game ctor: Failed to load Inconsolata.otf");
	}
	mScoreText.setFont(mFont);
	mScoreText.setPosition(0, height);
	mScoreText.setColor(sf::Color::Red);
	mScoreText.setCharacterSize(25);
	mScoreText.setString("Score: " + std::to_string(mScore));
	mPiece.setFillColor(PieceColor);
	mSnake.setFillColor(SnakeColor);
	mWindow.setVerticalSyncEnabled(true);
	mWindow.clear(BackgroundColor);
}

void Game::restart()
{
	unsigned int gridSize = mBoard.getWidth() / mBoard.getNumOfGrids();
	mScore = 0;
	mScoreText.setString("Score:" + std::to_string(mScore));
	mSnake = Snake(InitialSnakePoint, InitialSnakeSize, gridSize,
				   direction::Right);
	this->findRandomPosition(mPiece);
	mGameState = State::Playing;
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen()) {
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			handleKeyEvents();
			if (mGameState == State::Playing) {
				update();
			}
		}
		render();
	}
}

void Game::update()
{
	if (mSnake.isDead() || !mBoard.contains(mSnake.getHead())) {
		mGameState = State::GameOver;
	}
	float gridSize = (float)mBoard.getWidth() / mBoard.getNumOfGrids();
	mSnake.move(gridSize);
	if (mPiece.atTheSamePosition(mSnake.getHead().getPosition())) {
		mSnake.addPiece(mPiece);
		mScore += ScoreAdd;
		mScoreText.setString("Score:" + std::to_string(mScore));
		this->findRandomPosition(mPiece);
	}
}

void Game::render()
{
	mWindow.clear(BackgroundColor);
	switch (mGameState) {
	case State::Playing:
	case State::Paused:
		mWindow.draw(mPiece);
		mWindow.draw(mSnake);
		mWindow.draw(mScoreText);
		break;
	case State::GameOver:
	{
		static sf::Text gameOverText;
		static bool gameOverTextInitialized{false};
		if (!gameOverTextInitialized) {
			initGameOverText(gameOverText);
		}
		mWindow.draw(gameOverText);
		mWindow.draw(mScoreText);
		break;
	}
	default:
		break;
	}
	mWindow.display();
}

void Game::handleKeyEvents()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		mWindow.close();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
		if (mGameState == State::Playing) {
			mGameState = State::Paused;
		} else if (mGameState == State::Paused) {
			mGameState = State::Playing;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
		this->restart();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		mSnake.setDirection(direction::Up);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		mSnake.setDirection(direction::Down);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		mSnake.setDirection(direction::Left);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		mSnake.setDirection(direction::Right);
}

void Game::findRandomPosition(Piece& p)
{
	float gridSize = (float)mBoard.getWidth() / mBoard.getNumOfGrids();
	while (true) {
		unsigned int xGridPos = static_cast<unsigned int>(std::rand())
							  % mBoard.getNumOfGrids();
		unsigned int yGridPos = static_cast<unsigned int>(std::rand())
							  % mBoard.getNumOfGrids();
		sf::Vector2f newPos(xGridPos * gridSize, yGridPos * gridSize);
		p.setPosition(newPos);
		if (!mSnake.contains(p)) {
			break;
		}
	}
}

void Game::initGameOverText(sf::Text& gameOverText) const
{
	gameOverText.setFont(mFont);
	gameOverText.setColor(sf::Color::Black);
	gameOverText.setCharacterSize(60);
	gameOverText.setString("GAME OVER");
	sf::FloatRect rect = gameOverText.getLocalBounds();
	gameOverText.setOrigin(rect.left + rect.width / 2,
						   rect.top + rect.height / 2);
	gameOverText.setPosition(mBoard.getWidth() / 2, mBoard.getHeight() / 2);
}
