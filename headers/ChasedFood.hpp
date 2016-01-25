// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ChasedFood.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/25 18:13:34 by rduclos           #+#    #+#             //
//   Updated: 2016/01/25 18:13:35 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CHASEDFOOD_HPP
# define CHASEDFOOD_HPP

# include "ABonus.hpp"

class ChasedFood : public ABonus
{
	private:

	int		_place;
	int		_maxTime;

	public:

	ChasedFood(void);
	ChasedFood(int value, int x, int y, int place, bool spawner);
	ChasedFood(const ChasedFood & src);
	~ChasedFood(void);

	ChasedFood	&		operator=(const ChasedFood & src);

	void				taken(Snake & snake);
	void				update(double time);
	void				draw(double time);
	char				*sendPos(void);
	char				*sendPosNext(void);

};

#endif
