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

typedef std::chrono::high_resolution_clock Clock;

enum	e_Mode
{
	Solo,
	Multi,
	DeathNote
};

class GameManager
{
	private:

	int			_nbPlayer;
	int			_width;
	int			_height;
	double		_speed;
	AGameMode	*_mode;

	double			deltaTime(void);

	public:

	GameManager(void);
	GameManager(int nbplayer, int width, int height, double speed);
	GameManager(const GameManager & copy);
	~GameManager(void);

	GameManager	&	operator=(const GameManager & ass);

	void			init(int nbplayer, int width, int height, double speed);
	void			loop(e_Mode mode);

};

#endif
