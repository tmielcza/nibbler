// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SuperFood.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/25 18:12:35 by rduclos           #+#    #+#             //
//   Updated: 2016/01/25 18:12:35 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "SuperFood.hpp"
#include "GraphicsManager.hpp"
#include "Snake.hpp"
#include "MapManager.hpp"

SuperFood::SuperFood(void)
{

}

SuperFood::SuperFood(int value, int x, int y)
{
	GraphicsManager::Instance().popSuperFood(x, y, 10 - value);
	this->_pos.setX(x);
	this->_pos.setY(y);
	this->_value = value;
	this->_timing = 0;
	this->_time = 0;
	this->_isalive = true;
	this->_eatable = true;
}

SuperFood::SuperFood(const SuperFood & src)
{
	*this = src;
}

SuperFood::~SuperFood(void)
{
	GraphicsManager::Instance().depopFood(this->_pos.getX(), this->_pos.getY());
	MapManager::Instance().bonusdepop(this->_pos.getX(), this->_pos.getY());
}

SuperFood	&		SuperFood::operator=(const SuperFood & src)
{
	this->_value = src._value;
	this->_timing = src._timing;
	this->_isalive = src._isalive;
	this->_time = src._time;
	this->_pos = src._pos;
	return (*this);
}

void				SuperFood::taken(Snake & snake)
{
	GraphicsManager::Instance().popWave(this->getX(), this->getY());
	if (this->_value == 9)
		snake.add_score((this->_value + 1) * 20);
	else
		snake.add_score((this->_value + 1) * 2);
	delete this;
}

void				SuperFood::update(double time)
{
	this->_time += time;
	if ((this->_time - this->_timing) >= 1)
	{
		this->_timing++;
		this->_value++;
		GraphicsManager::Instance().updateSuperFood(this->_pos.getX(), this->_pos.getY(), 10 - this->_value);
	}
	if (this->_time >= 9)
	{
		MapManager::Instance()._Map[this->_pos.getX()][this->_pos.getY()] = NULL;
		delete this;
	}
}

void				SuperFood::draw(double time)
{
	(void)time;
}
