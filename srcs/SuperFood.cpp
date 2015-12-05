
#include "SuperFood.hpp"

SuperFood::SuperFood(int x, int y)
{
	this->_pos.setPos(Point(x, y));
	this->_value = 100;
}

SuperFood::SuperFood(const SuperFood & src)
{
	*this = src;
}

SuperFood::~SuperFood(void)
{

}

SuperFood	&		operator=(const SuperFood & src)
{
	return (*this);
}

void				taken(Snake & snake)
{
	snake.add_score(this->value / (this->time / 100));
	snake.add_to_tail();
	delete this;
}

void				update(double time)
{
	if ((this->_time += time) >= B_TIME)
	{
		delete this;
	}
}

void				draw(double time)
{
	(Void)time;
}
