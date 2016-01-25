// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/22 17:12:29 by rduclos           #+#    #+#             //
//   Updated: 2016/01/25 18:11:24 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Player.hpp"
#include "MapManager.hpp"
#include "GraphicsManager.hpp"

Player::Player(void)
{
	std::cout << "Creating Player !" << std::endl;
	this->_pl2 = false;
	this->_client = true;
	this->_local = true;
	this->_time = 0;
	this->_Snake = new Snake();
	this->_tosend = "";
	MapManager::Instance().setSnake(this->_Snake);
}

Player::Player(bool pl2, bool client, bool local)
{
	std::cout << "Creating Player !" << std::endl;
	this->_tosend = "";
	this->_pl2 = pl2;
	this->_local = local;
	this->_client = client;
	this->_time = 0;
	this->_Snake = new Snake(client, local);
	MapManager::Instance().setSnake(this->_Snake);
}

Player::Player(e_Cardinal direc, int x, int y, int index, bool pl2, bool client, bool local)
{
	this->_tosend = "";
	this->_pl2 = pl2;
	this->_local = local;
	this->_client = client;
	this->_time = 0;
	std::cout << "Creating Player in Player index : " << index << std::endl;
	this->_Snake = new Snake(direc, x, y, client, local, index);
	MapManager::Instance().setSnake(this->_Snake);
}

Player::Player(Snake *snake)
{
	if (snake != NULL)
	{
		std::cout << "Creating Player !" << std::endl;
		this->_Snake = snake;
		this->_pl2 = false;
		this->_tosend = "";
		this->_client = true;
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

bool		Player::verify_lL(e_Cardinal d)
{
	if (this->_lastInputs.size() == 0)
	{
		if ((this->_Snake->getHeadSnakeDirec() & Longitude) &&
			(d & Latitude))
			return true;
		else if ((this->_Snake->getHeadSnakeDirec() & Latitude) &&
				 (d & Longitude))
			return true;
		return false;
	}
	else
	{
		std::list<e_Cardinal>::iterator			begin = this->_lastInputs.begin();

		if (((*begin) & Longitude) &&
			(d & Latitude))
			return true;
		else if (((*begin) & Latitude) &&
				 (d & Longitude))
			return true;
		return false;
	}
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
			if (tuchs != end)
			{
				this->_Snake->turn(*tuchs);
				this->_lastInputs.erase(tuchs);
			}
		}
		this->_Snake->befor_move();
		this->_Snake->move();
		this->_time = 0.;
		if (this->_local == true)
		{
			this->_tosend = "VS";
			this->_tosend += std::to_string(this->getIndex()) + "_";
			this->_tosend += std::to_string(this->getCycles()) + "_";
			this->_tosend += std::to_string(this->getX()) + "_";
			this->_tosend += std::to_string(this->getY()) + "_";
			this->_tosend += std::to_string(this->getDirec());
		}
	}
	this->_Snake->draw(this->_time);
	GraphicsManager::Instance().drawScore(this->_time, this->_Snake->getHeadSnakeX(),
										  this->_Snake->getHeadSnakeY(),
										  (e_Dir)this->_Snake->getHeadSnakeDirec(),
										  this->_Snake->getScore());
}

void		Player::add_touch(e_Cardinal touch)
{
	this->_lastInputs.push_back(touch);
}

int			Player::getSizeTouch(void)
{
	return (this->_lastInputs.size());
}

e_Cardinal	Player::getFirstTouch(void)
{
	std::list<e_Cardinal>::iterator		firstTouch = this->_lastInputs.begin();

	e_Cardinal tmp = (*firstTouch);
	return (tmp);
}

int			Player::getX(void)
{
	return (this->_Snake->getHeadSnakeX());
}

int			Player::getY(void)
{
	return (this->_Snake->getHeadSnakeY());
}

e_Cardinal	Player::getDirec(void)
{
	return (this->_Snake->getHeadSnakeDirec());
}

void		Player::setX(int x)
{
	std::cout << "Switch position of ";
	std::cout << this->getIndex() << " at x : ";
	std::cout << this->_Snake->getHeadSnakeX() << " to " << x << std::endl;
	this->_Snake->setHeadSnakeX(x);
	this->_time = 0;
}

void		Player::setY(int y)
{
	std::cout << "Switch position of ";
	std::cout << this->getIndex() << " at y : ";
	std::cout << this->_Snake->getHeadSnakeY() << " to " << y << std::endl;
	this->_Snake->setHeadSnakeY(y);
	this->_time = 0;
}

void		Player::setDirec(e_Cardinal direc)
{
	this->_Snake->setHeadSnakeDirec(direc);
}

int			Player::getIndex(void)
{
	return (this->_Snake->getIndex());
}

bool		Player::getPL2(void)
{
	return (this->_pl2);
}

void		Player::move(void)
{
	this->_Snake->move();
}

char		*Player::SnaketakeToSend(void)
{
	return (this->_Snake->takeToSend());
}

void		Player::SnakeClearToSend(void)
{
	this->_Snake->ClearToSend();
}

char		*Player::takeToSend(void)
{
	if (this->_tosend == "")
		return NULL;
	char *tmp = (char *)this->_tosend.c_str();
	return tmp;
}

void		Player::ClearToSend(void)
{
	this->_tosend = "";
}

int			Player::getCycles(void)
{
	return (this->_Snake->getCycles());
}
