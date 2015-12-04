// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Snake.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 16:10:59 by rduclos           #+#    #+#             //
//   Updated: 2015/12/03 21:02:38 by rduclos          ###   ########.fr       //
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

class Snake
{
	private:

	const int					_index;
	static int					_curIndex;
	std::list<Segment*>			_snake;
	Segment						*_tail;
	int							_nbmove;
	int						 	_score;
	double						_speed;
	bool						_alive;

	Snake(Snake const & copy);

	Snake					&	operator=(Snake const & ass);
	bool						check_place_snake(int x, int y);

	public:

	Snake(void);
	Snake(e_Cardinal direction, int x, int y);
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
	void						take_bonus(ABonus const & taken);
	e_Cardinal					getHeadSnakeDirec(void);
	int							getHeadSnakeX(void);
	int							getHeadSnakeY(void);
	int							getIndex(void);
	double						getSpeed(void);
	bool						IsAlive(void);
	void						draw(double time);

};

#endif
