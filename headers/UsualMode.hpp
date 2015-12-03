// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   UsualMode.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/03 17:28:39 by rduclos           #+#    #+#             //
//   Updated: 2015/12/03 17:43:20 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef USUALMODE_HPP
# define USUALMODE_HPP

# include "AGameMode.hpp"
# include "MapManager.hpp"

class UsualMode : public AGameMode
{
	public:

	UsualMode(void);
	UsualMode(const UsualMode & src);
	UsualMode(int nbplayers, int width, int height, e_preMode premode);
	~UsualMode(void);

	UsualMode	&	operator=(const UsualMode & src);

	void			init(void);
	void			run(void);
};

#endif
