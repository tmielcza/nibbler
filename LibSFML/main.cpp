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
	Head		tail1({80, 150}, {120, 150});
	Head		tail2({120, 150}, {120, 190});
	Head		tail3({120, 190}, {80, 190});
	Head		head({80, 190}, {80, 150});
	Wall		wall1({40, 40});
	Wall		wall2({40, 80});
	float		chasedSize = 0;

	while (true)
	{
//		std::list<e_Input>	test = getInput(win);
		dis.clear();
		food1.draw(dis);
		food2.draw(dis);
		multi.draw(dis);
		tail1.draw(dis);
		tail2.draw(dis);
		tail3.draw(dis);
		head.draw(dis);
		wall1.draw(dis);
		wall2.draw(dis);

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

void test2(void)
{
	Displayer	dis(10, 10);

	for (int i = 0; i < 9; i++)
	{
		dis.putWall(0, i);
		dis.putWall(i, 9);
		dis.putWall(9, 9 - i);
		dis.putWall(9 - i, 0);
	}

	dis.popFood(2, 2);
	dis.popFood(3, 2);
	float last;

	while (true)
	{
//		std::list<e_Input>	test = getInput(win);
		dis.clear();

		float	t = floor(dis.getTime() / 2);
		if ((int)t % 2 == 0 && t != last)
		{
			last = t;
			printf("Food Mode Changed\n");
			dis.switchFoodMode();
		}
		dis.display();
	}
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	test2();

	return 0;
}
