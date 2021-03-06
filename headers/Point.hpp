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

class Point
{
	protected :

	int		_x;
	int		_y;

	public:

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

	int			getX(void) const;
	int			getY(void) const;
	void		setX(int x);
	void		setY(int y);
};

#endif // POINT_HPP
