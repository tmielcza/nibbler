// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ABonus.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/04 12:58:05 by rduclos           #+#    #+#             //
//   Updated: 2015/04/07 16:32:30 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ABONUS_HPP
# define ABONUS_HPP

# include "AEntity.hpp"
# include <iostream>
# include <string>

class Snake;

class ABonus : public AEntity
{
	private:

	ABonus(void);

	protected:

	int		_value;
	bool	_isalive;

	public:

	ABonus(ABonus const & copy);
	ABonus(int value, int x, int y);
	~ABonus(void);

	ABonus	&			operator=(ABonus const & ass);

	bool				isalive(void);
	void				bonus_taken(const Snake & snake);

	virtual void		taken(Snake & snake) = 0;
	virtual void		update(float time) = 0;
	virtual void		draw(float time) = 0;

};

#endif
