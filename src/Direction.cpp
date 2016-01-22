#include "Direction.hpp"

namespace direction {
Direction reverseDirection(const Direction& dir)
{
	Direction negated_direction;
	switch (dir) {
	case Up:
		negated_direction = Direction::Down;
		break;
	case Down:
		negated_direction = Direction::Up;
		break;
	case Left:
		negated_direction = Direction::Right;
		break;
	case Right:
		negated_direction = Direction::Left;
		break;
	case NoDirection:
		negated_direction = Direction::NoDirection;
		break;
	default:
		throw std::invalid_argument("Direction operator! : Invalid direction");
	}
	return negated_direction;
}

sf::Vector2f getMoveOffsets(const Direction dir)
{
	sf::Vector2f offsets(0, 0);
	switch (dir) {
	case Up:
		offsets.x = 0;
		offsets.y = -1;
		break;
	case Down:
		offsets.x = 0;
		offsets.y = 1;
		break;
	case Left:
		offsets.x = -1;
		offsets.y = 0;
		break;
	case Right:
		offsets.x = 1;
		offsets.y = 0;
		break;
	case NoDirection:
		break;
	}
	return offsets;
}
}

