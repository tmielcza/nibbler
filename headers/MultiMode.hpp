// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MultiMode.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/03 17:28:39 by rduclos           #+#    #+#             //
//   Updated: 2016/01/25 18:14:43 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MULTIMODE_HPP
# define MULTIMODE_HPP

# include "AGameMode.hpp"
# include "MapManager.hpp"

class MultiMode : public AGameMode
{
	private:

	bool			_master;
	bool			_pl2;
	int				_port;
	char			*_addr;

	MultiMode(bool pl2, int port, std::string addr);
	bool			check_end(void);

	public:

	MultiMode(void);
	MultiMode(bool pl2, int port);
	MultiMode(bool pl2, char *addr, int port);
	MultiMode(const MultiMode & src);
	~MultiMode(void);

	MultiMode	&	operator=(const MultiMode & src);

	void			init_serv(int nbPlayers, int width, int height, bool wall);
	void			init_clt(void);
	void			run(void);

};

#endif
