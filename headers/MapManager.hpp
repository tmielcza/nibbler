// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MapManager.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 16:00:36 by rduclos           #+#    #+#             //
//   Updated: 2015/11/17 17:59:58 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MAPMANAGER_HPP
# define MAPMANAGER_HPP

# include "Snake.hpp"
# include "Food.hpp"
# include "ABonus.hpp"
# include "Wall.hpp"
# include "Point.hpp"
# include "IDisplayer.hpp"
# include <list>

enum e_PopMode
{
	InsideMode,
	OutsideMode,
	BorderMode
};

class MapManager
{
	private:

	MapManager(void);
	~MapManager(void);

	std::list<Snake>	_snakes;
	std::list<Food>		_foods;
	std::list<ABonus*>	_bonus;
	Wall				_wall;
	int					_nbPlayer;
	static MapManager	_instance;

	MapManager(MapManager const & copy);

	MapManager	&	operator=(MapManager const & copy);

	public:

	static MapManager&		Instance(void);
	void			init(int nbplayer, int width, int height);
	int				verify_colision(void);
	void			verify_snakeaten(void);
	void			verify_snaketaken(void);
	bool			verify_places(Point point);
	void			move(int index);
	void			setSnakeDir(int index, e_Dir dir);
	bool			InZone(Point point, Point upleft, Point downright, e_PopMode mode);
	void			foodpop(e_PopMode mode);
	void			foodpop(Point upleft, Point downright, e_PopMode mode);
	void			foodpop(Point center, int radius, e_PopMode mode);
	void			foodeaten(Snake & eater, Food & eaten);
	void			bonuspop(void);
	void			bonustaken(Snake & taker, ABonus *taken);
	int				getFoodnb(void);
	int				getBonusnb(void);
};

#endif
