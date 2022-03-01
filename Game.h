/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void DrawBar(float x, float y, float r, float g, float b);
	void DrawBall(float x, float y, float r, float g, float b);
	float Move_Barr(float y);
	float Box1(float x);
	float Box2(float y);
	float Ball(float y);
	float Box0x(float x);
	float Box0y(float y);
	bool Box_Ball0(float x);
	bool Box_Ball1(float x);
	bool ColissionXR(float x);
	bool CollisionXL(float x);
	bool CollisionY(float y);
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	float x_bar0 = 50;
	float y_bar0 = 300;
	float x_bar1 = gfx.ScreenWidth-50;
	int y_bar1 = 300;
	int x_ball = 398;
	int y_ball = 300;
	int vx_ball = 0;
	int vy_ball = 0;
	bool isOver = false;
	bool colR = false;
	bool colXL = false;
	bool colYL = false;
	bool colYR = false;
	int number;
	/********************************/
};