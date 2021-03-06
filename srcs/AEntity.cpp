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

void		AEntity::setPos(Point & set)
{
	this->_pos = set;
}

int			AEntity::getX(void) const
{
	return (this->_pos.getX());
}

int			AEntity::getY(void) const
{
	return (this->_pos.getY());
}

void		AEntity::setX(int x)
{
	this->_pos.setX(x);
}

void		AEntity::setY(int y)
{
	this->_pos.setY(y);
}

bool		AEntity::getEatable(void) const
{
	return (this->_eatable);
}
