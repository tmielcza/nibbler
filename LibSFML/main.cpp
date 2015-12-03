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
