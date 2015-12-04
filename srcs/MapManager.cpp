// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MapManager.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 17:43:33 by rduclos           #+#    #+#             //
//   Updated: 2015/12/04 16:53:31 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "MapManager.hpp"

MapManager	MapManager::_instance = MapManager();

MapManager::MapManager(void)
{
	std::cout << "Starting MapManager !!!" << std::endl;
}

MapManager::~MapManager(void)
{
	std::cout << "Ending MapManager !!!" << std::endl;
}

MapManager&	MapManager::Instance(void)
{
	return (MapManager::_instance);
}

int		MapManager::getFoodnb(void)
{
	return (this->_foods.size());
}

int		MapManager::getBonusnb(void)
{
	return (this->_bonus.size());
}

void	MapManager::init(int nbplayer, int width, int height)
{
	this->_Map = new AEntity**[width];
	for (int i = 0; i < (width); i++)
	{
		this->_Map[i] = new AEntity*[height];
		for (int j = 0; j < (height); j++)
			this->_Map[i][j] = NULL;
	}
	this->_width = width;
	this->_height = height;
	this->_nbPlayer = nbplayer;
}

void		MapManager::move(int index)
{
	for (auto i = this->_snakes.begin(), end = this->_snakes.end(); i != end; i++)
	{
		if ((*i)->getIndex() == index)
		{
			(*i)->befor_move();
			(*i)->move();
			return ;
		}
	}
}

void		MapManager::setSnakeDir(int index, bool left)
{
	for (auto i = this->_snakes.begin(), end = this->_snakes.end(); i != end; i++)
	{
		if ((*i)->getIndex() == index)
		{
			if (left == true)
				(*i)->turn_left();
			else
				(*i)->turn_right();
			return ;
		}
	}

}

bool		MapManager::InZone(Point point, Point upleft, Point downright, e_PopMode mode)
{
	if (mode == InsideMode)
	{
		if (point.getX() >= upleft.getX() && point.getX() < downright.getX() &&
			point.getY() >= upleft.getY() && point.getY() < downright.getY())
			return (true);
	}
	else if (mode == OutsideMode)
	{
		if (point.getX() < upleft.getX() && point.getX() >= downright.getX() &&
			point.getY() < upleft.getY() && point.getY() >= downright.getY())
			return (true);
	}
	else if (mode == BorderMode)
	{
		if (((point.getX() >= upleft.getX() && point.getX() < downright.getX()) &&
			 (point.getY() == upleft.getY() || point.getY() == downright.getY())) ||
			((point.getY() >= upleft.getY() && point.getY() < downright.getY()) &&
			 (point.getX() == upleft.getX() || point.getX() == downright.getX())))
			return (true);
	}
	return (false);
}

void	MapManager::foodpop(Point upleft, Point downright, e_PopMode mode = InsideMode)
{
	if (mode == InsideMode)
	{
		int x = upleft.getX() + (rand() % downright.getX());
		int y = upleft.getY() + (rand() % downright.getY());
		while (this->_Map[x][y] != NULL || x > this->_width || y > this->_height)
		{
			x = upleft.getX() + (rand() % downright.getX());
			y = upleft.getY() + (rand() % downright.getY());
		}
		Food *f = new Food(1, x, y);
		this->_Map[x][y] = f;
		this->_foods.push_front(f);
	}
}

void	MapManager::foodpop(Point center, int radius, e_PopMode mode = InsideMode)
{
	if (mode == InsideMode)
	{
		int tmpx = center.getX() - radius;
		int tmpy = center.getY() - radius;
		if (tmpx < 0)
			tmpx = 0;
		if (tmpy < 0)
			tmpy = 0;
		int x = tmpx + (rand() % (radius * 2));
		int y = tmpy + (rand() % (radius * 2));
		while (this->_Map[x][y] != NULL || x > this->_width || y > this->_height)
		{
			x = tmpx + (rand() % (radius * 2));
			y = tmpy + (rand() % (radius * 2));
		}
		Food *f = new Food(1, x, y);
		this->_Map[x][y] = f;
		this->_foods.push_front(f);
	}
}

void	MapManager::foodeaten(Snake & eater, Food & eaten)
{
	eater.eat(eaten);
}

void	MapManager::bonuspop(void)
{
	int x = rand() % this->_width;
	int y = rand() % this->_height;
	while (this->_Map[x][y] != NULL)
	{
		x = rand() % this->_width;
		y = rand() % this->_height;
	}
/*	

	this->_Map[x][y] =
*/
}

void	MapManager::bonustaken(Snake & taker, ABonus *taken)
{
	taken->taken(taker);
}

int		MapManager::getWidth(void)
{
	return (this->_width);
}

int		MapManager::getHeight(void)
{
	return (this->_height);
}

void	MapManager::setWall(int x, int y)
{
	if (MapManager::Instance()._Map[x][y] == NULL)
	{
		Wall *w = new Wall(x, y);
		MapManager::Instance()._Map[x][y] = w;
		this->_walls.push_front(w);
	}
}

void	MapManager::setWall(Point pos)
{
	int x = pos.getX();
	int y = pos.getY();

	if (MapManager::Instance()._Map[x][y] == NULL)
	{
		Wall *w = new Wall(pos);
		MapManager::Instance()._Map[x][y] = w;
		this->_walls.push_front(w);
	}
}

void	MapManager::setSnake(Snake *snake)
{
	this->_snakes.push_back(snake);
}

void	MapManager::update(double time)
{
	(void)time;
}
