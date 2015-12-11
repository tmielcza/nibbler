// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Displayer.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/09 14:16:22 by tmielcza          #+#    #+#             //
//   Updated: 2015/12/11 20:58:34 by tmielcza         ###   ########.fr       //
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
	if (!this->_font.loadFromFile("resources/Neon.ttf"))
	{
	}
	this->_text.setFont(this->_font);
	this->_text.setCharacterSize(24);
	this->_text.setColor(sf::Color::Red);
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
	this->_texture.display();
	this->_win.draw(this->_sprite);
	this->_win.draw(this->_text);
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

void	Displayer::drawTail(float time, int x, int y, e_Dir last, int id)
{
	sf::Vector2f		pos;

	pos = posOnScreen(x, y) + offsetFromDir(last) * (1 - time);

	this->_tail.setParameter("index", (float)id);
	this->drawSprite(this->_tail, pos, {40, 40}, this->getTime());
}

void	Displayer::drawHead(float time, int x, int y, e_Dir last, int id)
{
	sf::Vector2f		pos;

	pos = posOnScreen(x, y) + offsetFromDir(last) * (1 - time);

	this->_head.setParameter("index", (float)id);
	this->drawSprite(this->_head, pos, {40, 40}, this->getTime());
}

void	Displayer::drawScore(float time, int x, int y, e_Dir last, int score)
{
	sf::Vector2f		pos;

	pos = posOnScreen(x, y) + offsetFromDir(last) * (1 - time);

	this->_text.setPosition(pos);
	this->_text.setString(std::to_string(score));
	this->_win.draw(this->_text);
}

void	Displayer::popWave(int x, int y)
{
	vec2	position = this->posOnScreen(x, y);
	position.x /= this->_win.getSize().x;
	position.y /= this->_win.getSize().y;
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

	this->_walls.push_back(new Wall(position));
}

void	Displayer::popFood(int x, int y)
{
	vec2	position = this->posOnScreen(x, y);

	this->_foods.push_back(new Food(position, this->getTime()));
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

void	Displayer::popChasedFood(int x, int y, int size, float time)
{
	vec2	position = this->posOnScreen(x, y);

	this->_bonuses.push_back(new ChasedFood(position, time, size));
}

void	Displayer::popSlowFood(int x, int y)
{
	vec2	position = this->posOnScreen(x, y);

	this->_bonuses.push_back(new SlowFood(position));
}

void	Displayer::popCutFood(int x, int y)
{
	vec2	position = this->posOnScreen(x, y);

	this->_bonuses.push_back(new CutFood(position));
}

void	Displayer::depopFood(int x, int y)
{
	for (auto it = this->_foods.begin(); it != this->_foods.end(); it++)
	{
		int _x = (int)((*it)->pos.x / 40);
		int _y = (int)((*it)->pos.y / 40);
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
		int _x = (int)((*it)->pos.x / 40);
		int _y = (int)((*it)->pos.y / 40);
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
		int _x = (int)((*it)->pos.x / 40);
		int _y = (int)((*it)->pos.y / 40);
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
