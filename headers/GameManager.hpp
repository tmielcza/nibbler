// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/08 17:04:14 by rduclos           #+#    #+#             //
//   Updated: 2015/12/03 21:39:07 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GAMEMANAGER_HPP
# define GAMEMANAGER_HPP

# include <chrono>

# include "MapManager.hpp"
# include "GraphicsManager.hpp"
# include "Player.hpp"

typedef std::chrono::high_resolution_clock Clock;

class GameManager
{
	private:

	int						_nbPlayer;
	int						_width;
	int						_height;
	bool					_master;
	std::list<Player*>		_players;
	Player					*_me;

	public:

	GameManager(void);
	GameManager(int nbplayer, int width, int height);
	GameManager(const GameManager & copy);
	~GameManager(void);

	GameManager	&	operator=(const GameManager & ass);

	double			deltaTime(void);
	void			init(int nbplayer, int width, int height);
	bool			IsAlive(void);
	void			update_one(double time);
	void			update(double time);

};

#endif
