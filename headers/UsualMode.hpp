
#ifndef USUALMODE_HPP
# define USUALMODE_HPP

# include "AGameMode.hpp"

class UsualMode : public AGameMode
{
	public:

	UsualMode(void);
	UsualMode(const UsualMode & src);
	UsualMode(int nbplayers, int width, int height);
	~UsualMode(void);

	UsualMode	&	operator=(const UsualMode & src);

	void			init(void);
	void			run(void);
};

#endif
