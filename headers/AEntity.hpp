// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AEntity.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/04 12:58:05 by rduclos           #+#    #+#             //
//   Updated: 2015/04/07 15:06:42 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AENTITY_HPP
# define AENTITY_HPP

# include "Point.hpp"
# include <iostream>
# include <string>

class AEntity
{
	protected:

	Point	_pos;

	public:

	AEntity(void);
	AEntity(AEntity const & copy);
	~AEntity(void);

	AEntity	&	operator=(AEntity const & ass);

	Point	&	getPos(void);
	int			getX(void) const;
	int			getY(void) const;
	void		setX(int x);
	void		setY(int y);

};

#endif
