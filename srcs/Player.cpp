// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/22 17:12:29 by rduclos           #+#    #+#             //
//   Updated: 2015/11/22 17:19:45 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Player.hpp"

Player::Player(void)
{
	this->_Snake = new Snake();
}

Player::Player(Snake *snake)
{
	this->_Snake = snake;
}

Player::Player(const Player & copy)
{
	*this = copy;
}

Player::~Player(void)
{

}

Player	&	Player::operator=(const Player & ass)
{
	this->_Snake = ass._Snake;
	this->_lastInput = ass._lastInput;
	this->_nextMove = ass._nextMove;
	return (*this);
}
