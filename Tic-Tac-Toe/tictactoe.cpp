// This file belongs strictly to FranckenatorProductions
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2023  Chase Poland, Nicholas Franck, Eric Peasley.

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
#include "tictactoe.h"
#include <circle/string.h>
#include <circle/util.h>

#define PLAYER_1 1
#define PLAYER_2 2

TicTacToe *TicTacToe::game;

TicTacToe::TicTacToe (void)
:
      player1wins(0),
      player2wins(0),
      m_status(Initial),
      m_2DGraphics(m_Options.GetWidth (), m_Options.GetHeight (), FALSE)
{
	game = this;
}

TicTacToe::~TicTacToe (void)
{
	game = 0;
}

void TicTacToe::Initialize (void)
{
      cur_row = 0;
      cur_col = 0;
      moves = 0;
      turn = PLAYER_1;
      for(int i = 0; i < 3; i++) 
      {
          for(int j = 0; j< 3; j++) 
          {
              grid[i][j] = 0;
          }
      }	
      m_status = Ongoing;
      // show board here
      m_2DGraphics.Initialize ();
      m_2DGraphics.ClearScreen(BLACK_COLOR);
	
	// 32 Shape Objects usable
	for (unsigned i = 0; i < nShapes; i++)
	{
		m_pShape[i] = new CGraphicShape (m_2DGraphics.GetWidth (), m_2DGraphics.GetHeight ());
	}
	
	RedrawGameState();
      
}

void TicTacToe::moveUp(void)
{
    if (cur_row != 0 && m_status == Ongoing)
    {
        cur_row--;
        
        // update graphics here
        
	RedrawGameState();
    }
}

void TicTacToe::moveDown(void)
{
    if (cur_row != 2 && m_status == Ongoing)
    {
        cur_row++;
        
        // update graphics here
        
	RedrawGameState();
    }
}

void TicTacToe::moveRight(void)
{
    if (cur_col != 2 && m_status == Ongoing)
    {
        game->cur_col++;
        // update graphics here
	RedrawGameState();
    }
}

void TicTacToe::moveLeft(void)
{
    if (cur_col != 0 && m_status == Ongoing)
    {
        cur_col--;
        
        // update graphics here
	RedrawGameState();
    }
}

void TicTacToe::placeTic(void)
{
    if(game->checkPlace() && m_status == Ongoing)
    {
          grid[cur_row][cur_col] = turn;
          moves++;
          if(game->checkWin() || moves == 9) 
          {
              //winner graphic
              m_status = Winner;
              
              if(moves == 9 && !game->checkWin())
              {
                    m_2DGraphics.ClearScreen(BLACK_COLOR);
                    m_pShape[13] -> DrawGameWinner(&m_2DGraphics, 0);
              }
              else 
              {
                     m_2DGraphics.ClearScreen(BLACK_COLOR);
                     m_pShape[13] -> DrawGameWinner(&m_2DGraphics,turn);
                     if(turn == 1)
                    {
                        game->Player1Wins();
                    } 
                    if(turn == 2) 
                    {
                        game->Player2Wins();
                    }
              }
              m_2DGraphics.UpdateDisplay();
          } 
          else 
          {
              if(turn == 1)
              {
                  
                  turn = PLAYER_2;
              } 
              else 
              {
                  
                  turn = PLAYER_1;
              }
              RedrawGameState();
          }
        
    }
}

boolean TicTacToe::checkPlace(void)
{
    if (grid[cur_row][cur_col] == 0)
    {
        return TRUE;
    }
    return FALSE;
}

boolean TicTacToe::checkWin(void)
{
        if(grid[0][0] == 1 && grid[0][1] == 1 && grid[0][2] == 1){return TRUE;}
 	if(grid[1][0] == 1 && grid[1][1] == 1 && grid[1][2] == 1){return TRUE;}
 	if(grid[2][0] == 1 && grid[2][1] == 1 && grid[2][2] == 1){return TRUE;}
 	//Vertical wins
 	if(grid[0][0] == 1 && grid[1][0] == 1 && grid[2][0] == 1){return TRUE;}
 	if(grid[0][1] == 1 && grid[1][1] == 1 && grid[2][1] == 1){return TRUE;}
	if(grid[0][2] == 1 && grid[1][2] == 1 && grid[2][2] == 1){return TRUE;}
//Diagonal wins
 	if(grid[0][0] == 1 && grid[1][1] == 1 && grid[2][2] == 1){return TRUE;}
 	if(grid[0][2] == 1 && grid[1][1] == 1 && grid[2][0] == 1){return TRUE;}
 	
	//Player 2 wins
	//Horizontal wins
 	if(grid[0][0] == 2 && grid[0][1] == 2 && grid[0][2] == 2){return TRUE;}
	if(grid[1][0] == 2 && grid[1][1] == 2 && grid[1][2] == 2){return TRUE;}
	if(grid[2][0] == 2 && grid[2][1] == 2 && grid[2][2] == 2){return TRUE;}
 	//Vertical wins
	if(grid[0][0] == 2 && grid[1][0] == 2 && grid[2][0] == 2){return TRUE;}
	if(grid[0][1] == 2 && grid[1][1] == 2 && grid[2][1] == 2){return TRUE;}
 	if(grid[0][2] == 2 && grid[1][2] == 2 && grid[2][2] == 2){return TRUE;}
 	//Diagonal wins
 	if(grid[0][0] == 2 && grid[1][1] == 2 && grid[2][2] == 2){return TRUE;}
	if(grid[0][2] == 2 && grid[1][1] == 2 && grid[2][0] == 2){return TRUE;}
	return FALSE;
}

void TicTacToe::Player1Wins(void)
{
    game->player1wins++;
}

void TicTacToe::Player2Wins(void)
{
    game->player2wins++;
}

void TicTacToe::GameOver(void)
{
    m_status = Gameover;
    m_2DGraphics.ClearScreen(BLACK_COLOR);
    m_pShape[19]->DrawGameOver(&m_2DGraphics,game->player1wins,game->player2wins);
    m_2DGraphics.UpdateDisplay();
}

GameStatus TicTacToe::getStatus(void)
{
    
    return m_status;
}

void TicTacToe::RedrawGameState(void)
{
     m_2DGraphics.ClearScreen(BLACK_COLOR);
    
     unsigned x = 1;
     // Draw Cells for Board @parm (int row, int col)
     for(int r = 0; r < 3; r++) {
        for(int c = 0; c < 3; c++) {
             m_pShape[x]->DrawCell(&m_2DGraphics, r, c);
             x = x+1;
        }
     }
     m_pShape[12]->DrawSelection(&m_2DGraphics, cur_row, cur_col);
     for(int r = 0; r < 3; r++) {
     	for(int c = 0; c < 3; c++) {
     	    if(grid[r][c] == 1) {
     	        m_pShape[1] -> DrawX(&m_2DGraphics, r, c);
     	    }
     	    if(grid[r][c] == 2) {
     	    	m_pShape[2]->DrawO(&m_2DGraphics, r, c);
     	    }
     	}
     }
     m_pShape[11]->DrawTurn(&m_2DGraphics, turn);
     m_pShape[17]->DrawHelp(&m_2DGraphics);
     m_2DGraphics.UpdateDisplay();
}

