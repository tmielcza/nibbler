// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Wall.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 16:31:40 by rduclos           #+#    #+#             //
//   Updated: 2015/04/05 18:12:43 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef WALL_HPP
# define WALL_HPP

# include <iostream>
# include <string>
# include "Point.hpp"

class Wall
{
	private:

	Point	_size;

	Wall(Wall const & copy);

	Wall	&	operator=(Wall const & ass);

	public:

	Wall(void);
	Wall(Point size);
	Wall(int width, int height);
	~Wall(void);

	void	initWall(int width, int height);
	int		getWidth(void) const;
	int		getHeight(void) const;
	Point	getSize(void) const;
};

#endif
