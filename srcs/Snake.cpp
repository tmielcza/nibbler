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
	this->save_my_tail();
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

Snake						&	Snake::operator=(Snake const & ass)
{
	auto								head = ass._snake.begin();

	this->init(head->_direction, head->getX(), head->getY());
	this->_score = ass._score;
	this->_nbmove = ass._nbmove;
	this->_speed = ass._speed;
	return (*this);
}

void							Snake::setNextDir(e_SDir NextDir)
{
	this->_nextDir = NextDir;
}

e_SDir							Snake::getNextDir(void)
{
	return (this->_nextDir);
}

void							Snake::save_my_tail(void)
{
	auto	tail = this->_snake.end();

	tail--;
	if (this->_tail)
		delete this->_tail;
	this->_tail = new Segment(tail->getX(), tail->getY(), tail->_direction);
}

bool							Snake::colision_wall(Wall const & wall)
{
	std::list<Segment>::iterator		head = this->_snake.begin();
	int									width = wall.getWidth();
	int									height = wall.getHeight();

	if (head->getX() < 0 || head->getX() >= width)
		return (true);
	else if (head->getY() < 0 || head->getY() >= height)
		return (true);
	return (false);
}

bool							Snake::colision_snake(Snake const & snake)
{
	std::list<Segment>::iterator			head = this->_snake.begin();
	auto											tmp = snake._snake.begin();
	auto											end = snake._snake.end();

	while (tmp != end)
	{
		if (tmp->getX() == head->getX() && tmp->getY() == head->getY())
			return (true);
		tmp++;
	}
	return (false);
}

bool								Snake::colision_itself(void)
{
	std::list<Segment>::iterator			start = this->_snake.begin();
	std::list<Segment>::iterator			end = this->_snake.end();
	std::list<Segment>::iterator			tmp = this->_snake.begin();

	tmp++;
	while (tmp != end)
	{
		if (start->getX() == tmp->getX() &&
			start->getY() == tmp->getY())
			return (true);
		tmp++;
	}
	return (false);
}

void							Snake::init(int direction, int x, int y)
{
	Segment		*seg;

	for (int i = 0; i < 4; i++)
	{
		seg = new Segment(x, y, (e_Cardinal)direction);
		this->_snake.push_back(*seg);
		if (seg->_direction == North)
			x++;
		else if (seg->_direction == South)
			x--;
		else if (seg->_direction == East)
			y++;
		else if (seg->_direction == West)
			y--;
	}
}

std::list<Segment>	&	Snake::get_snake(void)
{
	return (this->_snake);
}

void							Snake::turn_left(void)
{
	std::list<Segment>::iterator	head = this->_snake.begin();

	if (this->_nbmove == -1)
		this->_nbmove = 0;
	if (head->_direction == North)
		head->_direction = West;
	else if (head->_direction == South)
		head->_direction = East;
	else if (head->_direction == East)
		head->_direction = North;
	else if (head->_direction == West)
		head->_direction = South;
	this->_nbmove++;
}

void							Snake::turn_right(void)
{
	std::list<Segment>::iterator	head = this->_snake.begin();

	if (this->_nbmove == -1)
		this->_nbmove = 0;
	if (head->_direction == North)
		head->_direction = East;
	else if (head->_direction == South)
		head->_direction = West;
	else if (head->_direction == East)
		head->_direction = South;
	else if (head->_direction == West)
		head->_direction = North;
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
	seg->_direction = this->_tail->_direction;
	if (seg->_direction == North)
	{
		seg->setX(tmp->getX());
		seg->setY(tmp->getY() - 1);
	}
	else if (seg->_direction == South)
	{
		seg->setX(tmp->getX());
		seg->setY(tmp->getY() + 1);
	}
	else if (seg->_direction == East)
	{
		seg->setX(tmp->getX() - 1);
				  seg->setY(tmp->getY());
	}
	else if (seg->_direction == West)
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
