// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Food.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 16:28:13 by rduclos           #+#    #+#             //
//   Updated: 2015/12/02 16:30:18 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FOOD_HPP
# define FOOD_HPP

# include "AEntity.hpp"
# include <iostream>
# include <string>

class Snake;

class Food : public AEntity
{
	private:

	int		_value;
	bool	_spawner;
	double	_time;

	public:

	Food(void);
	Food(Food const & copy);
	Food(int value, int x, int y, bool spawner);
	~Food(void);

	Food	&	operator=(Food const & ass);
	bool		check_position(int x, int y);
	int			get_value(void) const;
	void		set_value(int value);
	bool		getSpawner(void) const;
	void		draw(double time);
	void		update(double time);
	void		eaten(Snake & eater) const;

};

#endif
