// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/08 17:19:46 by rduclos           #+#    #+#             //
//   Updated: 2015/12/04 17:32:26 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "GameManager.hpp"

GameManager::GameManager(void)
{
	std::cout << "Creating GameManager !" << std::endl;
	this->init(1, 25, 25);
}

GameManager::GameManager(int nbplayer, int width, int height)
{
	std::cout << "Creating GameManager !" << std::endl;
	this->init(nbplayer, width, height);
}

GameManager::GameManager(const GameManager & copy)
{
	*this = copy;
}

GameManager::~GameManager(void)
{
	delete this->_me;
	std::cout << "Destroying GameManager !" << std::endl;
}

GameManager	&	GameManager::operator=(const GameManager & ass)
{
	this->_nbPlayer = ass._nbPlayer;
	this->_width = ass._width;
	this->_height = ass._height;
	this->_players = ass._players;
	this->_master = ass._master;
	this->_me = ass._me;
	this->_players = ass._players;
	return (*this);
}

double			GameManager::deltaTime(void)
{
	static auto             last = Clock::now();
	auto                    time = Clock::now();
	float                   tmp;

	tmp = std::chrono::duration_cast<std::chrono::microseconds>(time - last).count() / 1000000.f;
	last = time;
	return (tmp);
}

void		GameManager::init(int nbplayer, int width, int height)
{
	this->_master = true;
	this->_nbPlayer = nbplayer;
	this->_width = width;
	this->_height = height;
	MapManager::Instance().init(nbplayer, width, height);
	this->_me = new Player();
}

bool		GameManager::IsAlive(void)
{
	return (this->_me->IsAlive());
}

void		GameManager::update_one(double time)
{
	this->_me->update(time);
	
}

void		GameManager::update(double time)
{
	this->_me->update(time);
	//update all list of snakes
}

/*
void		GameManager::loop(void)
{
	GraphicsManager::setLib(sfml, this->_width, this->_height);
	bool	run = true;
	double	time = 0;

	(void)mode;
//	this->_mode = mode;
	while (run)
	{
		double				delta = this->deltaTime();
		e_Input				input = (e_Input)0;
		std::list<e_Input>	inputs;
		double				refresh = 0;

//		auto it = inputs.begin();
		for (auto it = inputs.begin(); it != inputs.end(); it++)
		{
			if (*it != I_Dir)
				input = *it;
		}

		inputs = GraphicsManager::Instance().getInput();
		time += delta;
		refresh += delta;
		if (refresh >= 0.5)
		{
//			MapManager::Instance().
			refresh -= 0.5;
		}
	}
}

*/
