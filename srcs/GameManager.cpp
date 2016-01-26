// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/08 17:19:46 by rduclos           #+#    #+#             //
//   Updated: 2016/01/25 20:00:19 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "GameManager.hpp"
#include "AEntity.hpp"
#include "Player.hpp"

GameManager::GameManager(void)
{
	std::cout << "Creating GameManager !" << std::endl;
	this->_master = true;
	this->_multi = false;
	this->_massif = false;
	this->_leave = false;
	this->_pl2 = false;
	this->_start = false;
	this->_curPL = 1;
}

GameManager::GameManager(bool pl2, bool multi, bool massif, bool master)
{
	std::cout << "Creating GameManager !" << std::endl;
	this->_multi = multi;
	this->_massif = massif;
	this->_master = master;
	this->_leave = false;
	this->_start = false;
	this->_curPL = 1;
	this->_pl2 = pl2;
}

GameManager::GameManager(const GameManager & copy)
{
	*this = copy;
}

GameManager::~GameManager(void)
{
	if (this->_players != NULL && this->_players->size() > 0)
	{
		std::list<Player *>::iterator		pl = this->_players->begin();
		std::list<Player *>::iterator		end = this->_players->end();
		
		while (pl != end)
		{
			Player *del;
			del = (*pl);
			this->_players->erase(pl);
			pl = this->_players->begin();
			delete del;
		}
		if (this->_me != NULL)
			delete this->_me;
		if (this->_me2 != NULL)
			delete this->_me2;
	}
	std::cout << "Destroying GameManager !" << std::endl;
}
GameManager	&	GameManager::operator=(const GameManager & ass)
{
	this->_nbPlayer = ass._nbPlayer;
	this->_width = ass._width;
	this->_height = ass._height;
	this->_players = ass._players;
	this->_multi = ass._multi;
	this->_me = ass._me;
	this->_me2 = ass._me2;
	return (*this);
}

double			GameManager::deltaTime(void)
{
	static auto             last = Clock::now();
	auto                    time = Clock::now();
	float                   tmp;

	tmp = std::chrono::duration_cast<std::chrono::microseconds>(time - last).count() / 1000000.f;
	last = time;
	return (tmp);
}

void		GameManager::init(int nbplayer, int width, int height, bool wall)
{
	this->_nbPlayer = nbplayer;
	this->_width = width;
	this->_height = height;
	this->_wall = wall;
	if (this->_master == true)
		this->_me = new Player(false, this->_master, true);
	else
		this->_me = NULL;
	if (this->_master == true && this->_pl2 == true)
	{
		this->_curPL++;
		this->_me2 = new Player(true, this->_master, true);
	}
	else
		this->_me2 = NULL;
}

void		GameManager::init_tcp(char *addr, int port)
{
	if (this->_multi == true && this->_master == false && this->_massif == false)
	{
		//Version Client
		this->_client = new Client(this->_pl2);
		this->_client->init(addr, port);
	}
	else if (this->_multi == true && this->_master == true && this->_massif == true)
	{
		//Version Client Massif
		;
	}
	else if (this->_multi == true && this->_master == true && this->_massif == false)
	{
		//Version Server
		int i = this->_nbPlayer;
		int j = this->_curPL;
		this->_serv = new Server(port, this->_wall, this->_width, this->_height, i, j);
		this->_serv->init_clt(this->_clients);
	}
	else if (this->_multi == true && this->_master == true && this->_massif == true)
	{
		//Version Server Massif
		;
	}
	
}

bool		GameManager::IsAlive(void)
{
	bool	test = false;

	if (this->_me != NULL)
	{
		if (this->_me->IsAlive() == true)
			test = true;
		else
		{
			std::cout << "Player1 " << std ::endl;
			delete this->_me;
			this->_me = NULL;
		}
	}
	if (this->_me2 != NULL)
	{
		if (this->_me2->IsAlive() == true)
			test = true;
		else
		{
			std::cout << "Player2 " << std::endl;
			delete this->_me2;
			this->_me2 = NULL;
		}
	}
	if (this->_multi == true && this->_master == true)
	{
		int i = 0;
		while (i < this->_serv->getMaxFD())
		{
			if (this->_clients[i]->get_type() == CLT_FD)
			{
				Player *tmp1;
				Player *tmp2;
				if ((tmp1 = this->_clients[i]->getPlayer1()) != NULL)
				{
					if (this->_clients[i]->P1IsAlive() == true)
						test = true;
					else
					{
						this->_clients[i]->EndingP1();
						if (this->_clients[i]->getPlayer2() == NULL)
							this->_clients[i]->setAlive(false);
					}
				}
				if ((tmp2 = this->_clients[i]->getPlayer2()) != NULL)
				{
					if (this->_clients[i]->P2IsAlive() == true)
						test = true;
					else
					{
						this->_clients[i]->EndingP2();
						if (this->_clients[i]->getPlayer1() == NULL)
							this->_clients[i]->setAlive(false);
					}
				}
			}
			i++;
		}
	}
	else if (this->_multi == true)
	{
		std::list<Player *>::iterator		pl = this->_players->begin();
		std::list<Player *>::iterator		end = this->_players->end();

		while (pl != end)
		{
			if ((*pl)->IsAlive() == true)
				test = true;
			else
			{
				Player *del;
				del = (*pl);
				this->_players->erase(pl);
				delete del;
				pl = this->_players->begin();

			}
			pl++;
		}
	}
	if (this->_leave == true)
		test = false;
	return (test);
}



void		GameManager::update(double time)
{
	e_Input								input = I_Nope;
	std::list<e_Input>					inputs;
	bool								player1;
	int									cycle1 = 0;

	inputs = GraphicsManager::Instance().getInput();
	GraphicsManager::Instance().clear();
	for (auto it = inputs.begin(); it != inputs.end(); it++)
	{
		if ((*it & I_Close) != 0)
			this->_leave = true;
		if ((*it & I_Restart) != 0)
		{
			if (this->_master == true)
			{
				this->restart();
				for (int i = 0; i < this->_nbPlayer; i++)
					MapManager::Instance().foodpop(true);
			}
		}
		if ((*it & I_Dir) != 0)
		{
			input = (e_Input)(*it & I_Dir);
			player1 = (*it & I_Player1);
			if (this->_me != NULL && player1)
			{
				if (this->_me->getSizeTouch() < 3)
				{
//					if (this->_me->verify_lL((e_Cardinal)input) == 1)
//					{
						std::string tmp = "S";
						tmp += std::to_string(this->_me->getIndex());
//					tmp += "_";
//					tmp += std::to_string(this->_me->getCycles());
						tmp += "_";
						tmp += std::to_string(this->_me->getX());
						tmp += "_";
						tmp += std::to_string(this->_me->getY());
						tmp += "_";
						tmp += std::to_string((int)input);
						if (this->_multi == true && this->_master == true)
							this->_serv->send_msg_to_all(this->_clients, 0, tmp.c_str());	
						else if (this->_multi == true)
							this->_client->set_write((char *)tmp.c_str());
						this->_me->add_touch((e_Cardinal)input);
//					}
				}
			}
			else if (this->_me2 != NULL && !player1)
			{
				if (this->_me2->getSizeTouch() < 3)
				{
					this->_me2->add_touch((e_Cardinal)input);
					std::string tmp = "S";
					tmp += std::to_string(this->_me2->getIndex());
//					tmp += "_";
//					tmp += std::to_string(this->_me2->getCycles());
					tmp += "_";
					tmp += std::to_string(this->_me2->getX());
					tmp += "_";
					tmp += std::to_string(this->_me2->getY());
					tmp += "_";
					tmp += std::to_string((int)input);
					if (this->_multi == true && this->_master == true)
						this->_serv->send_msg_to_all(this->_clients, 0, tmp.c_str());
					else if (this->_multi == true)
						this->_client->set_write((char *)tmp.c_str());
				}
			}
		}
	}
	if (this->_me != NULL)
	{
		this->_me->update(time);
		if (this->_start == false)
			cycle1 = this->_me->getCycles();
		char *tmp = this->_me->takeToSend();
		if (tmp != NULL)
		{
			if (this->_multi == true && this->_master == true)
				this->_serv->send_msg_to_all(this->_clients, 0, tmp);
			else if (this->_multi == true)
				this->_client->set_write(tmp);
			this->_me->ClearToSend();
		}
		char *tmp1 = this->_me->SnaketakeToSend();
		if (tmp1 != NULL)
		{
			if (this->_multi == true && this->_master == true)
				this->_serv->send_msg_to_all(this->_clients, 0, tmp1);
			else if (this->_multi == true)
				this->_client->set_write(tmp1);
			this->_me->SnakeClearToSend();
		}
	}
	if (this->_me2 != NULL)
	{
		this->_me2->update(time);
		char *tmp = this->_me2->takeToSend();
		if (tmp != NULL)
		{
			if (this->_multi == true && this->_master == true)
				this->_serv->send_msg_to_all(this->_clients, 0, tmp);
			else if (this->_multi == true)
				this->_client->set_write(tmp);
			this->_me->ClearToSend();
		}
		char *tmp1 = this->_me2->SnaketakeToSend();
		if (tmp1 != NULL)
		{
			if (this->_multi == true && this->_master == true)
				this->_serv->send_msg_to_all(this->_clients, 0, tmp1);
			else if (this->_multi == true)
				this->_client->set_write(tmp1);
			this->_me2->SnakeClearToSend();
		}
	}
	if (this->_multi == true)
	{
		if (this->_master == true)
		{
			this->Server_Check(false);
			char *tmp = MapManager::Instance().takeToSend();
			if (tmp != NULL)
			{
				this->_serv->send_msg_to_all(this->_clients, -1, tmp);
				MapManager::Instance().ClearToSend();
			}
			for (int i = 0; i < this->_serv->getMaxFD(); i++)
			{
				if (this->_clients[i]->get_type() == CLT_FD)
				{
					Player *tmp1;
					Player *tmp2;
					if ((tmp1 = this->_clients[i]->getPlayer1()) != NULL)
					{
						tmp1->update(time);
						if (this->_start == false)
						{
							this->_start = true;
//							tmp1->setCycles(-1);
						}
					}
					if ((tmp2 = this->_clients[i]->getPlayer2()) != NULL)
					{
						tmp2->update(time);
						if (this->_start == false)
						{
							this->_start = true;
//							tmp2->setCycles(0);
						}
					}
				}
			}
		}
		else
		{
			std::list<Player *>::iterator		pl = this->_players->begin();
			std::list<Player *>::iterator		end = this->_players->end();

			while (pl != end)
			{
				(*pl)->update(time);
				pl++;
			}
		}
	}
}

bool			GameManager::leaving(void)
{
	return (this->_leave);
}

void			GameManager::restart(void)
{
	if (this->_multi == false)
	{
		if (this->_me != NULL)
			delete this->_me;
		if (this->_pl2 == true && this->_me2 != NULL)
			delete this->_me2;
		MapManager::Instance().restart();
		this->_me = new Player();
		if (this->_pl2 == true)
			this->_me2 = new Player(true, true, true);
	}
}

int				GameManager::getCurPL(void)
{
	return (this->_curPL);
}

void			GameManager::Server_Check(bool co)
{
	this->_serv->run_serv(co);
}

void			GameManager::setPlayertoServ(void)
{
	this->_serv->setPlayers(this->_me, this->_me2);
}

void			GameManager::Client_Check(void)
{
	this->_client->run_clt();
}

int				GameManager::getCltPL(void)
{
	return (this->_client->getNBPlayers());
}

int				GameManager::getMaxPlayer(void)
{
	return (this->_nbPlayer);
}

int				GameManager::getServPL(void)
{
	return (this->_serv->getNbPlayers());
}

bool			GameManager::Client_init(void)
{
	return (this->_client->getInit());
}

void			GameManager::init_from_clt(void)
{
	bool	wall = this->_client->getWall();
	int		width = this->_client->getWidth();
	int		height = this->_client->getHeight();
	int		maxPlayer = this->_client->getMaxPlayer();

	MapManager::Instance().setWall(wall);
	this->_nbPlayer = maxPlayer;
	this->_width = width;
	this->_height = height;
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
	this->init(this->_nbPlayer, this->_width, this->_height, wall);
	this->_me = this->_client->getPlayer1();
	this->_me2 = this->_client->getPlayer2();
}

void				GameManager::Bring_Serv_Clients(void)
{
	this->_clients = this->_serv->getClients();
}

void				GameManager::Bring_Client_Serv(void)
{
	this->_me = this->_client->getPlayer1();
	this->_me2 = this->_client->getPlayer2();
	this->_players = this->_client->getClients();
}
