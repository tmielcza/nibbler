// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Displayer.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/09 14:16:22 by tmielcza          #+#    #+#             //
//   Updated: 2015/12/14 17:09:16 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Displayer.hpp"

Displayer::Displayer(int x, int y)
	: _time(0)
{
	int		wx, wy;
	if (x > 30 || y > 30)
	{
		int		max = x > y ? x : y;
		wx = x * (30 * 40) / max;
		wy = y * (30 * 40) / max;
	}
	else
	{
		wx = x * 40;
		wy = y * 40;
	}
	this->_win = new sf::RenderWindow(sf::VideoMode(wx, wy), "Nibbler");
	this->_bg = new Background(vec2(wx / 2, wy / 2));
	this->_size = {x, y};
	this->_isFoodOn = true;
	this->_tail.loadFromFile("resources/tail.gl", sf::Shader::Fragment);
	this->_head.loadFromFile("resources/head.gl", sf::Shader::Fragment);
	this->_texture.create(wx, wy);
	this->_sprite.setTexture(this->_texture.getTexture());
	this->_tmptexture.create(wx, wy);
	this->_tmpsprite.setTexture(this->_tmptexture.getTexture());
	if (!this->_font.loadFromFile("resources/Neon.ttf"))
	{
	}
	this->_text.setFont(this->_font);
	this->_text.setCharacterSize(24);
	this->_text.setColor(sf::Color::Red);
}

Displayer::~Displayer(void)
{
	this->_win->close();
	delete this->_win;
	delete this->_bg;
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
	return (sf::Vector2f(this->_win->getSize().x, this->_win->getSize().y));
}

void	Displayer::display(void)
{
	for (auto it = _foods.begin(); it != _foods.end(); it++)
	{
		(*it)->draw(*this);
	}
	for (auto bonus : _bonuses)
	{
		bonus->update(*this);
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
	for (auto it = this->_waves.begin(), end = this->_waves.end(); it != end;)
	{
		(*it)->update(*this);
		if ((*it)->isAlive())
			it++;
		else
			it = this->_waves.erase(it);
	}
	for (auto wave : _waves)
	{
		wave->draw(*this);
	}
	this->_win->draw(this->_sprite);
	this->_win->display();
	this->_delta = this->deltaTime();
	this->_time += this->_delta;
}

void	Displayer::clear(void)
{
	this->_texture.clear();
	this->_bg->draw(*this);
	this->_texture.display();
}

void	Displayer::drawSprite(sf::Shader& shad, vec2 pos, vec2 size, float time)
{
	sf::RectangleShape	rectangle(size);
	sf::RenderStates	states;

	shad.setParameter("coord", vec2(pos.x, this->_win->getSize().y - pos.y));
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

bool	Displayer::getFoodMode(void) const
{
	return(this->_isFoodOn);
}

vec2	Displayer::offsetFromDir(e_Dir dir)
{
	static const std::map<e_Dir, vec2> offsets = {
		{Right, {-40, 0}},
		{Left, {40, 0}},
		{Up, {0, -40}},
		{Down, {0, 40}},
	};
	vec2 off = offsets.at(dir);

	off.x = off.x * this->_win->getSize().x / this->_size.x / 40;
	off.y = off.y * this->_win->getSize().y / this->_size.y / 40;
	return (off);
}

vec2	Displayer::posOnScreen(int x, int y)
{
	x = (x * this->_win->getSize().x) / this->_size.x;
	y = (y * this->_win->getSize().y) / this->_size.y;
	x += 20 * this->_win->getSize().x / this->_size.x / 40;
	y += 20 * this->_win->getSize().y / this->_size.y / 40;
	return (vec2(x, y));
}

vec2	Displayer::getSpriteSize(sf::Vector2<int> size) const
{
	return (this->getSpriteSize(size.x, size.y));
}
vec2	Displayer::getSpriteSize(int x, int y) const
{
	x = x * this->_win->getSize().x / this->_size.x / 40;
	y = y * this->_win->getSize().y / this->_size.y / 40;
	return (vec2(x, y));
}

void	Displayer::drawTail(float time, int x, int y, e_Dir last, int id)
{
	vec2	pos;

	pos = posOnScreen(x, y) + offsetFromDir(last) * (1 - time);

	this->_tail.setParameter("index", (float)id);
	this->drawSprite(this->_tail, pos, this->getSpriteSize(40, 40), this->getTime());
}

void	Displayer::drawHead(float time, int x, int y, e_Dir last, int id)
{
	vec2	pos;

	pos = posOnScreen(x, y) + offsetFromDir(last) * (1 - time);

	this->_head.setParameter("index", (float)id);
	this->drawSprite(this->_head, pos, this->getSpriteSize(40, 40), this->getTime());
}

void	Displayer::drawScore(float time, int x, int y, e_Dir last, int score)
{
	vec2	pos = posOnScreen(x, y) + offsetFromDir(last) * (1 - time);

	this->_text.setPosition(pos);
	this->_text.setString(std::to_string(score));
	this->_texture.draw(this->_text);
}

void	Displayer::popWave(int x, int y)
{
	vec2	position = this->posOnScreen(x, y);
	position.x /= this->_win->getSize().x;
	position.y /= this->_win->getSize().y;
	position.y = 1. - position.y;

	this->_waves.push_back(new Wave(position, this->getTime()));
}

void	Displayer::depopWave(ADisplayable* wave)
{
	std::cout << *this->_waves.begin() << std::endl;
	std::cout << wave << std::endl;
	auto it = find(this->_waves.begin(), this->_waves.end(), wave);
	auto a_wave = *it;
	this->_waves.erase(it);
	delete a_wave;
}

void	Displayer::putWall(int x, int y)
{
	vec2	position = this->posOnScreen(x, y);

	this->_walls.push_back(new Wall({x, y}, position));
}

void	Displayer::popFood(int x, int y)
{
	vec2	position = this->posOnScreen(x, y);

	this->_foods.push_back(new Food({x, y}, position, this->getTime()));
}

void	Displayer::popMultiFood(int x, int y)
{
	vec2	position = this->posOnScreen(x, y);

	this->_bonuses.push_back(new MultiFood({x, y}, position, this->getTime()));
}

void	Displayer::popSuperFood(int x, int y, int size)
{
	vec2	position = this->posOnScreen(x, y);

	this->_bonuses.push_back(new SuperFood({x, y}, position, this->getTime(), size));
}

void	Displayer::popChasedFood(int x, int y, int size, float time)
{
	vec2	position = this->posOnScreen(x, y);

	this->_bonuses.push_back(new ChasedFood({x, y}, position, time, size));
}

void	Displayer::popSlowFood(int x, int y)
{
	vec2	position = this->posOnScreen(x, y);

	this->_bonuses.push_back(new SlowFood({x, y}, position));
}

void	Displayer::popCutFood(int x, int y)
{
	vec2	position = this->posOnScreen(x, y);

	this->_bonuses.push_back(new CutFood({x, y}, position));
}

void	Displayer::depopFood(int x, int y)
{
	for (auto it = this->_foods.begin(); it != this->_foods.end(); it++)
	{
		int _x = (int)((*it)->Pos.x);
		int _y = (int)((*it)->Pos.y);
		if (_x == x && _y == y) 
		{
			Food *f = *it;
			this->_foods.erase(it);
			delete f;
			return ;
		}
	}
	for (auto it = this->_bonuses.begin(); it != this->_bonuses.end(); it++)
	{
		int _x = (int)((*it)->Pos.x);
		int _y = (int)((*it)->Pos.y);
		if (_x == x && _y == y)
		{
			delete *it;
			this->_bonuses.erase(it);
			return ;
		}
	}
}

void	Displayer::updateSuperFood(int x, int y, int size)
{
	for (auto it = this->_bonuses.begin(); it != this->_bonuses.end(); it++)
	{
		int _x = (int)((*it)->Pos.x);
		int _y = (int)((*it)->Pos.y);
		if (_x == x && _y == y)
		{
			SuperFood*	super = dynamic_cast<SuperFood*>(*it);
			super->setBranches(this->getTime(), size);
			return ;
		}
	}
}

void	Displayer::switchFoodMode(void)
{
	this->_isFoodOn = !this->_isFoodOn;
}

void	Displayer::setFoodMode(bool state)
{
	this->_isFoodOn = state;
}

std::list<e_Input>	Displayer::getInput(void)
{
	std::list<e_Input>	inputs;
	std::map<sf::Keyboard::Key, e_Input> keys=
		{
			{sf::Keyboard::Key::Up, I_Up1},
			{sf::Keyboard::Key::Down, I_Down1},
			{sf::Keyboard::Key::Left, I_Left1},
			{sf::Keyboard::Key::Right, I_Right1},
			{sf::Keyboard::Key::W, I_Up2},
			{sf::Keyboard::Key::S, I_Down2},
			{sf::Keyboard::Key::A, I_Left2},
			{sf::Keyboard::Key::D, I_Right2},
			{sf::Keyboard::Key::Escape, I_Close},
			{sf::Keyboard::Key::Space, I_Restart},
			{sf::Keyboard::Key::Num1, I_Lib1},
			{sf::Keyboard::Key::Num2, I_Lib2},
			{sf::Keyboard::Key::Num3, I_Lib3},
		};

	sf::Event event;
	while (this->_win->pollEvent(event))
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
			this->_win->close();
		}
	}
	return (inputs);
}

extern "C" IDisplayer* create(int width, int height)
{
	return (new Displayer(width, height));
}
