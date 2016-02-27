// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Client.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/25 18:10:18 by rduclos           #+#    #+#             //
//   Updated: 2016/01/25 19:39:59 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Client.hpp"
#include "MapManager.hpp"
#include "GraphicsManager.hpp"

Client::Client(void)
{
	bzero(this->tmp_read, BC_SIZE + 1);
	bzero(this->tmp_read, BC_SIZE + 1);
	FD_ZERO(&this->fd_read);
	FD_ZERO(&this->fd_write);
	this->r = 1;
	this->_pl2 = false;
	this->_init = false;
	this->_null1 = false;
	this->_null2 = false;
}

Client::Client(bool pl2)
{
	bzero(this->tmp_read, BC_SIZE + 1);
	bzero(this->tmp_read, BC_SIZE + 1);
	FD_ZERO(&this->fd_read);
	FD_ZERO(&this->fd_write);
	this->r = 1;
	this->_pl2 = pl2;
	this->_init = false;
	this->_null1 = false;
	this->_null2 = false;
	this->_nbPlayer = 0;
}

Client::~Client(void)
{

}

void		Client::init(char *adr, int port)
{
	struct protoent		*prt;
	struct sockaddr_in	clt;

	clt.sin_family = AF_INET;
	clt.sin_port = htons(port);
	clt.sin_addr.s_addr = inet_addr(adr);
	prt = getprotobyname("TCP");
	if (prt == 0)
	{
		std::cout << "Connect failed, wrong Port." << std::endl;
		exit(-42);
	}
	if ((this->sock = socket(PF_INET, SOCK_STREAM, prt->p_proto)) == -1)
	{
		std::cout << "soket failed, wrong Addresse." << std::endl;
		exit(-42);
	}
	if (connect(this->sock, (const struct sockaddr *)&clt, sizeof(clt)) == -1)
	{
		std::cout << "Connect failed, wrong Port." << std::endl;
		exit(-42);
	}
}

void		Client::check_actions(void)
{
	while (this->r != 0)
	{
		if (FD_ISSET(this->sock, &this->fd_read))
		{
			this->r--;
			this->receive_data();
		}
		else if (FD_ISSET(this->sock, &this->fd_write))
		{
			this->r--;
			this->send_data();
		}
	}
}

void		Client::do_select(void)
{
	fd_set				*read;
	fd_set				*write;
	struct timeval		waitd;

	waitd.tv_sec = 0;
	waitd.tv_usec = 1;
	read = &(this->fd_read);
	write = &(this->fd_write);
	FD_SET(this->sock, read);
	int i;
	if ((i = this->b_write.bc_iscmd()) == 1)
		FD_SET(this->sock, write);
	this->r = select(this->sock + 2, read, write, NULL, &waitd);
}

void		Client::run_clt(void)
{
	FD_ZERO(&this->fd_read);
	FD_ZERO(&this->fd_write);
	do_select();
	check_actions();
}

void		Client::send_data()
{
	int		i;

	this->b_write.bc_read(this->tmp_write);
	i = strlen(tmp_write);
//	std::cout << "Sending : " << this->tmp_write;
	send(sock, this->tmp_write, i, 0);
	bzero(&this->tmp_write, i);
}

void		Client::Snake_direc(char *tmp)
{
	int		index = atoi(tmp + 1);
	int		direc;
	int		i;

	i = 1;
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	direc = atoi(tmp + i);
	if (direc != 0)
	{
		std::list<Player*>::iterator	snake = this->_players.begin();
		std::list<Player*>::iterator	end = this->_players.end();

		while (snake != end)
		{
			if ((*snake)->getIndex() == index)
			{
				if ((*snake)->getSizeTouch() < 3)
					(*snake)->add_touch((e_Cardinal)direc);
			}
			snake++;
		}
	}
}

void		Client::popFood(char *tmp)
{
	int		i = 2;
	int		spawner = atoi(tmp + 1);
	while (tmp[i] != '\0' && (tmp[i] < '0' || tmp[i] > '9'))
		i++;
	int x = atoi(tmp + i);
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	int y = atoi(tmp + i);
	if (spawner == 1)
		MapManager::Instance().foodpop(true, x, y);
	else if (spawner == 0)
		MapManager::Instance().foodpop(false, x, y);
}

void		Client::popBonus(char *tmp)
{
	int		i = 0;
	int		b;
	int		r2 = 10;
	int		r3 = 0;

	if (tmp[1] == 'S')
		b = 0;
	else if (tmp[1] == 'C')
		b = 1;
	else if (tmp[1] == 'F')
		b = 2;
	else if (tmp[1] == 'H')
		b = 3;
	else if (tmp[1] == 'M')
		b = 4;
	while (tmp[i] != '\0' && (tmp[i] < '0' || tmp[i] > '9'))
		   i++;
	int x = atoi(tmp + i);
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	while (tmp[i] != '\0' && (tmp[i] < '0' || tmp[i] > '9'))
		i++;
	int y = atoi(tmp + i);
//	std::cout << "popBonus at : " << x << "-" << y << std::endl;
	if (b == 3 || b == 4)
	{
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		i++;
		r2 = atoi(tmp + i);
		if (b == 3)
		{
			while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
				i++;
						i++;
			r3 = atoi(tmp + i);
			
		}
		else
			;
	}
	MapManager::Instance().bonuspop(b, x, y, r2, r3);
}

void		Client::init_Game(char *tmp)
{
	int			i = 3;
	int			wall;
	
	wall = atoi(tmp + i);
	this->_wall = (bool)wall;
	if (this->_wall == true)
		std::cout << "True : " << wall;
	else
		std::cout << "False : " << wall;
	std::cout << std::endl;
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	this->_width = atoi(tmp + i);
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	this->_height = atoi(tmp + i);
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	this->_maxPlayer = atoi(tmp + i);
	MapManager::Instance().setWall(this->_wall);
	GraphicsManager::setLib(sfml, this->_width, this->_height);
	MapManager::Instance().init(this->_maxPlayer, this->_width, this->_height);
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	while (tmp[i] != '\0' && (tmp[i] < '0' || tmp[i] > '9'))
		i++;
	int	index = atoi(tmp + i);
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	int direc = atoi(tmp + i);
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	int x = atoi(tmp + i);
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	int y = atoi(tmp + i);
	this->_me1 = new Player((e_Cardinal)direc, x, y, index, false, false, true);
	this->_me1->setReady(true);
	this->_nbPlayer++;
	if (this->_pl2 == true)
	{
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		i++;
		while (tmp[i] != '\0' && (tmp[i] < '0' || tmp[i] > '9'))
			i++;
		index = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		i++;
		direc = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		i++;
		x = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		i++;
		y = atoi(tmp + i);
		this->_me2 = new Player((e_Cardinal)direc, x, y, index, true, false, true);
		this->_me2->setReady(true);
		this->_nbPlayer++;
	}
	else
		this->_me2 = NULL;
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	if (tmp[i] != '\0')
		i++;
	while (tmp[i] != '\0')
	{
		while (tmp[i] != '\0' && (tmp[i] < '0' || tmp[i] > '9'))
			i++;
		index = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		if (tmp[i] != '\0')
			i++;
		direc = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		if (tmp[i] != '\0')
			i++;
		x = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		if (tmp[i] != '\0')
			i++;
		y = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		std::cout << "Creating Player index : " << index << std::endl;
		Player *clt = new Player((e_Cardinal)direc, x, y, index, false, false, false);
		this->_players.push_back(clt);
		this->_nbPlayer++;
	}
	this->_init = true;
}

void		Client::init_Others(char *tmp)
{
	int		i = 0;
	int		index;
	int		direc;
	int		x;
	int		y;

	while (tmp[i] != '\0')
	{
		while (tmp[i] != '\0' && (tmp[i] < '0' || tmp[i] > '9'))
			i++;
		index = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		if (tmp[i] != '\0')
			i++;
		direc = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		if (tmp[i] != '\0')
			i++;
		x = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		if (tmp[i] != '\0')
			i++;
		y = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		Player *clt = new Player((e_Cardinal)direc, x, y, index, false, false, false);
		this->_players.push_back(clt);
		this->_nbPlayer++;
	}
}

void		Client::VerifySnakes(char *tmp)
{
	int			index = atoi(tmp + 2);

	std::list<Player*>::iterator player = this->_players.begin();
	std::list<Player*>::iterator end = this->_players.end();
	while (player != end)
	{
		if ((*player)->getIndex() == index)
			MapManager::Instance().VerifySnake(tmp, (*player));
		player++;
	}
}

void		Client::Snake_Eat(char *tmp)
{
	int		i = 3;
	int		index = atoi(tmp + i);
	int		x;
	int		y;

//	std::cout << "Snake Eating : " << tmp << std::endl;
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	x = atoi(tmp + i);
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	y = atoi(tmp + i);
	MapManager::Instance().Snake_Eat(index, x, y);
}

void		Client::Snake_Take(char *tmp)
{
	int		i = 3;
	int		index = atoi(tmp + i);
	int		x;
	int		y;

	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	x = atoi(tmp + i);
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	y = atoi(tmp + i);
	MapManager::Instance().Snake_Take(index, x, y);
}

void		Client::Snake_Death(char *tmp)
{
	int		index = atoi(tmp + 2);
	std::cout << "Death of Snake : " << index << std::endl;
	MapManager::Instance().Snake_Death(index);
}

void		Client::make_cmd(char *tmp)
{
	std::cout << "MSG : " << tmp << std::endl;
	if (tmp[0] == 'V')
		this->VerifySnakes(tmp);
	else if (tmp[0] == 'S')
		Snake_direc(tmp);
	else if (tmp[0] == 'E')
	{
		if (tmp[1] == 'F')
			this->Snake_Eat(tmp);
		else if (tmp[1] == 'B')
			this->Snake_Take(tmp);
	}
	else if (tmp[0] =='F')
		popFood(tmp);
	else if (tmp[0] == 'B')
		popBonus(tmp);
	else if (tmp[0] == 'D')
		this->Snake_Death(tmp);
	else if (strncmp(tmp, "C_co", 4) == 0)
	{
		if (this->_pl2 == true)
			this->set_write((char*)"2\n");
		else
			this->set_write((char*)"1\n");
	}
	else if (strncmp(tmp, "C_M", 3) == 0)
	{
		if (this->_init == false)
			init_Game(tmp);
		else
			init_Others(tmp);
	}
}

void		Client::receive_data(void)
{
	int		r;

	r = recv(this->sock, this->tmp_read, BC_SIZE, 0);
	if (r <= 0)
	{
		close(this->sock);
		if (this->_me1 != NULL)
			delete this->_me1;
		if (this->_me2 != NULL)
			delete this->_me2;
		if (this->_players.size() > 0)
		{
			std::list<Player*>::iterator pl = this->_players.begin();
			std::list<Player*>::iterator end = this->_players.end();
			while (pl != end)
			{
				Player *del = (*pl);
				this->_players.erase(pl);
				delete del;
				pl = this->_players.begin();
			}
		}
		exit(0);
	}
	else
	{
		this->tmp_read[r] = '\0';
		this->b_read.bc_write(this->tmp_read, 0);
		bzero(tmp_read, BC_SIZE + 1);
		while (this->b_read.bc_iscmd() == 1)
		{
			b_read.bc_read(this->tmp_read);
//			std::cout << "Receive Groups : " << this->tmp_read << std::endl;
			char **tab = ft_strtab(tmp_read);
			for (int i = 0; tab[i] != NULL; i++)
			{
				if (tab[i] != NULL && tab[i][0] != '\0')
				{
//					std::cout << "Receive : " << tab[i] << std::endl;
					make_cmd(tab[i]);
				}
			}
		}
	}
}

void		Client::set_write(char *tmp)
{
	this->b_write.bc_write(tmp, 1);
}

char		*Client::get_read(void)
{
	b_read.bc_read(tmp_read);
	return (tmp_read);
}

std::list<Player*>		*Client::getClients(void)
{
	return (&(this->_players));
}

bool					Client::getInit(void)
{
	return (this->_init);
}

bool					Client::getWall(void)
{
	return (this->_wall);
}

int						Client::getWidth(void)
{
	return (this->_width);
}

int						Client::getHeight(void)
{
	return (this->_height);
}

int						Client::getMaxPlayer(void)
{
	return (this->_maxPlayer);
}

int						Client::getNBPlayers(void)
{
	return (this->_nbPlayer);
}

Player				*Client::getPlayer1(void)
{
	return (this->_me1);
}

Player				*Client::getPlayer2(void)
{
	return (this->_me2);
}

bool				Client::getNull1(void)
{
	return this->_null1;
}

void				Client::setNull1(bool null1)
{
	this->_null1 = null1;
	if (this->_null1 == true)
		this->_me1 = NULL;
}

bool				Client::getNull2(void)
{
	return this->_null2;
}

void				Client::setNull2(bool null2)
{
	this->_null2 = null2;
	if (this->_null2 == true)
		this->_me2 = NULL;
}

char				**ft_strtab(char *str)
{
	char			**tab;
	int				i = 0;
	int				j = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			j++;
		i++;
	}
	i = 0;
	tab = (char **)malloc(sizeof(char *) * (j + 1));
	j = 1;
	tab[0] = str;
	while (str[i] != '\0')
	{
		if (str[i] == '\n' && str[i + 1] != '\0' && str[i + 1] != '\n')
		{
			str[i] = '\0';
			tab[j] = str + i + 1;
			j++;
		}
		else if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
	tab[j] = NULL;
	return (tab);
}
