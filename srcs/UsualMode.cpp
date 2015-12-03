
# include "UsualMode.hpp"

UsualMode::UsualMode(void)
{
	this->_nbPlayers = 1;
	this->_width = 100;
	this->_height = 100;
	this->_speed = 1;
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
	this->_speed = 1;
}

UsualMode::~UsualMode(void)
{

}

UsualMode	&	UsualMode::operator=(const UsualMode & src)
{
	this->_nbPlayers = src._nbPlayers;
	this->_width = src._width;
	this->_height = src._height;
	this->_speed = src._speed;
	return (*this);
}

void			UsualMode::init(void)
{
	int		height = MapManager::Instance().getHeight();
	int		width = MapManager::Instance().getWidth();

	for (int i = 0; i < height; i++)
		MapManager::Instance().setWall(i, width - 1);
	for (int i = 0; i < height; i++)
		MapManager::Instance().setWall(i, 0);
	for (int i = 0; i < width; i++)
		MapManager::Instance().setWall(i, height - 1);
	for (int i = 0; i < width; i++)
		MapManager::Instance().setWall(i, 0);
}

void			UsualMode::run(void)
{

}
