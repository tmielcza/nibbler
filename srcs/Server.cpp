#include "Server.hpp"

Server::Server(int port, bool wall, int width, int height, int playerMax)
{
	struct rlimit	rlp;

	if (getrlimit(RLIMIT_NOFILE, &rlp) == -1)
	{
		std::cerr << "Serveur : error getrlimit()" << std::endl;
		exit(-1);
	}
	this->max_fd = rlp.rlim_cur;
	init_srv(port);
	this->_wall = wall;
	this->_width = width;
	this->_height = height;
	this->_maxPlayer = playerMax;
	this->nbPlayers = 0;
}

Server::~Server(void)
{
	int		i;

	i = 0;
	while (i < this->max_fd)
	{
		delete(this->clients[i]);
		i++;
	}
	free(this->clients);
	close(this->ssock);
}

void	 Server::init_srv(int port)
{
	struct sockaddr_in		sockServer;

    sockServer.sin_family = AF_INET;
	sockServer.sin_port = htons(port);
	sockServer.sin_addr.s_addr = INADDR_ANY;
	bzero(&(sockServer.sin_zero),8);
	if ((this->ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
		std::cerr << "Serveur : error creation socket()" << std::endl;
		exit(-1);
	}
	if(bind(this->ssock,(struct sockaddr*)&sockServer,sizeof(struct sockaddr)) == -1)
	{
		std::cerr << "Serveur : error bind() : " << port << std::endl;
		exit(-1);
	}
	if(listen(this->ssock, 42) == -1)
	{
		std::cerr << "Serveur : error listen()" << std::endl;
		exit(-1);
	}
}

void	Server::init_clt(S_Client **clients)
{
	int 			i;

	i = 0;
	if ((clients = (S_Client **)malloc(sizeof(S_Client *) * max_fd)) == NULL)
	{
		std::cerr << "Server : error malloc clients" << std::endl;
		exit(-1);
	}
	while (i < max_fd)
	{
		clients[i] = new S_Client(i);
		clients[i]->set_type(FREE_FD);
		i++;
	}
	this->clients = clients;
}

void     Server::connection(S_Client **clients)
{
	int						cs;
	struct sockaddr_in		clt;
	unsigned int			len;

	if ((cs = accept(ssock, (struct sockaddr *)&clt, &len)) == -1)
	{
		std::cout << "Server : error accept client" << std::endl;
		exit(-1);
	}
	std::cout << "Client : " << cs << " connected." << std::endl;
	clients[cs]->set_type(CLT_FD);
	clients[cs]->set_write((char *)"C_co");
}

void	Server::init_fd(S_Client **clients)
{
	int		i;

	i = 0;
	FD_ZERO(&(this->fd_read));
	FD_ZERO(&(this->fd_write));
	FD_SET(this->ssock, &(this->fd_read));
	this->fd_max = this->ssock + 1;
	while (i < max_fd)
	{
		if (clients[i]->get_type() != FREE_FD)
		{
			FD_SET(i, &(this->fd_read));
			if (clients[i]->is_write() == 1)
				FD_SET(i, &(this->fd_write));
			this->fd_max = i + 1;
		}
		i++;
	}
}


void	Server::send_msg_to_all(S_Client **clients, int cs, const char *msg)
{
	int			i = -1;

	while (++i < max_fd)
	{
		if (clients[i]->get_type() != FREE_FD && i != cs)
			clients[i]->set_write((char*)msg);
	}
}

void	Server::name_client(S_Client **clients, int cs, char *msg)
{
	int		i;

	i = 0;
	while (msg[i] != '\n')
		i++;
	msg[i] = '\0';
	std::string name(msg);
	clients[cs]->set_name(name);
}

void		Server::create_snake(S_Client **clients, int cs, char *msg)
{
	std::string		tmp = "C_M";

	this->nbPlayers++;
	tmp += std::to_string(this->_wall) + "_" + std::to_string(this->_width) + "-";
	tmp += std::to_string(this->_height) + ":" + std::to_string(this->_maxPlayer) + "_";
	tmp += clients[cs]->setPlayer1();
	if (msg[0] == '2')
	{
		tmp += "_";
		tmp += clients[cs]->setPlayer2();
		this->nbPlayers++;
	}
	int x = this->_me1->getX();
	int y = this->_me1->getY();
	e_Cardinal direc = this->_me1->getDirec();
	int index = this->_me1->getIndex();
	tmp += "C_S" + std::to_string(index) + "_" + std::to_string(direc) + "_";
	tmp += std::to_string(x) + "-" + std::to_string(y);
	if (this->_me2 != NULL)
	{
		x = this->_me1->getX();
		y = this->_me1->getY();
		direc = this->_me1->getDirec();
		index = this->_me1->getIndex();
		tmp += "C_S" + std::to_string(index) + "_" + std::to_string(direc) + "_";
		tmp += std::to_string(x) + "-" + std::to_string(y);		
	}
	int i = 0;
	while (i < this->max_fd)
	{
		if (this->clients[i]->get_type() == CLT_FD && i != cs)
		{
			tmp += this->clients[i]->setPlayer1();
			if (this->clients[i]->getPL2() == true)
				tmp += this->clients[i]->setPlayer2();
		}
		i++;
	}
	tmp += "\n";
	clients[cs]->set_write((char *)tmp.c_str());
}

void	Server::do_cmd(S_Client **clients, int cs, char *msg)
{
	Player *tmp1 = clients[cs]->getPlayer1();
	Player *tmp2 = clients[cs]->getPlayer2();
	if (msg[0] != 'I')
	{
		int index = atoi(msg + 1);
		int direc = atoi(msg + 3);
		if (tmp1 != NULL && tmp1->getIndex() == index)
		{
			if (tmp1->getSizeTouch() < 3)
				tmp1->add_touch((e_Cardinal)direc);
		}
		else if (tmp2 != NULL && tmp2->getIndex() == index)
		{
			if (tmp2->getSizeTouch() < 3)
				tmp2->add_touch((e_Cardinal)direc);
		}
	}
}

void	Server::check_actions(S_Client **clients, int cs, char *msg)
{
	if (clients[cs]->getPlayer1() != NULL || clients[cs]->getPlayer2() != NULL)
	{
		this->do_cmd(clients, cs, msg);
		send_msg_to_all(clients, cs, msg);
	}
	else
		create_snake(clients, cs, msg);
}

void	Server::check_fd(S_Client **clients)
{
	int		i;
	char	*msg;

	i = 0;
	if (FD_ISSET(ssock, &fd_read) != 0)
		connection(clients);
	while (i < fd_max)
	{
		if (clients[i]->get_type() != FREE_FD)
		{
			if (FD_ISSET(i, &fd_read) != 0)
			{
				if ((msg = clients[i]->c_receive()) != NULL)
					check_actions(clients, i, msg);
			}
			else if (FD_ISSET(i, &fd_write) != 0)
				clients[i]->c_send();
			if (FD_ISSET(i, &fd_read) != 0 || FD_ISSET(i, &fd_write) != 0)
				r--;
		}
		i++;
	}
}

void	Server::check_fd_noCo(S_Client **clients)
{
	int		i;
	char	*msg;

	i = 0;
	while (i < fd_max)
	{
		if (clients[i]->get_type() != FREE_FD)
		{
			if (FD_ISSET(i, &fd_read) != 0)
			{
				if ((msg = clients[i]->c_receive()) != NULL)
					check_actions(clients, i, msg);
			}
			else if (FD_ISSET(i, &fd_write) != 0)
				clients[i]->c_send();
			if (FD_ISSET(i, &fd_read) != 0 || FD_ISSET(i, &fd_write) != 0)
				this->r--;
		}
		i++;
	}
}


int		Server::run_serv(bool co)
{
	struct timeval	waitd;

	waitd.tv_sec = 0;
	waitd.tv_usec = 1;
	init_fd(this->clients);
	this->r = select(fd_max, &(this->fd_read), &(this->fd_write), NULL, &waitd);
	if (co == true)
		check_fd(this->clients);
	else
		check_fd_noCo(this->clients);
	return (1);
}

void	Server::stop_serv(void)
{
	std::cout << "Server Stopped." << std::endl;
}

S_Client	**Server::getClients(void)
{
	return this->clients;
}

int			Server::getLimit(void)
{
	return this->max_fd;
}

int			Server::getMaxFD(void)
{
	return (this->max_fd);
}

int			Server::getNbPlayers(void)
{
	return (this->nbPlayers);
}

void		Server::setPlayers(Player *me1, Player *me2)
{
	this->_me1 = me1;
	this->_me2 = me2;
}
