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

ABonus::ABonus(void)
{

}

ABonus::ABonus(const ABonus & copy)
{
	*this = copy;
}

ABonus::ABonus(int value, bool alive)
{
	this->_value = value;
	this->_isalive = alive;
}

ABonus::~ABonus(void)
{

}

ABonus	&	ABonus::operator=(const ABonus & ass)
{
	this->_pos = ass._pos;
	return (*this);
}

bool		ABonus::isdead(void)
{
	return (this->_isalive);
}

void		ABonus::bonus_taken(const Snake & snake)
{
	(void)snake;
}
