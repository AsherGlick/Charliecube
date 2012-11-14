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

// number of LEDs
#define BUFFERSIZE 192

#include "Arduino.h" //#include "WProgram.h"
#include "mappings.h"
#include "niceTimer.h"

// Node for a linked list of the pins which turn on an LED
struct _frame_light{
  char pin1;
  char pin2;
  char brightness; // brightnesses are relative to PWMMMAX (currently 8)
  struct _frame_light * next;
};

// Beginning of linked list of all lit LEDs
_frame_light * _cube__frame;
// Currently lit LED
_frame_light * _cube_current_frame;
// array with brightness of each LED
char * _cube_buffer;

bool continuePattern = false;

/********************************** INIT CUBE *********************************\
| This function will allocate the memory required for the LED cube buffers.    |
| which is 1157 bytes
\******************************************************************************/
void initCube() {
  _cube__frame = (_frame_light*)malloc(sizeof(_frame_light) * (BUFFERSIZE+1));
  _cube_buffer = (char*)malloc(sizeof(char) * BUFFERSIZE);
  
  
  for (int i = 0; i < BUFFERSIZE; i++) {
    _cube_buffer[i] = 0;
  }
  _cube__frame->next = _cube__frame;
  _cube__frame->pin1=0;
  _cube__frame->pin2=0;
  _cube_current_frame = _cube__frame;
  
  
  // Configure Interrupt for color display
  setTimer2Prescaler(1);
  enableTimer2OverflowInterrupt();
  setTimer2Mode (TIMER2_NORMAL);
  
  // Configure Interrupt for Animation Progression
  setTimer1Prescaler(256);
  enableTimer1OverflowInterrupt();
  setTimer1Mode (TIMER1_NORMAL);  
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
|  the three primary colors red, green, and blue                               |
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

/******************************* ROUND CLOSEST *******************************\
| This function takes in a numberator and denominator and rounds to the        |
| nearist number instead of truncating. It does this by calculating an extra   |
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
#define O -7

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
    _cube_buffer[(((color)%3)*64)+(x*16)+(y*4)+z] += brightness;
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
  drawLine(color,8,startx, starty, startz, endx, endy, endz);
}
  //////////////////////////////////////////////////////////////////////////////
 /////////////////////////////////// DISPLAY //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
int pwmm = 0; //incremented each loop through display list 
int display_length; //number of lit LEDs
/* Populates the specified _frame_light
 *
 * copy_frame should specify the most recently allocated frame in _cube__frame.
 * The next frame is added to the linked list, overwritten with the correct info,
 * and then copy_frame updated.
 *
 * pin1 and pin2 refer to the logical groups (eg 1-16). The mapping of these to
 * actual Arduino pins is specified by the PXX macros in mappings.h
 *
 * brightness should be from 0-255
 *
 * Side effects: updates display_length
 */
void flushElement(_frame_light* &copy_frame,int pin1,int pin2,int brightness) {
  pin1--;
  pin2--;
  
  (copy_frame+1)->next=copy_frame;
  copy_frame++;
  copy_frame->pin1=pin1;
  copy_frame->pin2=pin2;
  copy_frame->brightness=brightness;
  display_length++;
}
/******************************** FLUSH BUFFER ********************************\
| This takes the buffer frame and sets the display memory to match, because    |
| the display memory needs to be faster it is split up into two arrays instead |
| of just one. The display frame is actually a ciclic linked list which allows |
| the program to just loop through and turn on the LEDs without the need to    |
| check to see if it is at the end of the loop                                 |
\******************************************************************************/

void flushBuffer() {
  _frame_light * copy_frame = _cube__frame;
  display_length = 0;
  
  // copy lit LEDs (those with _cube_buffer[i]>0 into the circularly linked list
  int i=0;  
  // Do some macro manipulation to build up flushElement calls for all LEDs
  // Expands to 192 lines of the FLUSH_ELEM macro, with the pins replaced by the mappings in mappins.h:
  // b111,b112,b113,b114,b121,b122,...,g111,...,r444
#define FLUSH_ELEM(c,x,y,z) if(_cube_buffer[ i ] != 0) flushElement(copy_frame, PINS(c,x,y,z) ,_cube_buffer[ i ]); i++
#define PINS_Z(c,x,y) FLUSH_ELEM( c,x,y,1 ); FLUSH_ELEM( c,x,y,2 ); FLUSH_ELEM( c,x,y,3 ); FLUSH_ELEM( c,x,y,4 )
#define PINS_Y(c,x) PINS_Z(c,x,1); PINS_Z(c,x,2); PINS_Z(c,x,3); PINS_Z(c,x,4)
#define PINS_X(c) PINS_Y(c,1); PINS_Y(c,2); PINS_Y(c,3); PINS_Y(c,4);

  PINS_X(b); PINS_X(g); PINS_X(r);

#undef PINS_X
#undef PINS_Y
#undef PINS_Z
#undef FLUSH_ELEM
  
  // circularly link the list
  (_cube__frame+1)->next=copy_frame;
  _cube_current_frame=_cube__frame+1;
}


/*************************** INTERRUPT DISPLAY LEDS ***************************\
| This is the interrupt function to turn on one led. After it turns that one   |
| on it will 
\******************************************************************************/
byte pinsB[] = {P1B,P2B,P3B,P4B,P5B,P6B,P7B,P8B,P9B,P10B,P11B,P12B,P13B,P14B,P15B,P16B};
byte pinsC[] = {P1C,P2C,P3C,P4C,P5C,P6C,P7C,P8C,P9C,P10C,P11C,P12C,P13C,P14C,P15C,P16C};
byte pinsD[] = {P1D,P2D,P3D,P4D,P5D,P6D,P7D,P8D,P9D,P10D,P11D,P12D,P13D,P14D,P15D,P16D};
#ifndef PWMMAX
  #define PWMMMAX 8
#endif
#define FULL PWMMMAX
#define HALF PWMMMAX/2
// the interrupt function to display the leds
ISR(TIMER2_OVF_vect) {
  // fetch logical group for current LED
  int pin1 = _cube_current_frame->pin1;
  int pin2 = _cube_current_frame->pin2;
  int count = _cube_current_frame->brightness;

  // All LEDs off
  PORTB = 0x00;
  PORTC = 0x00;
  PORTD = 0x00;
  // Turn LED on for first count iterations through list
  if (count > pwmm){
    // set currently lit pins as outputs, all others as high impetance
    DDRB = pinsB[pin1] | pinsB[pin2];
    DDRC = pinsC[pin1] | pinsC[pin2];
    DDRD = pinsD[pin1] | pinsD[pin2];
    // drive pin1 high and pin2 low
    PORTB = pinsB[pin1];
    PORTC = pinsC[pin1];
    PORTD = pinsD[pin1];
    
  }
  _cube_current_frame = _cube_current_frame->next;
  if (_cube_current_frame == _cube__frame+1){
    pwmm++;// = (pwmm+1)%PWMMMAX; // oooook so the modulus function is just a tincy bit toooooo slow when only one led is on
    if (pwmm == PWMMMAX) pwmm = 0; // by too slow i mean "to slow for the program to process an update" here is the fix
  }
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
// set the interupt function to signal when the pattern is finished
ISR(TIMER1_OVF_vect) {
  animationTimer++;
  if (animationTimer == animationMax) {
    continuePattern = false;
    animationTimer=0;
  }
}

#endif
