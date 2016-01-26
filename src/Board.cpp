#include <stdexcept>
#include "Board.hpp"

Board::Board(const unsigned int width, const unsigned int height,
			 const unsigned int numOfGrids)
	: mWidth(width)
	, mHeight(height)
	, mNumOfGrids(numOfGrids)
{
	if (width != height) {
		throw std::invalid_argument("Board: Width and height must be equal");
	}
}
