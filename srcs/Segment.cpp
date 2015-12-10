// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Segment.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/06 19:00:25 by rduclos           #+#    #+#             //
//   Updated: 2015/12/09 18:29:05 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Segment.hpp"
#include "MapManager.hpp"
#include "GraphicsManager.hpp"

Segment::Segment(void)
{
	
}

Segment::Segment(const Segment & copy)
{
	*this = copy;
}

Segment::Segment(int x, int y, e_Cardinal direction, int id)
{
	this->_id = id;
	this->_pos.setX(x);
	this->_pos.setY(y);
	this->_eatable = false;
	this->_direction = direction;
}

Segment::~Segment(void)
{

}

Segment	&	Segment::operator=(const Segment & ass)
{
	this->_pos = ass._pos;
	this->_direction = ass._direction;
	this->_eatable = ass._eatable;
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
	GraphicsManager::Instance().drawTail(time, this->_pos.getX(), this->_pos.getY(), (e_Dir)(this->_direction), this->_id);
}

int			Segment::getID(void)
{
	return (this->_id);
}
