// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Snake.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 16:10:59 by rduclos           #+#    #+#             //
//   Updated: 2015/04/29 18:28:36 by rduclos          ###   ########.fr       //
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
	Forward,
	Left,
	Right
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

	public:

	Snake(Snake const & copy);
	Snake(e_Cardinal direction, int x, int y);
	~Snake(void);

	void						setNextDir(e_SDir NextDir);
	e_SDir						getNextDir(void);
	Snake					&	operator=(Snake const & ass);
	void						save_my_tail(void);
	bool						colision_wall(Wall const & wall);
	bool						colision_snake(Snake const & snake);
	bool						colision_itself(void);
	void						init(int direction, int x, int y);
	std::list<Segment>		&	get_snake(void);
	void						move(void);
	void						turn_left(void);
	void						turn_right(void);
	void						eat(Food const & eaten);
	void						take_bonus(ABonus const & taken);
	int							getHeadSnakeX(void);
	int							getHeadSnakeY(void);

};

#endif
