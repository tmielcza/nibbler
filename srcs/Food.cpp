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
	this->_value = value;
	this->_pos._x = x;
	this->_pos._y = y;
}

Food::~Food(void)
{
	std::cout << "Food has been eaten !" << std::endl;
}

Food	&	Food::operator=(Food const & ass)
{
	this->_pos._x = ass._pos._x;
	this->_pos._y = ass._pos._y;
	this->_value = ass._value;
	return (*this);
}

bool		Food::check_position(int x, int y)
{
	if (this->_pos._x == x && this->_pos._y == y)
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
