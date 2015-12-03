// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   UsualMode.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/03 17:28:46 by rduclos           #+#    #+#             //
//   Updated: 2015/12/03 19:46:20 by rduclos          ###   ########.fr       //
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

	for (int i = 0; i < height; i++)
		MapManager::Instance().setWall(i, width - 1);
	for (int i = 0; i < height; i++)
		MapManager::Instance().setWall(i, 0);
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

	GraphicsManager::setLib(sfml, this->_width, this->_height);
//	double	time = 0;
	
	while (this->check_end())
	{
//		double				delta = this->deltaTime();
//		e_Input				input = I_Nope;
//		std::list<e_Input>	inputs;
//		double				refresh = 0;
		
//		inputs = GraphicsManager::Instance().getInput();
//		for (auto it = inputs.begin(); it != inputs.end(); it++)
//		{
//			if (*it & I_Dir != 0)
//				input = *it;
//		}
		
	}
}
