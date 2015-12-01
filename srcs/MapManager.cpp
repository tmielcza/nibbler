// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MapManager.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 17:43:33 by rduclos           #+#    #+#             //
//   Updated: 2015/11/17 18:06:11 by rduclos          ###   ########.fr       //
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
	int		x;
	int		y;
	int		direction;

	this->_Map = new AEntity**[width + 2];
	for (int i = 0; i < (width + 2); i++)
	{
		this->_Map[i] = new AEntity*[height + 2];
		for (int j = 0; j < (height + 2); j++)
			this->_Map[i][j] = NULL;
	}
	this->_width = width;
	this->_height = height;
	this->_nbPlayer = nbplayer;
	x = (width + 2) / 2;
	y = (height + 2) / 2;
	direction = 1;
	Snake *snake = new Snake((e_Cardinal)direction, x, y);
	this->_snakes.push_back(snake);
}

void		MapManager::move(int index)
{
	(void)index;
}

void		MapManager::setSnakeDir(int index, e_Dir dir)
{
	(void)index;
	(void)dir;
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
	(void)upleft;
	(void)downright;
	(void)mode;
}

void	MapManager::foodpop(Point center, int radius, e_PopMode mode = InsideMode)
{
	(void)center;
	(void)radius;
	(void)mode;
}

void	MapManager::foodeaten(Snake & eater, Food & eaten)
{
	(void)eater;
	(void)eaten;
}

void	MapManager::bonuspop(void)
{

}

void	MapManager::bonustaken(Snake & taker, ABonus *taken)
{
	taken->bonus_taken(taker);
}
