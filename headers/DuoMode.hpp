// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   DuoMode.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/03 17:28:39 by rduclos           #+#    #+#             //
//   Updated: 2015/12/03 19:24:45 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef DUOMODE_HPP
# define DUOMODE_HPP

# include "AGameMode.hpp"
# include "MapManager.hpp"

class DuoMode : public AGameMode
{
	private:

	bool			check_end(void);

	public:

	DuoMode(void);
	DuoMode(bool wall);
	DuoMode(const DuoMode & src);
	DuoMode(int nbplayers, int width, int height, bool wall);
	~DuoMode(void);

	DuoMode	&	operator=(const DuoMode & src);

	void			init(bool wall);
	void			run(void);

};

#endif
