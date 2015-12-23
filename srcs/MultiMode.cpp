// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MultiMode.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/03 17:28:46 by rduclos           #+#    #+#             //
//   Updated: 2015/12/04 21:37:12 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

# include "MultiMode.hpp"

MultiMode::MultiMode(void)
{
	std::cout << "Creating MultiMode !" << std::endl;
	srand(time(NULL));
	this->_nbPlayers = 4;
	this->_width = 50;
	this->_height = 40;
	this->_speed = 1;
	this->_master = true;
	this->_pl2 = true;
}

MultiMode::MultiMode(bool pl2, int port)
{
	std::cout << "Creating MultiMode !" << std::endl;
	srand(time(NULL));
	this->_nbPlayers = 4;
	this->_width = 50;
	this->_height = 40;
	this->_speed = 1;
	this->_master = true;
	this->_pl2 = pl2;
	this->_port = port;
	this->_addr = NULL;
}

MultiMode::MultiMode(bool pl2, char *addr, int port)
{
	std::cout << "Creating MultiMode !" << std::endl;
	srand(time(NULL));
	this->_speed = 1;
	this->_master = false;
	this->_pl2 = pl2;
	this->_port = port;
	this->_addr = addr;
	this->_nbPlayers = 2;
}

MultiMode::MultiMode(const MultiMode & src)
{
	*this = src;
}

MultiMode::~MultiMode(void)
{
	delete this->_game;
	std::cout << "Destroying MultiMode !" << std::endl;
}

MultiMode	&	MultiMode::operator=(const MultiMode & src)
{
	this->_nbPlayers = src._nbPlayers;
	this->_width = src._width;
	this->_height = src._height;
	this->_speed = src._speed;
	this->_game = src._game;
	this->_master = src._master;
	this->_pl2 = src._pl2;
	this->_port = src._port;
	this->_addr = src._addr;
	return (*this);
}

void			MultiMode::init_clt(void)
{
	int		i = 0;
	this->_game = new GameManager(this->_pl2, true, false, this->_master);
	this->_game->init_tcp(this->_addr, this->_port);
	std::cout << "Wait until everybody is here : ";
	std::cout << this->_game->getCltPL() << "/" << this->_nbPlayers << std::endl;
	while ((this->_game->getCltPL()) < this->_nbPlayers)
	{
		if (this->_game->Client_init() == true && i == 0)
		{
			if (i == 0)
			{
				std::cout << "Init my Client." << std::endl;
				this->_game->init_from_clt();
				i = 1;
			}
			GraphicsManager::Instance().clear();
			GraphicsManager::Instance().display();
		}
		this->_game->Client_Check();
		std::cout << "Wait until everybody is here : ";
		std::cout << this->_game->getCurPL() << "/" << this->_nbPlayers << std::endl;
	}
	std::cout << "Wait until everybody is here : ";
	std::cout << this->_game->getCurPL() << "/" << this->_nbPlayers << std::endl;
	
}

void			MultiMode::init_serv(int nbPlayers, int width, int height, bool wall)
{

	MapManager::Instance().setWall(wall);
	this->_nbPlayers = nbPlayers;
	this->_width = width;
	this->_height = height;
	GraphicsManager::setLib(sfml, this->_width, this->_height);
	MapManager::Instance().init(this->_nbPlayers, this->_width, this->_height);
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
	this->_game = new GameManager(this->_pl2, true, false, this->_master);
	this->_game->init(this->_nbPlayers, this->_width, this->_height, wall);
	this->_game->init_tcp(this->_addr, this->_port);
	this->_game->setPlayertoServ();
	std::cout << "Wait until everybody is here : ";
	std::cout << this->_game->getCurPL() << "/" << this->_nbPlayers << std::endl;
	while ((this->_game->getCurPL() + this->_game->getServPL()) < this->_nbPlayers)
	{
		GraphicsManager::Instance().clear();
		GraphicsManager::Instance().display();
		this->_game->Server_Check(true);
		std::cout << "Wait until everybody is here : ";
		std::cout << this->_game->getCurPL() << "/" << this->_nbPlayers << std::endl;
	}
}

bool			MultiMode::check_end(void)
{
	//need to check the net too
	return (this->_game->IsAlive());
}

void			MultiMode::run(void)
{
	double					delta = 0;
	std::list<e_Input>		inputs;
	bool					leave = false;

	std::cout << "Enter in while" << std::endl;
	if (this->_master == true)
		for (int i = 0; i < this->_nbPlayers; i++)
		{
			MapManager::Instance().foodpop(true);
			this->_game->Bring_Serv_Clients();
		}
	else
		this->_game->Bring_Client_Serv();
	while (this->_game->leaving() == false && leave != true)
	{		
		GraphicsManager::Instance().clear();
		GraphicsManager::Instance().display();
		while (this->check_end())
		{
			delta = this->_game->deltaTime();
			if (this->_master == true)
				this->_game->Server_Check(false);
			else
				this->_game->Client_Check();
			this->_game->update(delta);
			MapManager::Instance().update(delta);
			GraphicsManager::Instance().display();
		}
		inputs = GraphicsManager::Instance().getInput();
		for (auto it = inputs.begin(); it != inputs.end(); it++)
		{
			if ((*it & I_Close) != 0)
				leave = true;
			if (this->_master == true && (*it & I_Restart) != 0)
			{
				this->_game->restart();
				for (int i = 0; i < this->_nbPlayers; i++)
					MapManager::Instance().foodpop(true);
			}
		}
	}
}
