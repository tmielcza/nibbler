// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MapManager.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 16:00:36 by rduclos           #+#    #+#             //
//   Updated: 2015/12/03 17:18:04 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MAPMANAGER_HPP
# define MAPMANAGER_HPP

# include "Snake.hpp"
# include "Food.hpp"
# include "Player.hpp"
# include "ABonus.hpp"
# include "SuperFood.hpp"
# include "MultiFood.hpp"
# include "ChasedFood.hpp"
# include "SlowBonus.hpp"
# include "CutBonus.hpp"
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
	std::list<Wall*>	_walls;
	std::string			_tosend;
	bool				_berase;
	bool				_wall;
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
	void				removeSnake(Snake *snake);
	void				setSnakeDir(int index, bool left);
	bool				InZone(Point point, Point upleft, Point downright, e_PopMode mode);
	void				foodpop(bool spawner);
	void				foodpop(Point upleft, Point downright, bool spawner, e_PopMode mode);
	void				foodpop(Point center, int radius, bool spawner, e_PopMode mode);
	void				foodpop(bool spawner, int x, int y);
	void				foodepop(int x, int y);
	void				bonuspop(void);
	void				bonuspop(int b);
	void				bonuspop(int b, int x, int y, int r2, int r3);
	void				bonusdepop(int x, int y);
	void				add_Bonus(ABonus *bonus);
	int					getBonusnb(void);
	int					getWidth(void);
	int					getHeight(void);
	void				setWall(int x, int y);
	void				setWall(Point pos);
	void				setSnake(Snake *snake);
	void				update(double time);
	void				restart(void);
	char				*takeToSend(void);
	void				setToSend(char *tmp);
	void				ClearToSend(void);
	bool				getWall(void);
	void				setWall(bool wall);
	void				Snake_Eat(int index, int x, int y);
	void				Snake_Take(int index, int x, int y);
	void				Snake_Death(int index);
	void				VerifySnake(char *tmp, Player *pl);
	void				VerifyFB(void);

};

#endif
