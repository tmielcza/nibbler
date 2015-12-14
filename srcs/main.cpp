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

int		main(int ac, char **av)
{
	int		height = 22;
	int		width = 22;
	bool	wall = true;
	bool	pl2 = false;
	bool	solo = true;
	int		nbPlayers = 1;

	if (ac < 2)
	{
		SoloMode		game(true);
		game.run();
	}
	else
	{
		int i = 1;
		while (i < ac)
		{
			if (strcmp(av[i], "-wall") == 0)
				wall = false;
			else if (strcmp(av[i], "-d") == 0)
			{
				pl2 = true;
				if (nbPlayers == 1)
					nbPlayers = 2;
			}
			else if (strcmp(av[i], "-pl") == 0)
			{
				i++;
				nbPlayers = atoi(av[i]);
				if (nbPlayers < 0)
				{
					std::cout << "Error: Number of players can't be negatif !" << std::endl;
					exit(42);
				}
			}
			else if (strcmp(av[i], "-r") == 0)
				solo = false;
			else if (strcmp(av[i], "-h") == 0)
			{
				i++;
				height = atoi(av[i]);
				if ((height / nbPlayers) < 3 || height < 16)
				{
					std::cout << "Error: Map height isn't enought !" << std::endl;
					exit(42);
				}
			}
			else if (strcmp(av[i], "-w") == 0)
			{
				i++;
				width = atoi(av[i]);
				if ((width / nbPlayers) < 10 || width < 16)
				{
					std::cout << "Error: Map width isn't enought !" << std::endl;
					exit(42);
				}
			}
			else if (strcmp(av[i], "-h") == 0)
			{
				i++;
			}
			else if (strcmp(av[i], "-p") == 0)
			{
				i++;
			}
			i++;
		}
		if (solo == true && pl2 == false)
		{
			SoloMode		game(nbPlayers, width, height, wall);
			game.run();
		}
		else if (solo == true && pl2 == true)
		{
			DuoMode			game(nbPlayers, width, height, wall);
			game.run();
		}
/*		else
		{
			if (nbPlayers <= 10)
			{
				MultiMode		game(nbPlayers, width, height, pl2, wall);
				game.run();
			}
			else
			{
				MassMultiMode	game(nbPlayers, width, height, pl2, wall);
				game.run();
			}
		}*/
	}
	return (0);
}
