// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/08 17:19:46 by rduclos           #+#    #+#             //
//   Updated: 2015/11/17 18:05:01 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "GameManager.hpp"

GameManager::GameManager(void)
{

}

GameManager::GameManager(int nbplayer, int width, int height, double speed) :_nbPlayer(nbplayer), _width(width), _height(height), _speed(speed)
{
		MapManager::Instance().init(nbplayer, width, height);
}

GameManager::GameManager(const GameManager & copy)
{
	*this = copy;
}

GameManager::~GameManager(void)
{
	
}

GameManager	&	GameManager::operator=(const GameManager & ass)
{
	this->_nbPlayer = ass._nbPlayer;
	this->_speed = ass._speed;
	this->_width = ass._width;
	this->_height = ass._height;
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

void		GameManager::init(int nbplayer, int width, int height, double speed)
{
	this->_nbPlayer = nbplayer;
	this->_width = width;
	this->_height = height;
	this->_speed = speed;
	MapManager::Instance().init(nbplayer, width, height);
}

void		GameManager::loop(e_preMode mode)
{
	(void)mode;
	(void)this->_mode;
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
