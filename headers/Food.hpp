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

class Food : public AEntity
{
	private:

	int		_value;

	public:

	Food(void);
	Food(Food const & copy);
	Food(int value, int x, int y);
	~Food(void);

	Food	&	operator=(Food const & ass);
	bool		check_position(int x, int y);
	int			get_value(void) const;
	void		set_value(int value);
	void		draw(double time);
};

#endif
