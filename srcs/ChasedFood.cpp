
#include "ChasedFood.hpp"
#include "GraphicsManager.hpp"
#include "Snake.hpp"
#include "MapManager.hpp"

ChasedFood::ChasedFood(void)
{

}

ChasedFood::ChasedFood(int value, int x, int y, bool first)
{
	this->_first = first;
	this->_pos.setX(x);
	this->_pos.setY(y);
	this->_value = value;
	this->_time = 0;
	this->_isalive = true;
	this->_eatable = true;
	if (first == true)
		this->_maxTime = 6;
	else
		this->_maxTime = 2;
	GraphicsManager::Instance().popSuperFood(x, y, 2);
}

ChasedFood::ChasedFood(const ChasedFood & src)
{
	*this = src;
}

ChasedFood::~ChasedFood(void)
{
	GraphicsManager::Instance().depopFood(this->_pos.getX(), this->_pos.getY());
	MapManager::Instance().bonusdepop(this->_pos.getX(), this->_pos.getY());
}

ChasedFood	&		ChasedFood::operator=(const ChasedFood & src)
{
	this->_value = src._value;
	this->_time = src._time;
	this->_isalive = src._isalive;
	this->_pos = src._pos;
	return (*this);
}

void				ChasedFood::taken(Snake & snake)
{
	if (this->_value > 0)
	{
		int x = (snake.getHeadSnakeX() - 1) + (rand() % 3);
		int y = (snake.getHeadSnakeY() - 1) + (rand() % 3);
		int i = 0;
		
		while (MapManager::Instance()._Map[x][y] != NULL && i < 10)
		{
			x = (snake.getHeadSnakeX() - 1) + (rand() % 3);
			y = (snake.getHeadSnakeY() - 1) + (rand() % 3);
			i++;
		}
		if (MapManager::Instance()._Map[x][y] != NULL)
		{
			while (MapManager::Instance()._Map[x][y] != NULL)
			{
				x = (snake.getHeadSnakeX() - 2) + (rand() % 4);
				y = (snake.getHeadSnakeY() - 2) + (rand() % 4);
			}
		}
		if (MapManager::Instance()._Map[x][y] == NULL)
		{
			ChasedFood *b = new ChasedFood(this->_value - 1, x, y, false);
			MapManager::Instance()._Map[x][y] = b;
			MapManager::Instance().add_Bonus(b);
		}
	}
/*
	snake.add_to_tail();
	GraphicsManager::Instance().popWave(this->getX(), this->getY());	
	snake.add_score(this->_value * 10);
	for (int i = 0; i < this->_value; i++)
		MapManager::Instance().foodpop(this->_pos, 3, 0, (e_PopMode)0);
*/
	delete this;
}

void				ChasedFood::update(double time)
{
	this->_time += time;
	if (this->_time >= this->_maxTime)
	{
		MapManager::Instance()._Map[this->_pos.getX()][this->_pos.getY()] = NULL;
		delete this;
	}
}

void				ChasedFood::draw(double time)
{
	(void)time;
}
