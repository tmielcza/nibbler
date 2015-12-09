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
	I_Nope = 0,
	I_Up = 1 << 0,
	I_Down = 1 << 1,
	I_Right = 1 << 2,
	I_Left = 1 << 3,
	I_Ok = 1 << 4,
	I_Cancel = 1 << 5,
	I_Lib1 = 1 << 6,
	I_Lib2 = 1 << 7,
	I_Lib3 = 1 << 8,
	I_Close = 1 << 9,
	I_2Up = 1 << 10,
	I_2Down = 1 << 11,
	I_2Right = 1 << 12,
	I_2Left = 1 << 13,
	I_Dir = 1 | 2 | 4 | 8,
	I_2Dir = I_2Up | I_2Down | I_2Right | I_2Left
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
