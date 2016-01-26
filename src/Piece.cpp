#include <cstdlib>
#include "Piece.hpp"

Piece::Piece(const float x, const float y, const float edgeLength)
	: mCircle(edgeLength / 2)
	, mDirection(direction::NoDirection)
{
	this->setPosition(x, y);
	this->setFillColor(sf::Color::Black);
}

Piece::Piece(const sf::Vector2f pos, const float edgeLength)
	: mCircle(edgeLength / 2)
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
	mCircle.setPosition(pos);
}

void Piece::setFillColor(const sf::Color& color)
{
	mCircle.setFillColor(color);
}

void Piece::move(const float dist)
{
	sf::Vector2f offsets(direction::getMoveOffsets(mDirection));
	//mCircle.getSize.x == msquare.getSize.y (Piece being a square is an
	// invariant of this class)
	mCircle.move(offsets * dist);
}

bool Piece::atTheSamePosition(const sf::Vector2f& pos) const
{
	sf::Vector2f piecePos(this->getPosition());
	float xDiff = piecePos.x - pos.x;
	float yDiff = piecePos.y - pos.y;
	xDiff = std::abs(xDiff);
	yDiff = std::abs(yDiff);
	return xDiff < ErrorTerm && yDiff < ErrorTerm;
}

bool Piece::atTheSamePosition(const Piece& other) const
{
	return this->atTheSamePosition(other.getPosition());
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mCircle, states);
}
