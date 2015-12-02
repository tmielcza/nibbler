#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"

#include<stdio.h>
#include<stdlib.h>

#define SIZEX 640
#define SIZEY 480

#include <iostream>
#include <chrono>
#include <list>
#include <map>

#include "Displayer.hpp"
#include "ADisplayable.hpp"

typedef std::chrono::high_resolution_clock Clock;

double		deltaTime(void)
{
	static auto				last = Clock::now();
	auto					time = Clock::now();
	float					tmp;

	tmp = std::chrono::duration_cast<std::chrono::microseconds>(time - last).count() / 1000000.f;
	last = time;
	return (tmp);
}

/**************************
 *	ReCoPiEr CeTtE mErDe  *
 **************************

void		drawTail(sf::RenderWindow& win, float time, sf::Vector2f pos, sf::Vector2f last, sf::Vector2f next)
{
	sf::Shader			shad;

	shad.loadFromFile("tail.gl", sf::Shader::Fragment);

	pos.x += last.x * 40 * (1 - time);
	pos.y += last.y * 40 * (1 - time);
	(void)next;

	drawSprite(win, shad, pos, {40, 40}, time);
}

void		drawHead(sf::RenderWindow& win, float time, sf::Vector2f pos, sf::Vector2f last)
{
	sf::Shader			shad;

	shad.loadFromFile("head.gl", sf::Shader::Fragment);

	pos.x += last.x * 40 * (1 - time);
	pos.y += last.y * 40 * (1 - time);

	drawSprite(win, shad, pos, {40, 40}, time);
}
*/

void test(void)
{
	Displayer	dis(10, 10);
	Food		food1({80, 80}, 0.3);
	Food		food2({500, 340}, 0.7);
	MultiFood	multi({120, 40}, 0.1);
	SuperFood	super({120, 80}, 0.6, 10);
	ChasedFood	chase({80, 120}, 2, 0.08);
	float		chasedSize = 0;

	while (true)
	{
//		std::list<e_Input>	test = getInput(win);
		dis.clear();
		food1.draw(dis);
		food2.draw(dis);
		multi.draw(dis);

		super.setBranches(10 - floor(fmod(dis.getTime(), 10.)));
		super.update(dis);
		super.draw(dis);

		float	t = floor(dis.getTime() / 2);
		if (chasedSize < t)
		{
			float	posx = 80 + fmod(t, 5.) * 40;
			chasedSize += 1;
			chase = ChasedFood({posx, 120}, 2, (fmod(chasedSize, 5.) + 2) * 0.04);
		}
		chase.update(dis);
		chase.draw(dis);

		dis.display();
	}
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	test();

	return 0;
}
