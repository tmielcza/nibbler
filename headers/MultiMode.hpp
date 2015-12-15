// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MultiMode.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/03 17:28:39 by rduclos           #+#    #+#             //
//   Updated: 2015/12/03 19:24:45 by rduclos          ###   ########.fr       //
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
//	std::string		_addr;

	MultiMode(bool pl2, int port, std::string addr);
	bool			check_end(void);

	public:

	MultiMode(void);
	MultiMode(bool pl2, int port);
	MultiMode(const MultiMode & src);
	~MultiMode(void);

	MultiMode	&	operator=(const MultiMode & src);

	void			init(int nbPlayers, int width, int height, bool wall);
	void			run(void);

};

#endif
