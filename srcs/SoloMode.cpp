// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SoloMode.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/03 17:28:46 by rduclos           #+#    #+#             //
//   Updated: 2015/12/04 21:37:12 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

# include "SoloMode.hpp"

SoloMode::SoloMode(void)
{
	std::cout << "Creating SoloMode !" << std::endl;
	srand(time(NULL));
	this->_nbPlayers = 1;
	this->_width = 22;
	this->_height = 17;
	this->_speed = 1;
	MapManager::Instance().init(this->_nbPlayers, this->_width, this->_height);
	this->init(true);
	this->_game = new GameManager(false, false, false, true);
	this->_game->init(this->_nbPlayers, this->_width, this->_height, true);
}

SoloMode::SoloMode(bool wall)
{
	std::cout << "Creating SoloMode !" << std::endl;
	srand(time(NULL));
	this->_nbPlayers = 1;
	this->_width = 22;
	this->_height = 17;
	this->_speed = 1;
	MapManager::Instance().init(this->_nbPlayers, this->_width, this->_height);
	this->init(wall);
	this->_game = new GameManager(false, false, false, true);
	this->_game->init(this->_nbPlayers, this->_width, this->_height, wall);
}

SoloMode::SoloMode(const SoloMode & src)
{
	*this = src;
}

SoloMode::SoloMode(int nbplayers, int width, int height, bool wall)
{
	std::cout << "Creating SoloMode !" << std::endl;
	srand(time(NULL));
	this->_nbPlayers = nbplayers;
	this->_width = width;
	this->_height = height;
	this->_speed = 1;
	MapManager::Instance().init(this->_nbPlayers, this->_width, this->_height);
	this->init(wall);
	this->_game = new GameManager(false, false, false, true);
	this->_game->init(nbplayers, width, height, wall);
}

SoloMode::~SoloMode(void)
{
	delete this->_game;
	std::cout << "Destroying SoloMode !" << std::endl;
}

SoloMode	&	SoloMode::operator=(const SoloMode & src)
{
	this->_nbPlayers = src._nbPlayers;
	this->_width = src._width;
	this->_height = src._height;
	this->_speed = src._speed;
	this->_game = src._game;
	return (*this);
}

void			SoloMode::init(bool wall)
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

bool			SoloMode::check_end(void)
{
	return (this->_game->IsAlive());
}

void			SoloMode::run(void)
{
	double					delta = 0;
	std::list<e_Input>		inputs;
	bool					leave = false;

	std::cout << "Enter in while" << std::endl;
	MapManager::Instance().foodpop(true);
	while (this->_game->leaving() == false && leave != true)
	{
		GraphicsManager::Instance().clear();
		GraphicsManager::Instance().display();
		while (this->check_end())
		{
			delta = this->_game->deltaTime();
			this->_game->update(delta);
			MapManager::Instance().update(delta);
			GraphicsManager::Instance().display();
		}
		inputs = GraphicsManager::Instance().getInput();
		for (auto it = inputs.begin(); it != inputs.end(); it++)
		{
			if ((*it & I_Close) != 0)
				leave = true;
			if ((*it & I_Restart) != 0)
			{
				std::cout << "Restart the Game !" << std::endl;
				this->_game->restart();
				MapManager::Instance().foodpop(true);
			}
		}
	}
}
