// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Snake.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 17:52:27 by rduclos           #+#    #+#             //
//   Updated: 2015/12/07 19:03:36 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Snake.hpp"
#include "MapManager.hpp"
#include "GraphicsManager.hpp"

int		Snake::_curIndex = 0;

Snake::Snake(void) : _index(Snake::_curIndex++)
{
	this->_score = 0;
	this->_nbmove = 0;
	this->_speed = 4;
	this->_alive = true;
	this->init();
	std::cout << "Creating Snake !!" << std::endl;
}

Snake::Snake(e_Cardinal direction, int x, int y) : _index(Snake::_curIndex++)
{
	this->_score = 0;
	this->_nbmove = 0;
	this->_speed = 4;
	this->_increm = 0.5;
	this->init(direction, x, y);
	this->_alive = true;
	std::cout << "Creating Snake !!" << std::endl;
}

Snake::~Snake(void)
{
	std::list<Segment*>::iterator		tmp = this->_snake.begin();
	std::list<Segment*>::iterator		end = this->_snake.end();

	std::cout << "Destroying Snake !!" << std::endl;
	while (tmp != end)
	{
		this->_snake.pop_front();
		tmp = this->_snake.begin();
	}
}

bool							Snake::check_place_snake(int x, int y)
{
	bool		good = true;

	if (MapManager::Instance()._Map[x][y] != NULL)
		good = false;
	if (MapManager::Instance()._Map[x - 1][y] != NULL)
		good = false;
	if (MapManager::Instance()._Map[x - 2][y] != NULL)
		good = false;
	if (MapManager::Instance()._Map[x - 3][y] != NULL)
		good = false;
	return (good);
}

void							Snake::init(void)
{
	int		width = MapManager::Instance().getWidth();
	int		height = MapManager::Instance().getHeight();
	int		x = (width - (width - (width / 4)));
	int		y = (rand() % height);

	while (check_place_snake(x, y) == false)
		y = rand() % height;
	this->init(East, x, y);
}

void							Snake::init(e_Cardinal direction, int x, int y)
{
	Segment		*seg;

	for (int i = 0; i < 4; i++)
	{
		seg = new Segment(x, y, direction);
		this->_snake.push_back(seg);		
		if (seg->get_Direc() == North)
			y--;
		else if (seg->get_Direc() == South)
			y++;
		else if (seg->get_Direc() == East)
			x--;
		else if (seg->get_Direc() == West)
			x++;
	}
	this->_tail = seg;
}

std::list<Segment*>	&			Snake::get_snake(void)
{
	return (this->_snake);
}


void							Snake::add_to_tail(void)
{
	Segment								*seg = new Segment();

	seg->set_Direc(this->_tail->get_Direc());
	if (seg->get_Direc() == North)
	{
		seg->setX(this->_tail->getX());
		seg->setY(this->_tail->getY() - 1);
	}
	else if (seg->get_Direc() == South)
	{
		seg->setX(this->_tail->getX());
		seg->setY(this->_tail->getY() + 1);
	}
	else if (seg->get_Direc() == East)
	{
		seg->setX(this->_tail->getX() - 1);
		seg->setY(this->_tail->getY());
	}
	else if (seg->get_Direc() == West)
	{
		seg->setX(this->_tail->getX() + 1);
		seg->setY(this->_tail->getY());
	}
	seg->set_Direc(this->_tail->get_Direc());
	this->_snake.push_back(seg);
	this->_tail = seg;
}

void							Snake::add_score(int score)
{
	this->_score += score;
}

void							Snake::befor_move(void)
{
	std::list<Segment*>::iterator		head = this->_snake.begin();
	int x = (*head)->getX();
	int y = (*head)->getY();

	e_Cardinal direc = (*head)->get_Direc();

	if (direc == North)
	{
		y++;
		if (y >= MapManager::Instance().getHeight())
			y = 0;
	}
	else if (direc == South)
	{
		y--;
		if (y < 0)
			y = MapManager::Instance().getHeight() - 1;
	}
	else if (direc == East)
	{
		x++;
		if (x >= MapManager::Instance().getWidth())
			x = 0;
	}
	else if (direc == West)
	{
		x--;
		if (x < 0)
			x = MapManager::Instance().getWidth() - 1;
	}
	if (MapManager::Instance()._Map[x][y] != NULL)
	{
		if (MapManager::Instance()._Map[x][y]->getEatable() == false)
			this->_alive = false;
		else
		{
			if (dynamic_cast<Food*>(MapManager::Instance()._Map[x][y]))
				this->eat(*dynamic_cast<Food *>(MapManager::Instance()._Map[x][y]));
			else
				this->take_bonus(*dynamic_cast<ABonus *>(MapManager::Instance()._Map[x][y]));
		}
	}
}

void							Snake::move(void)
{
	std::list<Segment*>::iterator		seg = this->_snake.begin();
	std::list<Segment*>::iterator		end = this->_snake.end();
	int									x = (*seg)->getX();
	int									y = (*seg)->getY();
	Point								tmp = (*seg)->getPos();
	e_Cardinal							direc = (*seg)->get_Direc();

	MapManager::Instance()._Map[x][y] = NULL;
	if (direc == North)
	{
		if ((y = (*seg)->getY() + 1) < MapManager::Instance().getHeight())
			(*seg)->setY(y);
		else
			(*seg)->setY(0);
	}
	else if (direc == South)
	{
		if ((y = (*seg)->getY() -1) >= 0)
			(*seg)->setY(y);
		else
			(*seg)->setY(MapManager::Instance().getHeight() - 1);
	}
	else if (direc == East)
	{
		if ((x = (*seg)->getX() + 1) < MapManager::Instance().getWidth())
			(*seg)->setX(x);
		else
			(*seg)->setX(0);
	}
	else if (direc == West)
	{
		if ((x = (*seg)->getX() - 1) >= 0)
			(*seg)->setX(x);
		else
			(*seg)->setX(MapManager::Instance().getWidth() - 1);
	}
	MapManager::Instance()._Map[x][y] = (*seg);
	seg++;
	while (seg != end)
	{
		Point tmp2 = (*seg)->getPos();
		(*seg)->setPos(tmp);
		MapManager::Instance()._Map[tmp2.getX()][tmp2.getY()] = NULL;
		MapManager::Instance()._Map[tmp.getX()][tmp.getY()] = (*seg);
		tmp = tmp2;
		seg++;
	}
}

void							Snake::turn(e_Cardinal direction)
{
	Segment*	head = *(this->_snake.begin());
	
	if (head->get_Direc() & Latitude)
		if (direction & Longitude)
		{
			if (direction == North)
				direction = South;
			else
				direction = North;
			head->set_Direc(direction);
		}
	if (head->get_Direc() & Longitude)
		if (direction & Latitude)
			head->set_Direc(direction);
	if (this->_nbmove == -1)
		this->_nbmove = 0;
	this->_nbmove++;
	if (this->_nbmove == 3)
		GraphicsManager::Instance().switchFoodMode();
}

void							Snake::turn_left(void)
{
	std::list<Segment*>::iterator	head = this->_snake.begin();

	if (this->_nbmove == -1)
		this->_nbmove = 0;
	if ((*head)->get_Direc() == North)
		(*head)->set_Direc(West);
	else if ((*head)->get_Direc() == South)
		(*head)->set_Direc(East);
	else if ((*head)->get_Direc() == East)
		(*head)->set_Direc(North);
	else if ((*head)->get_Direc() == West)
		(*head)->set_Direc(South);
	this->_nbmove++;
}

void							Snake::turn_right(void)
{
	std::list<Segment*>::iterator	head = this->_snake.begin();

	if (this->_nbmove == -1)
		this->_nbmove = 0;
	if ((*head)->get_Direc() == North)
		(*head)->set_Direc(East);
	else if ((*head)->get_Direc() == South)
		(*head)->set_Direc(West);
	else if ((*head)->get_Direc() == East)
		(*head)->set_Direc(South);
	else if ((*head)->get_Direc() == West)
		(*head)->set_Direc(North);
	this->_nbmove++;
}

void							Snake::eat(Food const & eaten)
{
	GraphicsManager::Instance().popWave(this->getHeadSnakeX(), this->getHeadSnakeY());
	this->add_to_tail();
	if (this->_nbmove <= 2 && this->_nbmove >= 0)
		this->_score = eaten.get_value() * 2;
	else
		this->_score = eaten.get_value();
	this->_speed += 0.2;
//	this->_speed += this->_increm;
//	if (this->_increm > 0.01)
//		this->_increm -= 0.01;
//	else
//		this->_increm = 0.01;
	if (eaten.getSpawner() == true)
		MapManager::Instance().foodpop(true);
	eaten.eaten(*this);
	std::cout << "eat : " << this->_nbmove << std::endl;
	if (this->_nbmove > 2)
		GraphicsManager::Instance().switchFoodMode();
	this->_nbmove = 0;
}

void							Snake::take_bonus(ABonus & taken)
{
	taken.taken(*this);
	std::cout << "Bonus have been taken by the Snake" << std::endl;
}

e_Cardinal						Snake::getHeadSnakeDirec(void)
{
	std::list<Segment*>::iterator			head = this->_snake.begin();

	return ((*head)->get_Direc());
}
int								Snake::getHeadSnakeX(void)
{
	std::list<Segment*>::iterator			head = this->_snake.begin();

	return ((*head)->getX());
}

int								Snake::getHeadSnakeY(void)
{
	std::list<Segment*>::iterator			head = this->_snake.begin();

	return ((*head)->getY());
}

int								Snake::getIndex(void)
{
	return (this->_index);
}

double							Snake::getSpeed(void)
{
	return (this->_speed);
}

bool							Snake::IsAlive(void)
{
	return (this->_alive);
}

void							Snake::draw(double time)
{
	float x, y;

	(void)time;
	x = this->getHeadSnakeX();
	y = this->getHeadSnakeY();
	auto it = this->_snake.begin();
	GraphicsManager::Instance().drawHead(time, x, y, (e_Dir)(*it)->get_Direc());
	it++;
	for (auto end = this->_snake.end(); it != end; it++)
	{
		(*it)->draw(time);
	}
}

void							Snake::update_directions(void)
{
	auto it = this->_snake.begin();
	e_Cardinal last_dir = (*it)->get_Direc();
	e_Cardinal tmp_dir;

	it++;
	for (auto end = this->_snake.end(); it != end; it++)
	{
		tmp_dir = (*it)->get_Direc();
		(*it)->set_Direc(last_dir);
		last_dir = tmp_dir;
	}
}
