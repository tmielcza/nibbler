// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Snake.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 17:52:27 by rduclos           #+#    #+#             //
//   Updated: 2015/04/29 18:26:55 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Snake.hpp"

int		Snake::_curIndex = 0;

Snake::Snake(void) : _index(Snake::_curIndex++)
{
	std::cout << "Creating snake !!" << std::endl;
	this->_score = 0;
	this->_nbmove = 0;
	this->_speed = 1;
	this->init(East, 7, 7);
}

Snake::Snake(const Snake & copy) : _index(copy._index)
{
	*this = copy;
}

Snake::Snake(e_Cardinal direction, int x, int y) : _index(Snake::_curIndex++)
{
	std::cout << "Creating snake !!" << std::endl;
	this->_score = 0;
	this->_nbmove = 0;
	this->_speed = 1;
	this->init(direction, x, y);
}

Snake::~Snake(void)
{
	std::list<Segment>::iterator		tmp = this->_snake.begin();
	std::list<Segment>::iterator		end = this->_snake.end();

	std::cout << "Destroyng snake !!" << std::endl;
	while (tmp != end)
	{
		this->_snake.pop_front();
		tmp = this->_snake.begin();
	}
}

void							Snake::setNextDir(e_SDir NextDir)
{
	this->_nextDir = NextDir;
}

e_SDir							Snake::getNextDir(void)
{
	return (this->_nextDir);
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

void							Snake::add_to_tail(void)
{
//	std::list<Segment>::iterator	head = this->_snake.begin();
//	std::list<Segment>::iterator	tail = this->_snake.end();

}

void							Snake::befor_move(void)
{

}

void							Snake::move(void)
{

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
	std::list<Segment>::iterator		tmp = this->_snake.begin();
	std::list<Segment>::iterator		end = this->_snake.end();
	Segment								*seg = new Segment();

	(void)eaten;
	while (tmp != end)
		tmp++;
	tmp--;
	seg->set_Direc(this->_tail->get_Direc());
	if (seg->get_Direc() == North)
	{
		seg->setX(tmp->getX());
		seg->setY(tmp->getY() - 1);
	}
	else if (seg->get_Direc() == South)
	{
		seg->setX(tmp->getX());
		seg->setY(tmp->getY() + 1);
	}
	else if (seg->get_Direc() == East)
	{
		seg->setX(tmp->getX() - 1);
				  seg->setY(tmp->getY());
	}
	else if (seg->get_Direc() == West)
	{
		seg->setX(tmp->getX() + 1);
				  seg->setY(tmp->getY());
	}
	this->_snake.push_back(*seg);
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
