// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Snake.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 17:52:27 by rduclos           #+#    #+#             //
//   Updated: 2015/12/02 16:25:21 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Snake.hpp"
#include "MapManager.hpp"

int		Snake::_curIndex = 0;

Snake::Snake(void) : _index(Snake::_curIndex++)
{
	std::cout << "Creating snake !!" << std::endl;
	this->_score = 0;
	this->_nbmove = 0;
	this->_speed = 1;
	this->init(East, 7, 7);
	this->_alive = true;
}

Snake::Snake(e_Cardinal direction, int x, int y) : _index(Snake::_curIndex++)
{
	std::cout << "Creating snake !!" << std::endl;
	this->_score = 0;
	this->_nbmove = 0;
	this->_speed = 1;
	this->init(direction, x, y);
	this->_alive = true;
}

Snake::~Snake(void)
{
	std::list<Segment>::iterator		tmp = this->_snake.begin();
	std::list<Segment>::iterator		end = this->_snake.end();

	std::cout << "Destroying snake !!" << std::endl;
	while (tmp != end)
	{
		this->_snake.pop_front();
		tmp = this->_snake.begin();
	}
}

void							Snake::init(int direction, int x, int y)
{
	Segment		*seg;

	for (int i = 0; i < 4; i++)
	{
		seg = new Segment(x, y, (e_Cardinal)direction);
		this->_snake.push_back(*seg);		
		if (seg->get_Direc() == North)
			x++;
		else if (seg->get_Direc() == South)
			x--;
		else if (seg->get_Direc() == East)
			y++;
		else if (seg->get_Direc() == West)
			y--;
	}
	this->_tail = seg;
}

std::list<Segment>	&			Snake::get_snake(void)
{
	return (this->_snake);
}

/*
void							Snake::add_to_tail(void)
{
//	std::list<Segment>::iterator	head = this->_snake.begin();
//	std::list<Segment>::iterator	tail = this->_snake.end();

}
*/

void							Snake::befor_move(void)
{
	std::list<Segment>::iterator		head = this->_snake.begin();

	int x = head->getX();
	int y = head->getY();
	e_Cardinal direc = head->get_Direc();
	if (direc == North)
		y++;
	else if (direc == South)
		y--;
	else if (direc == East)
		x++;
	else if (direc == West)
		x--;
	if (MapManager::Instance()._Map[x][y] != NULL)
	{
		if (MapManager::Instance()._Map[x][y]->getEatable() == false)
			this->_alive = false;
		else
			this->eat(*dynamic_cast<Food *>(MapManager::Instance()._Map[x][y]));
	}
}

void							Snake::move(void)
{
	std::list<Segment>::iterator		seg = this->_snake.begin();
	std::list<Segment>::iterator		end = this->_snake.end();

	Point tmp = seg->getPos();
	e_Cardinal direc = seg->get_Direc();
	if (direc == North)
	{
		if ((int x = seg->getY() + 1) < MapManager::Instance().getHeight())
			seg->setY(x);
		else
			seg->setY(0);
		
	}
	else if (direc == South)
		seg->setY(seg->getY() - 1);
	else if (direc == East)
		seg->setX(seg->getX() + 1);
	else if (direc == West)
		seg->setX(seg->getX() - 1);
	seg++;
	while (seg != end)
	{
		Point tmp2 = seg->getPos();
		seg->setPos(tmp);
		tmp = tmp2;
		seg++;
	}
}

void							Snake::turn_left(void)
{
	std::list<Segment>::iterator	head = this->_snake.begin();

	if (this->_nbmove == -1)
		this->_nbmove = 0;
	if (head->get_Direc() == North)
		head->set_Direc(West);
	else if (head->get_Direc() == South)
		head->set_Direc(East);
	else if (head->get_Direc() == East)
		head->set_Direc(North);
	else if (head->get_Direc() == West)
		head->set_Direc(South);
	this->_nbmove++;
}

void							Snake::turn_right(void)
{
	std::list<Segment>::iterator	head = this->_snake.begin();

	if (this->_nbmove == -1)
		this->_nbmove = 0;
	if (head->get_Direc() == North)
		head->set_Direc(East);
	else if (head->get_Direc() == South)
		head->set_Direc(West);
	else if (head->get_Direc() == East)
		head->set_Direc(South);
	else if (head->get_Direc() == West)
		head->set_Direc(North);
	this->_nbmove++;
}

void							Snake::eat(Food const & eaten)
{
	Segment								*seg = new Segment();

	(void)eaten;
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
	this->_snake.push_back(*seg);
	this->_tail = seg;
	if (this->_nbmove <= 2 && this->_nbmove >= 0)
		this->_score = eaten.get_value() * 2;
	else
		this->_score = eaten.get_value();
	this->_speed += 0.1;
	this->_nbmove = 0;
}

void							Snake::take_bonus(ABonus const & taken)
{
	(void)taken;
//	taken.bonus(this);
}

int								Snake::getHeadSnakeX(void)
{
	std::list<Segment>::iterator			head = this->_snake.begin();

	return (head->getX());
}

int								Snake::getHeadSnakeY(void)
{
	std::list<Segment>::iterator			head = this->_snake.begin();

	return (head->getY());
}

int								Snake::getIndex(void)
{
	return (this->_index);
}
