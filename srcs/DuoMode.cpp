// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   DuoMode.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/03 17:28:46 by rduclos           #+#    #+#             //
//   Updated: 2015/12/04 21:37:12 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

# include "DuoMode.hpp"

DuoMode::DuoMode(void)
{
	std::cout << "Creating DuoMode !" << std::endl;
	srand(time(NULL));
	this->_nbPlayers = 1;
	this->_width = 22;
	this->_height = 17;
	this->_speed = 1;
	this->_game = new GameManager(this->_nbPlayers, this->_width, this->_height);
	this->_game->init_second();
	this->init(true);
}

DuoMode::DuoMode(bool wall)
{
	std::cout << "Creating DuoMode !" << std::endl;
	srand(time(NULL));
	this->_nbPlayers = 1;
	this->_width = 22;
	this->_height = 17;
	this->_speed = 1;
	this->_game = new GameManager(this->_nbPlayers, this->_width, this->_height);
	this->_game->init_second();
	this->init(wall);
}

DuoMode::DuoMode(const DuoMode & src)
{
	*this = src;
}

DuoMode::DuoMode(int nbplayers, int width, int height, bool wall)
{
	std::cout << "Creating DuoMode !" << std::endl;
	this->_nbPlayers = nbplayers;
	this->_width = width;
	this->_height = height;
	this->_speed = 1;
	this->_game = new GameManager(nbplayers, width, height);
	this->init(wall);
}

DuoMode::~DuoMode(void)
{
	delete this->_game;
	std::cout << "Destroying DuoMode !" << std::endl;
}

DuoMode	&	DuoMode::operator=(const DuoMode & src)
{
	this->_nbPlayers = src._nbPlayers;
	this->_width = src._width;
	this->_height = src._height;
	this->_speed = src._speed;
	return (*this);
}

void			DuoMode::init(bool wall)
{
	int		height = MapManager::Instance().getHeight();
	int		width = MapManager::Instance().getWidth();
	
	GraphicsManager::setLib(sfml, this->_width, this->_height);
	if (wall == true)
	{
		for (int i = 0; i < height; i++)
			MapManager::Instance().setWall(width - 1, i);
		for (int i = 0; i < height; i++)
			MapManager::Instance().setWall(0, i);
		for (int i = 0; i < width; i++)
			MapManager::Instance().setWall(i, height - 1);
		for (int i = 0; i < width; i++)
			MapManager::Instance().setWall(i, 0);
	}
}

bool			DuoMode::check_end(void)
{
	return (this->_game->IsAlive());
}

void			DuoMode::run(void)
{
	double				delta = 0;

	std::cout << "Enter in while" << std::endl;
	MapManager::Instance().foodpop(true);
	while (this->check_end())
	{
//		GraphicsManager::Instance().clear();
		delta = this->_game->deltaTime();
		this->_game->update(delta);
		MapManager::Instance().update(delta);
		GraphicsManager::Instance().display();
	}
}
