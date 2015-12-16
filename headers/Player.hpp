// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/29 19:17:33 by rduclos           #+#    #+#             //
//   Updated: 2015/12/03 21:20:45 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Snake.hpp"
# include "IDisplayer.hpp"

class Player
{
	private:

	Snake					*_Snake;
	std::list<e_Cardinal>	_lastInputs;
	double					_time;
	bool					_local;
	bool					_pl2;

	public:

	Player(void);
	Player(bool pl2, bool local);
	Player(e_Cardinal direc, int x, int y, int index, bool pl2, bool local);
	Player(Snake *snake);
	Player(const Player & copy);
	~Player(void);

	Player	&	operator=(const Player & ass);
	bool		IsAlive(void);
	int			verify_lL(e_Cardinal d);
	void		update(double time);
	void		add_touch(e_Cardinal touch);
	int			getSizeTouch(void);
	int			getX(void);
	int			getY(void);
	e_Cardinal	getDirec(void);
	int			getIndex(void);

};

#endif
