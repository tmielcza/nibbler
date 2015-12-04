// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/22 17:12:29 by rduclos           #+#    #+#             //
//   Updated: 2015/12/03 21:32:34 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Player.hpp"
#include "MapManager.hpp"

Player::Player(void)
{
	std::cout << "Creating Player !" << std::endl;
	this->_Snake = new Snake();
	MapManager::Instance().setSnake(this->_Snake);
}

Player::Player(Snake *snake)
{
	if (snake != NULL)
	{
		std::cout << "Creating Player !" << std::endl;
		this->_Snake = snake;
		MapManager::Instance().setSnake(this->_Snake);
	}
}

Player::Player(const Player & copy)
{
	*this = copy;
}

Player::~Player(void)
{
	delete this->_Snake;
	std::cout << "Destroying Player !" << std::endl;
}

Player	&	Player::operator=(const Player & ass)
{
	this->_Snake = ass._Snake;
	this->_lastInput = ass._lastInput;
	this->_nextMove = ass._nextMove;
	return (*this);
}

bool		Player::IsAlive(void)
{
	return (this->_Snake->IsAlive());
}

void		Player::move(e_Cardinal direc)
{
	this->_Snake->turn(direc);
}
