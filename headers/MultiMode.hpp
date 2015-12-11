// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MultiMode.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/03 17:28:39 by rduclos           #+#    #+#             //
//   Updated: 2015/12/03 19:24:45 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MULTIMODE_HPP
# define MULTIMODE_HPP

# include "AGameMode.hpp"
# include "MapManager.hpp"

class MultiMode : public AGameMode
{
	private:

	bool			check_end(void);

	public:

	MultiMode(void);
	MultiMode(bool wall);
	MultiMode(const MultiMode & src);
	MultiMode(int nbplayers, int width, int height, bool wall);
	~MultiMode(void);

	MultiMode	&	operator=(const MultiMode & src);

	void			init(bool wall);
	void			run(void);

};

#endif
