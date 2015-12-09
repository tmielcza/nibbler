// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IDisplayer.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: tmielcza <tmielcza@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/11 15:41:34 by tmielcza          #+#    #+#             //
//   Updated: 2015/12/08 18:28:12 by tmielcza         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IDISPLAYER_HPP
# define IDISPLAYER_HPP

enum	e_Dir
{
	Up,
	Down,
	Left,
	Right
};

enum	e_Input
{
	I_Nope = 0,
	I_Up = 1,
	I_Down = 2,
	I_Right = 4,
	I_Left = 8,
	I_Ok = 16,
	I_Cancel = 32,
	I_Lib1 = 64,
	I_Lib2 = 128,
	I_Lib3 = 256,
	I_Close = 512,
	I_Up2 = 1024,
	I_Down2 = 2048,
	I_Right2 = 4096,
	I_Left2 = 8192,
	I_Dir2 = 1024 | 2048 | 4096 | 8192,
	I_Dir = 1 | 2 | 4 | 8
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
	virtual void				popWave(int x, int y);
	virtual std::list<e_Input>	getInput(void) = 0;
};

#endif // IDISPLAYER_HPP
