/*
 * =============================================================================
 *
 *       Filename:  Snake.cpp
 *
 *    Description:  Definition of Snake object
 *
 *        Version:  1.0
 *        Created:  01/18/2016 05:07:18 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Esref Ozdemir (esref.ozdemir27@gmail.com)
 *   Organization:  None
 *
 * =============================================================================
 */

#include <iterator>
#include <iostream>
#include <stdexcept>
#include "Snake.hpp"

Snake::Snake(const sf::Vector2f& pos, const size_t length,
			 const float gridSize, const direction::Direction dir)
	: mGridSize(gridSize)
	, mPieces() //vector is default initialized
{
	//offsets in the current movement direction
	sf::Vector2f offsets(direction::getMoveOffsets(dir));
	//need to reverse it so that we can place the remaining pieces at the back
	//of this Snake
	offsets = -offsets;
	for (size_t i = 0; i < length; ++i) {
		float xPos = pos.x + i * offsets.x * gridSize;
		float yPos = pos.y + i * offsets.y * gridSize;
		Piece p(xPos, yPos, gridSize);
		p.setDirection(dir); //given direction
		p.setFillColor(sf::Color::Black); //default color
		mPieces.push_back(p);
	}
}

const Piece& Snake::getHead() const
{
	return mPieces.front();
}

void Snake::setPosition(const sf::Vector2f& pos)
{
	this->setPosition(pos.x, pos.y);
}

void Snake::setPosition(const float x, const float y)
{
	sf::Vector2f oldPosition = mPieces.front().getPosition();
	sf::Vector2f headNewPos(x, y);
	mPieces.front().setPosition(headNewPos); //place head at the given pos
	//start from the second element
	std::vector<Piece>::iterator iter = std::next(mPieces.begin(), 1);
	for (; iter != mPieces.end(); ++iter) {
		//relative pos of this piece to the old position of head
		sf::Vector2f dstToHead = oldPosition - iter->getPosition();
		iter->setPosition(headNewPos + dstToHead);
	}
}

void Snake::setDirection(const direction::Direction& dir)
{
	//if not in the opposite direction
	if (reverseDirection(dir) != mPieces.front().getDirection() &&
		dir != mPieces.front().getDirection())
	{
		mPieces.front().setDirection(dir);
	}
}

void Snake::setFillColor(const sf::Color color)
{
	for (Piece& p: mPieces) {
		p.setFillColor(color); //uniform color to all pieces
	}
}

void Snake::move()
{
	std::vector<Piece>::iterator iter(mPieces.begin());
	for (; iter != mPieces.end(); ++iter) {
		iter->move();
	}
	this->shiftDirections();
}

bool Snake::isDead() const
{
	std::vector<Piece>::const_iterator iter = std::next(mPieces.begin(), 1);
	for (; iter != mPieces.end(); ++iter) {
		if (this->getHead().atTheSamePosition(*iter)) {
			return true;
		}
	}
	return false;
}

void Snake::addPiece(const Piece& p)
{
	Piece addedPiece(p);
	addedPiece.setDirection(mPieces.back().getDirection());
	sf::Vector2f tailPos(mPieces.back().getPosition());
	sf::Vector2f offsets(direction::getMoveOffsets(mPieces.back().getDirection()));
	offsets = -offsets;
	sf::Vector2f newPos(tailPos.x + mGridSize * offsets.x,
						tailPos.y + mGridSize * offsets.y);
	addedPiece.setPosition(newPos);
	addedPiece.setFillColor(this->getFillColor());
	mPieces.push_back(addedPiece);
}

bool Snake::contains(const Piece& p) const
{
	std::vector<Piece>::const_iterator iter(mPieces.begin());
	for (; iter != mPieces.end(); ++iter) {
		if (iter->atTheSamePosition(p)) {
			return true;
		}
	}
	return false;
}

/*
 * Shifts the direction of each Piece to the one that is following it.
 */
void Snake::shiftDirections()
{
	std::vector<Piece>::iterator iter(std::prev(mPieces.end(), 2));
	//iterate over [First elem, Previous of Last elem]
	//end() points to the One Past Last elem
	for (; iter != std::prev(mPieces.begin(), 1); --iter) {
		std::vector<Piece>::iterator next_iter = std::next(iter, 1);
		next_iter->setDirection(iter->getDirection());
	}
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Piece& p : mPieces) {
		target.draw(p, states);
	}
}

