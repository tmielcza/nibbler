// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Wall.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 16:31:40 by rduclos           #+#    #+#             //
//   Updated: 2015/12/02 16:31:10 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef WALL_HPP
# define WALL_HPP

# include <iostream>
# include <string>
# include "Point.hpp"
# include "AEntity.hpp"

class Wall : public AEntity
{
	public:

	Wall(void);
	~Wall(void);
	Wall(Point pos);
	Wall(int x, int y);
	Wall(Wall const & copy);

	Wall	&	operator=(Wall const & ass);
	void		initWall(int x, int y);
	void		draw(double time);

};

#endif
