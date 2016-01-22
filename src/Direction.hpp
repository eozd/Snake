#ifndef DIRECTION_HPP
#define DIRECTION_HPP
/*
 * =============================================================================
 *
 *       Filename:  Direction.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/18/2016 04:54:10 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Esref Ozdemir (esref.ozdemir27@gmail.com)
 *   Organization:  None
 *
 * =============================================================================
 */

#include <stdexcept>
#include <SFML/Graphics.hpp>

namespace direction {

enum Direction
{
	Up,
	Down,
	Left,
	Right,
	NoDirection
};

/**
  * Returns the reverse direction of the given Direction parameter.
  * reverse(NoDirection) == NoDirection
  */
Direction reverseDirection(const Direction& dir);
/**
  * Returns the movement offsets if an object is moving in the given direction.
  * Returned move offsets is an sf::Vector2f object with
  * x = 0, 1 and y = 0, 1
  */
sf::Vector2f getMoveOffsets(const Direction dir);

}
#endif
