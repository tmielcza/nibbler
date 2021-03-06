// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Snake.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/03 17:52:27 by rduclos           #+#    #+#             //
//   Updated: 2016/01/25 19:38:29 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Snake.hpp"
#include "MapManager.hpp"
#include "GraphicsManager.hpp"

int		Snake::_curIndex = 0;

Snake::Snake(void) : _index(Snake::_curIndex++)
{
	this->_score = 0;
	this->_nbmove = 0;
	this->_speed = 4;
	this->_slow = 0.;
	this->_alive = true;
	this->_client = true;
	this->_local = true;
	this->_increm = 0.35;
	this->_tosend = "";
	this->_cycles = 0;
	this->init();
}

Snake::Snake(bool client, bool local) : _index(Snake::_curIndex++)
{
	this->_score = 0;
	this->_nbmove = 0;
	this->_cycles = 0;
	this->_speed = 4;
	this->_alive = true;
	this->_client = client;
	this->_local = local;
	this->_increm = 0.35;
	this->_slow = 0.;
	this->_tosend = "";
	this->init();
}

Snake::Snake(e_Cardinal direction, int x, int y, bool client, bool local, int index)
  : _index(index)
{
	this->_score = 0;
	this->_nbmove = 0;
	this->_cycles = 0;
	this->_speed = 4;
	this->_increm = 0.35;
	this->_tosend = "";
	this->init(direction, x, y);
	this->_alive = true;
	this->_client = client;
	this->_local = local;
}

Snake::~Snake(void)
{
	if (this->_snake.size() > 0)
	{
		std::list<Segment*>::iterator		tmp = this->_snake.begin();
		std::list<Segment*>::iterator		end = this->_snake.end();
		
		std::cout << "Destroying Snake : " << this->_index << std::endl;
		while (tmp != end)
		{
			if ((*tmp) != NULL)
			{
				Segment *s = *tmp;
				int x = s->getX();
				int y = s->getY();
				MapManager::Instance()._Map[x][y] = NULL;
				this->_snake.erase(tmp);
				delete s;
			}
			else
				this->_snake.remove((*tmp));
			tmp = this->_snake.begin();
		}
	}
	MapManager::Instance().removeSnake(this);
}

bool							Snake::check_place_snake(int x, int y)
{
	bool		good = true;

	if (MapManager::Instance()._Map[x][y] != NULL)
		good = false;
	if (MapManager::Instance()._Map[x - 1][y] != NULL)
		good = false;
	if (MapManager::Instance()._Map[x - 2][y] != NULL)
		good = false;
	if (MapManager::Instance()._Map[x - 3][y] != NULL)
		good = false;
	if (y > 0 && MapManager::Instance()._Map[x][y - 1] != NULL)
		good = false;
	if (y < MapManager::Instance().getHeight() - 1 &&
		MapManager::Instance()._Map[x][y + 1] != NULL)
		good = false;
	return (good);
}

void							Snake::init(void)
{
	int		width = MapManager::Instance().getWidth();
	int		height = MapManager::Instance().getHeight();
	int		x = (width - (width - (width / 4)));
	int		y = (rand() % height);

	while (check_place_snake(x, y) == false)
		y = rand() % height;
	this->init(East, x, y);
}

void							Snake::init(e_Cardinal direction, int x, int y)
{
	Segment		*seg;

	std::cout << "Creating Snake in init Index : " << this->_index;
	std::cout << " at pos " << x << "-" << y << " direction " << direction << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (x < 0)
			x = MapManager::Instance().getWidth() - 1;
		else if (x >= MapManager::Instance().getWidth())
			x = 0;
		if (y < 0)
			y = MapManager::Instance().getHeight() - 1;
		else if (y >= MapManager::Instance().getHeight())
			y = 0;
		seg = new Segment(x, y, direction, this->_index);
		this->_snake.push_back(seg);
		MapManager::Instance()._Map[x][y] = seg;
		if (seg->get_Direc() == North)
			y--;
		else if (seg->get_Direc() == South)
			y++;
		else if (seg->get_Direc() == East)
			x--;
		else if (seg->get_Direc() == West)
			x++;
	}
	this->_tail = seg;

}

std::list<Segment*>	&			Snake::get_snake(void)
{
	return (this->_snake);
}


void							Snake::add_to_tail(void)
{
	e_Cardinal			e = this->_tail->get_Direc();
	int					x = this->_tail->getX();
	int					y = this->_tail->getY();

	Segment *seg = new Segment(x, y, e, this->_index);
//	MapManager::Instance()._Map[x][y] = seg;
	this->_snake.push_back(seg);
	this->_tail = seg;
}

void							Snake::add_score(int score)
{
	this->_score += score;
}

void							Snake::befor_move(void)
{
	std::list<Segment*>::iterator		head = this->_snake.begin();
	int x = (*head)->getX();
	int y = (*head)->getY();


	e_Cardinal direc = (*head)->get_Direc();
	if (this->_cycles < 1000)
		this->_cycles++;
	else
		this->_cycles = 0;
	if (direc == North)
	{
		y++;
		if (y >= MapManager::Instance().getHeight())
			y = 0;
	}
	else if (direc == South)
	{
		y--;
		if (y < 0)
			y = MapManager::Instance().getHeight() - 1;
	}
	else if (direc == East)
	{
		x++;
		if (x >= MapManager::Instance().getWidth())
			x = 0;
	}
	else if (direc == West)
	{
		x--;
		if (x < 0)
			x = MapManager::Instance().getWidth() - 1;
	}
	if (MapManager::Instance()._Map[x][y] != NULL)
	{
		if (MapManager::Instance()._Map[x][y]->getEatable() == false)
		{
			if (this->_local == true && MapManager::Instance()._Map[x][y] != this->_tail)
				this->_alive = false;
			if (this->_alive == false)
			{
				this->_tosend = "DS";
				this->_tosend += std::to_string(this->_index);
				if (dynamic_cast<Segment *>(MapManager::Instance()._Map[x][y]))
					std::cout << "Dead by a Segment : ";
				else if (dynamic_cast<Wall *>(MapManager::Instance()._Map[x][y]))
					std::cout << "Dead by a Wall : ";
				else
					std::cout << "Dead by an unknown AEntity : ";
			}
		}
		else
		{
			if (this->_local == true)
			{
				if (dynamic_cast<Food*>(MapManager::Instance()._Map[x][y]))
					this->eat(*dynamic_cast<Food *>(MapManager::Instance()._Map[x][y]));
				else if (dynamic_cast<ABonus*>(MapManager::Instance()._Map[x][y]))
					this->take_bonus(*dynamic_cast<ABonus *>(MapManager::Instance()._Map[x][y]));
			}
		}
	}
}

void							Snake::move(void)
{
	std::list<Segment*>::iterator		seg = this->_snake.begin();
	std::list<Segment*>::iterator		end = this->_snake.end();
	int									x = (*seg)->getX();
	int									y = (*seg)->getY();
	Point								tmp = (*seg)->getPos();
	e_Cardinal							direc = (*seg)->get_Direc();

	if (this->_alive == true)
	{
		MapManager::Instance()._Map[x][y] = NULL;
		if (direc == North)
		{
			y = (*seg)->getY() + 1;
			if (y >= MapManager::Instance().getHeight())
				y = 0;
			(*seg)->setY(y);
		}
		else if (direc == South)
		{
			y = (*seg)->getY() - 1;
			if (y < 0)
				y = MapManager::Instance().getHeight() - 1;
			(*seg)->setY(y);
		}
		else if (direc == East)
		{
			x = (*seg)->getX() + 1;
			if (x >= MapManager::Instance().getWidth())
				x = 0;
			(*seg)->setX(x);
		}
		else if (direc == West)
		{
			x = (*seg)->getX() - 1;
			if (x < 0)
				x = MapManager::Instance().getWidth() - 1;
			(*seg)->setX(x);
		}
		x = (*seg)->getX();
		y = (*seg)->getY();
		MapManager::Instance()._Map[x][y] = (*seg);
		seg++;
		while (seg != end)
		{
			Point tmp2 = (*seg)->getPos();
			(*seg)->setPos(tmp);
			MapManager::Instance()._Map[tmp2.getX()][tmp2.getY()] = NULL;
			MapManager::Instance()._Map[tmp.getX()][tmp.getY()] = (*seg);
			tmp = tmp2;
			seg++;
		}
		if (this->_slow > 0)
		{
			double tmp = this->_slow / 100 * 5;
			this->_slow -= tmp;
			this->_speed += tmp;
			if (this->_slow <= 0.01)
			{
				this->_speed += this->_slow;
				this->_slow = 0;
			}
		}
	}
}

void							Snake::turn(e_Cardinal direction)
{
	Segment*	head = *(this->_snake.begin());
	
	if (head->get_Direc() & Latitude)
		if (direction & Longitude)
		{
			if (direction == North)
				direction = South;
			else
				direction = North;
			head->set_Direc(direction);
		}
	if (head->get_Direc() & Longitude)
		if (direction & Latitude)
			head->set_Direc(direction);
	if (this->_nbmove == -1)
		this->_nbmove = 0;
	this->_nbmove++;
	if (this->_local == true && this->_nbmove == 3)
		GraphicsManager::Instance().switchFoodMode();
}

void							Snake::turn_left(void)
{
	std::list<Segment*>::iterator	head = this->_snake.begin();

	if (this->_nbmove == -1)
		this->_nbmove = 0;
	if ((*head)->get_Direc() == North)
		(*head)->set_Direc(West);
	else if ((*head)->get_Direc() == South)
		(*head)->set_Direc(East);
	else if ((*head)->get_Direc() == East)
		(*head)->set_Direc(North);
	else if ((*head)->get_Direc() == West)
		(*head)->set_Direc(South);
	this->_nbmove++;
}

void							Snake::turn_right(void)
{
	std::list<Segment*>::iterator	head = this->_snake.begin();

	if (this->_nbmove == -1)
		this->_nbmove = 0;
	if ((*head)->get_Direc() == North)
		(*head)->set_Direc(East);
	else if ((*head)->get_Direc() == South)
		(*head)->set_Direc(West);
	else if ((*head)->get_Direc() == East)
		(*head)->set_Direc(South);
	else if ((*head)->get_Direc() == West)
		(*head)->set_Direc(North);
	this->_nbmove++;
}

void							Snake::eat(Food const & eaten)
{
	int x = this->getHeadSnakeX();
	int y = this->getHeadSnakeY();
	GraphicsManager::Instance().popWave(x, y);
	this->add_to_tail();
	this->_tosend = "EFS";
	this->_tosend += std::to_string(this->_index);
	this->_tosend += "-";
	this->_tosend += std::to_string(eaten.getX());
	this->_tosend += "-";
	this->_tosend += std::to_string(eaten.getY());
	if (this->_nbmove <= 2 && this->_nbmove >= 0)
		this->add_score(eaten.get_value() * 2);
	else
		this->add_score(eaten.get_value());
	this->_speed += this->_increm;
	if (this->_increm > 0.05)
		this->_increm -= 0.01;
	if (this->_increm < 0.05)
		this->_increm = 0.05;
	if (this->_client == true && eaten.getSpawner() == true)
		MapManager::Instance().foodpop(true);
	eaten.eaten(*this);
	if (this->_local == true && this->_nbmove > 2)
		GraphicsManager::Instance().switchFoodMode();
	this->_nbmove = 0;
}

void							Snake::take_bonus(ABonus & taken)
{
	taken.taken(*this);
	this->_nbmove = 0;
	GraphicsManager::Instance().setFoodMode(true);
	this->_tosend = "EBS";
	this->_tosend += std::to_string(this->_index);
	this->_tosend += "-";
	this->_tosend += std::to_string(taken.getX());
	this->_tosend += "-";
	this->_tosend += std::to_string(taken.getY());
}

e_Cardinal						Snake::getHeadSnakeDirec(void)
{
	std::list<Segment*>::iterator			head = this->_snake.begin();
	std::list<Segment*>::iterator			end = this->_snake.end();

	if (head != end && (*head) != NULL)
		return ((*head)->get_Direc());
	else
	{
		std::cout << "FUCKING SHIT : " << this->_index << std::endl;
		return ((e_Cardinal)0);
	}
}
int								Snake::getHeadSnakeX(void)
{
	std::list<Segment*>::iterator			head = this->_snake.begin();
	std::list<Segment*>::iterator			end = this->_snake.end();

	if (head != end && (*head) != NULL)
		return ((*head)->getX());
	else
	{
		std::cout << "FUCKING SHIT : " << this->_index << std::endl;
		return 0;
	}
}

int								Snake::getHeadSnakeY(void)
{
	std::list<Segment*>::iterator			head = this->_snake.begin();
	std::list<Segment*>::iterator			end = this->_snake.end();

	if (head != end && (*head) != NULL)
		return ((*head)->getY());
	else
	{
		std::cout << "FUCKING SHIT : " << this->_index << std::endl;
		return 0;
	}
}

void							Snake::setHeadSnakeX(int x)
{
	std::list<Segment*>::iterator			head = this->_snake.begin();
	std::list<Segment*>::iterator			end = this->_snake.end();

	if (head != end && (*head) != NULL)
	{
		int _x = (*head)->getX();
		int _y = (*head)->getY();
		MapManager::Instance()._Map[_x][_y] = NULL;
		(*head)->setX(x);
		MapManager::Instance()._Map[x][_y] = (*head);
	}
	else
		std::cout << "FUCKING SHIT : " << this->_index << std::endl;
}

void							Snake::setHeadSnakeY(int y)
{
	std::list<Segment*>::iterator			head = this->_snake.begin();
	std::list<Segment*>::iterator			end = this->_snake.end();

	if (head != end && (*head) != NULL)
	{
		int _x = (*head)->getX();
		int _y = (*head)->getY();
		MapManager::Instance()._Map[_x][_y] = NULL;
		(*head)->setY(y);
		MapManager::Instance()._Map[_x][y] = (*head);
	}
	else
		std::cout << "FUCKING SHIT : " << this->_index << std::endl;

}

void							Snake::setHeadSnakeDirec(e_Cardinal direc)
{
	std::list<Segment*>::iterator			head = this->_snake.begin();
	std::list<Segment*>::iterator			end = this->_snake.end();

	if (head != end && (*head) != NULL)
	{
		if ((*head)->get_Direc() != direc)
		{
			this->_nbmove++;
			(*head)->set_Direc(direc);
			
		}
	}
	else
		std::cout << "FUCKING SHIT : " << this->_index << std::endl;
}

void							Snake::setScore(int score)
{
	this->_score = score;
}

int								Snake::getIndex(void)
{
	return (this->_index);
}

double							Snake::getSpeed(void)
{
	return (this->_speed);
}

int								Snake::getScore(void)
{
	return (this->_score);
}

int								Snake::getCycles(void)
{
	return (this->_cycles);
}

void							Snake::setCycles(int cycle)
{
	this->_cycles = cycle;
}

bool							Snake::IsAlive(void)
{
	return (this->_alive);
}

void							Snake::SetAlive(bool alive)
{
	this->_alive = alive;
}

void							Snake::draw(double time)
{
	float x, y;

	(void)time;
	x = this->getHeadSnakeX();
	y = this->getHeadSnakeY();
	auto it = this->_snake.begin();
	GraphicsManager::Instance().drawHead(time, x, y, (e_Dir)(*it)->get_Direc(), this->_index);
	it++;
	for (auto end = this->_snake.end(); it != end; it++)
	{
		(*it)->draw(time);
	}
}

void							Snake::update_directions(void)
{
	auto it = this->_snake.begin();
	e_Cardinal last_dir = (*it)->get_Direc();
	e_Cardinal tmp_dir;

	it++;
	for (auto end = this->_snake.end(); it != end; it++)
	{
		tmp_dir = (*it)->get_Direc();
		(*it)->set_Direc(last_dir);
		last_dir = tmp_dir;
	}
}

void		Snake::Slow(double less)
{
	double tmp = ((this->_speed / 100) * less);
	this->_slow = tmp / 2;
	this->_speed -= tmp;
}

void		Snake::Cut(size_t less)
{
	size_t c = (this->_snake.size() / less);
	size_t p = this->_snake.size() - c;
	while (p < this->_snake.size())
	{
		std::list<Segment *>::iterator		seg = this->_snake.begin();
		size_t tmp = p;
		while (tmp > 0)
		{
			seg++;
			tmp--;
		}
		Segment *s = *seg;
		MapManager::Instance()._Map[s->getX()][s->getY()] = NULL;
		this->_snake.erase(seg);
		delete s;
	}
	std::list<Segment *>::iterator		seg = this->_snake.begin();
	std::list<Segment *>::iterator		end = this->_snake.end();
	while (seg != end)
	{
		this->_tail = *seg;
		seg++;
	}
}

char		*Snake::takeToSend(void)
{
	if (this->_tosend == "")
		return NULL;
	return ((char *)this->_tosend.c_str());
}

void		Snake::ClearToSend(void)
{
	this->_tosend = "";
}

void		Snake::add_Cycle(int cycle, int x, int y, int direc)
{
	t_MC	*tmp = new t_MC;

	tmp->cycle = cycle;
	tmp->x = x;
	tmp->y = y;
	tmp->direc = direc;
	this->_msgCycles.push_back(tmp);
//	std::cout << "Creating MSG Cycle n" << cycle << " at " << x << "-" << y << std::endl;
}

void		Snake::Verify_Snake(char *tmp)
{
	std::list<Segment*>::iterator		sbegin = this->_snake.begin();
	std::list<Segment*>::iterator		send = this->_snake.end();
	int				i = 0;
	int				score;
	int				nbmove;
	double			speed;
	int				x;
	int				y;
	int				direc;

	while (tmp[i] != '\0' && (tmp[i] < '0' || tmp[i] > '9'))
		i++;
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	score = atoi(tmp + i);
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	nbmove = atoi(tmp + i);
	while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	i++;
	speed = atof(tmp + i);
	while ((tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9') || tmp[i] == '.')
		i++;
	i++;
	if (this->_score != score)
		this->_score = score;
	if (this->_nbmove != nbmove)
		this->_nbmove = nbmove;
	if (this->_speed != speed)
		this->_speed = speed;
	while (tmp[i] != '\0')
	{
		x = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		if (tmp[i] != '\0')
			i++;
		y = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		if (tmp[i] != '\0')
			i++;
		direc = atoi(tmp + i);
		while (tmp[i] != '\0' && tmp[i] >= '0' && tmp[i] <= '9')
			i++;
		if (tmp[i] != '\0')
			i++;
		if (sbegin != send)
		{
			if ((*sbegin)->getX() != x)
			{
				int _x = (*sbegin)->getX();
				int _y = (*sbegin)->getY();
				MapManager::Instance()._Map[_x][_y] = NULL;
				(*sbegin)->setX(x);
				MapManager::Instance()._Map[x][_y] = (*sbegin);
			}
			if ((*sbegin)->getX() != y)
			{
				int _x = (*sbegin)->getX();
				int _y = (*sbegin)->getY();
				MapManager::Instance()._Map[_x][_y] = NULL;
				(*sbegin)->setY(y);
				MapManager::Instance()._Map[_x][y] = (*sbegin);
			}
			if ((*sbegin)->get_Direc() != (e_Cardinal)direc)
				(*sbegin)->set_Direc((e_Cardinal)direc);
			sbegin++;
		}
/*
		else
		{
			Segment *seg = new Segment(x, y, (e_Cardinal)direc, this->_index);
			this->_snake.push_back(seg);
			MapManager::Instance()._Map[x][y] = seg;
		}
*/
	}
}

std::string	Snake::make_vtosend(void)
{
	std::list<Segment*>::iterator		sbegin = this->_snake.begin();
	std::list<Segment*>::iterator		send = this->_snake.end();
	std::string		tmp;

	tmp = "VS";
	tmp += std::to_string(this->_index) + "_";
	tmp += std::to_string(this->_score) + "_";
	tmp += std::to_string(this->_nbmove) + "_";
	tmp += std::to_string(this->_speed) + "_";
	while (sbegin != send)
	{
		if ((*sbegin) != this->_tail)
		{
			tmp += std::to_string((*sbegin)->getX()) + "_";
			tmp += std::to_string((*sbegin)->getY()) + "_";
			tmp += std::to_string((*sbegin)->get_Direc()) + "_";
		}
		else
		{
			tmp += std::to_string((*sbegin)->getX()) + "_";
			tmp += std::to_string((*sbegin)->getY()) + "_";
			tmp += std::to_string((*sbegin)->get_Direc());
		}
		sbegin++;
	}
	return (tmp);
}
