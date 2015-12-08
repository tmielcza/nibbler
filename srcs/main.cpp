// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/08 16:24:19 by rduclos           #+#    #+#             //
//   Updated: 2015/12/03 17:43:55 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "SoloMode.hpp"

int		main(void)
{
	SoloMode		game(false);

	srand(time(NULL));
	game.run();
	return (0);
}
