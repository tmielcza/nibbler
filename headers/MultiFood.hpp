
#ifndef MULTIFOOD_HPP
# define MULTIFOOD_HPP

# include "ABonus.hpp"

class MultiFood : public ABonus
{
	public:

	MultiFood(void);
	MultiFood(int value, int x, int y);
	MultiFood(const MultiFood & src);
	~MultiFood(void);

	MultiFood	&		operator=(const MultiFood & src);

	void				taken(Snake & snake);
	void				update(double time);
	void				draw(double time);

};

#endif
