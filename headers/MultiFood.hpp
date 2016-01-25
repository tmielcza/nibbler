// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MultiFood.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/25 18:14:31 by rduclos           #+#    #+#             //
//   Updated: 2016/01/25 18:14:31 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MULTIFOOD_HPP
# define MULTIFOOD_HPP

# include "ABonus.hpp"

class MultiFood : public ABonus
{
	private:

	bool		_spawner;

	public:

	MultiFood(void);
	MultiFood(int value, int x, int y, bool spawner);
	MultiFood(const MultiFood & src);
	~MultiFood(void);

	MultiFood	&		operator=(const MultiFood & src);

	void				taken(Snake & snake);
	void				update(double time);
	void				draw(double time);

};

#endif
