// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ADisplayable.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/09 15:05:51 by tmielcza          #+#    #+#             //
//   Updated: 2015/12/12 20:38:49 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ADisplayable.hpp"
#include "Displayer.hpp"

// ADisplayable

ADisplayable::ADisplayable(vec2i gridpos, vec2 pos, std::string shaderName, float time)
{
	this->_alive = true;
	this->Pos = gridpos;
	this->pos = {pos.x, pos.y};
	this->_shad.loadFromFile("resources/" + shaderName, sf::Shader::Fragment);
	this->_time = time;
}

ADisplayable::ADisplayable(const ADisplayable& src)
{
	*this = src;
}

ADisplayable&	ADisplayable::operator=(const ADisplayable& rhs)
{
	this->_time = rhs._time;
	this->pos = rhs.pos;
	return (*this);
}

void		ADisplayable::update(Displayer& dis)
{
	(void)dis;
}

bool		ADisplayable::isAlive(void)
{
	return (this->_alive);
}

// Food

Food::Food(vec2i gridpos, vec2 pos, float time)
	: ADisplayable(gridpos, pos, "food.gl", fmod(time, 1))
{

}

void	Food::draw(Displayer& dis)
{
	this->_shad.setParameter("on", dis.getFoodMode());
	dis.drawSprite(this->_shad, this->pos, dis.getSpriteSize(40, 40),
				   fmod(dis.getTime() + this->_time, 1));
}

void	Food::drawOff(Displayer& dis)
{
	this->_shad.setParameter("on", dis.getFoodMode());
	dis.drawSprite(this->_shad, this->pos, dis.getSpriteSize(40, 40),
				   fmod(dis.getTime() + this->_time, 1));
}

// Multi

MultiFood::MultiFood(vec2i gridpos, vec2 pos, float time)
	: ADisplayable(gridpos, pos, "multi.gl", fmod(time, 1))
{
}

void	MultiFood::draw(Displayer& dis)
{
	dis.drawSprite(this->_shad, this->pos, dis.getSpriteSize(40, 40),
				   fmod(dis.getTime() + this->_time, 1));
}

// Super

SuperFood::SuperFood(vec2i gridpos, vec2 pos, float time, float branches)
	: ADisplayable(gridpos, pos, "super.gl", time), _branches(0.f),
	  _time(time)
{
	this->setBranches(time, branches);
}

void	SuperFood::draw(Displayer& dis)
{
	this->_shad.setParameter("branches", this->_branches);
	dis.drawSprite(this->_shad, this->pos, dis.getSpriteSize(40, 40),
				   fmod(dis.getTime() + this->_time, 1));
}

SuperFood::~SuperFood(void)
{
}

SuperFood::SuperFood(const SuperFood& src)
	: ADisplayable(src)
{
	*this = src;
}

SuperFood&	SuperFood::operator=(const SuperFood& rhs)
{
	ADisplayable::operator=(rhs);
	this->_branches = rhs._branches;
	this->_toBranches = rhs._toBranches;
	return (*this);
}

void		SuperFood::setBranches(float time, float branches)
{
	this->_fromBranches = this->_branches;
	this->_toBranches = branches;
	this->_time = time;
}

void		SuperFood::update(Displayer& dis)
{
	(void)dis; // Mieux ?

	float coef = (dis.getTime() - this->_time) * 10.f;
	if (coef <= 1.0f)
		this->_branches = this->_fromBranches * (1 - coef) + this->_toBranches * coef;
	else
		this->_branches = this->_toBranches;
}

// Chased

ChasedFood::ChasedFood(vec2i gridpos, vec2 pos, float total, float size)
	: ADisplayable(gridpos, pos, "chase.gl", 0), _left(total),
	  _total(total), _size((size + 2) * 0.04)
{
}

void	ChasedFood::draw(Displayer& dis)
{
	this->_shad.setParameter("rot", 1 - this->_left / this->_total);
	this->_shad.setParameter("size", this->_size);
	dis.drawSprite(this->_shad, this->pos, dis.getSpriteSize(100, 100),
				   fmod(dis.getTime() + this->_time, 1));
}

ChasedFood::~ChasedFood(void)
{
}

ChasedFood::ChasedFood(const ChasedFood& src)
	: ADisplayable(src)
{
	*this = src;
}

ChasedFood&	ChasedFood::operator=(const ChasedFood& rhs)
{
	ADisplayable::operator=(rhs);
	this->_total = rhs._total;
	this->_left = rhs._left;
	this->_size = rhs._size;
	return (*this);
}

void		ChasedFood::update(Displayer& dis)
{
	this->_left -= dis.getDeltaTime();
	if (this->_left < 0)
	{
		this->_left = 0;
	}
}

// Background

Background::Background(vec2 pos)
	:ADisplayable({0, 0}, pos, "bg.gl", 0)
{
}

void	Background::draw(Displayer& dis)
{
//	std::cout << dis.getTime() << std::endl;
	dis.drawSprite(this->_shad, this->pos, dis.getSize(), fmod(dis.getTime(), 1));
}

// Tail

Tail::~Tail(void)
{
}

Tail::Tail(vec2i gridpos, vec2 pos, vec2 last)
	: ADisplayable(gridpos, pos, "tail.gl", 0.f), _last(last)
{
}

void	Tail::draw(Displayer& dis)
{
	vec2 pos;
	float time = fmod(dis.getTime(), 1.f);

	pos = this->_last * (1.f - time) + this->pos * time;
	dis.drawSprite(this->_shad, pos, {40, 40},
				   fmod(dis.getTime(), 1.));
}

// Head

Head::~Head(void)
{
}

Head::Head(vec2i gridpos, vec2 pos, vec2 last)
	: ADisplayable(gridpos, pos, "resources/head.gl", 0.f), _last(last)
{
}

void	Head::draw(Displayer& dis)
{
	vec2 pos;
	float time = fmod(dis.getTime(), 1.f);

	pos = this->_last * (1.f - time) + this->pos * time;
	dis.drawSprite(this->_shad, pos, dis.getSpriteSize(40, 40), dis.getTime());
}

// Wall

Wall::Wall(vec2i gridpos, vec2 pos)
	: ADisplayable(gridpos, pos, "wall.gl", 0.f)
{
}

void	Wall::draw(Displayer& dis)
{
	dis.drawSprite(this->_shad, this->pos, dis.getSpriteSize(40, 40), 0.f);
}

// Wave

Wave::Wave(vec2 pos, float time)
	: ADisplayable({0, 0}, pos, "take.gl", time)
{
	this->_shad.setParameter("pos", pos);
}

void	Wave::draw(Displayer& dis)
{
	dis.postProcess(this->_shad);
}

void	Wave::update(Displayer& dis)
{
	this->_shad.setParameter("size", dis.getTime() - this->_time);
	if (dis.getTime() - this->_time > 2)
		this->_alive = false;
}

// Slow

SlowFood::SlowFood(vec2i gridpos, vec2 pos)
	: ADisplayable(gridpos, pos, "slow.gl", 0.0f)
{
}

void	SlowFood::draw(Displayer& dis)
{
	dis.drawSprite(this->_shad, this->pos, dis.getSpriteSize(40, 40), dis.getTime());
}

// Cut

CutFood::CutFood(vec2i gridpos, vec2 pos)
	: ADisplayable(gridpos, pos, "cut.gl", 0.0f)
{
}

void	CutFood::draw(Displayer& dis)
{
	dis.drawSprite(this->_shad, this->pos, dis.getSpriteSize(40, 40), dis.getTime());
}
