// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IDisplayer.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/11 15:41:34 by tmielcza          #+#    #+#             //
//   Updated: 2015/12/09 17:05:12 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IDISPLAYER_HPP
# define IDISPLAYER_HPP

enum	e_Dir
{
	Up = 1,
	Down = 2,
	Right = 4,
	Left = 8
};

enum	e_Input
{
	I_Player1 = 1 << 10,
	I_Nope = 0,
	I_Up = 1 << 0,
	I_Down = 1 << 1,
	I_Right = 1 << 2,
	I_Left = 1 << 3,

	I_Up1 = I_Up | I_Player1,
	I_Down1 = I_Down | I_Player1,
	I_Right1 = I_Right | I_Player1,
	I_Left1 = I_Left | I_Player1,

	I_Up2 = I_Up,
	I_Down2 = I_Down,
	I_Right2 = I_Right,
	I_Left2 = I_Left,

	I_Ok = 1 << 4,
	I_Cancel = 1 << 5,
	I_Lib1 = 1 << 6,
	I_Lib2 = 1 << 7,
	I_Lib3 = 1 << 8,
	I_Close = 1 << 9,
	I_Dir = I_Up | I_Down | I_Right | I_Left
};

class IDisplayer
{
public:
	virtual void				clear(void) = 0;
	virtual void				display(void) = 0;
	virtual void				popFood(int x, int y) = 0;
	virtual void				popMultiFood(int x, int y) = 0;
	virtual void				popSuperFood(int x, int y, int size) = 0;
	virtual void				popChasedFood(int x, int y, int size, float time) = 0;
	virtual void				depopFood(int x, int y) = 0;
	virtual void				updateSuperFood(int x, int y, int size) = 0;
	virtual void				switchFoodMode(void) = 0;
	virtual void				drawTail(float time, int x, int y, e_Dir last) = 0;
	virtual void				drawHead(float time, int x, int y, e_Dir last) = 0;
	virtual void				putWall(int x, int y) = 0;
	virtual void				popWave(int x, int y) = 0;
	virtual std::list<e_Input>	getInput(void) = 0;
};

#endif // IDISPLAYER_HPP
