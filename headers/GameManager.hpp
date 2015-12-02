// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/08 17:04:14 by rduclos           #+#    #+#             //
//   Updated: 2015/11/17 18:03:50 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GAMEMANAGER_HPP
# define GAMEMANAGER_HPP

# include <chrono>

# include "MapManager.hpp"
# include "GraphicsManager.hpp"
# include "AGameMode.hpp"
# include "Player.hpp"

typedef std::chrono::high_resolution_clock Clock;

enum	e_preMode
{
	Solo,
	Multi,
	Network
};

class GameManager
{
	private:

	int						_nbPlayer;
	int						_width;
	int						_height;
	double					_speed;
	AGameMode				*_mode;
	std::list<Player*>		_players;

	double			deltaTime(void);

	public:

	GameManager(void);
	GameManager(int nbplayer, int width, int height, double speed);
	GameManager(const GameManager & copy);
	~GameManager(void);

	GameManager	&	operator=(const GameManager & ass);

	void			init(int nbplayer, int width, int height, double speed);
	void			loop(e_preMode mode);

};

#endif
