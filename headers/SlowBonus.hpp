
#ifndef SLOWBONUS_HPP
# define SLOWBONUS_HPP

# include "ABonus.hpp"

class SlowBonus : public ABonus
{
	public:

	SlowBonus(void);
	SlowBonus(int value, int x, int y);
	SlowBonus(const SlowBonus & src);
	~SlowBonus(void);

	SlowBonus	&		operator=(const SlowBonus & src);

	void				taken(Snake & snake);
	void				update(double time);
	void				draw(double time);

};

#endif
