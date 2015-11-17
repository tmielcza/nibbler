// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AEntity.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/06 18:46:31 by rduclos           #+#    #+#             //
//   Updated: 2015/04/08 14:37:56 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "AEntity.hpp"

AEntity::AEntity(void)
{

}

AEntity::AEntity(AEntity const & copy)
{
	*this = copy;
}

AEntity::~AEntity(void)
{

}

AEntity	&	AEntity::operator=(AEntity const & ass)
{
	this->_pos = ass._pos;
	return (*this);
}

Point	&	AEntity::getPos(void)
{
	return (this->_pos);
}

int			AEntity::getX(void) const
{
	return (this->_pos._x);
}

int			AEntity::getY(void) const
{
	return (this->_pos._y);
}

void		AEntity::setX(int x)
{
	this->_pos._x = x;
}

void		AEntity::setY(int y)
{
	this->_pos._y = y;
}
