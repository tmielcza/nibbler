// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Wall.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 18:26:10 by rduclos           #+#    #+#             //
//   Updated: 2015/04/07 14:52:38 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Wall.hpp"

Wall::Wall(void)
{
	std::cout << "Wall Builed !!!" << std::endl;
}

Wall::Wall(Point pos)
{
	std::cout << "Wall Builed !!!" << std::endl;
	this->_pos.setX(pos.getX());
	this->_pos.setY(pos.getY());
}

Wall::Wall(int x, int y)
{
	std::cout << "Wall Builed !!!" << std::endl;
	this->_pos.setX(x);
	this->_pos.setY(y);
	this->_eatable = false;
}

Wall::Wall(Wall const & copy)
{
	*this = copy;
}

Wall::~Wall(void)
{
	std::cout << "Destruction of the Wall !!!" << std::endl;
}

void		Wall::initWall(int x, int y)
{
	this->_pos.setX(x);
	this->_pos.setY(y);
	this->_eatable = false;
}

Wall	&	Wall::operator=(Wall const & ass)
{
	this->_pos = ass._pos;
	return (*this);
}

void		Wall::draw(double time)
{
	(void)time;
}
