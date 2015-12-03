// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AGameMode.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/11 21:34:58 by tmielcza          #+#    #+#             //
//   Updated: 2015/11/17 17:52:13 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "AGameMode.hpp"
#include "GraphicsManager.hpp"

AGameMode::AGameMode(void)
{

}

AGameMode::AGameMode(const AGameMode & src)
{
	*this = src;
}

AGameMode::AGameMode(int nplayers, int width, int height)
  : _width(width), _height(height), _nbPlayers(nplayers)
{

}

AGameMode::~AGameMode(void)
{

}

AGameMode	&	AGameMode::operator=(const AGameMode & src)
{
	this->_width = src._width;
	this->_height = src._height;
	this->_nbPlayers = src._nbPlayers;
	return (*this);
}

/*
void	NormalMode::run(void)
{
	GraphicsManager::setLib(sfml, this->_x, this->_y);
}
*/
