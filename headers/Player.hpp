// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/29 19:17:33 by rduclos           #+#    #+#             //
//   Updated: 2016/01/25 18:30:39 by rduclos          ###   ########.fr       //
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
	std::string				_tosend;
	double					_time;
	bool					_local;
	bool					_client;
	bool					_pl2;
	bool					_ready;

	public:

	Player(void);
	Player(bool pl2, bool client, bool local);
	Player(e_Cardinal direc, int x, int y, int index, bool pl2, bool client, bool local);
	Player(Snake *snake);
	Player(const Player & copy);
	~Player(void);

	Player	&	operator=(const Player & ass);
	bool		IsAlive(void);
	bool		verify_lL(e_Cardinal d);
	void		verifyTurn(void);
	void		update(double time);
	void		add_touch(e_Cardinal touch);
	int			getSizeTouch(void);
	e_Cardinal	getFirstTouch(void);
	int			getX(void);
	int			getY(void);
	void		setX(int x);
	void		setY(int y);
	void		setDirec(e_Cardinal direc);
	e_Cardinal	getDirec(void);
	void		setScore(int score);
	int			getScore(void);
	int			getIndex(void);
	int			getCycles(void);
	void		setCycles(int cycle);
	bool		getReady(void);
	void		setReady(bool ready);
	bool		getPL2(void);
	void		move(void);
	char		*SnaketakeToSend(void);
	void		SnakeClearToSend(void);
	char		*takeToSend(void);
	void		ClearToSend(void);
	void		Verify_Snake(char *tmp);
	void		add_Cycle(int cycle, int x, int y, int direc);
	void		CheckSnakeCycle(void);

};

#endif
