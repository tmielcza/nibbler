// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Segment.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/06 17:53:12 by rduclos           #+#    #+#             //
//   Updated: 2015/12/02 16:30:59 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SEGMENT_HPP
# define SEGMENT_HPP

# include "AEntity.hpp"


class Segment : public AEntity
{
	protected :

	e_Cardinal		_direction;

	public:

	Segment(void);
	Segment(const Segment & copy);
	Segment(int x, int y, e_Cardinal direction);
	~Segment(void);

	Segment&		operator=(const Segment& ass);
	e_Cardinal		get_Direc(void);
	void			set_Direc(e_Cardinal direc);
};

#endif
