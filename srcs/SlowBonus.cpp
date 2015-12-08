
#include "SlowBonus.hpp"
#include "GraphicsManager.hpp"
#include "Snake.hpp"
#include "MapManager.hpp"

SlowBonus::SlowBonus(void)
{

}

SlowBonus::SlowBonus(int value, int x, int y)
{
	this->_pos.setX(x);
	this->_pos.setY(y);
	this->_value = value;
	this->_time = 0;
	this->_isalive = true;
	this->_eatable = true;
	GraphicsManager::Instance().popMultiFood(x, y);
}

SlowBonus::SlowBonus(const SlowBonus & src)
{
	*this = src;
}

SlowBonus::~SlowBonus(void)
{
	GraphicsManager::Instance().depopFood(this->_pos.getX(), this->_pos.getY());
	MapManager::Instance().bonusdepop(this->_pos.getX(), this->_pos.getY());
}

SlowBonus	&		SlowBonus::operator=(const SlowBonus & src)
{
	this->_value = src._value;
	this->_time = src._time;
	this->_isalive = src._isalive;
	this->_pos = src._pos;
	return (*this);
}

void				SlowBonus::taken(Snake & snake)
{
	GraphicsManager::Instance().popWave(this->getX(), this->getY());
	snake.Slow(10.);
	delete this;
}

void				SlowBonus::update(double time)
{
	this->_time += time;
	if (this->_time >= 8)
	{
		MapManager::Instance()._Map[this->_pos.getX()][this->_pos.getY()] = NULL;
		delete this;
	}
}

void				SlowBonus::draw(double time)
{
	(void)time;
}
