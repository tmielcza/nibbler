
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

UsualMode::~UsualMode(void)
{

}

UsualMode	&	UsualMode::operator=(const UsualMode & src)
{
	this->_nbPlayers = src._nbPlayers;
	this->_width = src._width;
	this->_height = src._height;
	return (*this);
}

void			UsualMode::init(void)
{

}

void			UsualMode::run(void)
{

}
