// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/08 17:19:46 by rduclos           #+#    #+#             //
//   Updated: 2015/12/02 16:57:25 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "GameManager.hpp"

GameManager::GameManager(void)
{
	this->init(1, 100, 100, Solo);
}

GameManager::GameManager(int nbplayer, int width, int height, e_preMode premode)
{
	this->init(nbplayer, width, height, premode);
}

GameManager::GameManager(const GameManager & copy)
{
	*this = copy;
}

GameManager::~GameManager(void)
{
//	delete this->_mode;
}

GameManager	&	GameManager::operator=(const GameManager & ass)
{
	this->_nbPlayer = ass._nbPlayer;
	this->_premode = ass._premode;
	this->_width = ass._width;
	this->_height = ass._height;
	this->_mode = ass._mode;
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

void		GameManager::init(int nbplayer, int width, int height, e_preMode premode)
{
	this->_master = true;
	this->_nbPlayer = nbplayer;
	this->_width = width;
	this->_height = height;
	this->_premode = premode;
	this->_mode = new UsualMode(nbplayer, width, height);
	this->_mode->init();
	MapManager::Instance().init(nbplayer, width, height);
	this->_me = new Player();
}

void		GameManager::loop(void)
{
	this->_mode->run();
}

/*
void		GameManager::loop(e_preMode mode)
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
