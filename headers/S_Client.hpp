#ifndef S_CLIENT_HPP
# define S_CLIENT_HPP

# include <iostream>
# include <cstdlib>
# include <unistd.h>
# include <strings.h>
# include <cstring>
# include <sys/types.h>//pour les sockets
# include <sys/socket.h>//pour les sockets
# include <netinet/in.h>//pour les sockets
# include <arpa/inet.h>//pour les sockets
# include "Buff_Circle.hpp"
# include "Player.hpp"


enum types {SRV_FD, CLT_FD, FREE_FD};

class S_Client
{

	private:
	int				sock;
	int			  	type;
	std::string  	name;
	Buff_Circle		b_read;
	Buff_Circle		b_write;
	char			tmp_read[BC_SIZE + 1];
	char			tmp_write[BC_SIZE + 1];
	Player			*_pl1;
	Player			*_pl2;
	
	S_Client(void);
	S_Client(const S_Client & src);
	S_Client	&	operator=(const S_Client & src);

	public:
	S_Client(int me);
	~S_Client(void);
	void			c_send(void);
	int				is_write(void);
	char			*c_receive(void);
	void			clear_tmp_read(void);
	void			set_name(std::string me);
	std::string		get_name(void);
	int				is_named(void);
	void			set_type(int me);
	int				get_type(void);
	void			set_write(char *tmp);
	char			*get_read(void);
	Player			*getPlayer1(void);
	Player			*getPlayer2(void);
	std::string		setPlayer1(void);
	std::string		setPlayer2(void);
	bool			getPL2(void);

};

#endif
