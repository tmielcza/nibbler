
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
