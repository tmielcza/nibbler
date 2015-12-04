// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   UsualMode.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/03 17:28:46 by rduclos           #+#    #+#             //
//   Updated: 2015/12/04 21:32:02 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

# include "UsualMode.hpp"

UsualMode::UsualMode(void)
{
	std::cout << "Creating UsualMode !" << std::endl;
	this->_nbPlayers = 1;
	this->_width = 25;
	this->_height = 25;
	this->_speed = 1;
	this->_game = new GameManager();
	this->init();
}

UsualMode::UsualMode(const UsualMode & src)
{
	*this = src;
}

UsualMode::UsualMode(int nbplayers, int width, int height)
{
	std::cout << "Creating UsualMode !" << std::endl;
	this->_nbPlayers = nbplayers;
	this->_width = width;
	this->_height = height;
	this->_speed = 1;
	this->_game = new GameManager(nbplayers, width, height);
	this->init();
}

UsualMode::~UsualMode(void)
{
	delete this->_game;
	std::cout << "Destroying UsualMode !" << std::endl;
}

UsualMode	&	UsualMode::operator=(const UsualMode & src)
{
	this->_nbPlayers = src._nbPlayers;
	this->_width = src._width;
	this->_height = src._height;
	this->_speed = src._speed;
	return (*this);
}

void			UsualMode::init(void)
{
	int		height = MapManager::Instance().getHeight();
	int		width = MapManager::Instance().getWidth();

	GraphicsManager::setLib(sfml, this->_width, this->_height);
	for (int i = 0; i < height; i++)
		MapManager::Instance().setWall(width - 1, i);
	for (int i = 0; i < height; i++)
		MapManager::Instance().setWall(0, i);
	for (int i = 0; i < width; i++)
		MapManager::Instance().setWall(i, height - 1);
	for (int i = 0; i < width; i++)
		MapManager::Instance().setWall(i, 0);
}

bool			UsualMode::check_end(void)
{
	return (this->_game->IsAlive());
}

void			UsualMode::run(void)
{
	double				delta = 0;

	while (this->check_end())
	{
		delta = this->_game->deltaTime();
//		GraphicsManager::Instance().clear();
		this->_game->update_one(delta);
		MapManager::Instance().update(delta);
		GraphicsManager::Instance().display();
	}
}
