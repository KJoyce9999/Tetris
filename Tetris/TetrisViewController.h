//
//  ViewController.h
//  Tetris
//
//  Created by Keenan Joyce on 1/21/19.
//  Copyright © 2019 Keenan Joyce. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TetrisGame.hpp"

@interface TetrisViewController : UIViewController <UITextFieldDelegate>

{
  NSOperationQueue *backgroundQueue;
  NSInvocationOperation *downwardTMOP;
  
  UIView *gameView;
  
  bool gameIsPaused;
  
  int panChangeSize;
  int xPanPrevChange;
  int yPanPrevChange;
  
  UITextField *activeText;
  
  UIColor *emptyGray;
  UIColor *ghostGray;
  UIColor *cyanI;
  UIColor *yellowO;
  UIColor *purpleT;
  UIColor *greenS;
  UIColor *redZ;
  UIColor *blueJ;
  UIColor *oragneL;
  
  IBOutlet UIButton *screenTapButton;
  
  IBOutlet UIButton *resumePause;
  IBOutlet UITextField *scoreText;
  IBOutlet UITextField *levelText;
  
  IBOutlet UITextField *tCell_00;
  IBOutlet UITextField *tCell_01;
  IBOutlet UITextField *tCell_02;
  IBOutlet UITextField *tCell_03;
  IBOutlet UITextField *tCell_04;
  IBOutlet UITextField *tCell_05;
  IBOutlet UITextField *tCell_06;
  IBOutlet UITextField *tCell_07;
  IBOutlet UITextField *tCell_08;
  IBOutlet UITextField *tCell_09;
  
  IBOutlet UITextField *tCell_10;
  IBOutlet UITextField *tCell_11;
  IBOutlet UITextField *tCell_12;
  IBOutlet UITextField *tCell_13;
  IBOutlet UITextField *tCell_14;
  IBOutlet UITextField *tCell_15;
  IBOutlet UITextField *tCell_16;
  IBOutlet UITextField *tCell_17;
  IBOutlet UITextField *tCell_18;
  IBOutlet UITextField *tCell_19;
  
  IBOutlet UITextField *tCell_20;
  IBOutlet UITextField *tCell_21;
  IBOutlet UITextField *tCell_22;
  IBOutlet UITextField *tCell_23;
  IBOutlet UITextField *tCell_24;
  IBOutlet UITextField *tCell_25;
  IBOutlet UITextField *tCell_26;
  IBOutlet UITextField *tCell_27;
  IBOutlet UITextField *tCell_28;
  IBOutlet UITextField *tCell_29;
  
  IBOutlet UITextField *tCell_30;
  IBOutlet UITextField *tCell_31;
  IBOutlet UITextField *tCell_32;
  IBOutlet UITextField *tCell_33;
  IBOutlet UITextField *tCell_34;
  IBOutlet UITextField *tCell_35;
  IBOutlet UITextField *tCell_36;
  IBOutlet UITextField *tCell_37;
  IBOutlet UITextField *tCell_38;
  IBOutlet UITextField *tCell_39;
  
  IBOutlet UITextField *tCell_40;
  IBOutlet UITextField *tCell_41;
  IBOutlet UITextField *tCell_42;
  IBOutlet UITextField *tCell_43;
  IBOutlet UITextField *tCell_44;
  IBOutlet UITextField *tCell_45;
  IBOutlet UITextField *tCell_46;
  IBOutlet UITextField *tCell_47;
  IBOutlet UITextField *tCell_48;
  IBOutlet UITextField *tCell_49;
  
  IBOutlet UITextField *tCell_50;
  IBOutlet UITextField *tCell_51;
  IBOutlet UITextField *tCell_52;
  IBOutlet UITextField *tCell_53;
  IBOutlet UITextField *tCell_54;
  IBOutlet UITextField *tCell_55;
  IBOutlet UITextField *tCell_56;
  IBOutlet UITextField *tCell_57;
  IBOutlet UITextField *tCell_58;
  IBOutlet UITextField *tCell_59;
  
  IBOutlet UITextField *tCell_60;
  IBOutlet UITextField *tCell_61;
  IBOutlet UITextField *tCell_62;
  IBOutlet UITextField *tCell_63;
  IBOutlet UITextField *tCell_64;
  IBOutlet UITextField *tCell_65;
  IBOutlet UITextField *tCell_66;
  IBOutlet UITextField *tCell_67;
  IBOutlet UITextField *tCell_68;
  IBOutlet UITextField *tCell_69;
  
  IBOutlet UITextField *tCell_70;
  IBOutlet UITextField *tCell_71;
  IBOutlet UITextField *tCell_72;
  IBOutlet UITextField *tCell_73;
  IBOutlet UITextField *tCell_74;
  IBOutlet UITextField *tCell_75;
  IBOutlet UITextField *tCell_76;
  IBOutlet UITextField *tCell_77;
  IBOutlet UITextField *tCell_78;
  IBOutlet UITextField *tCell_79;
  
  IBOutlet UITextField *tCell_80;
  IBOutlet UITextField *tCell_81;
  IBOutlet UITextField *tCell_82;
  IBOutlet UITextField *tCell_83;
  IBOutlet UITextField *tCell_84;
  IBOutlet UITextField *tCell_85;
  IBOutlet UITextField *tCell_86;
  IBOutlet UITextField *tCell_87;
  IBOutlet UITextField *tCell_88;
  IBOutlet UITextField *tCell_89;
  
  IBOutlet UITextField *tCell_90;
  IBOutlet UITextField *tCell_91;
  IBOutlet UITextField *tCell_92;
  IBOutlet UITextField *tCell_93;
  IBOutlet UITextField *tCell_94;
  IBOutlet UITextField *tCell_95;
  IBOutlet UITextField *tCell_96;
  IBOutlet UITextField *tCell_97;
  IBOutlet UITextField *tCell_98;
  IBOutlet UITextField *tCell_99;
  
  IBOutlet UITextField *tCell_100;
  IBOutlet UITextField *tCell_101;
  IBOutlet UITextField *tCell_102;
  IBOutlet UITextField *tCell_103;
  IBOutlet UITextField *tCell_104;
  IBOutlet UITextField *tCell_105;
  IBOutlet UITextField *tCell_106;
  IBOutlet UITextField *tCell_107;
  IBOutlet UITextField *tCell_108;
  IBOutlet UITextField *tCell_109;
  
  IBOutlet UITextField *tCell_110;
  IBOutlet UITextField *tCell_111;
  IBOutlet UITextField *tCell_112;
  IBOutlet UITextField *tCell_113;
  IBOutlet UITextField *tCell_114;
  IBOutlet UITextField *tCell_115;
  IBOutlet UITextField *tCell_116;
  IBOutlet UITextField *tCell_117;
  IBOutlet UITextField *tCell_118;
  IBOutlet UITextField *tCell_119;

  IBOutlet UITextField *tCell_120;
  IBOutlet UITextField *tCell_121;
  IBOutlet UITextField *tCell_122;
  IBOutlet UITextField *tCell_123;
  IBOutlet UITextField *tCell_124;
  IBOutlet UITextField *tCell_125;
  IBOutlet UITextField *tCell_126;
  IBOutlet UITextField *tCell_127;
  IBOutlet UITextField *tCell_128;
  IBOutlet UITextField *tCell_129;
  
  IBOutlet UITextField *tCell_130;
  IBOutlet UITextField *tCell_131;
  IBOutlet UITextField *tCell_132;
  IBOutlet UITextField *tCell_133;
  IBOutlet UITextField *tCell_134;
  IBOutlet UITextField *tCell_135;
  IBOutlet UITextField *tCell_136;
  IBOutlet UITextField *tCell_137;
  IBOutlet UITextField *tCell_138;
  IBOutlet UITextField *tCell_139;
  
  IBOutlet UITextField *tCell_140;
  IBOutlet UITextField *tCell_141;
  IBOutlet UITextField *tCell_142;
  IBOutlet UITextField *tCell_143;
  IBOutlet UITextField *tCell_144;
  IBOutlet UITextField *tCell_145;
  IBOutlet UITextField *tCell_146;
  IBOutlet UITextField *tCell_147;
  IBOutlet UITextField *tCell_148;
  IBOutlet UITextField *tCell_149;
  
  IBOutlet UITextField *tCell_150;
  IBOutlet UITextField *tCell_151;
  IBOutlet UITextField *tCell_152;
  IBOutlet UITextField *tCell_153;
  IBOutlet UITextField *tCell_154;
  IBOutlet UITextField *tCell_155;
  IBOutlet UITextField *tCell_156;
  IBOutlet UITextField *tCell_157;
  IBOutlet UITextField *tCell_158;
  IBOutlet UITextField *tCell_159;
  
  IBOutlet UITextField *tCell_160;
  IBOutlet UITextField *tCell_161;
  IBOutlet UITextField *tCell_162;
  IBOutlet UITextField *tCell_163;
  IBOutlet UITextField *tCell_164;
  IBOutlet UITextField *tCell_165;
  IBOutlet UITextField *tCell_166;
  IBOutlet UITextField *tCell_167;
  IBOutlet UITextField *tCell_168;
  IBOutlet UITextField *tCell_169;

  IBOutlet UITextField *tCell_170;
  IBOutlet UITextField *tCell_171;
  IBOutlet UITextField *tCell_172;
  IBOutlet UITextField *tCell_173;
  IBOutlet UITextField *tCell_174;
  IBOutlet UITextField *tCell_175;
  IBOutlet UITextField *tCell_176;
  IBOutlet UITextField *tCell_177;
  IBOutlet UITextField *tCell_178;
  IBOutlet UITextField *tCell_179;
  
  IBOutlet UITextField *tCell_180;
  IBOutlet UITextField *tCell_181;
  IBOutlet UITextField *tCell_182;
  IBOutlet UITextField *tCell_183;
  IBOutlet UITextField *tCell_184;
  IBOutlet UITextField *tCell_185;
  IBOutlet UITextField *tCell_186;
  IBOutlet UITextField *tCell_187;
  IBOutlet UITextField *tCell_188;
  IBOutlet UITextField *tCell_189;
  
  IBOutlet UITextField *tCell_190;
  IBOutlet UITextField *tCell_191;
  IBOutlet UITextField *tCell_192;
  IBOutlet UITextField *tCell_193;
  IBOutlet UITextField *tCell_194;
  IBOutlet UITextField *tCell_195;
  IBOutlet UITextField *tCell_196;
  IBOutlet UITextField *tCell_197;
  IBOutlet UITextField *tCell_198;
  IBOutlet UITextField *tCell_199;


}



@end

