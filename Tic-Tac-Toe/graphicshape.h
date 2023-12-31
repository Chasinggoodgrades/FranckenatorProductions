//
// kernel.h
//
// This file includes code from the Circle library:
//   Circle - A C++ bare metal environment for Raspberry Pi
//   Copyright (C) 2014-2023  R. Stange <rsta2@o2online.de>

// Additional modifications and enhancements have been made
// by [Chase Poland, Nicholas Franck, & Eric Peasley] as part of the [Franckenator Productions] project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef _graphicshape_h
#define _graphicshape_h

#include <circle/screen.h>
#include <circle/2dgraphics.h>
#include <circle/string.h>

enum
{
	GRAPHICSHAPE_RECT,
	GRAPHICSHAPE_OUTLINE,
	GRAPHICSHAPE_LINE,
	GRAPHICSHAPE_CIRCLE,
	GRAPHICSHAPE_CIRCLEOUTLINE,
	GRAPHICSHAPE_SPRITE_TRANSPARENTCOLOR,
	GRAPHICSHAPE_TEXT,
	NB_GRAPHICSHAPE
};

class CGraphicShape
{
public:
	CGraphicShape (unsigned nDisplayWidth, unsigned nDisplayHeight);
	~CGraphicShape (void);

	void DrawCell(C2DGraphics* renderer, int x, int y); // row, col
	void DrawX(C2DGraphics* renderer, int x, int y); // row, col
	void DrawO(C2DGraphics* renderer, int x, int y); // row, col
	void DrawTurn(C2DGraphics* renderer, int playerNumber); 
	void DrawSelection(C2DGraphics* renderer, int x, int y); //row , col, players#Turn
	void DrawGameWinner(C2DGraphics* renderer, int playerNumber);
	void DrawGameOver(C2DGraphics* renderer, int p1, int p2);
	void DrawHelp(C2DGraphics* renderer);

private:
	unsigned m_nDisplayWidth;
	unsigned m_nDisplayHeight;
	unsigned m_nType;
	float m_nPosX;
	float m_nPosY;
	unsigned m_nAngle;
	float m_nSpeed;
	unsigned m_nParam1;
	unsigned m_nParam2;
	TScreenColor m_Color;
};

#endif
