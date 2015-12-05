
#ifndef SUPERFOOD_HPP
# define SUPERFOOD_HPP

# include "ABonus.hpp"

class SuperFood : public ABonus
{
	public:

	SuperFood(void);
	SuperFood(int value, int x, int y);
	SuperFood(const SuperFood & src);
	~SuperFood(void);

	SuperFood	&		operator=(const SuperFood & src);

	void				taken(Snake & snake);
	void				update(double time);
	void				draw(double time);

};

#endif
