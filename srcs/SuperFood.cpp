
#include "SuperFood.hpp"

SuperFood::SuperFood(int x, int y)
{
	this->_pos.setPos(Point(x, y));
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
	snake.add_score(100);
	snake.add_to_tail();
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
