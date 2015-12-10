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
	std::list<Wall*>::iterator		wall = this->_walls.begin();
	std::list<Wall*>::iterator		del;
	std::list<Wall*>::iterator		end = this->_walls.end();

	while (wall != end)
	{
		del = wall;
		wall++;
		this->_walls.erase(del);
	}
	std::cout << "Ending MapManager !!!" << std::endl;
}

MapManager&	MapManager::Instance(void)
{
	return (MapManager::_instance);
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
	this->_berase = false;
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

void	MapManager::foodpop(bool spawner)
{
	int x = (rand() % this->_width);
	int y = (rand() % this->_height);

	while (this->_Map[x][y] != NULL)
	{
		x = (rand() % this->_width);
		y = (rand() % this->_height);
	}
	Food *f = new Food(1, x, y, spawner);
	this->_Map[x][y] = f;
	this->_foods.push_back(f);
//	int r = rand() % 4;
//	if (r == 2)
		this->bonuspop(3);
}

void	MapManager::foodpop(Point upleft, Point downright, bool spawner, e_PopMode mode = InsideMode)
{
	if (mode == InsideMode)
	{
		int x = upleft.getX() + (rand() % downright.getX());
		int y = upleft.getY() + (rand() % downright.getY());
		while (x >= this->_width || y >= this->_height || this->_Map[x][y] != NULL)
		{
			x = upleft.getX() + (rand() % downright.getX());
			y = upleft.getY() + (rand() % downright.getY());
		}
		if (x < this->_width && y < this->_height && this->_Map[x][y] == NULL)
		{
			Food *f = new Food(1, x, y, spawner);
			this->_Map[x][y] = f;
			this->_foods.push_back(f);
		}
	}
}

void	MapManager::foodpop(Point center, int radius, bool spawner, e_PopMode mode = InsideMode)
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
		while (x >= this->_width || y >= this->_height || this->_Map[x][y] != NULL)
		{
			x = tmpx + (rand() % (radius * 2));
			y = tmpy + (rand() % (radius * 2));
		}
		if (x < this->_width && y < this->_height && this->_Map[x][y] == NULL)
		{
			Food *f = new Food(1, x, y, spawner);
			this->_Map[x][y] = f;
			this->_foods.push_back(f);
		}
	}
}
		
void	MapManager::foodepop(int x, int y)
{
	std::list<Food *>::iterator		start = this->_foods.begin();
	std::list<Food *>::iterator		end = this->_foods.end();

	while (start != end)
	{
		int _x = (*start)->getX();
		int _y = (*start)->getY();
		if (_x == x && _y == y)
		{
			this->_berase = true;
			this->_foods.erase(start);
			return;
		}
		start++;
	}
}

void	MapManager::bonuspop(int b)
{
	int x = rand() % this->_width;
	int y = rand() % this->_height;
	while (this->_Map[x][y] != NULL)
	{
		x = rand() % this->_width;
		y = rand() % this->_height;
	}
	if (b == 0)
	{
		SlowBonus *b = new SlowBonus(10, x, y);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
	}
	else if (b == 1)
	{
		CutBonus *b = new CutBonus(10, x, y);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
	}
	else if (b == 2)
	{
		SuperFood *b = new SuperFood(1, x, y);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
	}
	else if (b == 3)
	{
		int r2 = 5 + (rand() % 5);
		ChasedFood *b = new ChasedFood(r2, x, y, 1);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
	}
	else if (b == 4)
	{
		int r2 = 2 + (rand() % 4);
		MultiFood *b = new MultiFood(r2, x, y);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
	}
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
	std::cout << "Bonus poped at x: " << x << " y: " << y << std::endl;
	int r = rand() % 100;
	if (r < 10)
	{
		SlowBonus *b = new SlowBonus(10, x, y);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
	}
	else if (r < 20)
	{
		CutBonus *b = new CutBonus(10, x, y);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
	}
	else if (r < 40)
	{
		SuperFood *b = new SuperFood(1, x, y);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
	}
	else if (r < 70)
	{
		int r2 = 5 + (rand() % 5);
		ChasedFood *b = new ChasedFood(r2, x, y, 1);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
	}
	else if (r < 100)
	{
		int r2 = 2 + (rand() % 4);
		MultiFood *b = new MultiFood(r2, x, y);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
	}

}

void	MapManager::bonusdepop(int x, int y)
{
	std::list<ABonus *>::iterator		start = this->_bonus.begin();
	std::list<ABonus *>::iterator		end = this->_bonus.end();

	while (start != end)
	{
		int _x = (*start)->getX();
		int _y = (*start)->getY();
		if (_x == x && _y == y)
		{
			this->_berase = true;
			this->_bonus.erase(start);
			std::cout << "Bonus depop at : " << _x << "-" << _y << std::endl;
			return;
		}
		start++;
	}
}

void	MapManager::add_Bonus(ABonus *bonus)
{
	this->_bonus.push_back(bonus);
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
	std::list<ABonus *>::iterator		bstart = this->_bonus.begin();
	std::list<ABonus *>::iterator		bend = this->_bonus.end();
	std::list<Food *>::iterator		fstart = this->_foods.begin();
	std::list<Food *>::iterator		fend = this->_foods.end();

	int i = 0;
	while (bstart != bend)
	{
		(*bstart)->update(time);
		if (this->_berase == true)
		{
			bstart = this->_bonus.begin();
			bend = this->_bonus.end();
			int j = 0;
			while (j < i)
			{
				bstart++;
				j++;
			}
			this->_berase = false;
		}
		else
			bstart++;
		i++;
	}
	i = 0;
	while (fstart != fend)
	{
		(*fstart)->update(time);
		if (this->_berase == true)
		{
			fstart = this->_foods.begin();
			fend = this->_foods.end();
			int j = 0;
			while (j < i)
			{
				fstart++;
				j++;
			}
			this->_berase = false;
		}
		else
			fstart++;
		i++;
	}
}
