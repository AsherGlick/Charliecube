/********************************** SIGNATURE *********************************\
|                                      ,,                                      |
|                     db             `7MM                                      |
|                    ;MM:              MM                                      |
|                   ,V^MM.    ,pP"Ybd  MMpMMMb.  .gP"Ya `7Mb,od8               |
|                  ,M  `MM    8I   `"  MM    MM ,M'   Yb  MM' "'               |
|                  AbmmmqMA   `YMMMa.  MM    MM 8M""""""  MM                   |
|                 A'     VML  L.   I8  MM    MM YM.    ,  MM                   |
|               .AMA.   .AMMA.M9mmmP'.JMML  JMML.`Mbmmd'.JMML.                 |
|                                                                              |
|                                                                              |
|                                  ,,    ,,                                    |
|                      .g8"""bgd `7MM    db        `7MM                        |
|                    .dP'     `M   MM                MM                        |
|                    dM'       `   MM  `7MM  ,p6"bo  MM  ,MP'                  |
|                    MM            MM    MM 6M'  OO  MM ;Y                     |
|                    MM.    `7MMF' MM    MM 8M       MM;Mm                     |
|                    `Mb.     MM   MM    MM YM.    , MM `Mb.                   |
|                      `"bmmmdPY .JMML..JMML.YMbmd'.JMML. YA.                  |
|                                                                              |
\******************************************************************************/
/*********************************** LICENCE **********************************\
| Copyright (c) 2012, Asher Glick                                              |
| All rights reserved.                                                         |
|                                                                              |
| Redistribution and use in source and binary forms, with or without           |
| modification, are permitted provided that the following conditions are met:  |
|                                                                              |
| * Redistributions of source code must retain the above copyright notice,     |
|   this list of conditions and the following disclaimer.                      |
| * Redistributions in binary form must reproduce the above copyright notice,  |
|   this list of conditions and the following disclaimer in the documentation  |
|   and/or other materials provided with the distribution.                     |
|                                                                              |
| THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  |
| AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    |
| IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   |
| ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE    |
| LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR          |
| CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         |
| SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS     |
| INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      |
| CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)      |
| ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   |
| POSSIBILITY OF SUCH DAMAGE.                                                  |
\******************************************************************************/
#ifndef _CUBEPLEX_H_
#define _CUBEPLEX_H_

#define BUFFERSIZE 192

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"    // for digitalRead, digitalWrite, etc
#else
  #include "WProgram.h"
#endif

#include "mappings.h"
#include "niceTimer.h"

struct _frame_light{
  unsigned char pin1;
  unsigned char pin2;
  unsigned int brightness;
  unsigned char next;
};

_frame_light * _cube__frame;
_frame_light * _cube_current_frame;
unsigned char * _cube_buffer;

bool continuePattern = false;

/********************************** INIT CUBE *********************************\
| This function will allocate the memory required for the LED cube buffers.    |
| which is about 600bytes
\******************************************************************************/
void initCube() {
  Serial.begin(9600);
  Serial.print(sizeof(_frame_light));
  Serial.print(sizeof(unsigned char));
  Serial.end();
  _cube__frame = (_frame_light*)malloc(sizeof(_frame_light) * (BUFFERSIZE+1));
  _cube_buffer = (unsigned char*)malloc(sizeof(unsigned char) * BUFFERSIZE);
  
  
  for (int i = 0; i < BUFFERSIZE; i++) {
    _cube_buffer[i] = 0;
  }
  _cube__frame->next = _cube__frame;
  _cube__frame->pin1=0;
  _cube__frame->pin2=0;
  _cube_current_frame = _cube__frame;
  
  
  // Configure Interrupt for color display
  //setTimer2Prescaler(1);
  //enableTimer2OverflowInterrupt();
  //setTimer2Mode (TIMER2_NORMAL);
  
  // Enable the brightness interrupt
  //enableTimer2CompareAInterrupt();
  //setTimer2OutputCompareA(0xFF);
  
  // Configure Interrupt for Animation Progression
  setTimer1Prescaler(8);
  enableTimer1OverflowInterrupt();
  setTimer1Mode (TIMER1_NORMAL);
  //enableTimer1CompareAInterrupt();
  //setTimer1OutputCompareA(0x00FF);
  
  _cube__frame[  0].pin1 =  4; _cube__frame[  0].pin2 =  8;
  _cube__frame[  1].pin1 = 16; _cube__frame[  1].pin2 =  4;
  _cube__frame[  2].pin1 = 12; _cube__frame[  2].pin2 = 16;
  _cube__frame[  3].pin1 =  8; _cube__frame[  3].pin2 = 12;
  _cube__frame[  4].pin1 =  4; _cube__frame[  4].pin2 =  7;
  _cube__frame[  5].pin1 = 13; _cube__frame[  5].pin2 =  4;
  _cube__frame[  6].pin1 = 11; _cube__frame[  6].pin2 = 13;
  _cube__frame[  7].pin1 =  7; _cube__frame[  7].pin2 = 11;
  _cube__frame[  8].pin1 =  4; _cube__frame[  8].pin2 =  6;
  _cube__frame[  9].pin1 = 15; _cube__frame[  9].pin2 =  4;
  _cube__frame[ 10].pin1 = 10; _cube__frame[ 10].pin2 = 15;
  _cube__frame[ 11].pin1 =  6; _cube__frame[ 11].pin2 = 10;
  _cube__frame[ 12].pin1 =  4; _cube__frame[ 12].pin2 =  5;
  _cube__frame[ 13].pin1 = 14; _cube__frame[ 13].pin2 =  4;
  _cube__frame[ 14].pin1 =  9; _cube__frame[ 14].pin2 = 14;
  _cube__frame[ 15].pin1 =  5; _cube__frame[ 15].pin2 =  9;
  _cube__frame[ 16].pin1 =  3; _cube__frame[ 16].pin2 =  8;
  _cube__frame[ 17].pin1 = 15; _cube__frame[ 17].pin2 =  3;
  _cube__frame[ 18].pin1 = 11; _cube__frame[ 18].pin2 = 15;
  _cube__frame[ 19].pin1 =  8; _cube__frame[ 19].pin2 = 11;
  _cube__frame[ 20].pin1 =  3; _cube__frame[ 20].pin2 =  7;
  _cube__frame[ 21].pin1 = 14; _cube__frame[ 21].pin2 =  3;
  _cube__frame[ 22].pin1 = 12; _cube__frame[ 22].pin2 = 14;
  _cube__frame[ 23].pin1 =  7; _cube__frame[ 23].pin2 = 12;
  _cube__frame[ 24].pin1 =  3; _cube__frame[ 24].pin2 =  6;
  _cube__frame[ 25].pin1 = 16; _cube__frame[ 25].pin2 =  3;
  _cube__frame[ 26].pin1 =  9; _cube__frame[ 26].pin2 = 16;
  _cube__frame[ 27].pin1 =  6; _cube__frame[ 27].pin2 =  9;
  _cube__frame[ 28].pin1 =  3; _cube__frame[ 28].pin2 =  5;
  _cube__frame[ 29].pin1 = 13; _cube__frame[ 29].pin2 =  3;
  _cube__frame[ 30].pin1 = 10; _cube__frame[ 30].pin2 = 13;
  _cube__frame[ 31].pin1 =  5; _cube__frame[ 31].pin2 = 10;
  _cube__frame[ 32].pin1 =  2; _cube__frame[ 32].pin2 =  8;
  _cube__frame[ 33].pin1 = 14; _cube__frame[ 33].pin2 =  2;
  _cube__frame[ 34].pin1 = 10; _cube__frame[ 34].pin2 = 14;
  _cube__frame[ 35].pin1 =  8; _cube__frame[ 35].pin2 = 10;
  _cube__frame[ 36].pin1 =  2; _cube__frame[ 36].pin2 =  7;
  _cube__frame[ 37].pin1 = 15; _cube__frame[ 37].pin2 =  2;
  _cube__frame[ 38].pin1 =  9; _cube__frame[ 38].pin2 = 15;
  _cube__frame[ 39].pin1 =  7; _cube__frame[ 39].pin2 =  9;
  _cube__frame[ 40].pin1 =  2; _cube__frame[ 40].pin2 =  6;
  _cube__frame[ 41].pin1 = 13; _cube__frame[ 41].pin2 =  2;
  _cube__frame[ 42].pin1 = 12; _cube__frame[ 42].pin2 = 13;
  _cube__frame[ 43].pin1 =  6; _cube__frame[ 43].pin2 = 12;
  _cube__frame[ 44].pin1 =  2; _cube__frame[ 44].pin2 =  5;
  _cube__frame[ 45].pin1 = 16; _cube__frame[ 45].pin2 =  2;
  _cube__frame[ 46].pin1 = 11; _cube__frame[ 46].pin2 = 16;
  _cube__frame[ 47].pin1 =  5; _cube__frame[ 47].pin2 = 11;
  _cube__frame[ 48].pin1 =  1; _cube__frame[ 48].pin2 =  8;
  _cube__frame[ 49].pin1 = 13; _cube__frame[ 49].pin2 =  1;
  _cube__frame[ 50].pin1 =  9; _cube__frame[ 50].pin2 = 13;
  _cube__frame[ 51].pin1 =  8; _cube__frame[ 51].pin2 =  9;
  _cube__frame[ 52].pin1 =  1; _cube__frame[ 52].pin2 =  7;
  _cube__frame[ 53].pin1 = 16; _cube__frame[ 53].pin2 =  1;
  _cube__frame[ 54].pin1 = 10; _cube__frame[ 54].pin2 = 16;
  _cube__frame[ 55].pin1 =  7; _cube__frame[ 55].pin2 = 10;
  _cube__frame[ 56].pin1 =  1; _cube__frame[ 56].pin2 =  6;
  _cube__frame[ 57].pin1 = 14; _cube__frame[ 57].pin2 =  1;
  _cube__frame[ 58].pin1 = 11; _cube__frame[ 58].pin2 = 14;
  _cube__frame[ 59].pin1 =  6; _cube__frame[ 59].pin2 = 11;
  _cube__frame[ 60].pin1 =  1; _cube__frame[ 60].pin2 =  5;
  _cube__frame[ 61].pin1 = 15; _cube__frame[ 61].pin2 =  1;
  _cube__frame[ 62].pin1 = 12; _cube__frame[ 62].pin2 = 15;
  _cube__frame[ 63].pin1 =  5; _cube__frame[ 63].pin2 = 12;
  _cube__frame[ 64].pin1 = 16; _cube__frame[ 64].pin2 =  8;
  _cube__frame[ 65].pin1 = 12; _cube__frame[ 65].pin2 =  4;
  _cube__frame[ 66].pin1 =  8; _cube__frame[ 66].pin2 = 16;
  _cube__frame[ 67].pin1 =  4; _cube__frame[ 67].pin2 = 12;
  _cube__frame[ 68].pin1 = 13; _cube__frame[ 68].pin2 =  7;
  _cube__frame[ 69].pin1 = 11; _cube__frame[ 69].pin2 =  4;
  _cube__frame[ 70].pin1 =  7; _cube__frame[ 70].pin2 = 13;
  _cube__frame[ 71].pin1 =  4; _cube__frame[ 71].pin2 = 11;
  _cube__frame[ 72].pin1 = 15; _cube__frame[ 72].pin2 =  6;
  _cube__frame[ 73].pin1 = 10; _cube__frame[ 73].pin2 =  4;
  _cube__frame[ 74].pin1 =  6; _cube__frame[ 74].pin2 = 15;
  _cube__frame[ 75].pin1 =  4; _cube__frame[ 75].pin2 = 10;
  _cube__frame[ 76].pin1 = 14; _cube__frame[ 76].pin2 =  5;
  _cube__frame[ 77].pin1 =  9; _cube__frame[ 77].pin2 =  4;
  _cube__frame[ 78].pin1 =  5; _cube__frame[ 78].pin2 = 14;
  _cube__frame[ 79].pin1 =  4; _cube__frame[ 79].pin2 =  9;
  _cube__frame[ 80].pin1 = 15; _cube__frame[ 80].pin2 =  8;
  _cube__frame[ 81].pin1 = 11; _cube__frame[ 81].pin2 =  3;
  _cube__frame[ 82].pin1 =  8; _cube__frame[ 82].pin2 = 15;
  _cube__frame[ 83].pin1 =  3; _cube__frame[ 83].pin2 = 11;
  _cube__frame[ 84].pin1 = 14; _cube__frame[ 84].pin2 =  7;
  _cube__frame[ 85].pin1 = 12; _cube__frame[ 85].pin2 =  3;
  _cube__frame[ 86].pin1 =  7; _cube__frame[ 86].pin2 = 14;
  _cube__frame[ 87].pin1 =  3; _cube__frame[ 87].pin2 = 12;
  _cube__frame[ 88].pin1 = 16; _cube__frame[ 88].pin2 =  6;
  _cube__frame[ 89].pin1 =  9; _cube__frame[ 89].pin2 =  3;
  _cube__frame[ 90].pin1 =  6; _cube__frame[ 90].pin2 = 16;
  _cube__frame[ 91].pin1 =  3; _cube__frame[ 91].pin2 =  9;
  _cube__frame[ 92].pin1 = 13; _cube__frame[ 92].pin2 =  5;
  _cube__frame[ 93].pin1 = 10; _cube__frame[ 93].pin2 =  3;
  _cube__frame[ 94].pin1 =  5; _cube__frame[ 94].pin2 = 13;
  _cube__frame[ 95].pin1 =  3; _cube__frame[ 95].pin2 = 10;
  _cube__frame[ 96].pin1 = 14; _cube__frame[ 96].pin2 =  8;
  _cube__frame[ 97].pin1 = 10; _cube__frame[ 97].pin2 =  2;
  _cube__frame[ 98].pin1 =  8; _cube__frame[ 98].pin2 = 14;
  _cube__frame[ 99].pin1 =  2; _cube__frame[ 99].pin2 = 10;
  _cube__frame[100].pin1 = 15; _cube__frame[100].pin2 =  7;
  _cube__frame[101].pin1 =  9; _cube__frame[101].pin2 =  2;
  _cube__frame[102].pin1 =  7; _cube__frame[102].pin2 = 15;
  _cube__frame[103].pin1 =  2; _cube__frame[103].pin2 =  9;
  _cube__frame[104].pin1 = 13; _cube__frame[104].pin2 =  6;
  _cube__frame[105].pin1 = 12; _cube__frame[105].pin2 =  2;
  _cube__frame[106].pin1 =  6; _cube__frame[106].pin2 = 13;
  _cube__frame[107].pin1 =  2; _cube__frame[107].pin2 = 12;
  _cube__frame[108].pin1 = 16; _cube__frame[108].pin2 =  5;
  _cube__frame[109].pin1 = 11; _cube__frame[109].pin2 =  2;
  _cube__frame[110].pin1 =  5; _cube__frame[110].pin2 = 16;
  _cube__frame[111].pin1 =  2; _cube__frame[111].pin2 = 11;
  _cube__frame[112].pin1 = 13; _cube__frame[112].pin2 =  8;
  _cube__frame[113].pin1 =  9; _cube__frame[113].pin2 =  1;
  _cube__frame[114].pin1 =  8; _cube__frame[114].pin2 = 13;
  _cube__frame[115].pin1 =  1; _cube__frame[115].pin2 =  9;
  _cube__frame[116].pin1 = 16; _cube__frame[116].pin2 =  7;
  _cube__frame[117].pin1 = 10; _cube__frame[117].pin2 =  1;
  _cube__frame[118].pin1 =  7; _cube__frame[118].pin2 = 16;
  _cube__frame[119].pin1 =  1; _cube__frame[119].pin2 = 10;
  _cube__frame[120].pin1 = 14; _cube__frame[120].pin2 =  6;
  _cube__frame[121].pin1 = 11; _cube__frame[121].pin2 =  1;
  _cube__frame[122].pin1 =  6; _cube__frame[122].pin2 = 14;
  _cube__frame[123].pin1 =  1; _cube__frame[123].pin2 = 11;
  _cube__frame[124].pin1 = 15; _cube__frame[124].pin2 =  5;
  _cube__frame[125].pin1 = 12; _cube__frame[125].pin2 =  1;
  _cube__frame[126].pin1 =  5; _cube__frame[126].pin2 = 15;
  _cube__frame[127].pin1 =  1; _cube__frame[127].pin2 = 12;
  _cube__frame[128].pin1 = 12; _cube__frame[128].pin2 =  8;
  _cube__frame[129].pin1 =  8; _cube__frame[129].pin2 =  4;
  _cube__frame[130].pin1 =  4; _cube__frame[130].pin2 = 16;
  _cube__frame[131].pin1 = 16; _cube__frame[131].pin2 = 12;
  _cube__frame[132].pin1 = 11; _cube__frame[132].pin2 =  7;
  _cube__frame[133].pin1 =  7; _cube__frame[133].pin2 =  4;
  _cube__frame[134].pin1 =  4; _cube__frame[134].pin2 = 13;
  _cube__frame[135].pin1 = 13; _cube__frame[135].pin2 = 11;
  _cube__frame[136].pin1 = 10; _cube__frame[136].pin2 =  6;
  _cube__frame[137].pin1 =  6; _cube__frame[137].pin2 =  4;
  _cube__frame[138].pin1 =  4; _cube__frame[138].pin2 = 15;
  _cube__frame[139].pin1 = 15; _cube__frame[139].pin2 = 10;
  _cube__frame[140].pin1 =  9; _cube__frame[140].pin2 =  5;
  _cube__frame[141].pin1 =  5; _cube__frame[141].pin2 =  4;
  _cube__frame[142].pin1 =  4; _cube__frame[142].pin2 = 14;
  _cube__frame[143].pin1 = 14; _cube__frame[143].pin2 =  9;
  _cube__frame[144].pin1 = 11; _cube__frame[144].pin2 =  8;
  _cube__frame[145].pin1 =  8; _cube__frame[145].pin2 =  3;
  _cube__frame[146].pin1 =  3; _cube__frame[146].pin2 = 15;
  _cube__frame[147].pin1 = 15; _cube__frame[147].pin2 = 11;
  _cube__frame[148].pin1 = 12; _cube__frame[148].pin2 =  7;
  _cube__frame[149].pin1 =  7; _cube__frame[149].pin2 =  3;
  _cube__frame[150].pin1 =  3; _cube__frame[150].pin2 = 14;
  _cube__frame[151].pin1 = 14; _cube__frame[151].pin2 = 12;
  _cube__frame[152].pin1 =  9; _cube__frame[152].pin2 =  6;
  _cube__frame[153].pin1 =  6; _cube__frame[153].pin2 =  3;
  _cube__frame[154].pin1 =  3; _cube__frame[154].pin2 = 16;
  _cube__frame[155].pin1 = 16; _cube__frame[155].pin2 =  9;
  _cube__frame[156].pin1 = 10; _cube__frame[156].pin2 =  5;
  _cube__frame[157].pin1 =  5; _cube__frame[157].pin2 =  3;
  _cube__frame[158].pin1 =  3; _cube__frame[158].pin2 = 13;
  _cube__frame[159].pin1 = 13; _cube__frame[159].pin2 = 10;
  _cube__frame[160].pin1 = 10; _cube__frame[160].pin2 =  8;
  _cube__frame[161].pin1 =  8; _cube__frame[161].pin2 =  2;
  _cube__frame[162].pin1 =  2; _cube__frame[162].pin2 = 14;
  _cube__frame[163].pin1 = 14; _cube__frame[163].pin2 = 10;
  _cube__frame[164].pin1 =  9; _cube__frame[164].pin2 =  7;
  _cube__frame[165].pin1 =  7; _cube__frame[165].pin2 =  2;
  _cube__frame[166].pin1 =  2; _cube__frame[166].pin2 = 15;
  _cube__frame[167].pin1 = 15; _cube__frame[167].pin2 =  9;
  _cube__frame[168].pin1 = 12; _cube__frame[168].pin2 =  6;
  _cube__frame[169].pin1 =  6; _cube__frame[169].pin2 =  2;
  _cube__frame[170].pin1 =  2; _cube__frame[170].pin2 = 13;
  _cube__frame[171].pin1 = 13; _cube__frame[171].pin2 = 12;
  _cube__frame[172].pin1 = 11; _cube__frame[172].pin2 =  5;
  _cube__frame[173].pin1 =  5; _cube__frame[173].pin2 =  2;
  _cube__frame[174].pin1 =  2; _cube__frame[174].pin2 = 16;
  _cube__frame[175].pin1 = 16; _cube__frame[175].pin2 = 11;
  _cube__frame[176].pin1 =  9; _cube__frame[176].pin2 =  8;
  _cube__frame[177].pin1 =  8; _cube__frame[177].pin2 =  1;
  _cube__frame[178].pin1 =  1; _cube__frame[178].pin2 = 13;
  _cube__frame[179].pin1 = 13; _cube__frame[179].pin2 =  9;
  _cube__frame[180].pin1 = 10; _cube__frame[180].pin2 =  7;
  _cube__frame[181].pin1 =  7; _cube__frame[181].pin2 =  1;
  _cube__frame[182].pin1 =  1; _cube__frame[182].pin2 = 16;
  _cube__frame[183].pin1 = 16; _cube__frame[183].pin2 = 10;
  _cube__frame[184].pin1 = 11; _cube__frame[184].pin2 =  6;
  _cube__frame[185].pin1 =  6; _cube__frame[185].pin2 =  1;
  _cube__frame[186].pin1 =  1; _cube__frame[186].pin2 = 14;
  _cube__frame[187].pin1 = 14; _cube__frame[187].pin2 = 11;
  _cube__frame[188].pin1 = 12; _cube__frame[188].pin2 =  5;
  _cube__frame[189].pin1 =  5; _cube__frame[189].pin2 =  1;
  _cube__frame[190].pin1 =  1; _cube__frame[190].pin2 = 15;
  _cube__frame[191].pin1 = 15; _cube__frame[191].pin2 = 12;
  
}
  //////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// HELPER FUNCTIONS //////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/******************************** CLEAR BUFFER ********************************\
| This function will clear the buffer that you can write to, this will allow   |
| you to draw an eniterly new frame int othe buffer
\******************************************************************************/
void clearBuffer () {
  for (int i = 0; i < BUFFERSIZE; i++) {
    _cube_buffer[i] = 0;
  }
}

/**************************** NEXT COLOR FUNCTIONS ****************************\
| These functions cycle thorugh                                                |
|  the three primary colors red, greed, and blue                               |
|  the secondary colors purple, teal, yellow (every pairing of two leds)       |
|  the ALL THE COLORS (red,green,blue,purple,teal,yellow,white)                |
\******************************************************************************/
int nextPrimaryColor(int color)   { return  (color+1)%3; }
int nextSecondaryColor(int color) { return ((color+1)%3)+3; }
int nextColor(int color)          { return  (color+1)%7; }

/********************************** SWAP INT **********************************\
| This function uses the fast xor swap to change the values of the two         |
| intigers passed into the function                                            |
\******************************************************************************/
void swapint(int & one, int & two) {
  one = one^two;
  two = one^two;
  one = one^two;
}

/******************************* ROUND CLOSTEST *******************************\
| This function takes in a numberator and denominator and rounds to the        |
| nearist number instead of trunkating. It does this by calculating an extra   |
| digit (this function should be changes to be more accurate)                  |
\******************************************************************************/
int roundClostest(int numerator, int denominator) {
  numerator = (numerator << 1)/denominator;
  int output = (numerator>>1) + (numerator % 2);
  return output;
}

  //////////////////////////////////////////////////////////////////////////////
 /////////////////////////////////// DRAWING //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#define B 0
#define G 1
#define R 2
#define T 3
#define Y 4
#define P 5
#define W 6
#define O 7

#define blue 0
#define green 1
#define red 2
#define teal 3
#define yellow 4
#define purple 5
#define white 6
#define off -7

/********************************** DRAW LED **********************************\
| This function turns on leds at a specified position. Depending on which      |
| color this function turns on different colors of the LED                     |
\******************************************************************************/
void drawLed(int color, int brightness, int x, int y, int z) {
  
  if ((color/3)==0) { // single color (red green blue)
  //_cube_buffer[(((color)%3)*64)+(x*16)+(y*4)+z] += brightness;
    _cube_buffer[(((color)%3)*64)+(x*16)+(y*4)+z] += brightness;
    _cube_buffer[(((color+1)%3)*64)+(x*16)+(y*4)+z] += 0;
  }
  else if ((color/3)==1) { // double color (teal yellow purple)
    _cube_buffer[(((color)%3)*64)+(x*16)+(y*4)+z] += brightness;
    _cube_buffer[(((color+1)%3)*64)+(x*16)+(y*4)+z] += brightness;
  }
  else if (color == 6){ // all colors (white)
    _cube_buffer[((0)*64)+(x*16)+(y*4)+z] += brightness;
    _cube_buffer[((1)*64)+(x*16)+(y*4)+z] += brightness;
    _cube_buffer[((2)*64)+(x*16)+(y*4)+z] += brightness;
  }
  else if (color == -7) {
    _cube_buffer[((0)*64)+(x*16)+(y*4)+z] = 0;
    _cube_buffer[((1)*64)+(x*16)+(y*4)+z] = 0;
    _cube_buffer[((2)*64)+(x*16)+(y*4)+z] = 0;
  }
}
void drawLed(int color, int x, int y, int z) {
  drawLed(color,255,x,y,z);
}

/********************************** DRAW BOX **********************************\
| This function will draw a filled in box of the specified color on the cube   |
\******************************************************************************/
void drawBox(int color, int brightness, int startx, int starty, int startz, int endx, int endy, int endz) {
  if (startx > endx) swapint(startx,endx);
  if (starty > endy) swapint(starty,endy);
  if (startz > endz) swapint(startz,endz);
  
  for (int i = startx; i <= endx; i++) {
    for (int j = starty; j <= endy; j++) {
      for (int k = startz; k <= endz; k++) {
        drawLed(color,brightness,i,j,k);
      }
    } 
  }
}
void drawBox(int color, int startx, int starty, int startz, int endx, int endy, int endz) {
  drawBox(color,8,startx,starty,startz,endx,endy,endz);
}
/******************************* DRAW HOLLOW BOX ******************************\
| This function will draw the walls, celing, and floor of a defined box        |
\******************************************************************************/
void drawHollowBox(int color, int brightness, int startx, int starty, int startz, int endx, int endy, int endz) {
  if (startx > endx) swapint(startx,endx);
  if (starty > endy) swapint(starty,endy);
  if (startz > endz) swapint(startz,endz);
  
  
  for (int i = startx; i <= endx; i ++) {
    for (int j = starty; j <= endy; j ++) {
      for (int k = startz; k <= endz; k ++) {
        if (i == startx || i == endx || j == starty || j == endy || k == startz || k == endz) {
          drawLed(color,brightness,i,j,k);
        }
      } 
    }
  }
}
void drawHollowBox(int color, int startx, int starty, int startz, int endx, int endy, int endz) {
   drawHollowBox(color,255,startx,starty,startz,endx,endy,endz);
}
/****************************** DRAW BOX OUTLINE ******************************\
| This function will draw edges of a defined box but none of the planes        |
\******************************************************************************/
void drawBoxOutline(int color, int brightness, int startx, int starty, int startz, int endx, int endy, int endz) {
  if (startx > endx) swapint(startx,endx);
  if (starty > endy) swapint(starty,endy);
  if (startz > endz) swapint(startz,endz);
  
  
  for (int i = startx; i <= endx; i++) {
    for (int j = starty; j <= endy; j++) {
      for (int k = startz; k <= endz; k++) {
        int sum =  (i == startx) + (i == endy) + (j == starty) + (j == endy) + (k == startz) + (k == endz);
        if (sum >= 2){
          drawLed(color,brightness,i,j,k);
        }
      } 
    }
  }
}
void drawBoxOutline(int color, int startx, int starty, int startz, int endx, int endy, int endz) {
   drawHollowBox(color,255,startx,starty,startz,endx,endy,endz);
}
/******************************* DRAW BOX WALLS *******************************\
| This function will draw the virtical walls and all four sides of a defined   |
| box                                                                          |
\******************************************************************************/
void drawBoxWalls(int color, int brightness, int startx, int starty, int startz, int endx, int endy, int endz) {
  if (startx > endx) swapint(startx,endx);
  if (starty > endy) swapint(starty,endy);
  if (startz > endz) swapint(startz,endz);
  
  for (int i = startz; i <= endz; i++) {
    // draw y walls
    for (int j = starty; j <= endy; j++) {
      drawLed(color,brightness,startx,j,i);
      drawLed(color,brightness,endx,j,i);
    }
    // draw x walls
    for (int j = startx; j <= endx; j++) {
      drawLed(color,brightness,j,starty,i);
      drawLed(color,brightness,j,endy,i);
    }
  }
}
void drawBoxWalls(int color, int startx, int starty, int startz, int endx, int endy, int endz) {
  drawBoxWalls(color,255,startx,starty,startz,endx,endy,endz);
}
/********************************** DRAW LINE *********************************\
| This function will attempt to draw a line between the two points given. Due  |
| to the limited avalibility of pixels the best approximation is chosen for    |
| each pixel value                                                             |
\******************************************************************************/
void drawLine(int color, int brightness, int startx, int starty, int startz, int endx, int endy, int endz) {
  bool reverseX = false;
  bool reverseY = false;
  bool reverseZ = false;
  if (startx > endx) {swapint(startx,endx);reverseX=true;}
  if (starty > endy) {swapint(starty,endy);reverseY=true;}
  if (startz > endz) {swapint(startz,endz);reverseZ=true;}

  int delx = endx - startx;
  int dely = endy - starty;
  int delz = endz - startz;
  
  int longest = (delx>dely?delx>delz?delx:delz>dely?delz:dely:dely>delz?dely:delz>delx?delz:delx);
  for (int i = 0; i < longest; i++) {
    int xpos;
    if (reverseX) xpos = roundClostest(((longest-i)*delx),longest) + startx;
    else xpos = roundClostest((i*delx),longest) + startx;
    
    int ypos;
    if (reverseY) ypos = roundClostest(((longest-i)*dely),longest) + starty;
    else ypos = roundClostest((i*dely),longest) + starty;
    
    int zpos;
    if (reverseZ) zpos = roundClostest(((longest-i)*delz),longest) + startz;
    else zpos = roundClostest((i*delz),longest) + startz;
    
    drawLed(color,brightness,xpos,ypos,zpos);
  }
  
  if (reverseX) swapint(startx,endx);
  if (reverseY) swapint(starty,endy);
  if (reverseZ) swapint(startz,endz);
  drawLed(color,brightness,endx,endy,endz);
}
void drawLine(int color, int startx, int starty, int startz, int endx, int endy, int endz) {
  drawLine(color,255,startx, starty, startz, endx, endy, endz);
}
  //////////////////////////////////////////////////////////////////////////////
 /////////////////////////////////// DISPLAY //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
int pwmm = 0;
unsigned int offtime; // how long the leds should be off per cycle
void flushElement(_frame_light* &copy_frame,int pin1,int pin2,unsigned int brightness) {
  pin1--;
  pin2--;
  
  (copy_frame+1)->next=copy_frame;
  copy_frame++;
  copy_frame->pin1=pin1;// | ( brightness & 0xF0);
  copy_frame->pin2=pin2;// | ((brightness & 0x0F) << 4);
  //brightness = 8;
  copy_frame->brightness = 65535 - brightness; // 
  offtime += 255-brightness;
}
/******************************** FLUSH BUFFER ********************************\
| This takes the buffer frame and sets the display memory to match, because    |
| the display memory needs to be faster it is split up into two arrays instead |
| of just one. The display frame is actually a ciclic linked list which allows |
| the program to just loop through and turn on the LEDs without the need to    |
| check to see if it is at the end o  f the loop                                 |
\******************************************************************************/

void flushBuffer() {
  _frame_light * previousActivatedFrame = _cube__frame+192; // Use this to determine if an led is on and how to handle inserting and deleting elements in the list
  //offtime = 0; // no longer set offtime to 0, all modifications will be done within the loop
  
  for (int i = 0; i < 192; i++) {
    if (previousActivatedFrame->next == i) { // Previously On
      if (_cube_buffer[i] == 0) { // Turning Off
        // set previous's next to this's next
        // remove the brightness modification from offtime
      }
      else { // Staying On (with possible brightness change)
        // change the offtime variable based on the difference in brightnesses
        // change the brightness value
        // Set this as the previousActivatedFrame
      }
    }
    else { // Previously Off
      if (_cube_buffer[i] == 0) {} // Staying Off (do nothing)
      else { // Turning On
        //Set this's next to the previous's next
        // set this brightness to the brightness value
        // modify the offtime based on the brightness
        // Set the the previous's mext to this
        // Set this as the previousActivatedFrame
      }
      
    }
  }
  //flushElement(copy_frame,17,17,offtime); // Include time that the leds are off
}


/*************************** INTERRUPT DISPLAY LEDS ***************************\
| This is the interrupt function to turn on one led. After it turns that one   |
| on it will 
\******************************************************************************/
byte pinsB[] = {P1B,P2B,P3B,P4B,P5B,P6B,P7B,P8B,P9B,P10B,P11B,P12B,P13B,P14B,P15B,P16B,0x00};
byte pinsC[] = {P1C,P2C,P3C,P4C,P5C,P6C,P7C,P8C,P9C,P10C,P11C,P12C,P13C,P14C,P15C,P16C,0x00};
byte pinsD[] = {P1D,P2D,P3D,P4D,P5D,P6D,P7D,P8D,P9D,P10D,P11D,P12D,P13D,P14D,P15D,P16D,0x00};

ISR(TIMER1_OVF_vect) {
  PORTB = 0x00;
  PORTC = 0x00;
  PORTD = 0x00;
  
  int pin1 = _cube_current_frame->pin1;
  int pin2 = _cube_current_frame->pin2;
  int brightness = _cube_current_frame->brightness;
  
  _cube_current_frame = _cube_current_frame->next;
  
  DDRB = pinsB[pin1] | pinsB[pin2];
  DDRC = pinsC[pin1] | pinsC[pin2];
  DDRD = pinsD[pin1] | pinsD[pin2];
  
  PORTB = pinsB[pin1];
  PORTC = pinsC[pin1];
  PORTD = pinsD[pin1];

  setTimer1Value(brightness);
}

/******************************************************************************\
| Some helpfull info for overflowing timers with different prescaler values    |
|  16000000 / (   1*256) = 16000000 / 256    =  62500 Hz                       |
|  16000000 / (   8*256) = 16000000 / 2048   =  ~7812 Hz                       |
|  16000000 / (  32*256) = 16000000 / 8192   =  ~1953 Hz                       |
|  16000000 / (  64*256) = 16000000 / 16384  =   ~976 Hz                       |
|  16000000 / ( 128*256) = 16000000 / 32768  =   ~488 Hz                       | 
|  16000000 / ( 256*256) = 16000000 / 65536  =   ~244 Hz                       |
|  16000000 / (1024*256) = 16000000 / 262144 =    ~61 Hz                       |
\******************************************************************************/
int animationTimer = 0;
int animationMax = 0;

/*ISR(TIMER1_OVF_vect) {
  animationTimer++;
  if (animationTimer == animationMax) {
    continuePattern = false;
    animationTimer=0;
  }
  
  //DDRB = pinsB[4] | pinsB[8];
  //DDRC = pinsC[4] | pinsC[8];
  //DDRD = pinsD[4] | pinsD[8];
  
  //PORTB = pinsB[4];
  //PORTC = pinsC[4];
  //PORTD = pinsD[4];
  
}*/


// Turn off led
/*ISR(TIMER2_COMPA_vect) {
  PORTB = 0x00;
  PORTC = 0x00;
  PORTD = 0x00;
  
  //DDRB = pinsB[4] | pinsB[8];
  //DDRC = pinsC[4] | pinsC[8];
  //DDRD = pinsD[4] | pinsD[8];
  
  //PORTB = pinsB[4];
  //PORTC = pinsC[4];
  //PORTD = pinsD[4];
}*/

#endif
