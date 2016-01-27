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
	this->_tosend = "";
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

/*
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
*/

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
	if (spawner == true)
	{
		if (this->_tosend == "")
			this->_tosend = "F1_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
		else
			this->_tosend += "F1_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
	}
	else
	{
		if (this->_tosend == "")
			this->_tosend = "F0_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
		else
			this->_tosend += "F0_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
	}
	int r = rand() % 4;
	if (r == 2)
		this->bonuspop();
}

void	MapManager::foodpop(bool spawner, int x, int y)
{
	Food *f = new Food(1, x, y, spawner);
	this->_Map[x][y] = f;
	this->_foods.push_back(f);
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
			if (spawner == true)
			{
				if (this->_tosend == "")
					this->_tosend = "F1_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
				else
					this->_tosend += "F1_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
			}
			else
			{
				if (this->_tosend == "")
					this->_tosend = "F0_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
				else
					this->_tosend += "F0_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
			}
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
			if (spawner == true)
			{
				if (this->_tosend == "")
					this->_tosend = "F1_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
				else
					this->_tosend += "F1_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
			}
			else
			{
				if (this->_tosend == "")
					this->_tosend = "F0_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
				else
					this->_tosend += "F0_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
			}
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
			this->_Map[x][y] = NULL;
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
		if (this->_tosend == "")
			this->_tosend = "BS_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
		else
			this->_tosend += "BS_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
	}
	else if (b == 1)
	{
		CutBonus *b = new CutBonus(10, x, y);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
		if (this->_tosend == "")
			this->_tosend = "BC_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
		else
			this->_tosend += "BC_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
	}
	else if (b == 2)
	{
		SuperFood *b = new SuperFood(1, x, y);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
		if (this->_tosend == "")
			this->_tosend = "BF_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
		else
			this->_tosend += "BF_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
	}
	else if (b == 3)
	{
		int r2 = 5 + (rand() % 5);
		ChasedFood *b = new ChasedFood(r2, x, y, 1, true);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
		if (this->_tosend == "")
		{
			this->_tosend = "BH_" + std::to_string(x) + "_" + std::to_string(y) + ":";
			this->_tosend += std::to_string(r2) + "_1";
			this->_tosend += "\n";
		}
		else
		{
			this->_tosend += "BH_" + std::to_string(x) + "_" + std::to_string(y) + ":";
			this->_tosend += std::to_string(r2) + "_1";
			this->_tosend += "\n";
		}
	}
	else if (b == 4)
	{
		int r2 = 2 + (rand() % 4);
		MultiFood *b = new MultiFood(r2, x, y, true);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
		if (this->_tosend == "")
		{
			this->_tosend = "BM_" + std::to_string(x) + "_" + std::to_string(y) + ":";
			this->_tosend += std::to_string(r2);
			this->_tosend += "\n";
		}
		else
		{
			this->_tosend += "BM_" + std::to_string(x) + "_" + std::to_string(y) + ":";
			this->_tosend += std::to_string(r2);
			this->_tosend += "\n";
		}
	}
}

void	MapManager::bonuspop(int b, int x, int y, int r2, int r3)
{
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
		ChasedFood *b = new ChasedFood(r2, x, y, r3, false);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
	}
	else if (b == 4)
	{
		MultiFood *b = new MultiFood(r2, x, y, false);
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
	int r = rand() % 100;
	std::cout << "Bonus poped at x: " << x << " y: " << y << std::endl;
	if (r < 20)
	{
		SlowBonus *b = new SlowBonus(10, x, y);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
		if (this->_tosend == "")
			this->_tosend = "BS_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
		else
			this->_tosend += "BS_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
	}
	else if (r < 30)
	{
		CutBonus *b = new CutBonus(10, x, y);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
		if (this->_tosend == "")
			this->_tosend = "BC_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
		else
			this->_tosend += "BC_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
	}
	else if (r < 60)
	{
		SuperFood *b = new SuperFood(1, x, y);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
		if (this->_tosend == "")
			this->_tosend = "BF_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
		else
			this->_tosend += "BF_" + std::to_string(x) + "_" + std::to_string(y) + "\n";
	}
	else if (r < 90)
	{
		int r2 = 5 + (rand() % 5);
		ChasedFood *b = new ChasedFood(r2, x, y, 1, true);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
		if (this->_tosend == "")
		{
			this->_tosend = "BH_" + std::to_string(x) + "_" + std::to_string(y) + ":";
			this->_tosend += std::to_string(r2) + "_1";
			this->_tosend += "\n";
		}
		else
		{
			this->_tosend += "BH_" + std::to_string(x) + "_" + std::to_string(y) + ":";
			this->_tosend += std::to_string(r2) + "_1";
			this->_tosend += "\n";
		}
	}
	else if (r < 100)
	{
		int r2 = 2 + (rand() % 4);
		MultiFood *b = new MultiFood(r2, x, y, true);
		this->_Map[x][y] = b;
		this->_bonus.push_back(b);
		if (this->_tosend == "")
		{
			this->_tosend = "BM_" + std::to_string(x) + "_" + std::to_string(y) + ":";
			this->_tosend += std::to_string(r2);
			this->_tosend += "\n";
		}
		else
		{
			this->_tosend += "BM_" + std::to_string(x) + "_" + std::to_string(y) + ":";
			this->_tosend += std::to_string(r2);
			this->_tosend += "\n";
		}
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
			std::cout << "Bonus depop at : " << _x << "_" << _y << std::endl;
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

void					MapManager::restart(void)
{
	std::list<Food *>::iterator			fbegin = this->_foods.begin();
	std::list<Food *>::iterator			fend = this->_foods.end();
	std::list<ABonus *>::iterator		bbegin = this->_bonus.begin();
	std::list<ABonus *>::iterator		bend = this->_bonus.end();
	std::list<Wall *>::iterator			wbegin = this->_walls.begin();
	std::list<Wall *>::iterator			wend = this->_walls.end();

	while (fbegin != fend)
	{
		Food *f = *fbegin;
		this->_foods.erase(fbegin);
		fbegin = this->_foods.begin();
		delete f;
	}
	while (bbegin != bend)
	{
		ABonus *b = *bbegin;
		this->_bonus.erase(bbegin);
		bbegin = this->_bonus.begin();
		delete b;
	}
	int x = 0;
	int y = 0;
	while (x < this->_width)
	{
		y = 0;
		while (y < this->_height)
		{
			this->_Map[x][y] = NULL;
			y++;
		}
		x++;
	}
	while (wbegin != wend)
	{
		x = (*wbegin)->getX();
		y = (*wbegin)->getY();
		this->_Map[x][y] = (*wbegin);
		wbegin++;
	}
}

char				*MapManager::takeToSend(void)
{
	if (this->_tosend == "")
		return (NULL);
	char *tmp = (char *)this->_tosend.c_str();
	return (tmp);
}

void				MapManager::setToSend(char *tmp)
{
	if (this->_tosend == "")
		this->_tosend = tmp;
	else
		this->_tosend += tmp;
}

void				MapManager::ClearToSend(void)
{
	this->_tosend = "";
}

bool				MapManager::getWall(void)
{
	return (this->_wall);
}

void				MapManager::setWall(bool wall)
{
	this->_wall = wall;
}

void				MapManager::Snake_Eat(int index, int x, int y)
{
	std::list<Food *>::iterator		Fbegin = this->_foods.begin();
	std::list<Food *>::iterator		Fend = this->_foods.end();

	while (Fbegin != Fend)
	{
		if ((*Fbegin)->getX() == x && (*Fbegin)->getY() == y)
		{
			std::list<Snake *>::iterator Sbegin = this->_snakes.begin();
			std::list<Snake *>::iterator Send = this->_snakes.end();

			while (Sbegin != Send)
			{
				if ((*Sbegin)->getIndex() == index)
				{
					(*Sbegin)->eat(*(*Fbegin));
					break;
				}
				Sbegin++;
			}
			break;
		}
		Fbegin++;
	}
}

void				MapManager::Snake_Take(int index, int x, int y)
{
	std::list<ABonus *>::iterator		Bbegin = this->_bonus.begin();
	std::list<ABonus *>::iterator		Bend = this->_bonus.end();

	while (Bbegin != Bend)
	{
		if ((*Bbegin)->getX() == x && (*Bbegin)->getY() == y)
		{
			std::list<Snake *>::iterator Sbegin = this->_snakes.begin();
			std::list<Snake *>::iterator Send = this->_snakes.end();

			while (Sbegin != Send)
			{
				if ((*Sbegin)->getIndex() == index)
				{
					(*Sbegin)->take_bonus(*(*Bbegin));
					break;
				}
				Sbegin++;
			}
			break;
		}
		Bbegin++;
	}
}

void				MapManager::Snake_Death(int index)
{
	std::list<Snake *>::iterator	Sbegin = this->_snakes.begin();
	std::list<Snake *>::iterator	Send = this->_snakes.end();
	
	while (Sbegin != Send)
	{
		if ((*Sbegin)->getIndex() == index)
		{
			(*Sbegin)->SetAlive(false);
			break;
		}
			Sbegin++;
	}
}
