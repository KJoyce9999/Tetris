//
//  ViewController.m
//  Tetris
//
//  Created by Keenan Joyce on 1/21/19.
//  Copyright © 2019 Keenan Joyce. All rights reserved.
//

#import "TetrisViewController.h"
#include <iostream>

@interface TetrisViewController ()
{
  TetrisGame currentGame;
}
@end

@implementation TetrisViewController

- (void)viewDidLoad {

  [super viewDidLoad];
  
  UIGraphicsBeginImageContext(self.view.frame.size); // re-size image to fit view
  [[UIImage imageNamed:@"milky-way-960x539.jpg"] drawInRect:self.view.bounds];
  UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
  UIGraphicsEndImageContext();
  self.view.backgroundColor = [UIColor colorWithPatternImage:image];
  
  scoreText.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"milky-way-960x539.jpg"]];
  levelText.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"milky-way-960x539.jpg"]];
  resumePause.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@""]];
  
  [resumePause setTitle:@"New Game" forState:(UIControlStateNormal)];
  
  UIPanGestureRecognizer *pan = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handlePan:)];
  [self.view addGestureRecognizer:pan];
  
  [self disableTextFieldKeyboards];
  [self loadColors];
  
  backgroundQueue = [NSOperationQueue new];
  panChangeSize = 35;
  xPanPrevChange = 0;
  yPanPrevChange = 0;
  gameIsPaused = true;
  currentGame.newBoard();
  
  [self displayGameBoard];
  
  if(currentGame.currentTM->TMValue != 0)
  {[self displaGhostTM]; [self displayCurrentTM];}
}

- (void)didReceiveMemoryWarning
{
  [super didReceiveMemoryWarning];
  // Dispose of any resources that can be recreated.
}

-(BOOL)textFieldShouldBeginEditing:(UITextField *)textField  //called to hide both keyboard and blinking cursor when textField is slected
{return false;}

-(void) gameRun
{
  while(!currentGame.checkForEndGame())
  {
    if(gameIsPaused)
    {return;}
    
    if(currentGame.currentTM->TMValue == 0) //make sure there not already an active game piece
    {currentGame.addRandomTM(); dispatch_sync(dispatch_get_main_queue(), ^{[self displayGameBoard]; [self displaGhostTM]; [self displayCurrentTM];}); [NSThread sleepForTimeInterval:currentGame.levelTime];}
  
    if(currentGame.shiftTM(-1, 0))
    {dispatch_sync(dispatch_get_main_queue(), ^{[self displayGameBoard]; [self displaGhostTM]; [self displayCurrentTM];}); [NSThread sleepForTimeInterval:currentGame.levelTime];}
    else
    {currentGame.changeBoard(currentGame.getTM()); currentGame.completeLines(); dispatch_sync(dispatch_get_main_queue(), ^{[self displayGameBoard];});}
  }
  [backgroundQueue cancelAllOperations];
  [NSThread sleepForTimeInterval:currentGame.levelTime];
  if(currentGame.checkForEndGame())
  {
    UIAlertController *alertController = [UIAlertController
                                          alertControllerWithTitle:[NSString stringWithFormat:@"Game Over!"]
                                          message:[NSString stringWithFormat:@"You Reached Level %i With %i Points", currentGame.level, currentGame.score]
                                          preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *newGame = [UIAlertAction
                               actionWithTitle:NSLocalizedString(@"Continue",)
                               style:UIAlertActionStyleDefault
                               handler:^(UIAlertAction *newGame)
                              {self->currentGame.newBoard(); [self displayGameBoard]; [self resumePause];}];
    [alertController addAction:newGame];
    [self presentViewController:alertController animated:YES completion:nil];
  }
  
}

-(IBAction) resumePause
{
  if(gameIsPaused)
  {
    [resumePause setTitle:@"Pause" forState:(UIControlStateNormal)];
    downwardTMOP = [[NSInvocationOperation alloc] initWithTarget:self selector:@selector(gameRun) object:nil];
    
    gameIsPaused = false;
    [backgroundQueue addOperation:downwardTMOP];
  }
  else if(!gameIsPaused)
  {
    if(currentGame.currentTM->TMValue==0)
    {[self->resumePause setTitle:@"New Game" forState:(UIControlStateNormal)];}
    else
    [resumePause setTitle:@"Resume" forState:(UIControlStateNormal)];
    gameIsPaused = true;
    [backgroundQueue cancelAllOperations];
    [NSThread sleepForTimeInterval:currentGame.levelTime];
  }
}

- (void)handlePan:(UIPanGestureRecognizer *)recognizer  //handle swipe movements
{
  CGPoint movement = [recognizer translationInView:self.view];  //object that contains x & y finger movement
  
  if((movement.x > (xPanPrevChange + panChangeSize)) && (movement.y > -panChangeSize)) //swipe right
  {
    xPanPrevChange += panChangeSize;
    currentGame.shiftTM(0, 1);
    [self displayGameBoard];
    [self displaGhostTM];
    [self displayCurrentTM];
  }
  else if((movement.x < (xPanPrevChange - panChangeSize)) && (movement.y > -panChangeSize))  //swipe left
  {
    xPanPrevChange -= panChangeSize;
    currentGame.shiftTM(0, -1);
    [self displayGameBoard];
    [self displaGhostTM];
    [self displayCurrentTM];
  }
  else if(movement.y > (yPanPrevChange + panChangeSize))  //swipe down
  {
    yPanPrevChange += panChangeSize;
    currentGame.shiftTM(-1, 0);
    [self displayGameBoard];
    [self displaGhostTM];
    [self displayCurrentTM];
  }
  else if(movement.y < (yPanPrevChange - (panChangeSize*2)))  //swipe up
  {
    yPanPrevChange -= (panChangeSize*2);
    while(currentGame.shiftTM(-1, 0));
    [self displayGameBoard];
    [self displayCurrentTM];
  }
  if(recognizer.state == UIGestureRecognizerStateEnded) //reset values when finger is lifted
  {
    xPanPrevChange = 0;
    yPanPrevChange = 0;
  }
}

-(IBAction)screenTap
{
  if(!gameIsPaused)
  {
    currentGame.rotateTM();
    [self displayGameBoard];
    [self displaGhostTM];
    [self displayCurrentTM];
  }
}

-(void) displayGameBoard
{
  for(int row = 0; row < 24; row++)
    {for(int col = 0; col < 10; col++)
    {[self fillCellWithColor:row :col :currentGame.getBoardValue(row, col)];
      }
  }
  scoreText.text = [NSString stringWithFormat:@"%i", currentGame.score];
  levelText.text = [NSString stringWithFormat:@"%i", currentGame.level];
}

-(void) displayCurrentTM
{
  coord *tempC = currentGame.currentTM->c1;
  if(((tempC->row >= 0)&&(tempC->row < 20)) && ((tempC->col >= 0)&&(tempC->col < 10)))
  {[self fillCellWithColor:tempC->row :tempC->col :currentGame.currentTM->TMValue];}
  tempC = currentGame.currentTM->c2;
  if(((tempC->row >= 0)&&(tempC->row < 20)) && ((tempC->col >= 0)&&(tempC->col < 10)))
  {[self fillCellWithColor:tempC->row :tempC->col :currentGame.currentTM->TMValue];}
  tempC = currentGame.currentTM->c3;
  if(((tempC->row >= 0)&&(tempC->row < 20)) && ((tempC->col >= 0)&&(tempC->col < 10)))
  {[self fillCellWithColor:tempC->row :tempC->col :currentGame.currentTM->TMValue];}
  tempC = currentGame.currentTM->c4;
  if(((tempC->row >= 0)&&(tempC->row < 20)) && ((tempC->col >= 0)&&(tempC->col < 10)))
  {[self fillCellWithColor:tempC->row :tempC->col :currentGame.currentTM->TMValue];}
}

-(void) displaGhostTM
{
  coord *tempC = currentGame.ghostTM->c1;
  if(((tempC->row >= 0)&&(tempC->row < 20)) && ((tempC->col >= 0)&&(tempC->col < 10)))
  {[self fillCellWithColor:tempC->row :tempC->col :currentGame.ghostTM->TMValue];}
  tempC = currentGame.ghostTM->c2;
  if(((tempC->row >= 0)&&(tempC->row < 20)) && ((tempC->col >= 0)&&(tempC->col < 10)))
  {[self fillCellWithColor:tempC->row :tempC->col :currentGame.ghostTM->TMValue];}
  tempC = currentGame.ghostTM->c3;
  if(((tempC->row >= 0)&&(tempC->row < 20)) && ((tempC->col >= 0)&&(tempC->col < 10)))
  {[self fillCellWithColor:tempC->row :tempC->col :currentGame.ghostTM->TMValue];}
  tempC = currentGame.ghostTM->c4;
  if(((tempC->row >= 0)&&(tempC->row < 20)) && ((tempC->col >= 0)&&(tempC->col < 10)))
  {[self fillCellWithColor:tempC->row :tempC->col :currentGame.ghostTM->TMValue];}
}

-(void)fillCellWithColor: (int) row : (int) col : (int) type
{
  [self assignActiveCell:row :col];
  
  switch(type)
  {
    case 0:
      activeText.backgroundColor = emptyGray;
      break;
    case 1:
      activeText.backgroundColor = cyanI;
      break;
    case 2:
      activeText.backgroundColor = yellowO;
      break;
    case 3:
      activeText.backgroundColor = purpleT;
      break;
    case 4:
      activeText.backgroundColor = greenS;
      break;
    case 5:
      activeText.backgroundColor = redZ;
      break;
    case 6:
      activeText.backgroundColor = blueJ;
      break;
    case 7:
      activeText.backgroundColor = oragneL;
      break;
    case 8:
      activeText.backgroundColor = ghostGray;
      break;
  }
}

-(void) loadColors
{
  emptyGray = [UIColor colorWithRed:0.69 green:0.69 blue:0.69 alpha:0.36];
  ghostGray = [UIColor colorWithRed:0.36 green:0.36 blue:0.36 alpha:0.18];
  cyanI = [UIColor colorWithRed:0.27 green:0.90 blue:0.94 alpha:1.00];
  yellowO = [UIColor colorWithRed:0.99 green:0.96 blue:0.00 alpha:1.00];
  purpleT = [UIColor colorWithRed:0.54 green:0.09 blue:0.99 alpha:1.00];
  greenS = [UIColor colorWithRed:0.00 green:0.81 blue:0.04 alpha:1.00];
  redZ = [UIColor colorWithRed:0.99 green:0.00 blue:0.00 alpha:1.00];
  blueJ = [UIColor colorWithRed:0.00 green:0.22 blue:0.99 alpha:1.00];
  oragneL = [UIColor colorWithRed:0.99 green:0.54 blue:0.0 alpha:1.00];
}

-(void) disableTextFieldKeyboards //disable keyboard from popping up when clicking on textField cells
{
  for(int row = 0; row < 20; row ++)
  {for(int col = 0; col < 10; col++)
    {[self assignActiveCell:row :col];
      activeText.delegate = self;
    }
  }
  scoreText.delegate = self;
}

-(void) assignActiveCell: (int) row : (int) col
{
  int cellIndex = (row * 10) + col;
  
  switch(cellIndex)
  {
    case 0:
      activeText = tCell_00;
      break;
    case 1:
      activeText = tCell_01;
      break;
    case 2:
      activeText = tCell_02;
      break;
    case 3:
      activeText = tCell_03;
      break;
    case 4:
      activeText = tCell_04;
      break;
    case 5:
      activeText = tCell_05;
      break;
    case 6:
      activeText = tCell_06;
      break;
    case 7:
      activeText = tCell_07;
      break;
    case 8:
      activeText = tCell_08;
      break;
    case 9:
      activeText = tCell_09;
      break;
    case 10:
      activeText = tCell_10;
      break;
    case 11:
      activeText = tCell_11;
      break;
    case 12:
      activeText = tCell_12;
      break;
    case 13:
      activeText = tCell_13;
      break;
    case 14:
      activeText = tCell_14;
      break;
    case 15:
      activeText = tCell_15;
      break;
    case 16:
      activeText = tCell_16;
      break;
    case 17:
      activeText = tCell_17;
      break;
    case 18:
      activeText = tCell_18;
      break;
    case 19:
      activeText = tCell_19;
      break;
    case 20:
      activeText = tCell_20;
      break;
    case 21:
      activeText = tCell_21;
      break;
    case 22:
      activeText = tCell_22;
      break;
    case 23:
      activeText = tCell_23;
      break;
    case 24:
      activeText = tCell_24;
      break;
    case 25:
      activeText = tCell_25;
      break;
    case 26:
      activeText = tCell_26;
      break;
    case 27:
      activeText = tCell_27;
      break;
    case 28:
      activeText = tCell_28;
      break;
    case 29:
      activeText = tCell_29;
      break;
    case 30:
      activeText = tCell_30;
      break;
    case 31:
      activeText = tCell_31;
      break;
    case 32:
      activeText = tCell_32;
      break;
    case 33:
      activeText = tCell_33;
      break;
    case 34:
      activeText = tCell_34;
      break;
    case 35:
      activeText = tCell_35;
      break;
    case 36:
      activeText = tCell_36;
      break;
    case 37:
      activeText = tCell_37;
      break;
    case 38:
      activeText = tCell_38;
      break;
    case 39:
      activeText = tCell_39;
      break;
    case 40:
      activeText = tCell_40;
      break;
    case 41:
      activeText = tCell_41;
      break;
    case 42:
      activeText = tCell_42;
      break;
    case 43:
      activeText = tCell_43;
      break;
    case 44:
      activeText = tCell_44;
      break;
    case 45:
      activeText = tCell_45;
      break;
    case 46:
      activeText = tCell_46;
      break;
    case 47:
      activeText = tCell_47;
      break;
    case 48:
      activeText = tCell_48;
      break;
    case 49:
      activeText = tCell_49;
      break;
    case 50:
      activeText = tCell_50;
      break;
    case 51:
      activeText = tCell_51;
      break;
    case 52:
      activeText = tCell_52;
      break;
    case 53:
      activeText = tCell_53;
      break;
    case 54:
      activeText = tCell_54;
      break;
    case 55:
      activeText = tCell_55;
      break;
    case 56:
      activeText = tCell_56;
      break;
    case 57:
      activeText = tCell_57;
      break;
    case 58:
      activeText = tCell_58;
      break;
    case 59:
      activeText = tCell_59;
      break;
    case 60:
      activeText = tCell_60;
      break;
    case 61:
      activeText = tCell_61;
      break;
    case 62:
      activeText = tCell_62;
      break;
    case 63:
      activeText = tCell_63;
      break;
    case 64:
      activeText = tCell_64;
      break;
    case 65:
      activeText = tCell_65;
      break;
    case 66:
      activeText = tCell_66;
      break;
    case 67:
      activeText = tCell_67;
      break;
    case 68:
      activeText = tCell_68;
      break;
    case 69:
      activeText = tCell_69;
      break;
    case 70:
      activeText = tCell_70;
      break;
    case 71:
      activeText = tCell_71;
      break;
    case 72:
      activeText = tCell_72;
      break;
    case 73:
      activeText = tCell_73;
      break;
    case 74:
      activeText = tCell_74;
      break;
    case 75:
      activeText = tCell_75;
      break;
    case 76:
      activeText = tCell_76;
      break;
    case 77:
      activeText = tCell_77;
      break;
    case 78:
      activeText = tCell_78;
      break;
    case 79:
      activeText = tCell_79;
      break;
    case 80:
      activeText = tCell_80;
      break;
    case 81:
      activeText = tCell_81;
      break;
    case 82:
      activeText = tCell_82;
      break;
    case 83:
      activeText = tCell_83;
      break;
    case 84:
      activeText = tCell_84;
      break;
    case 85:
      activeText = tCell_85;
      break;
    case 86:
      activeText = tCell_86;
      break;
    case 87:
      activeText = tCell_87;
      break;
    case 88:
      activeText = tCell_88;
      break;
    case 89:
      activeText = tCell_89;
      break;
    case 90:
      activeText = tCell_90;
      break;
    case 91:
      activeText = tCell_91;
      break;
    case 92:
      activeText = tCell_92;
      break;
    case 93:
      activeText = tCell_93;
      break;
    case 94:
      activeText = tCell_94;
      break;
    case 95:
      activeText = tCell_95;
      break;
    case 96:
      activeText = tCell_96;
      break;
    case 97:
      activeText = tCell_97;
      break;
    case 98:
      activeText = tCell_98;
      break;
    case 99:
      activeText = tCell_99;
      break;
    case 100:
      activeText = tCell_100;
      break;
    case 101:
      activeText = tCell_101;
      break;
    case 102:
      activeText = tCell_102;
      break;
    case 103:
      activeText = tCell_103;
      break;
    case 104:
      activeText = tCell_104;
      break;
    case 105:
      activeText = tCell_105;
      break;
    case 106:
      activeText = tCell_106;
      break;
    case 107:
      activeText = tCell_107;
      break;
    case 108:
      activeText = tCell_108;
      break;
    case 109:
      activeText = tCell_109;
      break;
    case 110:
      activeText = tCell_110;
      break;
    case 111:
      activeText = tCell_111;
      break;
    case 112:
      activeText = tCell_112;
      break;
    case 113:
      activeText = tCell_113;
      break;
    case 114:
      activeText = tCell_114;
      break;
    case 115:
      activeText = tCell_115;
      break;
    case 116:
      activeText = tCell_116;
      break;
    case 117:
      activeText = tCell_117;
      break;
    case 118:
      activeText = tCell_118;
      break;
    case 119:
      activeText = tCell_119;
      break;
    case 120:
      activeText = tCell_120;
      break;
    case 121:
      activeText = tCell_121;
      break;
    case 122:
      activeText = tCell_122;
      break;
    case 123:
      activeText = tCell_123;
      break;
    case 124:
      activeText = tCell_124;
      break;
    case 125:
      activeText = tCell_125;
      break;
    case 126:
      activeText = tCell_126;
      break;
    case 127:
      activeText = tCell_127;
      break;
    case 128:
      activeText = tCell_128;
      break;
    case 129:
      activeText = tCell_129;
      break;
    case 130:
      activeText = tCell_130;
      break;
    case 131:
      activeText = tCell_131;
      break;
    case 132:
      activeText = tCell_132;
      break;
    case 133:
      activeText = tCell_133;
      break;
    case 134:
      activeText = tCell_134;
      break;
    case 135:
      activeText = tCell_135;
      break;
    case 136:
      activeText = tCell_136;
      break;
    case 137:
      activeText = tCell_137;
      break;
    case 138:
      activeText = tCell_138;
      break;
    case 139:
      activeText = tCell_139;
      break;
    case 140:
      activeText = tCell_140;
      break;
    case 141:
      activeText = tCell_141;
      break;
    case 142:
      activeText = tCell_142;
      break;
    case 143:
      activeText = tCell_143;
      break;
    case 144:
      activeText = tCell_144;
      break;
    case 145:
      activeText = tCell_145;
      break;
    case 146:
      activeText = tCell_146;
      break;
    case 147:
      activeText = tCell_147;
      break;
    case 148:
      activeText = tCell_148;
      break;
    case 149:
      activeText = tCell_149;
      break;
    case 150:
      activeText = tCell_150;
      break;
    case 151:
      activeText = tCell_151;
      break;
    case 152:
      activeText = tCell_152;
      break;
    case 153:
      activeText = tCell_153;
      break;
    case 154:
      activeText = tCell_154;
      break;
    case 155:
      activeText = tCell_155;
      break;
    case 156:
      activeText = tCell_156;
      break;
    case 157:
      activeText = tCell_157;
      break;
    case 158:
      activeText = tCell_158;
      break;
    case 159:
      activeText = tCell_159;
      break;
    case 160:
      activeText = tCell_160;
      break;
    case 161:
      activeText = tCell_161;
      break;
    case 162:
      activeText = tCell_162;
      break;
    case 163:
      activeText = tCell_163;
      break;
    case 164:
      activeText = tCell_164;
      break;
    case 165:
      activeText = tCell_165;
      break;
    case 166:
      activeText = tCell_166;
      break;
    case 167:
      activeText = tCell_167;
      break;
    case 168:
      activeText = tCell_168;
      break;
    case 169:
      activeText = tCell_169;
      break;
    case 170:
      activeText = tCell_170;
      break;
    case 171:
      activeText = tCell_171;
      break;
    case 172:
      activeText = tCell_172;
      break;
    case 173:
      activeText = tCell_173;
      break;
    case 174:
      activeText = tCell_174;
      break;
    case 175:
      activeText = tCell_175;
      break;
    case 176:
      activeText = tCell_176;
      break;
    case 177:
      activeText = tCell_177;
      break;
    case 178:
      activeText = tCell_178;
      break;
    case 179:
      activeText = tCell_179;
      break;
    case 180:
      activeText = tCell_180;
      break;
    case 181:
      activeText = tCell_181;
      break;
    case 182:
      activeText = tCell_182;
      break;
    case 183:
      activeText = tCell_183;
      break;
    case 184:
      activeText = tCell_184;
      break;
    case 185:
      activeText = tCell_185;
      break;
    case 186:
      activeText = tCell_186;
      break;
    case 187:
      activeText = tCell_187;
      break;
    case 188:
      activeText = tCell_188;
      break;
    case 189:
      activeText = tCell_189;
      break;
    case 190:
      activeText = tCell_190;
      break;
    case 191:
      activeText = tCell_191;
      break;
    case 192:
      activeText = tCell_192;
      break;
    case 193:
      activeText = tCell_193;
      break;
    case 194:
      activeText = tCell_194;
      break;
    case 195:
      activeText = tCell_195;
      break;
    case 196:
      activeText = tCell_196;
      break;
    case 197:
      activeText = tCell_197;
      break;
    case 198:
      activeText = tCell_198;
      break;
    case 199:
      activeText = tCell_199;
      break;
  }
}


@end
