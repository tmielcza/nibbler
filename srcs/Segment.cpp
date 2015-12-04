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
#include "MapManager.hpp"

Segment::Segment(void)
{

}

Segment::Segment(const Segment & copy)
{
	*this = copy;
}

Segment::Segment(int x, int y, e_Cardinal direction)
{
	this->_pos.setX(x);
	this->_pos.setY(y);
	this->_eatable = false;
	this->_direction = direction;
	MapManager::Instance()._Map[x][y] = this;
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

e_Cardinal	Segment::get_Direc(void)
{
	return (this->_direction);
}

void		Segment::set_Direc(e_Cardinal direc)
{
	this->_direction = direc;
}

void		Segment::draw(double time)
{
	(void)time;
}
