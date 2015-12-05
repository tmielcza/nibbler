// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Food.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 18:03:56 by rduclos           #+#    #+#             //
//   Updated: 2015/04/07 14:49:08 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Food.hpp"
#include "GraphicsManager.hpp"

Food::Food(void)
{
	std::cout << "Food's poped from the big Tree !" << std::endl;
}

Food::Food(Food const & copy)
{
	*this = copy;
}

Food::Food(int value, int x, int y)
{
	std::cout << "Food's poped from the big Tree !" << std::endl;
	this->_value = value;
	this->_pos.setX(x);
	this->_pos.setY(y);
	this->_eatable = true;
	GraphicsManager::Instance().popFood(x, y);
}

Food::~Food(void)
{
	int x = this->_pos.getX();
	int y = this->_pos.getY();
	GraphicsManager::Instance().depopFood(x, y);
	std::cout << "Food in " << x << "-" << y << " has been eaten !" << std::endl;
}

Food	&	Food::operator=(Food const & ass)
{
	this->_pos.setX(ass._pos.getX());
	this->_pos.setY(ass._pos.getY());
	this->_eatable = true;
	this->_value = ass._value;
	return (*this);
}

bool		Food::check_position(int x, int y)
{
	if (this->_pos.getX() == x && this->_pos.getY() == y)
		return (true);
	return (false);
}

int			Food::get_value(void) const
{
	return (this->_value);
}

void		Food::set_value(int value)
{
	this->_value = value;
}

void		Food::draw(double time)
{
	(void)time;
}

void		Food::eaten(Snake & eater) const
{
	(void)eater;
	delete this;
}
