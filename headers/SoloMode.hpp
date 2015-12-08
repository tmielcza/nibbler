// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SoloMode.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/03 17:28:39 by rduclos           #+#    #+#             //
//   Updated: 2015/12/03 19:24:45 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SOLOMODE_HPP
# define SOLOMODE_HPP

# include "AGameMode.hpp"
# include "MapManager.hpp"

class SoloMode : public AGameMode
{
	private:

	bool			check_end(void);

	public:

	SoloMode(void);
	SoloMode(bool wall);
	SoloMode(const SoloMode & src);
	SoloMode(int nbplayers, int width, int height, bool wall);
	~SoloMode(void);

	SoloMode	&	operator=(const SoloMode & src);

	void			init(bool wall);
	void			run(void);

};

#endif
