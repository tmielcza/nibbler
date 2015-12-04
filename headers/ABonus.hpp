// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ABonus.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/04 12:58:05 by rduclos           #+#    #+#             //
//   Updated: 2015/12/02 16:30:46 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ABONUS_HPP
# define ABONUS_HPP

# include <chrono>

# include "AEntity.hpp"
# include <iostream>
# include <string>

# define B_TIME 5000000000

typedef std::chrono::high_resolution_clock Clock;

class Snake;

class ABonus : public AEntity
{
	private:

	ABonus(void);

	protected:

	int		_value;
	bool	_isalive;
	double	_time;

	public:

	ABonus(ABonus const & copy);
	ABonus(int value, int x, int y);
	virtual ~ABonus(void);

	ABonus	&			operator=(ABonus const & ass);

	bool				isalive(void);

	virtual void		taken(Snake & snake) = 0;
	virtual void		update(double time) = 0;
	virtual void		draw(double time) = 0;

};

#endif
