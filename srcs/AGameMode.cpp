// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AGameMode.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/11 21:34:58 by tmielcza          #+#    #+#             //
//   Updated: 2015/04/14 17:58:00 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "AGameMode.hpp"
#include "GraphicsManager.hpp"

AGameMode::AGameMode(int nplayers, int x, int y)
	: _x(x), _y(y), _nplayers(nplayers)
{
}

void	NormalMode::run(void)
{
	GraphicsManager::setLib(sfml, this->x, this->y);
}
