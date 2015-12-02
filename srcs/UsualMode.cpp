
# include "UsualMode.hpp"

UsualMode::UsualMode(void)
{
	
}

UsualMode::UsualMode(const UsualMode & src)
{
	*this = src;
}

UsualMode::UsualMode(int nbplayers, int width, int height)
{
	this->_nbPlayers = nbplayers;
	this->_width = width;
	this->_height = height;
}
