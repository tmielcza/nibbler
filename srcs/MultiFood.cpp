
#include "MultiFood.hpp"
#include "GraphicsManager.hpp"
#include "Snake.hpp"
#include "MapManager.hpp"

MultiFood::MultiFood(void)
{

}

MultiFood::MultiFood(int value, int x, int y)
{
	GraphicsManager::Instance().popMultiFood(x, y);
	this->_pos.setX(x);
	this->_pos.setY(y);
	this->_value = value;
	this->_time = 0;
	this->_isalive = true;
	this->_eatable = true;
}

MultiFood::MultiFood(const MultiFood & src)
{
	*this = src;
}

MultiFood::~MultiFood(void)
{
	GraphicsManager::Instance().depopFood(this->_pos.getX(), this->_pos.getY());
	MapManager::Instance().bonusdepop(this->_pos.getX(), this->_pos.getY());
}

MultiFood	&		MultiFood::operator=(const MultiFood & src)
{
	this->_value = src._value;
	this->_time = src._time;
	this->_isalive = src._isalive;
	this->_pos = src._pos;
	return (*this);
}

void				MultiFood::taken(Snake & snake)
{
	snake.add_to_tail();
	GraphicsManager::Instance().popWave(this->getX(), this->getY());	
	snake.add_score(this->_value * 10);
	for (int i = 0; i < this->_value; i++)
		MapManager::Instance().foodpop(this->_pos, 2, 0, (e_PopMode)0);
	delete this;
}

void				MultiFood::update(double time)
{
	this->_time += time;
	if (this->_time >= 9)
	{
		MapManager::Instance()._Map[this->_pos.getX()][this->_pos.getY()] = NULL;
		delete this;
	}
}

void				MultiFood::draw(double time)
{
	(void)time;
}
