// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Displayer.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/09 14:16:22 by tmielcza          #+#    #+#             //
//   Updated: 2015/12/06 19:31:56 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Displayer.hpp"

Displayer::Displayer(int x, int y)
	: _win(sf::VideoMode(x * 40, y * 40), "Nibbler"), _time(0), _bg(sf::Vector2f(x * 20, y * 20))
{
	this->_isFoodOn = true;
	this->_tail.loadFromFile("resources/tail.gl", sf::Shader::Fragment);
	this->_head.loadFromFile("resources/head.gl", sf::Shader::Fragment);
	this->_texture.create(x * 40, y * 40);
	this->_sprite.setTexture(this->_texture.getTexture());
	this->_tmptexture.create(x * 40, y * 40);
	this->_tmpsprite.setTexture(this->_tmptexture.getTexture());
}

Displayer::~Displayer(void)
{
	this->_win.close();
}

double	Displayer::deltaTime(void)
{
	static auto				last = Clock::now();
	auto					time = Clock::now();
	float					tmp;

	tmp = std::chrono::duration_cast<std::chrono::microseconds>(time - last).count() / 1000000.f;
	last = time;
	return (tmp);
}

double	Displayer::getDeltaTime(void) const
{
	return (this->_delta);
}

double	Displayer::getTime(void) const
{
	return (this->_time);
}

vec2	Displayer::getSize(void) const
{
	return (sf::Vector2f(this->_win.getSize().x, this->_win.getSize().y));
}

void	Displayer::display(void)
{
/*
	sf::Shader sha;
	sha.loadFromFile("resources/take.gl", sf::Shader::Fragment);
	sha.setParameter("pos", sf::Vector2f(0.3, 0.9));
	sha.setParameter("size", fmod(this->_time, 2));

	sf::Shader sha2;
	sha2.loadFromFile("resources/take.gl", sf::Shader::Fragment);
	sha2.setParameter("pos", sf::Vector2f(0.0, 1.0));
	sha2.setParameter("size", fmod(this->_time + 0.4, 2));
//*/

	this->postProcess(sha);
	this->postProcess(sha2);

	for (auto it = _foods.begin(); it != _foods.end(); it++)
	{
		(*it)->draw(*this);
	}
	for (auto it = _bonuses.begin(); it != _bonuses.end(); it++)
	{
		(*it)->draw(*this);
	}
	for (auto wall : _walls)
	{
		wall->draw(*this);
	}

	this->_texture.display();
	this->_win.draw(this->_sprite);
	this->_win.display();
	this->_delta = this->deltaTime();
	this->_time += this->_delta;
}

void	Displayer::clear(void)
{
	this->_texture.clear();
	this->_bg.draw(*this);
	this->_texture.display();
}

void	Displayer::drawSprite(sf::Shader& shad, vec2 pos, vec2 size, float time)
{
	sf::RectangleShape	rectangle(size);
	sf::RenderStates	states;

	shad.setParameter("coord", vec2(pos.x, this->_win.getSize().y - pos.y));
	shad.setParameter("resolution", size);
	shad.setParameter("time", time);
	rectangle.move(pos - size / 2.0f);
	states.shader = &shad;
	this->_texture.draw(rectangle, states);
}

void	Displayer::postProcess(sf::Shader& shad)
{
	sf::RenderStates	states;

	states.shader = &shad;
	this->_tmptexture.draw(this->_sprite, states);
	this->_tmptexture.display();
	this->_texture.draw(this->_tmpsprite);
	this->_texture.display();
}

bool	Displayer::getFoodMode(void)
{
	return(this->_isFoodOn);
}

sf::Vector2f	Displayer::offsetFromDir(e_Dir dir)
{
	static const std::map<e_Dir, sf::Vector2f> offsets = {
		{Right, {-40, 0}},
		{Left, {40, 0}},
		{Up, {0, -40}},
		{Down, {0, 40}},
	};

	return (offsets.at(dir));
}

sf::Vector2f	Displayer::posOnScreen(int x, int y)
{
	return (sf::Vector2f(x * 40 + 20, y * 40 + 20));
}

void	Displayer::drawTail(float time, int x, int y, e_Dir last)
{
	sf::Vector2f		pos;

	pos = posOnScreen(x, y) + offsetFromDir(last) * (1 - time);

	this->drawSprite(this->_tail, pos, {40, 40}, this->getTime());
}

void	Displayer::drawHead(float time, int x, int y, e_Dir last)
{
	sf::Vector2f		pos;

	pos = posOnScreen(x, y) + offsetFromDir(last) * (1 - time);

	this->drawSprite(this->_head, pos, {40, 40}, this->getTime());
}

void	Displayer::putWall(int x, int y)
{
	vec2	position = this->posOnScreen(x, y);

	this->_walls.push_back(new Wall(position));
}

void	Displayer::popFood(int x, int y)
{
	vec2	position = this->posOnScreen(x, y);

	this->_foods.push_back(new Food(position, x, y, this->getTime()));
}

void	Displayer::popMultiFood(int x, int y)
{
	vec2	position = this->posOnScreen(x, y);

	this->_bonuses.push_back(new MultiFood(position, this->getTime()));
}

void	Displayer::popSuperFood(int x, int y, int size)
{
	vec2	position = this->posOnScreen(x, y);

	this->_bonuses.push_back(new SuperFood(position, this->getTime(), size));
}

void	Displayer::popChasedFood(int x, int y, int size)
{
	vec2	position = this->posOnScreen(x, y);

	this->_bonuses.push_back(new ChasedFood(position, this->getTime(), size));
}

void	Displayer::depopFood(int x, int y)
{
	int i = 0;
	std::cout << "Try to erase food from gfx ..." << std::endl;
	for (auto it = this->_foods.begin(); it != this->_foods.end(); it++)
	{
		i++;
		int _x = (int)((*it)->getX());
		int _y = (int)((*it)->getY());
		std::cout << "Trying number " << i << " : x:" << _x << "-" << x;
		std::cout << " y:" << _y << "-" << y << std::endl;
		if ((*it)->getX() == x && (*it)->getY() == y) 
		{
			std::cout << "Erase Food from GFX" << std::endl;
			Food *f = *it;
			this->_foods.erase(it);
			delete f;
			return ;
		}
	}
/*
	for (auto it = this->_bonuses.begin(); it != this->_bonuses.end(); it++) {
		if ( (*it)->pos.x == x && (*it)->pos.y == y) {
			delete *it;
			this->_bonuses.erase(it);
			return ;
		}
	}
*/
}

void	Displayer::updateSuperFood(int x, int y, int size)
{
	for (auto it = this->_bonuses.begin(); it != this->_bonuses.end(); it++) {
		if ( (*it)->pos.x == x && (*it)->pos.y == y) {
			SuperFood*	super = dynamic_cast<SuperFood*>(*it);
			super->setBranches(size);
			return ;
		}
	}
}

void	Displayer::switchFoodMode(void)
{
	this->_isFoodOn = !this->_isFoodOn;
}

std::list<e_Input>	Displayer::getInput(void)
{
	std::list<e_Input>	inputs;
	std::map<sf::Keyboard::Key, e_Input> keys=
		{
			{sf::Keyboard::Key::Up, I_Up},
			{sf::Keyboard::Key::Down, I_Down},
			{sf::Keyboard::Key::Left, I_Left},
			{sf::Keyboard::Key::Right, I_Right},
			{sf::Keyboard::Key::Num1, I_Lib1},
			{sf::Keyboard::Key::Num2, I_Lib2},
			{sf::Keyboard::Key::Num3, I_Lib3},
		};

	sf::Event event;
	while (this->_win.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			auto	it = keys.find(event.key.code);
			if (it != keys.end())
			{
				inputs.push_back(it->second);
			}
		}
		if (event.type == sf::Event::Closed)
		{
			this->_win.close();
		}
	}
	return (inputs);
}

extern "C" IDisplayer* create(int width, int height)
{
	return (new Displayer(width, height));
}
