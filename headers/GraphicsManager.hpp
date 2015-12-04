// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GraphicsManager.hpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/11 12:14:41 by tmielcza          #+#    #+#             //
//   Updated: 2015/12/03 21:06:17 by rduclos          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GRAPHICSMANAGER_HPP
# define GRAPHICSMANAGER_HPP

# include <dlfcn.h>
# include <list>
# include "IDisplayer.hpp"

enum e_Lib
{
	sfml,
	size
};

typedef IDisplayer* (*DisplayerCreator)(int x, int y);

class GraphicsManager
{
	private:

	GraphicsManager(void);
	~GraphicsManager(void);	
	GraphicsManager(const GraphicsManager& copy);
	GraphicsManager&		operator=(const GraphicsManager& copy);

	static IDisplayer*		_instance;
	static void*			_handle;
	
	public:

	static IDisplayer&		Instance(void);
	static void				setLib(e_Lib lib, int width, int height);
};

#endif //GRAPHICSMANAGER_HPP
