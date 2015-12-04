// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ABonus.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/05 18:44:11 by rduclos           #+#    #+#             //
//   Updated: 2015/04/07 16:32:40 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ABonus.hpp"

ABonus::ABonus(const ABonus & copy)
{
	*this = copy;
}

ABonus::ABonus(int value, int x, int y)
{
	this->_value = value;
	this->_isalive = true;
	this->_eatable = true;
	this->_pos.setX(x);
	this->_pos.setY(y);
}

ABonus::~ABonus(void)
{

}

ABonus	&	ABonus::operator=(const ABonus & ass)
{
	this->_value = ass._value;
	this->_pos = ass._pos;
	this->_eatable = true;
	this->_isalive = true;
	return (*this);
}

bool		ABonus::isalive(void)
{
	return (this->_isalive);
}
