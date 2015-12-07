
#include "SuperFood.hpp"
#include "GraphicsManager.hpp"
#include "Snake.hpp"
#include "MapManager.hpp"

SuperFood::SuperFood(void)
{

}

SuperFood::SuperFood(int value, int x, int y)
{
	GraphicsManager::Instance().popSuperFood(x, y, 1);
	this->_pos.setX(x);
	this->_pos.setY(y);
	this->_value = value;
	this->_isalive = true;
	this->_eatable = true;
}

SuperFood::SuperFood(const SuperFood & src)
{
	*this = src;
}

SuperFood::~SuperFood(void)
{
	GraphicsManager::Instance().depopFood(this->_pos.getX(), this->_pos.getY());
	MapManager::Instance().bonusdepop(this->_pos.getX(), this->_pos.getY());
}

SuperFood	&		SuperFood::operator=(const SuperFood & src)
{
	this->_value = src._value;
	this->_isalive = src._isalive;
	this->_time = src._time;
	return (*this);
}

void				SuperFood::taken(Snake & snake)
{
	GraphicsManager::Instance().popWave(this->getX(), this->getY());	
	snake.add_score(this->_value * 10);
	snake.add_to_tail();
	delete this;
}

void				SuperFood::update(double time)
{
	static int		i;

	this->_time += time;
	if ((this->_time - i) >= 1)
	{
		i++;
		this->_value++;
		GraphicsManager::Instance().updateSuperFood(this->_pos.getX(), this->_pos.getY(), 10 - this->_value);
	}
	if (this->_time >= 10)
	{
		MapManager::Instance()._Map[this->_pos.getX()][this->_pos.getY()] = NULL;
		delete this;
	}
}

void				SuperFood::draw(double time)
{
	(void)time;
}
