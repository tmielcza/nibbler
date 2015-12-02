// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MapManager.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 16:00:36 by rduclos           #+#    #+#             //
//   Updated: 2015/12/02 16:11:45 by rduclos          ###   ########.fr       //
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
# include "AEntity.hpp"
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

	std::list<Snake*>	_snakes;
	std::list<Food*>	_foods;
	std::list<ABonus*>	_bonus;
	std::list<Wall*>	_wall;
	int					_nbPlayer;
	int					_width;
	int					_height;
	static MapManager	_instance;

	MapManager(MapManager const & copy);

	MapManager	&	operator=(MapManager const & copy);

	public:

	AEntity				***_Map;

	static MapManager&	Instance(void);
	void				init(int nbplayer, int width, int height);
	void				move(int index);
	void				setSnakeDir(int index, bool left);
	bool				InZone(Point point, Point upleft, Point downright, e_PopMode mode);
	void				foodpop(e_PopMode mode);
	void				foodpop(Point upleft, Point downright, e_PopMode mode);
	void				foodpop(Point center, int radius, e_PopMode mode);
	void				foodeaten(Snake & eater, Food & eaten);
	void				bonuspop(void);
	void				bonustaken(Snake & taker, ABonus *taken);
	int					getFoodnb(void);
	int					getBonusnb(void);
};

#endif
