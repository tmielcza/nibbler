#include "Client.hpp"
#include "MapManager.hpp"

Client::Client(void)
{
	bzero(this->tmp_read, BC_SIZE + 1);
	bzero(this->tmp_read, BC_SIZE + 1);
	FD_ZERO(&this->fd_read);
	FD_ZERO(&this->fd_write);
	this->r = 1;
	this->_pl2 = false;
	this->_init = false;
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
	send(sock, this->tmp_write, i, 0);
	bzero(&this->tmp_write, i);
}

void		Client::Snake_direc(char *tmp)
{
	int		index = atoi(tmp + 1);
	int		i;

	i = 1;
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	int		direc = atoi(tmp + i + 1);
	if (direc != 0)
	{
		std::list<Player*>::iterator	snake = this->_players.begin();
		std::list<Player*>::iterator	end = this->_players.end();

		while (snake != end)
		{
			if ((*snake)->getIndex() == index)
				if ((*snake)->getSizeTouch() < 3)
					(*snake)->add_touch((e_Cardinal)direc);
			snake++;
		}
	}
}

void		Client::popFood(char *tmp)
{
	int		x = atoi(tmp + 3);
	int		y = atoi(tmp + 5);
	MapManager::Instance().foodpop(x, y);
}

void		Client::popBonus(char *tmp)
{
	int		i = 3;
	int		b;
	int		r2 = 10;

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
	int x = atoi(tmp + 4);
	i++;
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	int y = atoi(tmp + i);
	if (b == 3 || b == 4)
	{
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		i++;
		r2 = atoi(tmp + i);
	}
	MapManager::Instance().bonuspop(b, x, y, r2);
}

void		Client::init_Game(char *tmp)
{
	int			i = 3;
	
	this->_wall = (bool)atoi(tmp + 4);
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
	std::cout << "Wall : " << this->_wall << std::endl;
	std::cout << "Width : " << this->_width << std::endl;
	std::cout << "Height : " << this->_height << std::endl;
	std::cout << "MaxPlayer : " << this->_maxPlayer << std::endl;
	std::cout << "Snake me index : " << index << std::endl;
	std::cout << "Snake Direc : " << direc << std::endl;
	std::cout << "PosX : " << x << std::endl;
	std::cout << "PosY : " << y << std::endl;
	this->_me1 = new Player((e_Cardinal)direc, x, y, index, false, false);
	this->_nbPlayer++;
	if (this->_pl2 == true)
	{
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		if (tmp[i] != '\0')
			i++;
		while (tmp[i] != '\0' && (tmp[i] < '0' || tmp[i] > '9'))
			   i++;
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
		std::cout << "Snake me2 index : " << index << std::endl;
		std::cout << "Snake Direc : " << direc << std::endl;
		std::cout << "PosX : " << x << std::endl;
		std::cout << "PosY : " << y << std::endl;
		this->_me2 = new Player((e_Cardinal)direc, x, y, index, true, false);
		this->_nbPlayer++;
	}
	else
		this->_me2 = NULL;
	while (tmp[i] != '\0')
	{
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		i++;
		while (tmp[i] != '\0' && (tmp[i] < '0' || tmp[i] > '9'))
			i++;
		index = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		direc = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		x = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		y = atoi(tmp + i);
		std::cout << "Snake Other index : " << index << std::endl;
		std::cout << "Snake Direc : " << direc << std::endl;
		std::cout << "PosX : " << x << std::endl;
		std::cout << "PosY : " << y << std::endl;
		Player *clt = new Player((e_Cardinal)direc, x, y, index, false, false);
		this->_players.push_back(clt);
		this->_nbPlayer++;
	}
	this->_init = true;
}

void		Client::make_cmd(char *tmp)
{
	if (strncmp(tmp, "S", 1) == 0)
		Snake_direc(tmp);
	else if (strncmp(tmp, "F", 1) == 0)
		popFood(tmp);
	else if (strncmp(tmp, "B", 1) == 0)
		popBonus(tmp);
	else if (strncmp(tmp, "C_co", 4) == 0)
	{
		if (this->_pl2 == true)
			this->set_write((char*)"2\n");
		else
			this->set_write((char*)"1\n");
	}
	else if (strncmp(tmp, "C_M", 3) == 0)
		init_Game(tmp);
}

void		Client::receive_data(void)
{
	int		r;

	r = recv(this->sock, this->tmp_read, BC_SIZE, 0);
	if (r <= 0)
	{
		close(this->sock);
		exit(0);
	}
	else
	{
		this->tmp_read[r] = '\0';
		this->b_read.bc_write(this->tmp_read, 0);
		bzero(tmp_read, BC_SIZE + 1);
		if (this->b_read.bc_iscmd() == 1)
		{
			b_read.bc_read(this->tmp_read);
			make_cmd(tmp_read);
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
