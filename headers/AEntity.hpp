// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AEntity.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/04 12:58:05 by rduclos           #+#    #+#             //
//   Updated: 2015/12/03 21:12:54 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AENTITY_HPP
# define AENTITY_HPP

# include "Point.hpp"
# include <iostream>
# include <string>

enum e_Cardinal
{
	None = 0,
	North = 1,
	South = 2,
	East = 4,
	West = 8,
	Longitude = North | South,
	Latitude = East | West
};

class AEntity
{
	protected:

	Point	_pos;
	bool	_eatable;

	public:

	AEntity(void);
	AEntity(AEntity const & copy);
	virtual ~AEntity(void);

	AEntity	&		operator=(AEntity const & ass);

	Point	&		getPos(void);
	void			setPos(Point & set);
	int				getX(void) const;
	int				getY(void) const;
	void			setX(int x);
	void			setY(int y);
	bool			getEatable(void) const;

	virtual void	draw(double time) = 0;

};

#endif
