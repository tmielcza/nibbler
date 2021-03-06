// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AGameMode.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/10 23:19:17 by tmielcza          #+#    #+#             //
//   Updated: 2015/12/03 19:23:54 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AGAMEMODE_HPP
# define AGAMEMODE_HPP

#include "GameManager.hpp"

class AGameMode
{
	private:

	virtual bool	check_end(void) = 0;

	protected:

	int				_width;
	int				_height;
	int				_nbPlayers;
	double			_speed;
	GameManager		*_game;

	public:

	AGameMode(void);
	AGameMode(const AGameMode& src);
	~AGameMode(void);
	AGameMode(int nplayers, int width, int height);

	AGameMode&		operator=(const AGameMode& src);

//	virtual void	init(bool wall) = 0;
	virtual void	run(void) = 0;

};

#endif
