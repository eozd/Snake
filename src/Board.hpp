#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Board : public sf::Drawable
{
public:
	/**
	  * Board ctor. Board is defined with a width, height and how many grids
	  * it will contain in one edge. If width = 400, height = 400, nOfGrids=20;
	  * then edge length of a single grid is 400/20 = 20 and there are 20 * 20
	  * 400 grids on the Board.
	  */
	Board(const int width, const int height, const int numOfGrids);
	/**
	  * Sets the color of how this Board object is drawn on the screen.
	  */
	void setColor(const sf::Color);
	sf::Color getColor() const;
	/** If this Board object contains the given Locatable type object
	  * Locatable type objects must have getPosition() method returning a 
	  * Vector2f object
	  */
	template<typename Locatable>
	bool contains(const Locatable& obj) const
	{
		sf::Vector2f pos(obj.getPosition());
		return pos.x >= 0 && pos.x <= (mWidth - mWidth / mNumOfGrids) &&
			   pos.y >= 0 && pos.y <= (mHeight - mHeight / mNumOfGrids);
	}

private:
	/**
	  * Calculates the position of each line that consists this Board object
	  * and initializes them i.e. stores them in mLines vector
	  */
	void initLines();
	/**
	  * Draws this Board object to the screen.
	  */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	//a line is a pair of vertices. Collection of lines will define our board
	const unsigned int LineVectorCount;
	const int mWidth;
	const int mHeight;
	const int mNumOfGrids;
	const sf::Color defaultColor;
	std::vector<sf::VertexArray> mLines;
};

#endif
