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

#include <cstdlib>
#include <iostream>
#include "Game.hpp"
#include "Direction.hpp"

Game::Game(const int width, const int height, const int numOfGrids)
	: mGridSize(width / (float)numOfGrids)
	, mNumOfGrids(numOfGrids)
	, mInitialSnakeSize(5)
	, mSecondsBetweenSteps(0.1)
	, mWindow(sf::VideoMode((unsigned int)width, (unsigned int)height), "Snake")
	, mBoard(width, height, numOfGrids)
	, mSnake(sf::Vector2f(0, 0), mInitialSnakeSize, mGridSize, direction::Right)
	, mPiece(0, 0, mGridSize)
	
{
	if (width <= 0 || height <= 0 || width != height) {
		throw std::invalid_argument("Window must be square");
	}
	mPiece.setFillColor(sf::Color::Red);
	mSnake.setFillColor(sf::Color::Black);
	this->findRandomPosition(mPiece);
	mWindow.setVerticalSyncEnabled(true);
	mWindow.clear(sf::Color::White);
}

void Game::run()
{
	while (mWindow.isOpen() && !mSnake.isDead() && mBoard.contains(mSnake)) {
		handleEvents();
		update();
		render();
		//wait for the give amount
		sf::Clock clock;
		while (clock.getElapsedTime().asSeconds() < mSecondsBetweenSteps);
	}
}

void Game::update()
{
	mSnake.move();
	if (mSnake.getHead().atTheSamePosition(mPiece)) {
		mSnake.addPiece(mPiece);
		this->findRandomPosition(mPiece);
	}
}

void Game::render()
{
	mWindow.clear(sf::Color::White);
	mWindow.draw(mBoard);
	mWindow.draw(mPiece);
	mWindow.draw(mSnake);
	mWindow.display();
}

void Game::handleEvents()
{
	sf::Event e;
	while (mWindow.pollEvent(e)) {
		switch (e.type) {
		case sf::Event::Closed:
			mWindow.close();
			break;
		case sf::Event::KeyPressed:
			handleKeyEvents(e.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handleKeyEvents(e.key.code, false);
			break;
		default:
			break;
		}
	}
}

void Game::handleKeyEvents(const sf::Keyboard::Key key, const bool pressed)
{
	if (pressed) {
		switch (key) {
		case sf::Keyboard::Up:
			mSnake.setDirection(direction::Up);
			break;
		case sf::Keyboard::Down:
			mSnake.setDirection(direction::Down);
			break;
		case sf::Keyboard::Left:
			mSnake.setDirection(direction::Left);
			break;
		case sf::Keyboard::Right:
			mSnake.setDirection(direction::Right);
			break;
		default:
			mSnake.setDirection(direction::NoDirection);
			break;
		}
	}
}

void Game::findRandomPosition(Piece& p)
{
	while (true) {
		int xGridPos = std::rand() % mNumOfGrids;
		int yGridPos = std::rand() % mNumOfGrids;
		sf::Vector2f newPos(xGridPos * mGridSize, yGridPos * mGridSize);
		p.setPosition(newPos);
		if (!mSnake.contains(p)) {
			break;
		}
	}
}
