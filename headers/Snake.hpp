// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Snake.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 16:10:59 by rduclos           #+#    #+#             //
//   Updated: 2015/11/17 18:02:35 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SNAKE_HPP
# define SNAKE_HPP

# include "Food.hpp"
# include "Wall.hpp"
# include "ABonus.hpp"
# include "Segment.hpp"
# include <list>

enum	e_SDir
{
	SForward,
	SLeft,
	SRight
};

class Snake
{
	private:

	const int					_index;
	static int					_curIndex;
	std::list<Segment>			_snake;
	Segment						*_tail;
	int							_nbmove;
	int						 	_score;
	double						_speed;
	e_SDir						_nextDir;

	Snake(void);
	Snake(Snake const & copy);

	Snake					&	operator=(Snake const & ass);

	public:

	Snake(e_Cardinal direction, int x, int y);
	~Snake(void);

	void						setNextDir(e_SDir NextDir);
	e_SDir						getNextDir(void);
	void						init(int direction, int x, int y);
	std::list<Segment>		&	get_snake(void);
	void						add_to_tail(void);
	void						befor_move(void);
	void						move(void);
	void						turn_left(void);
	void						turn_right(void);
	void						eat(Food const & eaten);
	void						take_bonus(ABonus const & taken);
	int							getHeadSnakeX(void);
	int							getHeadSnakeY(void);

};

#endif
