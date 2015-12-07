// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Displayer.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/09 14:16:31 by tmielcza          #+#    #+#             //
//   Updated: 2015/12/07 09:59:52 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef DISPLAYER_HPP
# define DISPLAYER_HPP

//# include <iostream>
# include <chrono>
# include <list>
//# include <map>

# include "SFML/Window.hpp"
# include "SFML/Graphics.hpp"
# include "SFML/OpenGL.hpp"
# include "IDisplayer.hpp"
# include "ADisplayable.hpp"

class	ADisplayable;

typedef	sf::Vector2f vec2;
typedef std::chrono::high_resolution_clock Clock;

class	Displayer : public IDisplayer
{
public:
						Displayer(int width, int height);
						~Displayer(void);

	double				getTime(void) const;
	void				drawSprite(sf::Shader& shad, vec2 pos, vec2 size, float time);
	void				postProcess(sf::Shader& shad);
	double				getDeltaTime(void) const;
	bool				getFoodMode(void);

	void				display(void);
	void				clear(void);
	void				popFood(int x, int y);
	void				popMultiFood(int x, int y);
	void				popSuperFood(int x, int y, int size);
	void				popChasedFood(int x, int y, int size);
	void				depopFood(int x, int y);
	void				updateSuperFood(int x, int y, int size);
	void				switchFoodMode(void);
	vec2				getSize(void) const;
	std::list<e_Input>	getInput(void);
	void				drawTail(float time, int x, int y, e_Dir last);
	void				drawHead(float time, int x, int y, e_Dir last);
	void				putWall(int x, int y);
	void				popWave(int x, int y);
	void				depopWave(ADisplayable* wave);

private:
						Displayer(void);
						Displayer(const Displayer& src);
	double				deltaTime(void);
	static sf::Vector2f	posOnScreen(int x, int y);
	static sf::Vector2f	offsetFromDir(e_Dir dir);

	sf::RenderWindow			_win;

	float						_time;

	sf::RenderTexture			_texture;
	sf::Sprite					_sprite;
	sf::RenderTexture			_tmptexture;
	sf::Sprite					_tmpsprite;

	sf::Shader					_tail;
	sf::Shader					_head;

	Background					_bg;

	float						_delta;

	bool						_isFoodOn;
	std::list<Food*>			_foods;
	std::list<ADisplayable*>	_bonuses;
	std::list<Wall*>			_walls;
	std::list<ADisplayable*>	_waves;
};

extern "C"
IDisplayer*	create(int width, int heigth);

#endif //DISPLAYER_HPP
