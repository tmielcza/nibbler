
#ifndef SUPERFOOD_HPP
# define SUPERFOOD_HPP

# include "ABonus.hpp"

class SuperFood : public ABonus
{
	private:

	SuperFood(void);

	public:

	SuperFood(int x, int y);
	SuperFood(const SuperFood & src);
	~SuperFood(void);

	SuperFood	&		operator=(const SuperFood & src);

	void				taken(Snake & snake);
	void				update(double time);
	void				draw(double time);

};

#endif
