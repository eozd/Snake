#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Board
{
public:
	/**
	  * Board ctor. Board is defined with a width, height and how many grids
	  * it will contain in one edge. If width = 400, height = 400, nOfGrids=20;
	  * then edge length of a single grid is 400/20 = 20 and there are 20 * 20
	  * 400 grids on the Board.
	  */
	Board(const unsigned int width, const unsigned int height,
		  const unsigned int numOfGrids);
	/** If this Board object contains the given Locatable type object
	  * Locatable type objects must have getGlobalBounds() method returning a 
	  * FloatRect object
	  */
	unsigned int getWidth() const noexcept { return mWidth; };
	unsigned int getHeight() const noexcept { return mHeight; };
	unsigned int getNumOfGrids() const noexcept { return mNumOfGrids; };
	template<typename Locatable>
	bool contains(const Locatable& obj) const
	{
		sf::FloatRect rect(obj.getGlobalBounds());
		return rect.left >= 0
			&& rect.left + rect.width <= mWidth
			&& rect.top >= 0
			&& rect.top + rect.height <= mHeight;
	}
private:
	const unsigned int mWidth;
	const unsigned int mHeight;
	const unsigned int mNumOfGrids;
};

#endif
