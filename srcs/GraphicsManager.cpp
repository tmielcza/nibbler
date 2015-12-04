// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GraphicsManager.cpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/11 13:58:27 by tmielcza          #+#    #+#             //
//   Updated: 2015/12/04 16:38:21 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <string>
#include "GraphicsManager.hpp"

GraphicsManager::GraphicsManager(void)
{
}

GraphicsManager::~GraphicsManager(void)
{
}

IDisplayer*	GraphicsManager::_instance = nullptr;
void*		GraphicsManager::_handle = nullptr;

IDisplayer&	GraphicsManager::Instance(void)
{
	return (*GraphicsManager::_instance);
}

void		GraphicsManager::setLib(e_Lib lib, int x, int y)
{
	static std::string	libs[size] = {"LibSFML/gfx-sfml.so"};

	if (_handle == nullptr)
	{
		dlclose(_handle);
		_handle = nullptr;
		_instance = nullptr;
	}
	_handle = dlopen(libs[lib].c_str(), RTLD_LAZY | RTLD_LOCAL);
	DisplayerCreator	create = reinterpret_cast<DisplayerCreator>(dlsym(_handle, "create"));
	_instance = create(x, y);
}
