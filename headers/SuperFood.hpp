// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SuperFood.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/25 18:15:24 by rduclos           #+#    #+#             //
//   Updated: 2016/01/25 18:15:24 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SUPERFOOD_HPP
# define SUPERFOOD_HPP

# include "ABonus.hpp"

class SuperFood : public ABonus
{
	private:

	int			_timing;

	public:

	SuperFood(void);
	SuperFood(int value, int x, int y);
	SuperFood(const SuperFood & src);
	~SuperFood(void);

	SuperFood	&		operator=(const SuperFood & src);

	void				taken(Snake & snake);
	void				update(double time);
	void				draw(double time);

};

#endif
