
#include "CutBonus.hpp"
#include "GraphicsManager.hpp"
#include "Snake.hpp"
#include "MapManager.hpp"

CutBonus::CutBonus(void)
{

}

CutBonus::CutBonus(int value, int x, int y)
{
	this->_pos.setX(x);
	this->_pos.setY(y);
	this->_value = value;
	this->_time = 0;
	this->_isalive = true;
	this->_eatable = true;
	GraphicsManager::Instance().popMultiFood(x, y);
}

CutBonus::CutBonus(const CutBonus & src)
{
	*this = src;
}

CutBonus::~CutBonus(void)
{
	GraphicsManager::Instance().depopFood(this->_pos.getX(), this->_pos.getY());
	MapManager::Instance().bonusdepop(this->_pos.getX(), this->_pos.getY());
}

CutBonus	&		CutBonus::operator=(const CutBonus & src)
{
	this->_value = src._value;
	this->_time = src._time;
	this->_isalive = src._isalive;
	this->_pos = src._pos;
	return (*this);
}

void				CutBonus::taken(Snake & snake)
{
	GraphicsManager::Instance().popWave(this->getX(), this->getY());
	snake.Cut(10);
	delete this;
}

void				CutBonus::update(double time)
{
	this->_time += time;
	if (this->_time >= 8)
	{
		MapManager::Instance()._Map[this->_pos.getX()][this->_pos.getY()] = NULL;
		delete this;
	}
}

void				CutBonus::draw(double time)
{
	(void)time;
}
