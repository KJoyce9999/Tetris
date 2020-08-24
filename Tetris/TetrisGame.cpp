//
//  TetrisGame.cpp
//  Tetris
//
//  Created by Keenan Joyce on 1/21/19.
//  Copyright © 2019 Keenan Joyce. All rights reserved.
//

#include "TetrisGame.hpp"
#include <stdlib.h>
#include <iostream>
#include <random>

TetrisGame::TetrisGame()      //class constructor
{
  gameBoard = new int*[24];         //allocate 24 pointers for rows
  currentTM = new tetromino;
  currentTM->c1 = new coord;
  currentTM->c2 = new coord;
  currentTM->c3 = new coord;
  currentTM->c4 = new coord;
  
  ghostTM = new tetromino;
  ghostTM->c1 = new coord;
  ghostTM->c2 = new coord;
  ghostTM->c3 = new coord;
  ghostTM->c4 = new coord;
  
  prevTM = prevPrevTM = 0;
  score = 0;
  level = 1;
  levelTime = 1.0;
  
  for(int i=0; i < 24; i++)        //at each row allocate 10 pointes for columns
  {gameBoard[i] = new int[10];}
}

TetrisGame::~TetrisGame()       //class deconstructor
{
  delete [] gameBoard;
  delete currentTM;
  delete ghostTM;
  gameBoard = NULL;
  currentTM = NULL;
  ghostTM = NULL;
}

void TetrisGame::newBoard()      //clears the board
{
  for(int row = 0; row < 24; row++)
  {for(int col = 0; col < 10; col++)
    {gameBoard[row][col] = 0;}
  }
  currentTM->TMValue = 0;
  ghostTM->TMValue = 0;
  prevTM = prevPrevTM = 0;
  score = 0;
  level = 1;
  levelTime = 1.0;
}

void TetrisGame::loadBoard(int **gameData)     //loads a board
{
  for(int row = 0; row < 24; row++)
  {for(int col = 0; col < 10; col++)
    {gameBoard[row][col] = gameData[row][col];}
  }
}

void TetrisGame::addRandomTM()       //adds a new random tetromino
{
  //generate random numbers 1-7, much better than rand()
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> dist7(1,7);
  
  currentTM->TMValue = dist7(rng);
  currentTM->rotatioNum = 0;
  
  while((prevTM == currentTM->TMValue) || (prevPrevTM == currentTM->TMValue))  //prevent more than two of the same TM type in a row
  {
    std::uniform_int_distribution<std::mt19937::result_type> dist7(1,7);
    currentTM->TMValue = dist7(rng);
  }
  prevPrevTM = prevTM;
  prevTM = currentTM->TMValue;
  
  switch(currentTM->TMValue)
  {
    case 1:
      popTMCoords(I);
      shiftTM(checkHigherPlace(currentTM), 0);
      break;
    case 2:
      popTMCoords(O);
      shiftTM(checkHigherPlace(currentTM), 0);
      break;
    case 3:
      popTMCoords(T);
      shiftTM(checkHigherPlace(currentTM), 0);
      break;
    case 4:
      popTMCoords(S);
      shiftTM(checkHigherPlace(currentTM), 0);
      break;
    case 5:
      popTMCoords(Z);
      shiftTM(checkHigherPlace(currentTM), 0);
      break;
    case 6:
      popTMCoords(J);
      shiftTM(checkHigherPlace(currentTM), 0);
      break;
    case 7:
      popTMCoords(L);
      shiftTM(checkHigherPlace(currentTM), 0);
      break;
  }
  ghostTM->TMValue = 8;
  ghostTM->c1->row = currentTM->c1->row;
  ghostTM->c1->col = currentTM->c1->col;
  ghostTM->c2->row = currentTM->c2->row;
  ghostTM->c2->col = currentTM->c2->col;
  ghostTM->c3->row = currentTM->c3->row;
  ghostTM->c3->col = currentTM->c3->col;
  ghostTM->c4->row = currentTM->c4->row;
  ghostTM->c4->col = currentTM->c4->col;
  shiftGhostTm();
}

void TetrisGame::popTMCoords(tetrominos piece)      //populates currentTM with proper coords
{
  switch (piece)
  {
    case emptyCell:
      break;
    case I:
      currentTM->c1->row = 18; currentTM->c1->col = 3;
      currentTM->c2->row = 18; currentTM->c2->col = 4;
      currentTM->c3->row = 18; currentTM->c3->col = 5;
      currentTM->c4->row = 18; currentTM->c4->col = 6;
      break;
    case O:
      currentTM->c1->row = 18; currentTM->c1->col = 4;
      currentTM->c2->row = 18; currentTM->c2->col = 5;
      currentTM->c3->row = 19; currentTM->c3->col = 4;
      currentTM->c4->row = 19; currentTM->c4->col = 5;
      break;
    case T:
      currentTM->c1->row = 18; currentTM->c1->col = 3;
      currentTM->c2->row = 18; currentTM->c2->col = 4;
      currentTM->c3->row = 18; currentTM->c3->col = 5;
      currentTM->c4->row = 19; currentTM->c4->col = 4;
      break;
    case S:
      currentTM->c1->row = 18; currentTM->c1->col = 3;
      currentTM->c2->row = 18; currentTM->c2->col = 4;
      currentTM->c3->row = 19; currentTM->c3->col = 4;
      currentTM->c4->row = 19; currentTM->c4->col = 5;
      break;
    case Z:
      currentTM->c1->row = 18; currentTM->c1->col = 4;
      currentTM->c2->row = 18; currentTM->c2->col = 5;
      currentTM->c3->row = 19; currentTM->c3->col = 3;
      currentTM->c4->row = 19; currentTM->c4->col = 4;
      break;
    case J:
      currentTM->c1->row = 18; currentTM->c1->col = 3;
      currentTM->c2->row = 18; currentTM->c2->col = 4;
      currentTM->c3->row = 18; currentTM->c3->col = 5;
      currentTM->c4->row = 19; currentTM->c4->col = 3;
      break;
    case L:
      currentTM->c1->row = 18; currentTM->c1->col = 3;
      currentTM->c2->row = 18; currentTM->c2->col = 4;
      currentTM->c3->row = 18; currentTM->c3->col = 5;
      currentTM->c4->row = 19; currentTM->c4->col = 5;
      break;
  }
}

void TetrisGame::changeBoard(tetromino *currentTM)     //adds currenTM to game board
{
  gameBoard[currentTM->c1->row][currentTM->c1->col] = currentTM->TMValue;
  gameBoard[currentTM->c2->row][currentTM->c2->col] = currentTM->TMValue;
  gameBoard[currentTM->c3->row][currentTM->c3->col] = currentTM->TMValue;
  gameBoard[currentTM->c4->row][currentTM->c4->col] = currentTM->TMValue;
  currentTM->TMValue = 0;
  currentTM->rotatioNum = 0;
  currentTM->c1->row = NULL;
  currentTM->c1->col = NULL;
  currentTM->c2->row = NULL;
  currentTM->c2->col = NULL;
  currentTM->c3->row = NULL;
  currentTM->c3->col = NULL;
  currentTM->c4->row = NULL;
  currentTM->c4->col = NULL;
  
  score += 5;
  assessLevel();
}

int TetrisGame::checkHigherPlace(tetromino *tempPiece)  //checks if new piece needs to start higher, -1 means no room for piece even with shift
{
  if((gameBoard[tempPiece->c1->row][tempPiece->c1->col] == 0)&&(gameBoard[tempPiece->c2->row][tempPiece->c2->col] == 0)&&(gameBoard[tempPiece->c3->row][tempPiece->c3->col] == 0)&&(gameBoard[tempPiece->c4->row][tempPiece->c4->row] == 0))
  {return 0;}
  else if((gameBoard[tempPiece->c1->row+1][tempPiece->c1->col] == 0)&&(gameBoard[tempPiece->c2->row+1][tempPiece->c2->col] == 0)&&(gameBoard[tempPiece->c3->row+1][tempPiece->c3->col] == 0)&&(gameBoard[tempPiece->c4->row+1][tempPiece->c4->row] == 0))
  {return 1;}
  else
  {return 2;}
}
void TetrisGame::shiftGhostTm()
{
  bool keepShifting = true;
  
  while(keepShifting)
  {
    if(checkForEndOfBoard(ghostTM->c1, -1, 0)) //makes sure shift wont make ghostTM fall off board
    {keepShifting = false;}
    else if(checkForEndOfBoard(ghostTM->c2, -1, 0))
    {keepShifting = false;}
    else if(checkForEndOfBoard(ghostTM->c3, -1, 0))
    {keepShifting = false;}
    else if(checkForEndOfBoard(ghostTM->c4, -1, 0))
    {keepShifting = false;}
  
    if(keepShifting)
    {
      if(checkForCollisions(ghostTM->c1, -1, 0))  //check for collisions
      {keepShifting = false;}
      else if(checkForCollisions(ghostTM->c2, -1, 0))
      {keepShifting = false;}
      else if(checkForCollisions(ghostTM->c3, -1, 0))
      {keepShifting = false;}
      else if(checkForCollisions(ghostTM->c4, -1, 0))
      {keepShifting = false;}
    }
  
    if(keepShifting == true)
    {
      ghostTM->c1->row += -1;
      ghostTM->c2->row += -1;
      ghostTM->c3->row += -1;
      ghostTM->c4->row += -1;
    }
  }
}

bool TetrisGame::shiftTM(int r, int c) //shifts current tetromino in specified direction, returns false if move not allowed
{
 
  if(checkForEndOfBoard(currentTM->c1, r, c)) //makes sure shift wont make currentTM fall off board
  {return false;}
  else if(checkForEndOfBoard(currentTM->c2, r, c))
  {return false;}
  else if(checkForEndOfBoard(currentTM->c3, r, c))
  {return false;}
  else if(checkForEndOfBoard(currentTM->c4, r, c))
  {return false;}
  
  
  if(checkForCollisions(currentTM->c1, r, c))  //check for collisions
  {return false;}
  else if(checkForCollisions(currentTM->c2, r, c))
  {return false;}
  else if(checkForCollisions(currentTM->c3, r, c))
  {return false;}
  else if(checkForCollisions(currentTM->c4, r, c))
  {return false;}
  else
  {
    currentTM->c1->row += r;
    currentTM->c1->col += c;
    currentTM->c2->row += r;
    currentTM->c2->col += c;
    currentTM->c3->row += r;
    currentTM->c3->col += c;
    currentTM->c4->row += r;
    currentTM->c4->col += c;
    
    ghostTM->c1->row = currentTM->c1->row;
    ghostTM->c1->col = currentTM->c1->col;
    ghostTM->c2->row = currentTM->c2->row;
    ghostTM->c2->col = currentTM->c2->col;
    ghostTM->c3->row = currentTM->c3->row;
    ghostTM->c3->col = currentTM->c3->col;
    ghostTM->c4->row = currentTM->c4->row;
    ghostTM->c4->col = currentTM->c4->col;
    shiftGhostTm();
    
    return true;
  }
}

void TetrisGame::completeLines()      //scans board to complete and remove entirely filled rows
{
  int lineCount = 0;
  for(int row = 0; row < 24; row++)
  {
    int count = 0;
    for(int col = 0; col < 10; col++)
    {
      if(gameBoard[row][col] != 0)
      {count++;}
    }
    if(count == 10)       //if full row found
    {clearLine(row--); lineCount++;}
  }
  switch(lineCount) //more score for larger line completions
  {
    case 0:
      break;
    case 1:
      score += 50;
      break;
    case 2:
      score += 140;
      break;
    case 3:
      score += 270;
      break;
    case 4:
      score += 440;
      break;
  }
  assessLevel();
}

void TetrisGame::clearLine(int x) //shift all rows down starting with specified row
{
  for(int row = x; row < 23; row++)
  {
    for(int col = 0; col < 10; col++)
    {gameBoard[row][col] = gameBoard[row + 1][col];}
  }
}

bool TetrisGame::checkForEndGame()       //scans the baord to see if game is over
{
  for(int i = 0; i < 10; i++)     //checks for any saved cells above view
  {if(gameBoard[20][i] != 0)
  {return true;}}
  
  return false;
}

bool TetrisGame::checkForEndOfBoard(coord *cX, int r, int c)     //checks if TM movement falls off board, true means hits end
{
  if((cX->row + r) > 21)     //checks if c1 hits an end of the board
  {return true;}
  else if((cX->row + r) < 0)
  {return true;}
  else if((cX->col + c) > 9)
  {return true;}
  else if((cX->col + c) < 0)
  {return true;}
  else
  {return false;}
}

bool TetrisGame::checkForCollisions(coord *cX, int r, int c)  //checks for collisions with other tetrominos, true means hits another TM
{
  if(gameBoard[cX->row + r][cX->col + c] != 0)    //checks if cX hits an another TM
  {return true;}
  else
  {return false;}
}

void TetrisGame::assessLevel()                        //determine when to increase level
{
  if((score >= 1000) && (score < 2000 ))
  {level = 2; levelTime = 0.90;}
  else if((score >= 2000) && (score < 3000 ))
  {level = 3; levelTime = 0.81;}
  else if((score >= 3000) && (score < 4000 ))
  {level = 4; levelTime = 0.72;}
  else if((score >= 4000) && (score < 5000 ))
  {level = 5; levelTime = 0.63;}
  else if((score >= 5000) && (score < 6000 ))
  {level = 6; levelTime = 0.54;}
  else if((score >= 6000) && (score < 7000 ))
  {level = 7; levelTime = 0.45;}
  else if((score >= 7000) && (score < 8000 ))
  {level = 8; levelTime = 0.36;}
  else if((score >= 8000) && (score < 9000 ))
  {level = 9; levelTime = 0.27;}
  else if((score >= 9000) && (score < 10000 ))
  {level = 10; levelTime = 0.18;}
}

int  TetrisGame::getBoardValue(int row, int col)         //returns value at specified cell
{return gameBoard[row][col];}

tetromino* TetrisGame::getTM()                       //returns entire TM object
{return currentTM;}

void TetrisGame::rotateTM()      //rotates current tetromino 90 degrees right
{
  if(currentTM->TMValue == 1)
  {
    if(currentTM->rotatioNum == 0)
    {rotationAnalysis(2, 2, 1, 1, 0, 0, -1, -1);}
    else if(currentTM->rotatioNum == 1)
    {rotationAnalysis(-2, 2, -1, 1, 0, 0, 1, -1);}
    else if(currentTM->rotatioNum == 2)
    {rotationAnalysis(-2, -2, -1, -1, 0, 0, 1, 1);}
    else if(currentTM->rotatioNum == 3)
    {rotationAnalysis(2, -2, 1, -1, 0, 0, -1, 1);}
  }
  else if(currentTM->TMValue == 3)
  {
    if(currentTM->rotatioNum == 0)
    {rotationAnalysis(1, 1, 0, 0, -1, -1, -1, 1);}
    else if(currentTM->rotatioNum == 1)
    {rotationAnalysis(-1, 1, 0, 0, 1, -1, -1, -1);}
    else if(currentTM->rotatioNum == 2)
    {rotationAnalysis(-1, -1, 0, 0, 1, 1, 1, -1);}
    else if(currentTM->rotatioNum == 3)
    {rotationAnalysis(1, -1, 0, 0, -1, 1, 1, 1);}
  }
  else if(currentTM->TMValue == 4)
  {
    if(currentTM->rotatioNum == 0)
    {rotationAnalysis(1, 1, 0, 0, -1, 1, -2, 0);}
    else if(currentTM->rotatioNum == 1)
    {rotationAnalysis(-1, 1, 0, 0, -1, -1, 0, -2);}
    else if(currentTM->rotatioNum == 2)
    {rotationAnalysis(-1, -1, 0, 0, 1, -1, 2, 0);}
    else if(currentTM->rotatioNum == 3)
    {rotationAnalysis(1, -1, 0, 0, 1, 1, 0, 2);}
  }
  else if(currentTM->TMValue == 5)
  {
    if(currentTM->rotatioNum == 0)
    {rotationAnalysis(0, 0, -1, -1, 0, 2, -1, 1);}
    else if(currentTM->rotatioNum == 1)
    {rotationAnalysis(0, 0, 1, -1, -2, 0, -1, -1);}
    else if(currentTM->rotatioNum == 2)
    {rotationAnalysis(0, 0, 1, 1, 0, -2, 1, -1);}
    else if(currentTM->rotatioNum == 3)
    {rotationAnalysis(0, 0, -1, 1, 2, 0, 1, 1);}
  }
  else if(currentTM->TMValue == 6)
  {
    if(currentTM->rotatioNum == 0)
    {rotationAnalysis(1, 1, 0, 0, -1, -1, 0, 2);}
    else if(currentTM->rotatioNum == 1)
    {rotationAnalysis(-1, 1, 0, 0, 1, -1, -2, 0);}
    else if(currentTM->rotatioNum == 2)
    {rotationAnalysis(-1, -1, 0, 0, 1, 1, 0, -2);}
    else if(currentTM->rotatioNum == 3)
    {rotationAnalysis(1, -1, 0, 0, -1, 1, 2, 0);}
  }
  else if(currentTM->TMValue == 7)
  {
    if(currentTM->rotatioNum == 0)
    {rotationAnalysis(1, 1, 0, 0, -1, -1, -2, 0);}
    else if(currentTM->rotatioNum == 1)
    {rotationAnalysis(-1, 1, 0, 0, 1, -1, 0, -2);}
    else if(currentTM->rotatioNum == 2)
    {rotationAnalysis(-1, -1, 0, 0, 1, 1, 2, 0);}
    else if(currentTM->rotatioNum == 3)
    {rotationAnalysis(1, -1, 0, 0, -1, 1, 0, 2);}
  }
  if(currentTM->rotatioNum == 4)
  {currentTM->rotatioNum = 0;}
  
  ghostTM->c1->row = currentTM->c1->row;
  ghostTM->c1->col = currentTM->c1->col;
  ghostTM->c2->row = currentTM->c2->row;
  ghostTM->c2->col = currentTM->c2->col;
  ghostTM->c3->row = currentTM->c3->row;
  ghostTM->c3->col = currentTM->c3->col;
  ghostTM->c4->row = currentTM->c4->row;
  ghostTM->c4->col = currentTM->c4->col;
  shiftGhostTm();
}

//check if rotation has room, and makes shift if available to make room, false means no valid rotation
bool TetrisGame::rotationAnalysis(int c1r, int c1c, int c2r, int c2c, int c3r, int c3c, int c4r, int c4c)
{
  //check if rotation is legal, and perform normally if it is
  if((!checkForCollisions(currentTM->c1, c1r, c1c)) && (!checkForCollisions(currentTM->c2, c2r, c2c)) && (!checkForCollisions(currentTM->c3, c3r, c3c)) && (!checkForCollisions(currentTM->c4, c4r, c4c)) &&
     (!checkForEndOfBoard(currentTM->c1, c1r, c1c)) && (!checkForEndOfBoard(currentTM->c2, c2r, c2c)) && (!checkForEndOfBoard(currentTM->c3, c3r, c3c)) && (!checkForEndOfBoard(currentTM->c4, c4r, c4c)))
  {
    currentTM->c1->row += c1r;
    currentTM->c1->col += c1c;
    currentTM->c2->row += c2r;
    currentTM->c2->col += c2c;
    currentTM->c3->row += c3r;
    currentTM->c3->col += c3c;
    currentTM->c4->row += c4r;
    currentTM->c4->col += c4c;
    currentTM->rotatioNum++;
    return true;
  }
  //if rotation is illegal because of wall or other TM collisions
  else if((checkForCollisions(currentTM->c1, c1r, c1c)) || (checkForCollisions(currentTM->c2, c2r, c2c)) || (checkForCollisions(currentTM->c3, c3r, c3c)) || (checkForCollisions(currentTM->c4, c4r, c4c)) ||
          (checkForEndOfBoard(currentTM->c1, c1r, c1c)) || (checkForEndOfBoard(currentTM->c2, c2r, c2c)) || (checkForEndOfBoard(currentTM->c3, c3r, c3c)) || (checkForEndOfBoard(currentTM->c4, c4r, c4c)))
  {
    //make rotation
    currentTM->c1->row += c1r;
    currentTM->c1->col += c1c;
    currentTM->c2->row += c2r;
    currentTM->c2->col += c2c;
    currentTM->c3->row += c3r;
    currentTM->c3->col += c3c;
    currentTM->c4->row += c4r;
    currentTM->c4->col += c4c;
    
    //and see if there is a valid shift to make room
    if(shiftTM(0, 1))
    {currentTM->rotatioNum++; return true;}
    else if(shiftTM(0, -1))
    {currentTM->rotatioNum++; return true;}
    else if(shiftTM(1, 0))
    {currentTM->rotatioNum++; return true;}
    else if(shiftTM(-1, 0))
    {currentTM->rotatioNum++; return true;}
    else if(shiftTM(0, 2))
    {currentTM->rotatioNum++; return true;}
    else if(shiftTM(0, -2))
    {currentTM->rotatioNum++; return true;}
    
    //otherwise reset rotation
    else
    {
      currentTM->c1->row -= c1r;
      currentTM->c1->col -= c1c;
      currentTM->c2->row -= c2r;
      currentTM->c2->col -= c2c;
      currentTM->c3->row -= c3r;
      currentTM->c3->col -= c3c;
      currentTM->c4->row -= c4r;
      currentTM->c4->col -= c4c;
    }
  }
  return false;
}

