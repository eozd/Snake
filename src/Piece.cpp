#include <cstdlib>
#include "Piece.hpp"

Piece::Piece(const float x, const float y, const float edgeLength)
	: mSquare(sf::Vector2f(edgeLength, edgeLength))
	, mDirection(direction::NoDirection)
{
	this->setPosition(x, y);
	this->setFillColor(sf::Color::Black);
}

Piece::Piece(const sf::Vector2f pos, const float edgeLength)
	: mSquare(sf::Vector2f(edgeLength, edgeLength))
	, mDirection(direction::NoDirection)
{
	this->setPosition(pos);
	this->setFillColor(sf::Color::Black);
}

void Piece::setDirection(const direction::Direction dir)
{
	mDirection = dir;
}

void Piece::setPosition(const float x, const float y)
{
	this->setPosition(sf::Vector2f(x, y));
}

void Piece::setPosition(const sf::Vector2f& pos)
{
	mSquare.setPosition(pos);
}

void Piece::setFillColor(const sf::Color& color)
{
	mSquare.setFillColor(color);
}

direction::Direction Piece::getDirection() const
{
	return mDirection;
}

const sf::Vector2f& Piece::getPosition() const
{
	return mSquare.getPosition();
}

const sf::Color& Piece::getFillColor() const
{
	return mSquare.getFillColor();
}

void Piece::move()
{
	sf::Vector2f offsets(direction::getMoveOffsets(mDirection));
	//mSquare.getSize.x == msquare.getSize.y (Piece being a square is an
	// invariant of this class)
	mSquare.move(offsets * mSquare.getSize().x);
}

bool Piece::atTheSamePosition(const Piece& other) const
{
	sf::Vector2f pos(getPosition());
	sf::Vector2f otherPos(other.getPosition());
	float xDiff = pos.x - otherPos.x;
	float yDiff = pos.y - otherPos.y;
	xDiff = std::abs(xDiff);
	yDiff = std::abs(yDiff);
	return xDiff < 0.0001 && yDiff < 0.0001;
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSquare, states);
}
