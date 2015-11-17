// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AGameMode.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/10 23:19:17 by tmielcza          #+#    #+#             //
//   Updated: 2015/11/17 17:53:44 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AGAMEMODE_HPP
# define AGAMEMODE_HPP

class AGameMode
{
public:
					AGameMode(void);
					AGameMode(const AGameMode& src);
					~AGameMode(void);
					AGameMode(int nplayers, int x, int y);
	virtual void	run(void) = 0;
	AGameMode&		operator=(const AGameMode& src);

private:
	int		_x;
	int		_y;
	int		_nplayers;
};

class NormalMode
{
	void	run(void);
};

#endif //AGAMEMODE_HPP
