// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/22 17:12:29 by rduclos           #+#    #+#             //
//   Updated: 2015/12/04 21:37:48 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Player.hpp"
#include "MapManager.hpp"
#include "GraphicsManager.hpp"

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
	this->_time = ass._time;
	return (*this);
}

bool		Player::IsAlive(void)
{
	return (this->_Snake->IsAlive());
}

void		Player::update(double time)
{
	e_Input				input = I_Nope;
	std::list<e_Input>	inputs;

	inputs = GraphicsManager::Instance().getInput();
	GraphicsManager::Instance().clear();
	for (auto it = inputs.begin(); it != inputs.end(); it++)
	{
		if ((*it & I_Dir) != 0)
			input = *it;
	}
	if ((input & I_Dir) != 0)
	{
		if ((this->_Snake->getHeadSnakeDirec() & Longitude) &&
			((e_Cardinal)input & Latitude))
			this->_lastInput = (e_Cardinal)input;
		else if ((this->_Snake->getHeadSnakeDirec() & Latitude) &&
				 ((e_Cardinal)input & Longitude))
			this->_lastInput = (e_Cardinal)input;
	}
	this->_time += (time * this->_Snake->getSpeed());
	if (this->_time >= 1)
//	if (this->_time >= SN_TIME)
	{
		if (this->_lastInput != None)
		{
			this->_Snake->turn(this->_lastInput);
			this->_lastInput = None;
		}
		std::cout << this->_Snake->getHeadSnakeX() << " "
				  << this->_Snake->getHeadSnakeY() << std::endl;
		this->_Snake->befor_move();
		this->_Snake->move();
		this->_time = 0.;
	}
	this->_Snake->draw(this->_time);
}
