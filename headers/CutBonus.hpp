
#ifndef CUTBONUS_HPP
# define CUTBONUS_HPP

# include "ABonus.hpp"

class CutBonus : public ABonus
{
	public:

	CutBonus(void);
	CutBonus(int value, int x, int y);
	CutBonus(const CutBonus & src);
	~CutBonus(void);

	CutBonus	&		operator=(const CutBonus & src);

	void				taken(Snake & snake);
	void				update(double time);
	void				draw(double time);

};

#endif
