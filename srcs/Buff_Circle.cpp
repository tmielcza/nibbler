// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Buff_Circle.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/25 18:10:06 by rduclos           #+#    #+#             //
//   Updated: 2016/01/25 18:10:06 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Buff_Circle.hpp"

Buff_Circle::Buff_Circle(void)
{
	bzero(bc_start, BC_SIZE + 1);
	bc_end = bc_start + BC_SIZE;
	bc_headr = bc_start;
	bc_headw = bc_start;
	bc_nbcmd = 0;
}

Buff_Circle::~Buff_Circle(void)
{
	bzero(bc_start, BC_SIZE + 1);
	bc_end = bc_start + BC_SIZE;
	bc_headr = bc_start;
	bc_headw = bc_start;
	bc_nbcmd = 0;
}

int		Buff_Circle::bc_iscmd(void)
{
	char	*tmp;

	tmp = bc_headr;
	while (*tmp != '\0')
	{
		if (*tmp == '\n')
			return (1);
		if (tmp >= bc_end)
			tmp = bc_start;
		else
			tmp++;
	}
	return (0);
}

void	Buff_Circle::bc_write(char *tmp, int type)
{
	int		i;

	i = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '\n')
			bc_nbcmd++;
		*bc_headw = tmp[i];
		if (bc_headw >= bc_end)
			bc_headw = bc_start;
		else
			bc_headw++;
		i++;
	}
	if (type == 1)
	{
		*bc_headw = '\n';
		if (bc_headw >= bc_end)
			bc_headw = bc_start;
		else
			bc_headw++;
		bc_nbcmd++;
	}
}

void	Buff_Circle::bc_read(char *tmp)
{
	int		j;

	j = -1;
	while (bc_nbcmd != 0)
	{
		if (*bc_headr != '\0')
			tmp[++j] = *bc_headr;
		*bc_headr = '\0';
		if (tmp[j] == '\n')
			bc_nbcmd--;
		if (bc_headr >= bc_end)
			bc_headr = bc_start;
		else
			bc_headr++;
	}
	tmp[++j] = '\0';
}

void	Buff_Circle::bc_display(void)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = bc_headr;
	std::cout << "Display BC :" << std::endl;
	while (*tmp != '\n')
	{
		std::cout << *tmp;
		if (tmp + 1 == bc_end)
			tmp = bc_start;
		else
			tmp++;
	}
	std::cout << std::endl;
}
