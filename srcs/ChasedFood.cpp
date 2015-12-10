
#include "ChasedFood.hpp"
#include "GraphicsManager.hpp"
#include "Snake.hpp"
#include "MapManager.hpp"

ChasedFood::ChasedFood(void)
{

}

ChasedFood::ChasedFood(int value, int x, int y, int place)
{
	this->_place = place;
	this->_pos.setX(x);
	this->_pos.setY(y);
	this->_value = value;
	this->_time = 0;
	this->_isalive = true;
	this->_eatable = true;
	if (place == 1)
		this->_maxTime = 6;
	else
		this->_maxTime = 2;
	GraphicsManager::Instance().popChasedFood(x, y, place, this->_maxTime);
//	GraphicsManager::Instance().popSuperFood(x, y, 3);
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
	int height = MapManager::Instance().getHeight();
	int width = MapManager::Instance().getWidth();
	bool pop = true;

	GraphicsManager::Instance().popWave(this->getX(), this->getY());
	if (this->_place != this->_value)
	{
		int x = (snake.getHeadSnakeX() - 1) + (rand() % 3);
		int y = (snake.getHeadSnakeY() - 1) + (rand() % 3);
		int i = 0;

		if (x < 0)
			x = width - 1;
		else if (x >= width)
			x = 0;
		if (y < 0)
			y = height - 1;
		else if (y >= height)
			y = 0;
		while (MapManager::Instance()._Map[x][y] != NULL && i < 20)
		{
			x = (snake.getHeadSnakeX() - 1) + (rand() % 3);
			y = (snake.getHeadSnakeY() - 1) + (rand() % 3);
			if (x < 0)
				x = width - 1;
			else if (x >= width)
				x = 0;
			if (y < 0)
				y = height - 1;
			else if (y >= height)
				y = 0;
			i++;
		}
		if (MapManager::Instance()._Map[x][y] != NULL)
		{
			i = 0;
			while (MapManager::Instance()._Map[x][y] != NULL && i < 20)
			{
				x = (snake.getHeadSnakeX() - 2) + (rand() % 4);
				y = (snake.getHeadSnakeY() - 2) + (rand() % 4);
				if (x < 0)
					x = width - 1;
				else if (x >= width)
					x = 0;
				if (y < 0)
					y = height - 1;
				else if (y >= height)
					y = 0;
				i++;
			}
		}
		if (x >= 0 && x < width && y >= 0 && y < height &&
			MapManager::Instance()._Map[x][y] == NULL)
		{
			ChasedFood *b = new ChasedFood(this->_value, x, y, this->_place + 1);
			MapManager::Instance()._Map[x][y] = b;
			MapManager::Instance().add_Bonus(b);
		}
		else
			pop = false;
	}
	if (this->_place != this->_value && pop == true)
		snake.add_score(this->_place);
	else
		snake.add_score(200);
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
