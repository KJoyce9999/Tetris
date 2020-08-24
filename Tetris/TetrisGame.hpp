//
//  TetrisGame.hpp
//  Tetris
//
//  Created by Keenan Joyce on 1/21/19.
//  Copyright © 2019 Keenan Joyce. All rights reserved.
//

#ifndef TetrisGame_hpp
#define TetrisGame_hpp

#include <stdio.h>

struct coord
{
  int row;
  int col;
};

enum tetrominos // piece types
{emptyCell, I, O, T, S, Z, J, L};

struct tetromino  //instance of actual piece
{
  int TMValue;
  
  int rotatioNum;
  
  struct coord *c1;
  struct coord *c2;
  struct coord *c3;
  struct coord *c4;
};

class TetrisGame
{
public:
  TetrisGame();                              //class constructor
  ~TetrisGame();                             //class deconstructor
  void newBoard();                           //clears the board
  void loadBoard(int **);                    //loads a board
  void addRandomTM();                        //adds a new random tetromino to the currentTM
  void popTMCoords(tetrominos);              //populates currentTM with proper coords
  int  checkHigherPlace(tetromino *);        //checks if new piece needs to start higher, returns how many rows
  void rotateTM();                           //rotates current tetromino
  bool rotationAnalysis(int, int, int, int, int, int, int, int);//check if rotation has room, and makes shift if available to make room, false means no valid rotation
  bool shiftTM(int, int);                    //shifts current TM in specified direction, returns false if move not allowed
  void changeBoard(tetromino *);             //adds currenTM to game board
  void completeLines();                      //scans board to complete and remove entirely filled rows
  bool checkForEndGame();                    //scans the baord to see if game is over, true means over
  bool checkForEndOfBoard(coord *, int, int);//checks if TM movement falls off board, true means hits end
  bool checkForCollisions(coord *, int, int);//checks for collisions with other tetrominos, true means hits another TM
  void clearLine(int);                       //deletes line and shifts above rows down
  int  getBoardValue(int, int);              //returns value at specified cell
  tetromino* getTM();                        //returns entire TM object
  int score;                                 //total score for current game
  int level;                                 //current game level
  float levelTime;                           //duration of TM movement
  void assessLevel();                        //determine when to increase level
  void shiftGhostTm();                       //automates where currentTM would land
  tetromino *currentTM;                      //current game piece
  tetromino *ghostTM;                        //ghost piece is where currentTM would land
  
private:
  int **gameBoard;            //visible game board is 20x10 there are 4 extra hidden vertical slots for new piece injection and rotation
  int prevTM;
  int prevPrevTM;
  
};

#endif /* TetrisGame_hpp */
