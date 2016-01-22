#include <stdexcept>
#include "Board.hpp"

Board::Board(const int width, const int height, const int numOfGrids)
	: LineVectorCount(2)
	, mWidth(width)
	, mHeight(height)
	, mNumOfGrids(numOfGrids)
	, defaultColor(sf::Color::Black)
{
	if (width != height) {
		throw std::invalid_argument("Board: Width and height must be equal");
	}
	initLines();
}

sf::Color Board::getColor() const
{
	return (mLines.at(0))[0].color;
}

void Board::setColor(const sf::Color color)
{
	for (sf::VertexArray& line : mLines) {
		for (unsigned int i = 0; i < line.getVertexCount(); ++i) {
			line[i].color = color;
		}
	}

}

void Board::initLines()
{
	//for numOfGrids = n, we draw n + 1 lines
	float gridSize = (float)mWidth / mNumOfGrids;
	for (int i = 0; i < mNumOfGrids + 1; ++i) {
		sf::VertexArray vArrHorizontal(sf::Lines, LineVectorCount);
		sf::VertexArray vArrVertical(sf::Lines, LineVectorCount);
		//horizontal line
		sf::Vertex left(sf::Vector2f(0, gridSize * i));
		sf::Vertex right(sf::Vector2f(mWidth, gridSize * i));
		//vertical line
		sf::Vertex top(sf::Vector2f(gridSize * i, 0));
		sf::Vertex bottom(sf::Vector2f(gridSize * i, mHeight));
		//set the colors
		left.color = defaultColor;
		right.color = defaultColor;
		top.color = defaultColor;
		bottom.color = defaultColor;
		//append the vertices to VertexArrays
		vArrHorizontal.append(left);
		vArrHorizontal.append(right);
		vArrVertical.append(top);
		vArrVertical.append(bottom);
		//add lines
		mLines.push_back(vArrHorizontal);
		mLines.push_back(vArrVertical);
	}
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//draw all the lines defined in the lines vector
	for (size_t i = 0; i < mLines.size(); ++i) { 
		target.draw(mLines.at(i), states);
	}
}
