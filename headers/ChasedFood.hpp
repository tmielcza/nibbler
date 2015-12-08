
#ifndef CHASEDFOOD_HPP
# define CHASEDFOOD_HPP

# include "ABonus.hpp"

class ChasedFood : public ABonus
{
	private:

	int		_place;
	int		_maxTime;

	public:

	ChasedFood(void);
	ChasedFood(int value, int x, int y, int place);
	ChasedFood(const ChasedFood & src);
	~ChasedFood(void);

	ChasedFood	&		operator=(const ChasedFood & src);

	void				taken(Snake & snake);
	void				update(double time);
	void				draw(double time);

};

#endif
