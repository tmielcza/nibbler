// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IDisplayer.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/11 15:41:34 by tmielcza          #+#    #+#             //
//   Updated: 2015/06/29 18:47:41 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IDISPLAYER_HPP
# define IDISPLAYER_HPP

enum e_Dir
{
	Up,
	Down,
	Left,
	Right
};

enum	e_Input
{
	I_Up,
	I_Down,
	I_Left,
	I_Right,
	I_Ok,
	I_Cancel,
	I_Lib1,
	I_Lib2,
	I_Lib3,
	I_Close
};

class IDisplayer
{
public:
	virtual void				clear(void) = 0;
	virtual void				display(void) = 0;
	virtual void				popFood(int x, int y) = 0;
	virtual void				popMultiFood(int x, int y) = 0;
	virtual void				popSuperFood(int x, int y, int size) = 0;
	virtual void				popChasedFood(int x, int y, int size) = 0;
	virtual void				depopFood(int x, int y) = 0;
	virtual void				updateSuperFood(int x, int y, int size) = 0;
	virtual void				switchFoodMode(void) = 0;
	virtual void				drawTail(float time, int x, int y, e_Dir last) = 0;
	virtual void				drawHead(float time, int x, int y, e_Dir last) = 0;
	virtual std::list<e_Input>	getInput(void) = 0;
};

#endif // IDISPLAYER_HPP
