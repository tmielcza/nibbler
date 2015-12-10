// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/08 16:24:19 by rduclos           #+#    #+#             //
//   Updated: 2015/12/10 20:56:48 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "SoloMode.hpp"
#include "DuoMode.hpp"

int		main(void)
{
	DuoMode		game(false);

	game.run();
	return (0);
}
