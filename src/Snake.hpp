#ifndef SNAKE_HPP
#define SNAKE_HPP
/*
 * =============================================================================
 *
 *       Filename:  Snake.hpp
 *
 *    Description:  Class representing a Snake object.
 *
 *        Version:  1.0
 *        Created:  01/18/2016 04:46:51 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Esref Ozdemir (esref.ozdemir27@gmail.com)
 *   Organization:  None
 *
 * =============================================================================
 */

#include <SFML/Graphics.hpp>
#include <vector>
#include "Direction.hpp"
#include "Piece.hpp"

class Snake : public sf::Drawable
{
public:
	/**
	 * Constructs a Snake object. A Snake object is always created so that it is
	 * linear after construction. That is, (size - 1) many RectangleShape
	 * objects are added to the Snake in the opposite direction of the 
	 * direction parameter.
	 */
	Snake(const sf::Vector2f& pos, const size_t length, const float gridSize,
		  const direction::Direction dir);
	/**
	  * setPosition preserves the relative positions of parts of a Snake object.
	  * If this Snake object was linear before a setPosition call, it will
	  * remain linear after a setPosition call. Its head will now be in the
	  * given position and the remaining parts will follow it.
	  */
	void setPosition(const float x, const float y);
	void setPosition(const sf::Vector2f& pos);
	const Piece& getHead() const noexcept { return mPieces.front(); };
	auto getSize() const noexcept { return mPieces.size(); };
	/**
	 * Sets and gets the direction of this Snake object. A Snake object's
	 * direction is defined as the direction of its head which is a Piece.
	 * A Snake object's direction cannot be changed by 180 degrees.
	 */
	direction::Direction getDirection() const noexcept
	{
		return mPieces.front().getDirection();
	}
	void setDirection(const direction::Direction& dir);
	/**
	 * Sets and gets the color of this Snake object
	 * setColor applies uniform color to all parts of this Snake object
	 */
	sf::Color getFillColor() const { return mPieces.front().getFillColor(); }
	void setFillColor(const sf::Color color);
	/**
	 * Moves this Snake object by one tile. Each Piece consisting
	 * this Snake object will have a newly calculated position. After all
	 * Piece objects consisting this Snake objects are moved, their directions
	 * are shifted. Each Piece will have the direction of the Piece that it is
	 * following. This way, Snake moves as a whole.
	 */
	void move(const float dist);
	/**
	 * Checks if this Snake object is dead. A snake object dies whenever
	 * it eats itself. That is, its head and some other RectangleShape
	 * consisting it overlaps.
	 */
	bool isDead() const;
	/**
	 * Adds a copied version of the given Piece object at the back of this
	 * Snake object
	 */
	void addPiece(const Piece&);
	/**
	 * Whether the given Piece object has the same coordinates with any of the
	 * Pieces consisting this Snake object
	 */
	bool contains(const Piece&) const;
private:
	/** Shifts the direction of each Piece to the one following it
	  * After this call, direction of the head of this Snake object is unchanged
	  */
	void shiftDirections();
	/**
	  * Draws this Snake object on the given RenderTarget object.
	  * SFML specific method. Check SFML RenderTarget
	  */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<Piece> mPieces; //collection of Pieces consisting this Snake
};

#endif
