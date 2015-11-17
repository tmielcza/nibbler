// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Point.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/05 15:14:05 by rduclos           #+#    #+#             //
//   Updated: 2015/04/08 15:47:04 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Point.hpp"

Point::Point(void)
{
}

Point::Point(const Point& src)
{
	*this = src;
}

Point::Point(int x, int y) : _x(x), _y(y)
{

}

Point::~Point(void)
{

}

Point&		Point::operator=(const Point& rhs)
{
	this->_x = rhs._x;
	this->_y = rhs._y;
	return (*this);
}

Point		Point::operator+(const Point& rhs) const
{
	return ( Point(this->_x + rhs._x, this->_y + rhs._y) );
}

Point		Point::operator+(const int rhs) const
{
	return ( Point(this->_x + rhs, this->_y + rhs) );
}

Point		Point::operator-(const Point& rhs) const
{
	return ( Point(this->_x - rhs._x, this->_y - rhs._y) );
}

Point		Point::operator-(const int rhs) const
{
	return ( Point(this->_x - rhs, this->_y - rhs) );
}

bool		Point::operator==(const Point& rhs) const
{
	if (this->_x == rhs._x && this->_y == rhs._y)
		return (true);
	return (false);
}

bool		Point::operator!=(const Point& rhs) const
{
	if (this->_x == rhs._x && this->_y == rhs._y)
		return (false);
	return (true);
}
