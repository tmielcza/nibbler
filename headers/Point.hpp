// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Point.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/05 15:11:29 by rduclos           #+#    #+#             //
//   Updated: 2015/04/08 15:47:23 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef POINT_HPP
# define POINT_HPP

# include <iostream>
# include <string>

struct Point
{
	Point(void);
	Point(const Point& src);
	Point(int x, int y);
	~Point(void);

	Point&		operator=(const Point& rhs);
	bool		operator==(const Point& rhs) const;
	bool		operator!=(const Point& rhs) const;
	Point		operator+(const Point& rhs) const;
	Point		operator-(const Point& rhs) const;
	Point		operator+(const int rhs) const;
	Point		operator-(const int rhs) const;

	int		_x;
	int		_y;
};

#endif // POINT_HPP
