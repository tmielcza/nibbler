// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: rduclos <rduclos@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/08 16:24:19 by rduclos           #+#    #+#             //
//   Updated: 2015/04/14 17:38:59 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <string>

#include "AGameMode.hpp"

int		main(void)
{
	AGameMode	mode = NormalMode(20, 20, 1);
	mode.run();
	return (0);
}
