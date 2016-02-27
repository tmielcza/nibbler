// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Snake.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 16:10:59 by rduclos           #+#    #+#             //
//   Updated: 2016/01/25 18:38:57 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <chrono>
# include <list>

# include "Food.hpp"
# include "Wall.hpp"
# include "ABonus.hpp"
# include "Segment.hpp"

# define SN_TIME 100

typedef std::chrono::high_resolution_clock Clock;

typedef struct					s_MsgCycles
{
	int							cycle;
	int							x;
	int							y;
	int							direc;
}								t_MC;

class Snake
{
	private:

	const int					_index;
	static int					_curIndex;
	std::list<Segment*>			_snake;
	std::list<t_MC*>			_msgCycles;
	std::string					_tosend;
	Segment						*_tail;
	int							_nbmove;
	int						 	_score;
	int							_cycles;
	double						_speed;
	double						_slow;
	double						_increm;
	bool						_alive;
	bool						_client;
	bool						_local;

	Snake(Snake const & copy);

	Snake					&	operator=(Snake const & ass);
	bool						check_place_snake(int x, int y);

	public:

	Snake(void);
	Snake(bool client, bool local);
	Snake(e_Cardinal direction, int x, int y, bool client, bool local, int index);
	~Snake(void);

	void						init(void);
	void						init(e_Cardinal direction, int x, int y);
	std::list<Segment*>		&	get_snake(void);
	void						add_to_tail(void);
	void						add_score(int score);
	void						befor_move(void);
	void						move(void);
	void						turn(e_Cardinal direction);
	void						turn_left(void);
	void						turn_right(void);
	void						eat(Food const & eaten);
	void						take_bonus(ABonus & taken);
	e_Cardinal					getHeadSnakeDirec(void);
	int							getHeadSnakeX(void);
	int							getHeadSnakeY(void);
	void						setHeadSnakeX(int x);
	void						setHeadSnakeY(int y);
	void						setHeadSnakeDirec(e_Cardinal direc);
	void						setScore(int score);
	int							getIndex(void);
	double						getSpeed(void);
	int							getScore(void);
	int							getCycles(void);
	void						setCycles(int cycsle);
	bool						IsAlive(void);
	void						SetAlive(bool alive);
	void						draw(double time);
	void						update_directions(void);
	void						Slow(double time);
	void						Cut(size_t cut);
	char						*takeToSend(void);
	void						ClearToSend(void);
	void						add_Cycle(int cycle, int x, int y, int direc);
	void						Verify_Snake(char *tmp);
	std::string					make_vtosend(void);
	void						CheckSnakeCycle(void);

};

#endif
