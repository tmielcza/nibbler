
#include "SuperFood.hpp"
#include "Snake.hpp"

SuperFood::SuperFood(void)
{

}

SuperFood::SuperFood(int value, int x, int y)
{
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
	snake.add_score(this->_value / (this->_time / 100));
	snake.add_to_tail();
	delete this;
}

void				SuperFood::update(double time)
{
	if ((this->_time += time) >= B_TIME)
	{
		delete this;
	}
}

void				SuperFood::draw(double time)
{
	(void)time;
}
