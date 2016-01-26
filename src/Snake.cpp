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

#include <iostream>
#include <stdexcept>
#include "Snake.hpp"

Snake::Snake(const sf::Vector2f& pos, const size_t length,
			 const float gridSize, const direction::Direction dir)
	: mPieces() //vector is default initialized
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
	auto iter = std::next(mPieces.begin());
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
	for (auto& p: mPieces) {
		p.setFillColor(color); //uniform color to all pieces
	}
}

void Snake::move(const float distance)
{
	for (auto& p : mPieces) {
		p.move(distance);
	}
	this->shiftDirections();
}

bool Snake::isDead() const
{
	auto iter = std::next(mPieces.begin());
	for (; iter != mPieces.end(); ++iter) {
		if (mPieces.front().atTheSamePosition(*iter)) {
			return true;
		}
	}
	return false;
}

void Snake::addPiece(const Piece& p)
{
	Piece addedPiece(p);
	addedPiece.setDirection(mPieces.back().getDirection());
	const sf::Vector2f& tailPos(mPieces.back().getPosition());
	sf::Vector2f offsets(
					direction::getMoveOffsets(mPieces.back().getDirection()));
	//we are going to place the new piece in the opposite direction of current
	//direction of the last piece
	offsets = -offsets;
	const float gridSize = mPieces.back().getSize();
	sf::Vector2f newPos(tailPos.x + gridSize * offsets.x,
						tailPos.y + gridSize * offsets.y);
	addedPiece.setPosition(newPos);
	addedPiece.setFillColor(this->getFillColor());
	mPieces.push_back(addedPiece);
}

bool Snake::contains(const Piece& p) const
{
	for (const auto& piece : mPieces) {
		if (piece.atTheSamePosition(p)) {
			return true;
		}
	}
	return false;
}

/**
 * Shifts the direction of each Piece to the one that is following it.
 */
void Snake::shiftDirections()
{
	auto reverse_iter = mPieces.rbegin();//start from the last element
	for (; reverse_iter != mPieces.rend() - 1; ++reverse_iter) {
		auto left = reverse_iter + 1; //left neighbour of reverse_iter
		reverse_iter->setDirection(left->getDirection());
	}
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& p : mPieces) {
		target.draw(p, states);
	}
}

