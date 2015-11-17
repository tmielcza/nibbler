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

Wall::Wall(int width, int height) : _size(width, height)
{
	std::cout << "Wall Builed !!!" << std::endl;
}

Wall::Wall(Point size) : _size(size)
{
	std::cout << "Wall Builed !!!" << std::endl;
}

Wall::~Wall(void)
{
	std::cout << "Destruction of the Wall !!!" << std::endl;
}

void	Wall::initWall(int width, int height)
{
	this->_size._x = width;
	this->_size._y = height;
}

int		Wall::getWidth(void) const
{
	return (this->_size._x);
}

int		Wall::getHeight(void) const
{
	return (this->_size._y);
}

Point	Wall::getSize(void) const
{
	return (this->_size);
}
