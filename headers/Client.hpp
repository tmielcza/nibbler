#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <cstdlib>
# include <unistd.h>
# include <strings.h>
# include <cstring>
# include <netdb.h>
# include <sys/types.h>//pour les sockets
# include <sys/socket.h>//pour les sockets
# include <netinet/in.h>//pour les sockets
# include <arpa/inet.h>//pour les sockets
# include <sys/select.h>

# include "Buff_Circle.hpp"
# include "Player.hpp"

class Client
{
	private:

	int						sock;
	int						r;
	fd_set					fd_read;
	fd_set					fd_write;
	Buff_Circle				b_read;
	Buff_Circle				b_write;
	char					tmp_read[BC_SIZE + 1];
	char					tmp_write[BC_SIZE + 1];
	Player					*_me1;
	Player					*_me2;
	std::list<Player*>		_players;
	bool					_pl2;
	bool					_init;
	bool					_wall;
	int						_width;
	int						_height;
	int						_maxPlayer;
	int						_nbPlayer;

	Client(const Client & src);
	Client	&	operator=(const Client & src);

	public:

	Client(void);
	Client(bool pl2);
	~Client(void);
	void				init(char *adr, int port);
	void				check_actions(void);
	void				do_select(void);
	void				run_clt(void);
	void				send_data(void);
	void				receive_data(void);
	void				set_write(char *tmp);
	char				*get_read(void);
	void				receive_entrance(void);
	void				Snake_direc(char *tmp);
	void				popFood(char *tmp);
	void				popBonus(char *tmp);
	void				init_Game(char *tmp);
	std::list<Player*>	*getClients(void);
	void				make_cmd(char *tmp);
	Player				*getPlayer1(void);
	Player				*getPlayer2(void);
	bool				getInit(void);
	bool				getWall(void);
	int					getWidth(void);
	int					getHeight(void);
	int					getMaxPlayer(void);
	int					getNBPlayers(void);

};

char				**ft_strtab(char *str);

#endif
