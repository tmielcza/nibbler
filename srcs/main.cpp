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
#include "MultiMode.hpp"

typedef struct		s_env
{
	int		height;
	int		width;
	bool	wall;
	bool	pl2;
	bool	solo;
	bool	master;
	int		nbPlayers;
	int		port;
	char	*addr;
}					t_env;

void	check_args(int ac, char **av, t_env *env)
{
	int i = 1;
	while (i < ac)
	{
		if (strcmp(av[i], "-nowall") == 0)
			env->wall = false;
		else if (strcmp(av[i], "-duo") == 0)
		{
			env->pl2 = true;
			if (env->nbPlayers == 1)
				env->nbPlayers = 2;
		}
		else if (strcmp(av[i], "-player") == 0)
		{
			i++;
			if (av[i] != NULL)
			{
				env->nbPlayers = atoi(av[i]);
				if (env->nbPlayers < 0)
				{
					std::cout << "Error: Number of players can't be negatif !" << std::endl;
					exit(-42);
				}
			}
			else
			{
				std::cout << "Player number is missing." << std::endl;
				exit(-42);
			}
		}
		else if (strcmp(av[i], "-height") == 0)
			i++;
		else if (strcmp(av[i], "-width") == 0)
			i++;
		else if (strcmp(av[i], "-host") == 0)
		{
			i++;
			if (av[i] != NULL)
			{
				env->master = false;
				env->solo = false;
				env->addr = av[i];
			}
			else
			{
				std::cout << "Address Host is missing." << std::endl;
				exit(-42);
			}
		}
		else if (strcmp(av[i], "-port") == 0)
		{
			i++;
			if (av[i] != NULL)
			{
				env->solo = false;
				env->port = atoi(av[i]);
				if (env->port < 1024 || env->port >= 49151)
				{
					std::cout << "Error : port ins't valide." << std::endl;
					exit(-42);
				}
				std::cout << "Port : " << env->port << std::endl;
			}
			else
			{
				std::cout << "Port is missing." << std::endl;
				exit(-42);
			}
		}
		else
		{
			std::cout << "Bad arguments : " << std::endl;
			std::cout << "-nowall : to play without walls." << std::endl;
			std::cout << "-duo : to play two players on this computer." << std::endl;
			std::cout << "-height : to fix the height manually." << std::endl;
			std::cout << "-width : to fix the width manually." << std::endl;
			std::cout << "-player : to fix th number max of players." << std::endl;
			std::cout << "-host : followed by an address IP of the hosting game." << std::endl;
			std::cout << "-port : to fix the port if you playing network" << std::endl;
			exit(-42);
		}
		i++;
	}
	i = 1;
	while (i < ac)
	{
		if (strcmp(av[i], "-height") == 0)
		{
			i++;
			if (av[i] != NULL)
			{
				env->height = atoi(av[i]);
				if (env->height > ((env->nbPlayers * 2) + 4) || env->height < 16)
				{
					std::cout << "Error: Map height isn't enought !" << std::endl;
					exit(-42);
				}
			}
			else
			{
				std::cout << "Height is missing." << std::endl;
				exit(-42);
			}
		}
		else if (strcmp(av[i], "-width") == 0)
		{
			i++;
			if (av[i] != NULL)
			{
				env->width = atoi(av[i]);
				if ((env->width / env->nbPlayers) < 10 || env->width < 16)
				{
					std::cout << "Error: Map width isn't enought !" << std::endl;
					exit(-42);
				}
			}
			else
			{
				std::cout << "Width is missing." << std::endl;
				exit(-42);
			}
		}
		else if (strcmp(av[i], "-nowall") == 0)
			;
		else if (strcmp(av[i], "-duo") == 0)
			;
		else if (strcmp(av[i], "-player") == 0)
			i++;
		else if (strcmp(av[i], "-host") == 0)
			i++;
		else if (strcmp(av[i], "-port") == 0)
			i++;
		else
		{
			std::cout << "Bad arguments : " << std::endl;
			std::cout << "-nowall : to play without walls." << std::endl;
			std::cout << "-duo : to play two players on this computer." << std::endl;
			std::cout << "-height : to fix the height manually." << std::endl;
			std::cout << "-width : to fix the width manually." << std::endl;
			std::cout << "-player : to fix th number max of players." << std::endl;
			std::cout << "-host : followed by an address IP of the hosting game." << std::endl;
			std::cout << "-port : to fix the port if you playing network" << std::endl;
			exit(-42);
		}
		i++;
	}
}

int		main(int ac, char **av)
{
	t_env	env;

	env.height = 22;
	env.width = 22;
	env.wall = true;
	env.pl2 = false;
	env.solo = true;
	env.master = true;
	env.nbPlayers = 1;
	env.port = 0;

	if (ac < 2)
	{
		SoloMode		game(env.wall);
		game.run();
	}
	else
	{
		check_args(ac, av, &env);
		if (env.solo == true && env.pl2 == false)
		{
			SoloMode		game(env.nbPlayers, env.width, env.height, env.wall);
			game.run();
		}
		else if (env.solo == true && env.pl2 == true)
		{
			DuoMode			game(env.nbPlayers, env.width, env.height, env.wall);
			game.run();
		}
		else if (env.solo == false &&
				 (((env.pl2 == false && env.nbPlayers > 1) || env.nbPlayers > 2) ||
				 env.master == false))
		{
			if (env.master == true)
			{
				MultiMode		game(env.pl2, env.port);

				std::cout << "Starting MultiMode" << std::endl;

				game.init_serv(env.nbPlayers, env.width, env.height, env.wall);
				game.run();
			}
			else
			{
				MultiMode		game(env.pl2, env.addr, env.port);

				game.init_clt();
				game.run();
			}
		}
		else
		{
			std::cout << "Veuillez entrer un nombre max de Player pour le server." << std::endl;
		}
	}
	return (0);
}
