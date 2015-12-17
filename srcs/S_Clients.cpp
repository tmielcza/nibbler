#include "S_Client.hpp"

S_Client::S_Client(int me)
{
	sock = me;
	bzero(tmp_read, BC_SIZE + 1);
	bzero(tmp_write, BC_SIZE + 1);
}

S_Client::~S_Client()
{
	bzero(tmp_read, BC_SIZE + 1);
	bzero(tmp_write, BC_SIZE + 1);
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
	send(sock, tmp_write, i, 0);
	bzero(tmp_write, i + 1);
}

char	*S_Client::c_receive(void)
{
	int		r;

	r = recv(sock, tmp_read, BC_SIZE, 0);
	if (r <= 0)
	{
		type = FREE_FD;
		std::cout << "S_Client : " << sock << " disconnected." << std::endl;
		name = "";
		close(sock);
	}
	else
	{
		b_read.bc_write(tmp_read, 0);
		bzero(tmp_read, BC_SIZE + 1);
		if (b_read.bc_iscmd() == 1)
		{
			b_read.bc_read(tmp_read);
			return (tmp_read);
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

std::string	S_Client::setPlayer1(void)
{
	this->_pl1 = new Player(false, true);
	int x = this->_pl1->getX();
	int y = this->_pl1->getY();
	e_Cardinal direc = this->_pl1->getDirec();
	int index = this->_pl1->getIndex();
	std::string tmp = "C_S" + std::to_string(index) + "_" + std::to_string(direc) + "_";
	tmp += std::to_string(x) + "-" + std::to_string(y) + "\n";
	return (tmp);
}

std::string	S_Client::setPlayer2(void)
{
	this->_pl2 = new Player(false, true);
	int x = this->_pl2->getX();
	int y = this->_pl2->getY();
	e_Cardinal direc = this->_pl2->getDirec();
	int index = this->_pl2->getIndex();
	std::string tmp = "C_S" + std::to_string(index) + "_" + std::to_string(direc) + "_";
	tmp += std::to_string(x) + "-" + std::to_string(y) + "\n";
	return (tmp);
}