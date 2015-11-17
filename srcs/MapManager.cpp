// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MapManager.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 17:43:33 by rduclos           #+#    #+#             //
//   Updated: 2015/04/25 17:07:36 by rduclos          ###   ########.fr       //
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
	int		j;
	int		direction;

	this->_wall.initWall(width, height);
	this->_nbPlayer = nbplayer;
	if (this->_nbPlayer == 1)
		Snake snake((e_Cardinal)(rand() % 4), (width / 2), (height / 2));
	else
	{
		x = (width / 2) - 3;
		y = (height / 2) - 3;
		direction = 3;
		j = 2;
		for (int i = 0; i < nbplayer; i++)
		{
			Snake snake((e_Cardinal)direction, x, y);
			this->_snakes.push_back(snake);
			if (i % 4 == 0)
			{
				if (i != 0)
					j *= 2;
				direction = 0;
				x += (4 + j);
			}
			else if (i % 4 == 1)
			{
				direction = 2;
				y += (4 + j);
			}
			else if (i % 4 == 2)
			{
				direction = 1;
				x -= (4 + (j * 2));
			}
			else
			{
				direction = 0;
				y -= (4 + (j * 2));
			}
		}
	}
}

int		MapManager::verify_colision(void)
{
	std::list<Snake>::iterator		tmp = this->_snakes.begin();
	std::list<Snake>::iterator		tmp2;
	std::list<Snake>::iterator		end = this->_snakes.end();
	int								i = 0;
	int								j = 0;

	while (tmp != end)
	{
		if (tmp->colision_wall(this->_wall) == 1)
			return (1);
		if (tmp->colision_itself() == 1)
			return (1);
		tmp2 = this->_snakes.begin();
		while (tmp2 != end)
		{
			if (i != j)
			{
				if (tmp->colision_snake(*tmp2) == 1)
					return (1);
			}
			tmp2++;
			j++;
		}
		tmp++;
		i++;
	}
	return (0);
}

void	MapManager::verify_snakeaten(void)
{
	std::list<Food>::iterator		ftmp = this->_foods.begin();
	std::list<Food>::iterator		fend = this->_foods.end();
	std::list<Snake>::iterator		stmp = this->_snakes.begin();
	std::list<Snake>::iterator		send = this->_snakes.end();

	while (stmp != send)
	{
		while (ftmp != fend)
		{
			if (stmp->getHeadSnakeX() == ftmp->getX() &&
				stmp->getHeadSnakeY() == ftmp->getY())
				this->foodeaten(*stmp, *ftmp);
			ftmp++;
		}
		stmp++;
	}
}

void	MapManager::verify_snaketaken(void)
{
	std::list<ABonus*>::iterator		btmp = this->_bonus.begin();
	std::list<ABonus*>::iterator		bend = this->_bonus.end();
	std::list<Snake>::iterator		stmp = this->_snakes.begin();
	std::list<Snake>::iterator		send = this->_snakes.end();

	while (stmp != send)
	{
		while (btmp != bend)
		{
			if (stmp->getHeadSnakeX() == (*btmp)->getX() &&
				stmp->getHeadSnakeY() == (*btmp)->getY())
				this->bonustaken(*stmp, *btmp);
			btmp++;
		}
		stmp++;
	}
}

void		MapManager::move(int index)
{

}

void		MapManager::setSnakeDir(int index, e_Dir dir)
{

}

bool		MapManager::InZone(Point point, Point upleft, Point downright, e_PopMode mode)
{
	if (mode == InsideMode)
	{
		if (point._x >= upleft._x && point._x < downright._x &&
			point._y >= upleft._y && point._y < downright._y)
			return (true);
	}
	else if (mode == OutsideMode)
	{
		if (point._x < upleft._x && point._x >= downright._x &&
			point._y < upleft._y && point._y >= downright._y)
			return (true);
	}
	else if (mode == BorderMode)
	{
		if (((point._x >= upleft._x && point._x < downright._x) &&
			 (point._y == upleft._y || point._y == downright._y)) ||
			((point._y >= upleft._y && point._y < downright._y) &&
			 (point._x == upleft._x || point._x == downright._x)))
			return (true);
	}
	return (false);
}

bool		MapManager::verify_places(Point point)
{
	auto		ftmp = this->_foods.begin();
	auto		fend = this->_foods.end();
	auto		stmp = this->_snakes.begin();
	auto		send = this->_snakes.end();
	auto		btmp = this->_bonus.begin();
	auto		bend = this->_bonus.end();

	while (ftmp != fend)
	{
		if (ftmp->getX() == point._x && ftmp->getY() == point._y)
			return (false);
		ftmp++;
	}
	while (btmp != bend)
	{
		if ((*btmp)->getPos() == point)
			return (false);
		btmp++;
	}
	while (stmp != send)
	{
		auto seg = stmp->get_snake();
		auto sstmp = seg.begin();
		auto ssend = seg.end();
		while (sstmp != ssend)
		{
			if (sstmp->getX() == point._x && sstmp->getY() == point._y)
				return (false);
			sstmp++;
		}
		stmp++;
	}
	return (true);
}

void	MapManager::foodpop(e_PopMode mode = InsideMode)
{
	foodpop(Point(0, 0), this->_wall.getSize(), mode);
}

void	MapManager::foodpop(Point upleft, Point downright, e_PopMode mode = InsideMode)
{
	std::list<Point>	places;

	if (upleft._x < 0)
		upleft._x = 0;
	else if (upleft._x > this->_wall.getWidth())
		upleft._x = this->_wall.getWidth();
	if (upleft._y < 0)
		upleft._y = 0;
	else if (upleft._y > this->_wall.getHeight())
		upleft._y = this->_wall.getHeight();
	if (downright._x < 0)
		downright._x = 0;
	else if (downright._x > this->_wall.getWidth())
		downright._x = this->_wall.getWidth();
	if (downright._y < 0)
		downright._y = 0;
	else if (downright._y > this->_wall.getHeight())
		downright._y = this->_wall.getHeight();
	for (int x = 0; x < this->_wall.getWidth(); x++)
	{
		for (int y = 0; y < this->_wall.getHeight(); y++)
		{
			Point point(x,y);
			if (this->InZone(point, upleft, downright, mode) == true &&
				this->verify_places(point) == true)
				places.push_back(point);
		}
	}
}

void	MapManager::foodpop(Point center, int radius, e_PopMode mode = InsideMode)
{
	foodpop(center - radius, center + radius, mode);
}

void	MapManager::foodeaten(Snake & eater, Food & eaten)
{
	std::list<Food>::iterator		tmp = this->_foods.begin();
	std::list<Food>::iterator		end = this->_foods.end();

	eater.eat(eaten);
	while (tmp != end)
	{
		if (tmp->getX() == eaten.getX() && tmp->getY() == eaten.getY())
		{
			this->_foods.erase(tmp);			
			break;
		}
		tmp++;
	}
}

void	MapManager::bonuspop(void)
{

}

void	MapManager::bonustaken(Snake & taker, ABonus *taken)
{
	taken->bonus_taken(taker);
}
