//***************************************************************************
//
// File Name : "DotMatrixLEDs_16x7.ino"
// Title : 16 by 7 Dot Matrix LED Sign for Ardiuno UNO Rev3
// Date : 6/26/19
// Version : 1.0
// Target MCU : Ardiuno UNO Rev3
// Target Hardware : Ardiuno UNO Rev3
// Authors : Zhen Sin (William) Wong
// DESCRIPTION: Driver for a 16 by 7 Dot Matrix LED board. This file
//    configures the target MCU's Digital Pins 2-13 as outputs to drive the 
//    board. Digital Pins 2-8 are used for the Anodes of the board and 
//    digital pins 9-12 are used as encoded Cathodes. These are put through
//    2 3-to-8 encoders to drive 16 columns of cathodes to be multiplexed.
//    The included code can display single characters with 2 justification
//    modes as well as scroll through a line of text with a variable speed.
//
// Revision History : Initial version
//
//
//**************************************************************************


#include <elapsedMillis.h>
#define toggleCath B00100000
#define resetCath B00100000
#define START_CHAR ' '
#define off B00000000
/*  code */
const byte sp_PORTD[] {B00000000, B00000000, B00000000, B00000000, B00000000};
const byte sp_PORTB[] {B00100000, B00100000, B00100000, B00100000, B00100000};
/* ! code */
const byte fact_PORTD[] {B00000000, B00111000, B01111100, B00111000, B00000000};
const byte fact_PORTB[] {B00100000, B00100000, B00100001, B00100000, B00100000};
/* " code */
const byte qt_PORTD[] {B00001100, B00011100, B00000000, B00001100, B00011100};
const byte qt_PORTB[] {B00100000, B00100000, B00100000, B00100000, B00100000};
/* # code */
const byte hsh_PORTD[] {B01010000, B11111100, B01010000, B11111100, B01010000};
const byte hsh_PORTB[] {B00100000, B00100001, B00100000, B00100001, B00100000};
/* $ code */
const byte dlr_PORTD[] {B10011000, B00100100, B11111100, B00100100, B11001000};
const byte dlr_PORTB[] {B00100000, B00100001, B00100001, B00100001, B00100000};
/* % code */
const byte pct_PORTD[] {B10001100, B01001100, B00100000, B10010000, B10001100};
const byte pct_PORTB[] {B00100001, B00100000, B00100000, B00100001, B00100001};
/* & code */
const byte and_PORTD[] {B11011000, B00100100, B01011000, B10000000, B01000000};
const byte and_PORTB[] {B00100000, B00100001, B00100001, B00100000, B00100001};
/* ' code */
const byte apst_PORTD[] {B00000000, B00000000, B00001100, B00011100, B00000000};
const byte apst_PORTB[] {B00100000, B00100000, B00100000, B00100000, B00100000};
/* ( code */
const byte opar_PORTD[] {B00000000, B00000000, B11111000, B00000100, B00000000};
const byte opar_PORTB[] {B00100000, B00100000, B00100000, B00100001, B00100000};
/* ) code */
const byte cpar_PORTD[] {B00000100, B11111000, B00000000, B00000000, B00000000};
const byte cpar_PORTB[] {B00100001, B00100000, B00100000, B00100000, B00100000};
/* * code */
const byte ast_PORTD[] {B10101000, B01110000, B11111100, B01110000, B10101000};
const byte ast_PORTB[] {B00100000, B00100000, B00100001, B00100000, B00100000};
/* + code */
const byte add_PORTD[] {B00100000, B00100000, B11111000, B00100000, B00100000};
const byte add_PORTB[] {B00100000, B00100000, B00100000, B00100000, B00100000};
/* , code */
const byte cma_PORTD[] {B11000000, B11000000, B00000000, B00000000, B00000000};
const byte cma_PORTB[] {B00100000, B00100001, B00100000, B00100000, B00100000};
/* - code */
const byte sub_PORTD[] {B00100000, B00100000, B00100000, B00100000, B00100000};
const byte sub_PORTB[] {B00100000, B00100000, B00100000, B00100000, B00100000};
/* . code */
const byte pd_PORTD[] {B00000000, B10000000, B10000000, B00000000, B00000000};
const byte pd_PORTB[] {B00100000, B00100001, B00100001, B00100000, B00100000};
/* / code */
const byte bkSls_PORTD[] {B10000000, B01000000, B00100000, B00010000, B00001100};
const byte bkSls_PORTB[] {B00100001, B00100000, B00100000, B00100000, B00100000};
/* 0 code */
const byte zero_PORTD[] {B11111000, B01000100, B00100100, B00010100, B11111000};
const byte zero_PORTB[] {B00100000, B00100001, B00100001, B00100001, B00100000};
/* 1 code */
const byte one_PORTD[] {B00000000, B00001000, B11111100, B00000000, B00000000};
const byte one_PORTB[] {B00100001, B00100001, B00100001, B00100001, B00100001};
/* 2 code */
const byte two_PORTD[] {B00001000, B10000100, B01000100, B00100100, B00011000};
const byte two_PORTB[] {B00100001, B00100001, B00100001, B00100001, B00100001};
/* 3 code */
const byte thr_PORTD[] {B10001000, B00000100, B00100100, B00100100, B11011000};
const byte thr_PORTB[] {B00100000, B00100001, B00100001, B00100001, B00100000};
/* 4 code */
const byte for_PORTD[] {B01100000, B01010000, B01001000, B11111100, B01000000};
const byte for_PORTB[] {B00100000, B00100000, B00100000, B00100001, B00100000};
/* 5 code */
const byte fv_PORTD[] {B10011100, B00010100, B00010100, B00010100, B11100100};
const byte fv_PORTB[] {B00100000, B00100001, B00100001, B00100001, B00100000};
/* 6 code */
const byte sx_PORTD[] {B11111000, B00100100, B00100100, B00100100, B11001000};
const byte sx_PORTB[] {B00100000, B00100001, B00100001, B00100001, B00100000};
/* 7 code */
const byte sv_PORTD[] {B10000100, B01000100, B00100100, B00010100, B00001100};
const byte sv_PORTB[] {B00100001, B00100000, B00100000, B00100000, B00100000};
/* 8 code */
const byte et_PORTD[] {B11011000, B00100100, B00100100, B00100100, B11011000};
const byte et_PORTB[] {B00100000, B00100001, B00100001, B00100001, B00100000};
/* 9 code */
const byte nin_PORTD[] {B00011000, B00100100, B10100100, B01100100, B00111000};
const byte nin_PORTB[] {B00100000, B00100001, B00100000, B00100000, B00100000};
/* : code */
const byte col_PORTD[] {B00000000, B10001100, B10001100, B00000000, B00000000};
const byte col_PORTB[] {B00100000, B00100001, B00100001, B00100000, B00100000};
/* ; code */
const byte smcol_PORTD[] {B00000000, B11001100, B11001100, B00000000, B00000000};
const byte smcol_PORTB[] {B00100000, B00100000, B00100001, B00100000, B00100000};
/* < code */
const byte lt_PORTD[] {B01000000, B01100000, B01010000, B01001000, B01000000};
const byte lt_PORTB[] {B00100000, B00100000, B00100000, B00100000, B00100000};
/* = code */
const byte eq_PORTD[] {B01010000, B01010000, B01010000, B01010000, B01010000};
const byte eq_PORTB[] {B00100000, B00100000, B00100000, B00100000, B00100000};
/* > code */
const byte gt_PORTD[] {B01000000, B01001000, B01010000, B01100000, B01000000};
const byte gt_PORTB[] {B00100000, B00100000, B00100000, B00100000, B00100000};
/* ? code */
const byte quest_PORTD[] {B00001000, B00000100, B01100100, B00100100, B00011000};
const byte quest_PORTB[] {B00100000, B00100000, B00100001, B00100000, B00100000};
/* @ code */
const byte at_PORTD[] {B11111000, B11100100, B01010100, B11100100, B11111000};
const byte at_PORTB[] {B00100000, B00100001, B00100001, B00100001, B00100000};
/* A code */
const byte A_PORTD[] {B11111000, B00100100, B00100100, B00100100, B11111000};
const byte A_PORTB[] {B00100001, B00100000, B00100000, B00100000, B00100001};
/* B code */
const byte B_PORTD[] {B11111100, B00100100, B00100100, B00111000, B11000000};
const byte B_PORTB[] {B00100001, B00100001, B00100001, B00100001, B00100000};
/* C code */
const byte C_PORTD[] {B11111000, B00000100, B00000100, B00000100, B10001000};
const byte C_PORTB[] {B00100000, B00100001, B00100001, B00100001, B00100000};
/* D code */
const byte D_PORTD[] {B11111100, B00000100, B00000100, B00000100, B11111000};
const byte D_PORTB[] {B00100001, B00100001, B00100001, B00100001, B00100000};
/* E code */
const byte E_PORTD[] {B11111100, B00100100, B00100100, B00000100, B00000100};
const byte E_PORTB[] {B00100001, B00100001, B00100001, B00100001, B00100001};
/* F code */
const byte F_PORTD[] {B11111100, B00100100, B00100100, B00100100, B00000100};
const byte F_PORTB[] {B00100001, B00100000, B00100000, B00100000, B00100000};
/* G code */
const byte G_PORTD[] {B11111000, B00000100, B01000100, B01000100, B11001000};
const byte G_PORTB[] {B00100000, B00100001, B00100001, B00100001, B00100000};
/* H code */
const byte H_PORTD[] {B11111100, B00100000, B00100000, B00100000, B11111100};
const byte H_PORTB[] {B00100001, B00100000, B00100000, B00100000, B00100001};
/* I code */
const byte I_PORTD[] {B00000100, B00000100, B11111100, B00000100, B00000100};
const byte I_PORTB[] {B00100001, B00100001, B00100001, B00100001, B00100001};
/* J code */
const byte J_PORTD[] {B10000000, B00000000, B00000000, B00000000, B11111100};
const byte J_PORTB[] {B00100000, B00100001, B00100001, B00100001, B00100000};
/* K code */
const byte K_PORTD[] {B11111100, B00100000, B01010000, B10001000, B00000100};
const byte K_PORTB[] {B00100001, B00100000, B00100000, B00100000, B00100001};
/* L code */
const byte L_PORTD[] {B11111100, B00000000, B00000000, B00000000, B00000000};
const byte L_PORTB[] {B00100001, B00100001, B00100001, B00100001, B00100001};
/* M code */
const byte M_PORTD[] {B11111100, B00001000, B00010000, B00001000, B11111100};
const byte M_PORTB[] {B00100001, B00100000, B00100000, B00100000, B00100001};
/* N code */
const byte N_PORTD[] {B11111100, B00010000, B00100000, B01000000, B11111100};
const byte N_PORTB[] {B00100001, B00100000, B00100000, B00100000, B00100001};
/* O code */
const byte O_PORTD[] {B11111000, B00000100, B00000100, B00000100, B11111000};
const byte O_PORTB[] {B00100000, B00100001, B00100001, B00100001, B00100000};
/* P code */
const byte P_PORTD[] {B11111100, B00100100, B00100100, B00100100, B00011000};
const byte P_PORTB[] {B00100001, B00100000, B00100000, B00100000, B00100000};
/* Q code */
const byte Q_PORTD[] {B11111000, B00000100, B01000100, B10000100, B01111000};
const byte Q_PORTB[] {B00100000, B00100001, B00100001, B00100000, B00100001};
/* R code */
const byte R_PORTD[] {B11111100, B00100100, B01100100, B10100100, B00011000};
const byte R_PORTB[] {B00100001, B00100000, B00100000, B00100000, B00100001};
/* S code */
const byte S_PORTD[] {B10011000, B00100100, B00100100, B00100100, B11001000};
const byte S_PORTB[] {B00100000, B00100001, B00100001, B00100001, B00100000};
/* T code */
const byte T_PORTD[] {B00000100, B00000100, B11111100, B00000100, B00000100};
const byte T_PORTB[] {B00100000, B00100000, B00100001, B00100000, B00100000};
/* U code */
const byte U_PORTD[] {B11111100, B00000000, B00000000, B00000000, B11111100};
const byte U_PORTB[] {B00100000, B00100001, B00100001, B00100001, B00100000};
/* V code */
const byte V_PORTD[] {B01111100, B10000000, B00000000, B10000000, B01111100};
const byte V_PORTB[] {B00100000, B00100000, B00100001, B00100000, B00100000};
/* W code */
const byte W_PORTD[] {B11111100, B10000000, B01000000, B10000000, B11111100};
const byte W_PORTB[] {B00100001, B00100000, B00100000, B00100000, B00100001};
/* X code */
const byte X_PORTD[] {B10001100, B01010000, B00100000, B01010000, B10001100};
const byte X_PORTB[] {B00100001, B00100000, B00100000, B00100000, B00100001};
/* Y code */
const byte Y_PORTD[] {B00001100, B00010000, B11100000, B00010000, B00001100};
const byte Y_PORTB[] {B00100000, B00100000, B00100001, B00100000, B00100000};
/* Z code */
const byte Z_PORTD[] {B10000100, B01000100, B00100100, B00010100, B00001100};
const byte Z_PORTB[] {B00100001, B00100001, B00100001, B00100001, B00100001};

//Table of pointers to code used for each character
const int char_lookup_PORTD[] {sp_PORTD, &fact_PORTD, &qt_PORTD, &hsh_PORTD, &dlr_PORTD, &pct_PORTD,  &and_PORTD, &apst_PORTD, &opar_PORTD, &cpar_PORTD, &ast_PORTD, &add_PORTD, 
                               &cma_PORTD, &sub_PORTD,&pd_PORTD, &bkSls_PORTD, &zero_PORTD, &one_PORTD, &two_PORTD, &thr_PORTD, &for_PORTD, &fv_PORTD, &sx_PORTD, 
                               &sv_PORTD, &et_PORTD, &nin_PORTD, &col_PORTD, &smcol_PORTD,  &lt_PORTD, &eq_PORTD, &gt_PORTD, &quest_PORTD, &at_PORTD, &A_PORTD,
                               &B_PORTD, &C_PORTD, &D_PORTD,&E_PORTD, &F_PORTD, &G_PORTD,&H_PORTD, &I_PORTD, &J_PORTD,&K_PORTD, &L_PORTD, &M_PORTD, 
                               &N_PORTD,&O_PORTD, &P_PORTD, &Q_PORTD,&R_PORTD, &S_PORTD, &T_PORTD,&U_PORTD, &V_PORTD, &W_PORTD,&X_PORTD, &Y_PORTD, &Z_PORTD};
const int char_lookup_PORTB[] {sp_PORTB, &fact_PORTB, &qt_PORTB, &hsh_PORTB, &dlr_PORTB, &pct_PORTB, &and_PORTD, &apst_PORTB, &opar_PORTB, &cpar_PORTB, &ast_PORTB, &add_PORTB, 
                               &cma_PORTB, &sub_PORTB,&pd_PORTB, &bkSls_PORTB, &zero_PORTB, &one_PORTB, &two_PORTB, &thr_PORTB, &for_PORTB, &fv_PORTB, &sx_PORTB, 
                               &sv_PORTB, &et_PORTB, &nin_PORTB, &col_PORTB, &smcol_PORTB,  &lt_PORTB, &eq_PORTB, &gt_PORTB, &quest_PORTB, &at_PORTB, 
                               &A_PORTB,&B_PORTB, &C_PORTB, &D_PORTB,&E_PORTB, &F_PORTB, &G_PORTB,&H_PORTB, &I_PORTB, &J_PORTB,&K_PORTB, &L_PORTB, &M_PORTB, 
                               &N_PORTB,&O_PORTB, &P_PORTB, &Q_PORTB,&R_PORTB, &S_PORTB, &T_PORTB,&U_PORTB, &V_PORTB, &W_PORTB,&X_PORTB, &Y_PORTB, &Z_PORTB};

//***************************************************************************
//
// Function Name : "colTest"
// Date : 6/26/19
// Version : 1.0
// Target MCU : Ardiuno UNO Rev3
// Target Hardware : Ardiuno UNO Rev3
// Authors : Zhen Sin (William) Wong
// DESCRIPTION: All LEDs of each column are lit up sequentially for an amount
//    of time specified by the "delayTime" parameter
//
// References : none
//
// Revision History : Initial version
//
//**************************************************************************
void colTest(int delayTime){
  PORTB = B00100001; // disable Cathodes
  PORTD = B11111100; //Enable all anodes
  byte col_Num = 0;
  for(col_Num; col_Num<=15; col_Num++){
    //PORTB = B00000001;              //Enable Cathodes, clear cathode codes
    PORTB = resetCath | 1;            //clear cathode codes
    PORTB = PORTB ^ toggleCath;
    PORTB = PORTB | (col_Num << 1);   //Copy in Cathode Code
    delay(delayTime);
    PORTB = PORTB ^ toggleCath;
    //PORTB = B00100001;              //Disable Cathodes
  }
   
}

//***************************************************************************
//
// Function Name : "rowTest"
// Date : 6/26/19
// Version : 1.0
// Target MCU : Ardiuno UNO Rev3
// Target Hardware : Ardiuno UNO Rev3
// Authors : Zhen Sin (William) Wong
// DESCRIPTION: All LEDs of each row are lit up sequentially for an amount
//    of time specified by the "inerval" parameter. This is performed by
//    multiplexing the Cathodes such that the LEDs in a row appear to be on
//    simultaneously.
//
// References : none
//
// Revision History : Initial version
//
//**************************************************************************
void rowTest(unsigned int interval){
  elapsedMillis timeElapsed;
  for(int row_Num = 1; row_Num<= B10000000; row_Num<<=1){
     PORTD = B00000000;  //Reset Anodes
     PORTB = resetCath;
     PORTD = PORTD | row_Num << 2;
     PORTB = PORTB | row_Num >> 7;
     timeElapsed = 0;
     while(timeElapsed < interval){
        byte col_Num = 0;
        for(col_Num; col_Num<=15; col_Num++){
          PORTB = resetCath;            //clear cathode codes
          PORTB = PORTB ^ (toggleCath | row_Num >> 7); //cathode On
          PORTB = PORTB | (col_Num << 1); //Copy in Cathode Code
          delayMicroseconds(50);
          //delay(1);
          PORTB = PORTB ^ toggleCath;
          
        }      
     }
   }  
}


//***************************************************************************
//
// Function Name : "displaySingleChar"
// Date : 6/26/19
// Version : 1.0
// Target MCU : Ardiuno UNO Rev3
// Target Hardware : Ardiuno UNO Rev3
// Authors : Zhen Sin (William) Wong
// DESCRIPTION: A single character defined by the "character" parameter is 
//    displayed on the board for a time defined by the "interval" parameter.
//    The position displayed on the board is defined by the "justMode" 
//    parameter as definied by the following:
//
//        Value | Justification  
//           0        left 
//           1        right
//        
// References : none
//
// Revision History : Initial version
//
//**************************************************************************
void displaySingleChar(char character, unsigned int interval, int justMode){
  int startCol;         //The column to start displaying
  int stopCol;          //The column to stop displaying

  if(justMode == 0){        //left justified
    startCol = 0;
    stopCol = 5;
  }
  else if(justMode == 1){   //right justified
    startCol = 11;
    stopCol = 16;
  }
  
  byte* PORTD_out = (byte*)char_lookup_PORTD[character - START_CHAR]; //table lookup for character column codes
  byte* PORTB_out = (byte*)char_lookup_PORTB[character - START_CHAR];
  elapsedMillis timeElapsed;
  
  while(timeElapsed < interval){
    for(int i = startCol; i<stopCol; i++){
      PORTD = PORTD_out[i-startCol];
      PORTB = (PORTB_out[i-startCol] | (i<<1));
      PORTB = PORTB ^ toggleCath; //Cathodes on
      delayMicroseconds(50);
      //delay(3);
      PORTB = PORTB ^ toggleCath; //Cathodes off
    }
  }
  
}

//***************************************************************************
//
// Function Name : "cycleAplhabet"
// Date : 6/26/19
// Version : 1.0
// Target MCU : Ardiuno UNO Rev3
// Target Hardware : Ardiuno UNO Rev3
// Authors : Zhen Sin (William) Wong
// DESCRIPTION: This function calls the function displaySingleChar by passing
//    the following arguments:
//          characters 'A' through 'Z' (done via for loop)
//          interval - a function parameter 
//          justMode - a function parameter 
//
// References : none
//
// Revision History : Initial version
//
//**************************************************************************
void cycleAlphabet (unsigned int interval, byte justMode){
  for(char i = 'A'; i<= 'Z'; i++){
    displaySingleChar(i, interval, justMode);
  }
}

//***************************************************************************
//
// Function Name : "scrollText"
// Date : 6/26/19
// Version : 1.0
// Target MCU : Ardiuno UNO Rev3
// Target Hardware : Ardiuno UNO Rev3
// Authors : Zhen Sin (William) Wong
// DESCRIPTION: This function scrolls through text passed as the parameter 
//    "text". The scroll speed is defined by the parameter scrollSpeed. 
//
// References : none
//
// Revision History : Initial version
//
//**************************************************************************
//Assumes that each character is EXACTLY 5 coulmns wide
void scrollText (String text, int scrollSpeed){

  elapsedMillis timeElapsed;

  byte* PORTD_out;
  byte* PORTB_out;

  char character;
  unsigned int code_PORTD[(6*text.length()+32)];
  unsigned int code_PORTB[(6*text.length()+32)];
  for(int i=0;i<16;i++){
    code_PORTD[i] = off;                  //Fill the beginning 16 elements with blanks
    code_PORTD[31-i] = off;
    code_PORTB[i] = off | resetCath;
    code_PORTB[31-i] = off | resetCath;    
  }

  //Set up array of data to display
  for(int i=0;i<text.length();i++){
    character = text.charAt(i);
    
    PORTD_out = (byte*)char_lookup_PORTD[character - START_CHAR]; //table lookup for character column codes
    PORTB_out = (byte*)char_lookup_PORTB[character - START_CHAR];

    for(int j = 0; j<5; j++){
      code_PORTD[6*i + 16 + j] = PORTD_out[j];
      code_PORTB[6*i + 16 + j] = PORTB_out[j];
      code_PORTD[6*i + 21 + j] = off;
      code_PORTB[6*i + 21 + j] = off;
    }
  }

  for(int i=6*text.length()+16 ;i<6*text.length()+32;i++){
    code_PORTD[i] = off;
    code_PORTB[i] = off | resetCath;
  }

   for(int i = 0; i<(6*text.length()+16); i++){
   timeElapsed = 0;
    while(timeElapsed < scrollSpeed){
        for(int j = 0; j<16; j++){
          PORTD = code_PORTD[i+j];
          PORTB = code_PORTB[i+j] | (j<<1);
          PORTB = PORTB ^ toggleCath; //Cathodes on
          delayMicroseconds(50);
          PORTB = PORTB ^ toggleCath; //Cathodes off
        }        
    }
   }
}


void setup() {
  //DDRD: Digital pins 7-2 for Anode Control
  //DDRB: Digital pins 8 for Anode Control; 9-12 for Cathode Control; 13 for Cathode Master Enable
  DDRD = B11111100;
  DDRB = B00111111;
  colTest(10);
  rowTest(10);
  PORTD = B00000000;
  PORTB = resetCath;
}


void loop() {
  // put your main code here, to run repeatedly:
  scrollText("IEEE", 90);
  scrollText("ARDUINO WORKSHOP", 90);
  //cycleAlphabet(500, 1);
  //displaySingleChar('',1,0);
}
