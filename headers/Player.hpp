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

	Snake		*_Snake;
	e_Cardinal	_lastInput;
	double		_time;

	public:

	Player(void);
	Player(Snake *snake);
	Player(const Player & copy);
	~Player(void);

	Player	&	operator=(const Player & ass);
	bool		IsAlive(void);
	void		update(double time);

};

#endif
