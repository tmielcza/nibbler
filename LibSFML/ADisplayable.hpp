// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ADisplayable.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/09 15:01:32 by tmielcza          #+#    #+#             //
//   Updated: 2015/12/07 19:55:42 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ADISPLAYABLE_HPP
# define ADISPLAYABLE_HPP

# include <cmath>
# include "SFML/Graphics.hpp"

#include <iostream> // Ta gueule 

typedef	sf::Vector2f vec2;

class	Displayer;

class	ADisplayable
{
public:
					ADisplayable(vec2 pos, std::string shaderName, float time);
					ADisplayable(void);
	virtual			~ADisplayable(void) {}
					ADisplayable(const ADisplayable& src);
	ADisplayable&	operator=(const ADisplayable& rhs);
	virtual void	draw(Displayer& dis) = 0;
	virtual void	update(Displayer& dis);

	vec2		pos;

protected:
	sf::Shader	_shad;
	float		_time;
};

class	Food : public ADisplayable
{
public:
					Food(vec2 pos, float time);
	virtual void	draw(Displayer& dis);
	virtual void	drawOff(Displayer& dis);
};

class	MultiFood : public ADisplayable
{
public:
					MultiFood(vec2 pos, float time);
	virtual void	draw(Displayer& dis);
};

class	SuperFood : public ADisplayable
{
public:
					SuperFood(void);
					~SuperFood(void);
					SuperFood(const SuperFood& src);
	SuperFood&		operator=(const SuperFood& rhs);
	SuperFood(vec2 pos, float time, float branches);
	void			setBranches(float time, float branches);
	virtual void	draw(Displayer& dis);
	void			update(Displayer& dis);

private:
	float			_branches;
	float			_fromBranches;
	float			_toBranches;
	float			_time;
};

class	ChasedFood : public ADisplayable
{
public:
					ChasedFood(void);
					~ChasedFood(void);
					ChasedFood(const ChasedFood& src);
	ChasedFood&		operator=(const ChasedFood& rhs);
					ChasedFood(vec2 pos, float total, float size);
	virtual void	draw(Displayer& dis);
	void			update(Displayer& dis);

private:
	float			_left;
	float			_total;
	float			_size;
};

class	Background : public ADisplayable
{
public:
					Background(vec2 pos);
	virtual void	draw(Displayer& dis);
};

class	Tail : public ADisplayable
{
public:
					Tail(void);
					~Tail(void);
					Tail(const Tail& src);
	Tail&			operator=(const Tail& rhs);

					Tail(vec2 pos, vec2 last);
	virtual void	draw(Displayer& dis);

private:
	vec2			_last;
};

class	Head : public ADisplayable
{
public:
					Head(void);
					~Head(void);
					Head(const Head& src);
	Head&			operator=(const Head& rhs);

					Head(vec2 pos, vec2 last);
	virtual void	draw(Displayer& dis);

private:
	vec2			_last;
};

class	Wall : public ADisplayable
{
public:
					Wall(vec2 pos);
	virtual void	draw(Displayer& dis);
};

class	Wave : public ADisplayable
{
public:
					Wave(vec2 pos, float time);
	virtual void	draw(Displayer& dis);
	void			update(Displayer& dis);
};

#endif // ADISPLAYABLE_HPP
