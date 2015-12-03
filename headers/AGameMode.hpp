// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AGameMode.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/10 23:19:17 by tmielcza          #+#    #+#             //
//   Updated: 2015/11/22 17:04:04 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AGAMEMODE_HPP
# define AGAMEMODE_HPP

class AGameMode
{
	protected:

	int		_width;
	int		_height;
	int		_nbPlayers;
	double	_speed;

	public:

	AGameMode(void);
	AGameMode(const AGameMode& src);
	~AGameMode(void);
	AGameMode(int nplayers, int width, int height);

	AGameMode&		operator=(const AGameMode& src);

	virtual void	init(void) = 0;
	virtual void	run(void) = 0;

};

#endif
