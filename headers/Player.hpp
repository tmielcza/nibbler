// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/29 19:17:33 by rduclos           #+#    #+#             //
//   Updated: 2015/12/03 18:44:03 by rduclos          ###   ########.fr       //
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
	e_Input		_lastInput;
	double		_nextMove;

	public:

	Player(void);
	Player(Snake *snake);
	Player(const Player & copy);
	~Player(void);

	Player	&	operator=(const Player & ass);
	bool		IsAlive(void);

};

#endif
