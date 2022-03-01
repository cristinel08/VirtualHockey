/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include<random>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{ 

		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> X_dist(0, 1);
		std::uniform_int_distribution<int> Y_dist(0, 1);
		if (X_dist(rng) == 0)
			vx_ball = 1;
		else vx_ball = -1;
		if (Y_dist(rng) == 0)
			vy_ball = 1;
		else vy_ball = -1;
	
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (isOver == false) {
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			y_bar1 -= 1;
		}
		if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			y_bar1 += 1;
		}
		if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			x_bar1 -= 1;

		}

		if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			x_bar1 += 1.5;
		}
		colR = ColissionXR(x_bar1);
		colYR = CollisionY(y_bar1);

		if (wnd.kbd.KeyIsPressed('W'))
		{
			y_bar0 -= 1;
		}
		if (wnd.kbd.KeyIsPressed('S'))
		{
			y_bar0 += 1;
			
		}
		if (wnd.kbd.KeyIsPressed('A'))
		{
			x_bar0 -= 1.5;

		}
		if (wnd.kbd.KeyIsPressed('D'))
		{
			x_bar0 += 1;
		}
		colXL = CollisionXL(x_bar0);		//schimb viteza mingii in momentul in care atinge unul dintre cei 2 jucatori
		colYL = CollisionY(y_bar0);
		
		x_bar0 = Box1(x_bar0);
		x_bar1 = Box0x(x_bar1);
		y_bar0 = Box2(y_bar0);
		y_bar1 = Box2(y_bar1);

		x_ball += vx_ball;
		y_ball += vy_ball;

		{
			const int y_ballold = y_ball;
			y_ball = Ball(y_ball);
			if (y_ballold != y_ball)
				vy_ball = -vy_ball;
		}

		if(colXL && colYL)
		{
			number = 1;
		}

		if (colR && colYR)
		{
			number = 2;
		}
		switch (number)
		{
		case 1:
			vx_ball = 1;
			break;
		case 2:
			vx_ball = -1;
			break;
		}
		isOver = Box_Ball0(x_ball);
		
	}
	else { 
		x_ball = 400;
		y_ball = 300;
		vx_ball = 0;
		vy_ball = 0;
	}
}

//afisez pe ecran desenele
void Game::ComposeFrame()
{
	DrawBar(x_bar0, y_bar0, 255, 255, 255);
	DrawBar(x_bar1, y_bar1, 255, 0, 255);
	DrawBall(x_ball, y_ball, 255,0,0);
	for (int i = 0; i < 293; i++)
		gfx.PutPixel(gfx.ScreenWidth/2, i, 0, 255, 0);
	for (int i = 300; i < gfx.ScreenHeight; i++)
		gfx.PutPixel(gfx.ScreenWidth/2, i, 0, 255, 0);

}
void Game::DrawBar(float x, float y, float r, float g, float b) {
	for (int i = 0; i < 20; i++)
		gfx.PutPixel(x, y + i, r, g, b);
}
void Game::DrawBall(float x, float y, float r, float g, float b) {
	gfx.PutPixel(x, y - 5, r,g,b);
	gfx.PutPixel(x , y - 4, r,g,b);
	gfx.PutPixel(x, y - 3, r,g,b);
	gfx.PutPixel(x + 1, y - 2, r,g,b);
	gfx.PutPixel(x + 2, y - 2, r,g,b);
	gfx.PutPixel(x + 3, y - 2, r,g,b);
	gfx.PutPixel(x + 4, y - 3, r,g,b);
	gfx.PutPixel(x + 4, y - 4, r,g,b);
	gfx.PutPixel(x + 4, y - 5, r,g,b);
	gfx.PutPixel(x + 3, y - 6, r,g,b);
	gfx.PutPixel(x + 2, y - 6, r,g,b);
	gfx.PutPixel(x + 1, y - 6, r,g,b);


}

// lungimea pe care se poate deplasa jucatorul din dreapta
float Game::Box1(float x) {
	if (x < 0)
	{
		return 0;
	}
	else if (x >= 400)
	{
		return 399;
	}
	else return x;
}

// inaltimea la care se pot deplasa jucatorii
float Game::Box2(float y) {
	if (y < 0)
		return 1;
	else if (y+20 >= gfx.ScreenHeight)
		return gfx.ScreenHeight - 21;
	else return y;
}

float Game::Ball(float y) {
	if (y - 6 < 0)
		return 6;
	else if (y - 2 >= gfx.ScreenHeight)
		return gfx.ScreenHeight - 2;
	else return y;
}

// lungimea pe care se poate deplasa jucatorul din stanga
float Game::Box0x(float x) {
	if (x <= 400)
	{
		return 401;
	}
	else if (x >= gfx.ScreenWidth)
	{
		return gfx.ScreenWidth-1;
	}
	else return x;
}		

//sa se termine jocul daca mingea atinge marginea din stanga sau din dreapta
bool Game::Box_Ball0(float x) {
	if (x + 5 >= gfx.ScreenWidth)
		return true;
	else if( x <= 0)
		return true;
	else return false;
}

//cand jucatorul din dreapta loveste mingea
bool Game::ColissionXR(float x)
{
	if (x <= x_ball + 7.4 && x >= x_ball + 3.4)
		return true;
	else return false;

}
//cand jucatorul din stanga loveste mingea
bool Game::CollisionXL(float x)
{
	if (x >= x_ball - 4 && x <= x_ball - 1)
		return true;
	else return false;
}

bool Game::CollisionY(float y)
{
	if (y + 20 >= y_ball - 6 &&
		y <= y_ball - 2)
		return true;
	else return false;
}