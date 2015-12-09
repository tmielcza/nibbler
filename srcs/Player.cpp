// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/22 17:12:29 by rduclos           #+#    #+#             //
//   Updated: 2015/12/08 18:09:35 by tmielcza         ###   ########.fr       //
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
	this->_lastInputs = ass._lastInputs;
	this->_time = ass._time;
	return (*this);
}

bool		Player::IsAlive(void)
{
	return (this->_Snake->IsAlive());
}

int			Player::verify_lL(e_Cardinal d)
{
	if ((this->_Snake->getHeadSnakeDirec() & Longitude) &&
		(d & Latitude))
		return 1;
	else if ((this->_Snake->getHeadSnakeDirec() & Latitude) &&
			 (d & Longitude))
		return 1;
	return 0;
}

void		Player::update(double time)
{
	std::list<e_Cardinal>::iterator		tuchs = this->_lastInputs.begin();
	std::list<e_Cardinal>::iterator		end = this->_lastInputs.end();

	this->_time += (time * this->_Snake->getSpeed());
	if (this->_time >= 1)
	{
		this->_Snake->update_directions();
		if (this->_lastInputs.size() > 0)
		{
			while (tuchs != end && this->verify_lL(*tuchs) != 1)
			{
				this->_lastInputs.erase(tuchs);
				tuchs++;
			}
			if (tuchs != end)
			{
				this->_Snake->turn(*tuchs);
				this->_lastInputs.erase(tuchs);
			}
		}
		std::cout << this->_Snake->getHeadSnakeX() << " "
				  << this->_Snake->getHeadSnakeY() << std::endl;
		this->_Snake->befor_move();
		this->_Snake->move();
		this->_time = 0.;
	}
	this->_Snake->draw(this->_time);
}

void		Player::add_touch(e_Cardinal touch)
{
	this->_lastInputs.push_back(touch);
}

int			Player::getSizeTouch(void)
{
	return (this->_lastInputs.size());
}
