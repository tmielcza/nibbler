// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Segment.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/06 19:00:25 by rduclos           #+#    #+#             //
//   Updated: 2015/04/07 14:51:41 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Segment.hpp"

Segment::Segment(void)
{

}

Segment::Segment(const Segment & copy)
{
	*this = copy;
}

Segment::Segment(int x, int y, e_Cardinal direction)
{
	this->_pos._x = x;
	this->_pos._y = y;
	this->_direction = direction;
}

Segment::~Segment(void)
{

}

Segment	&	Segment::operator=(const Segment & ass)
{
	this->_pos = ass._pos;
	this->_direction = ass._direction;
	return (*this);
}
