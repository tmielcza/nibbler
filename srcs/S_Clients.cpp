// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   S_Clients.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/25 18:11:43 by rduclos           #+#    #+#             //
//   Updated: 2016/01/25 18:11:44 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "S_Client.hpp"
#include "Client.hpp"

S_Client::S_Client(int me)
{
	sock = me;
	bzero(tmp_read, BC_SIZE + 1);
	bzero(tmp_write, BC_SIZE + 1);
	this->_alive = true;
}

S_Client::~S_Client()
{
	bzero(tmp_read, BC_SIZE + 1);
	bzero(tmp_write, BC_SIZE + 1);
}

void	S_Client::setAlive(bool alive)
{
	this->_alive = alive;
}

bool	S_Client::getAlive(void)
{
	return (this->_alive);
}

int		S_Client::is_write(void)
{
	if (this->b_write.bc_iscmd() == 1)
		return (1);
	return (0);
}

void	S_Client::c_send(void)
{
	int		i;

	b_write.bc_read(tmp_write);
	i = strlen(tmp_write);
	if (this->_pl1 != NULL)
		std::cout << "MSG " << this->_pl1->getCycles() << " Sending : " << this->tmp_write;
	send(sock, tmp_write, i, 0);
	bzero(tmp_write, i + 1);
}

char	**S_Client::c_receive(void)
{
	int			r;
	char		*tmp;

	r = recv(sock, tmp_read, BC_SIZE, 0);
	if (r <= 0)
	{
		type = FREE_FD;
		std::cout << "S_Client : " << this->sock << " disconnected." << std::endl;
		name = "";
		close(sock);
	}
	else
	{
		this->tmp_read[r] = '\0';
		b_read.bc_write(tmp_read, 0);
		bzero(tmp_read, BC_SIZE + 1);
		if (b_read.bc_iscmd() == 1)
		{
			b_read.bc_read(this->tmp_read);
			tmp = strdup(this->tmp_read);
//			std::cout << "Receiving from " << this->sock << " : " << tmp_read;
			char **tab = ft_strtab(this->tmp_read);
			return (tab);
		}
	}
	return (NULL);
}

void		S_Client::clear_tmp_read(void)
{
	bzero(tmp_read, BC_SIZE + 1);
}

void		S_Client::set_name(std::string me)
{
	name = me;
}

std::string	S_Client::get_name(void)
{
	return (name);
}

int			S_Client::is_named(void)
{
	if (name == "")
		return (0);
	return (1);
}

void		S_Client::set_type(int me)
{
	type = me;
}

int			S_Client::get_type(void)
{
	return (type);
}

void		S_Client::set_write(char *tmp)
{
	b_write.bc_write(tmp, 1);
}

char		*S_Client::get_read(void)
{
	b_read.bc_read(tmp_read);
	return (tmp_read);
}

Player		*S_Client::getPlayer1(void)
{
	return (this->_pl1);
}

Player		*S_Client::getPlayer2(void)
{
	return (this->_pl2);
}


std::string	S_Client::setPlayer1(bool create)
{
	if (create == true)
		this->_pl1 = new Player(false, true, false);
	int x = this->_pl1->getX();
	int y = this->_pl1->getY();
	e_Cardinal direc = this->_pl1->getDirec();
	int index = this->_pl1->getIndex();
	std::string tmp = "C_S" + std::to_string(index) + "_" + std::to_string(direc) + "_";
	tmp += std::to_string(x) + "-" + std::to_string(y);
	return (tmp);
}

std::string	S_Client::setPlayer2(bool create)
{
	if (create == true)
		this->_pl2 = new Player(false, true, false);
	int x = this->_pl2->getX();
	int y = this->_pl2->getY();
	e_Cardinal direc = this->_pl2->getDirec();
	int index = this->_pl2->getIndex();
	std::string tmp = "C_S" + std::to_string(index) + "_" + std::to_string(direc) + "_";
	tmp += std::to_string(x) + "-" + std::to_string(y);
	return (tmp);
}

bool		S_Client::getPL2(void)
{
	if (this->_pl2 != NULL)
		return (true);
	return (false);
}

bool		S_Client::P1IsAlive(void)
{
	return (this->_pl1->IsAlive());
}

bool		S_Client::P2IsAlive(void)
{
	return (this->_pl2->IsAlive());
}

void		S_Client::EndingP1(void)
{
	if (this->_pl1 != NULL)
	{
		delete this->_pl1;
		this->_pl1 = NULL;
	}
}

void		S_Client::EndingP2(void)
{
	if (this->_pl2 != NULL)
	{
		delete this->_pl2;
		this->_pl2 = NULL;
	}
}
