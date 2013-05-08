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

#define BUFFERSIZE 192 // Defined size of LED buffer

// Include the Arduino libraries in the source
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"  // For Arduino version 1.x
#else
  #include "WProgram.h" // For Arduino version 0.x
#endif

#include "mappings.h"
#include "niceTimer.h"

struct charliecubeForegroundLed{
  unsigned char pin1;
  unsigned char pin2;
  unsigned int brightness;
  unsigned char next;
};

charliecubeForegroundLed * charliecubeForegroundBuffer;  // foreground buffer
                              // background buffer

charliecubeForegroundLed * charliecubeCurrentLED;
unsigned char * charliecubeBackgroundBuffer;

bool continuePattern = false;

  int SET_LED(int one, int two, int i) {
    charliecubeForegroundBuffer[i].pin1 = one;
    charliecubeForegroundBuffer[i].pin2 = two;
    return i+1;
  }

/********************************** INIT CUBE *********************************\
| This function will allocate the memory required for the LED cube buffers.    |
| which is about [needs to be recalculated]
\******************************************************************************/
void initCube() {
  Serial.begin(9600);
  Serial.println(sizeof(charliecubeForegroundLed));
  Serial.println(sizeof(unsigned char));
  Serial.end();
  charliecubeForegroundBuffer = (charliecubeForegroundLed*)malloc(sizeof(charliecubeForegroundLed) * (BUFFERSIZE+1));
  charliecubeBackgroundBuffer = (unsigned char*)malloc(sizeof(unsigned char) * BUFFERSIZE);
  
  // ONLY NEEDED FOR DEBUGGING
  // Initialize the pins to not carry data over from the last build
  for (int i = 0; i < 192; i++) {
    charliecubeForegroundBuffer[  i].pin1 = 0; charliecubeForegroundBuffer[  i].pin2 = 0;
  }
  // END ONLY NEEDED FOR DEBUGGING

  for (int i = 0; i < BUFFERSIZE; i++) {
    charliecubeBackgroundBuffer[i] = 0;
  }

  // Initialize the 'OFF' LED of the list to start with an empty buffer
  charliecubeCurrentLED = charliecubeForegroundBuffer+192; 
  charliecubeCurrentLED->pin1 = 0;
  charliecubeCurrentLED->pin2 = 0;
  charliecubeCurrentLED->next = 192;
  charliecubeCurrentLED->brightness=0;

  
  //DEBUG STATEMENT
  /*
  charliecubeCurrentLED = charliecubeForegroundBuffer+191;
  charliecubeCurrentLED->next = 192;
  charliecubeCurrentLED->brightness=255;
  charliecubeCurrentLED = charliecubeForegroundBuffer+190;
  charliecubeCurrentLED->next = 191;
  charliecubeCurrentLED->brightness=255;
  */
  //END DEBUG
  
  // Configure Interrupt for Animation Progression
  #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
    // If the arduino is a 328 chip use Timer2
    Timer2_setPrescaler(256);
    Timer2_enableOverflowInterrupt();
    Timer2_setMode (TIMER2_NORMAL);
  #elif defined(__AVR_ATmega32U4__)
    // If the arduino is a 32U4 chip use Timer3
    Timer3_setPrescaler(256);
    Timer3_enableOverflowInterrupt();
    Timer3_setMode (TIMER3_NORMAL);
  #endif

  // Configure Interrupt for color display
  Timer1_setPrescaler(8);
  Timer1_enableOverflowInterrupt();
  Timer1_setMode (TIMER1_NORMAL);


  // Assign all the pin mappings to the display buffer  
  // This group of macros goes through all of the mappings in mappings.h and sets them to their pin memory slots
  int i = 0;
  #define DEFINE_LED(c,x,y,z) i=SET_LED(c##x##y##z,i)
  #define ITERATE_LED_Z_VALUES(c,x,y) DEFINE_LED( c,x,y,1 ); DEFINE_LED( c,x,y,2 ); DEFINE_LED( c,x,y,3 ); DEFINE_LED( c,x,y,4 )
  #define ITERATE_LED_Y_VALUES(c,x) ITERATE_LED_Z_VALUES(c,x,1); ITERATE_LED_Z_VALUES(c,x,2); ITERATE_LED_Z_VALUES(c,x,3); ITERATE_LED_Z_VALUES(c,x,4)
  #define ITERATE_LED_X_VALUES(c) ITERATE_LED_Y_VALUES(c,1); ITERATE_LED_Y_VALUES(c,2);   ITERATE_LED_Y_VALUES(c,3); ITERATE_LED_Y_VALUES(c,4);
  #define ITERATE_LED_COLORS() ITERATE_LED_X_VALUES(b); Serial.println(i); ITERATE_LED_X_VALUES(g); ITERATE_LED_X_VALUES(r);
  #define MAP_LEDS ITERATE_LED_COLORS();
  MAP_LEDS;
  #undef DEFINE_LED
  #undef ITERATE_LED_Z_VALUES
  #undef ITERATE_LED_Y_VALUES
  #undef ITERATE_LED_X_VALUES
  #undef ITERATE_LED_COLORS
  
  
  //testLED();

  
}
  //////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// HELPER FUNCTIONS //////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/******************************** CLEAR BUFFER ********************************\
| This function will clear the buffer that you can write to, this will allow   |
| you to draw an entirely new frame int other buffer                           |
\******************************************************************************/
void clearBuffer () {
  for (int i = 0; i < BUFFERSIZE; i++) {
    charliecubeBackgroundBuffer[i] = 0;
  }
}

/**************************** NEXT COLOR FUNCTIONS ****************************\
| These functions cycle through                                                |
|  the three primary colors red, greed, and blue                               |
|  the secondary colors purple, teal, yellow (every pairing of two LEDs)       |
|  the ALL THE COLORS (red,green,blue,purple,teal,yellow,white)                |
\******************************************************************************/
int nextPrimaryColor(int color)   { return  (color+1)%3; }
int nextSecondaryColor(int color) { return ((color+1)%3)+3; }
int nextColor(int color)          { return  (color+1)%7; }

/********************************** SWAP INT **********************************\
| This function uses the fast xor swap to change the values of the two         |
| integers passed into the function                                            |
\******************************************************************************/
void swapint(int & one, int & two) {
  one = one^two;
  two = one^two;
  one = one^two;
}

/******************************* ROUND CLOSTEST *******************************\
| This function takes in a numerator and denominator and rounds to the         |
| nearest number instead of truncating. It does this by calculating an extra   |
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
#define off 7

/********************************** DRAW LED **********************************\
| This function turns on LEDs at a specified position. Depending on which      |
| color this function turns on different colors of the LED                     |
\******************************************************************************/
void drawLed(int color, int brightness, int x, int y, int z) {
  
  if ((color/3)==0) { // single color (red green blue)
    charliecubeBackgroundBuffer[(((color)%3)*64)+(x*16)+(y*4)+z] += brightness;
    //charliecubeBackgroundBuffer[(((color+1)%3)*64)+(x*16)+(y*4)+z] += 0;
  }
  else if ((color/3)==1) { // double color (teal yellow purple)
    charliecubeBackgroundBuffer[(((color)%3)*64)+(x*16)+(y*4)+z] += brightness;
    charliecubeBackgroundBuffer[(((color+1)%3)*64)+(x*16)+(y*4)+z] += brightness;
  }
  else if (color == 6){ // all colors (white)
    charliecubeBackgroundBuffer[((0)*64)+(x*16)+(y*4)+z] += brightness;
    charliecubeBackgroundBuffer[((1)*64)+(x*16)+(y*4)+z] += brightness;
    charliecubeBackgroundBuffer[((2)*64)+(x*16)+(y*4)+z] += brightness;
  }
  else if (color == 7) {
    charliecubeBackgroundBuffer[((0)*64)+(x*16)+(y*4)+z] = 0;
    charliecubeBackgroundBuffer[((1)*64)+(x*16)+(y*4)+z] = 0;
    charliecubeBackgroundBuffer[((2)*64)+(x*16)+(y*4)+z] = 0;
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
  drawBox(color,255,startx,starty,startz,endx,endy,endz);
}
/******************************* DRAW HOLLOW BOX ******************************\
| This function will draw the walls, ceiling, and floor of a defined box       |
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
| This function will draw the vertical walls and all four sides of a defined   |
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
    for (int j = startx+1; j <= endx-1; j++) {
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
| to the limited availability of pixels the best approximation is chosen for   |
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
unsigned int offtime; // how long the leds should be off per cycle

/******************************** FLUSH BUFFER ********************************\
| This takes the buffer frame and sets the display memory to match, because    |
| the display memory needs to be faster it is split up into two arrays instead |
| of just one. The display frame is actually a cyclic linked list which allows |
| the program to just loop through and turn on the LEDs without the need to    |
| check to see if it is at the end of the loop                                 |
\******************************************************************************/

void flushBuffer() {
  // Use this to determine if an led is on and how to handle inserting and deleting elements in the list
  charliecubeForegroundLed * previousActivatedFrame = charliecubeForegroundBuffer+192;
  //offtime = 0; // no longer set offtime to 0, all modifications will be done within the loop
  int ledCount = 0; // How many leds are on?
  for (int i = 0; i < 192; i++) {
    int newBrightness = charliecubeBackgroundBuffer[i];
    if (previousActivatedFrame->next == i) { // Previously On
      int oldBrightness = charliecubeForegroundBuffer[i].brightness;
      if (newBrightness == 0) { // Turning Off
        previousActivatedFrame->next = charliecubeForegroundBuffer[i].next;// set previous's next to this's next
        offtime -= 255-oldBrightness;// remove the brightness modification from offtime
      }
      else { // Staying On (with possible brightness change)
        ledCount += 1;
        offtime += oldBrightness - newBrightness;// Change the offtime variable based on the difference in brightnesses
        charliecubeForegroundBuffer[i].brightness = newBrightness;// Change the brightness value
        previousActivatedFrame = charliecubeForegroundBuffer+i; // Set this as the previousActivatedFrame
      }
    }
    else { // Previously Off
      if (newBrightness == 0) {} // Staying Off (do nothing)
      else { // Turning On
        ledCount += 1;
        charliecubeForegroundBuffer[i].next = previousActivatedFrame->next;//Set this's next to the previous's next
        charliecubeForegroundBuffer[i].brightness = newBrightness; // set this brightness to the brightness value
        offtime += 255 - newBrightness;// modify the offtime based on the brightness
        previousActivatedFrame->next = i;// Set the the previous's mext to this
        previousActivatedFrame = charliecubeForegroundBuffer+i;// Set this as the previousActivatedFrame
      }
      
    }
  }
  if (ledCount == 0) {
    charliecubeForegroundBuffer[192].brightness = 255;
  }
  else {
    charliecubeForegroundBuffer[192].brightness = offtime;
  }
}


  //////////////////////////////////////////////////////////////////////////////
 /////////////////////////// INTERRUPT DEFINITIONS //////////////////////////// 
//////////////////////////////////////////////////////////////////////////////  


/*************************** INTERRUPT DISPLAY LEDS ***************************\
| This is the interrupt function to turn on one led. After it turns that one   |
| on it will 
\******************************************************************************/
#ifdef __AVR_ATmega328P__ // Arduino Duemilinova / Uno
byte pinsB[] = {0x00,WIRE_1_PORT_B,WIRE_2_PORT_B,WIRE_3_PORT_B,WIRE_4_PORT_B,
                WIRE_5_PORT_B,WIRE_6_PORT_B,WIRE_7_PORT_B,WIRE_8_PORT_B,
                WIRE_9_PORT_B,WIRE_10_PORT_B,WIRE_11_PORT_B,WIRE_12_PORT_B,
                WIRE_13_PORT_B,WIRE_14_PORT_B,WIRE_15_PORT_B,WIRE_16_PORT_B};
byte pinsC[] = {0x00,WIRE_1_PORT_C,WIRE_2_PORT_C,WIRE_3_PORT_C,WIRE_4_PORT_C,
                WIRE_5_PORT_C,WIRE_6_PORT_C,WIRE_7_PORT_C,WIRE_8_PORT_C,
                WIRE_9_PORT_C,WIRE_10_PORT_C,WIRE_11_PORT_C,WIRE_12_PORT_C,
                WIRE_13_PORT_C,WIRE_14_PORT_C,WIRE_15_PORT_C,WIRE_16_PORT_C};
byte pinsD[] = {0x00,WIRE_1_PORT_D,WIRE_2_PORT_D,WIRE_3_PORT_D,WIRE_4_PORT_D,
                WIRE_5_PORT_D,WIRE_6_PORT_D,WIRE_7_PORT_D,WIRE_8_PORT_D,
                WIRE_9_PORT_D,WIRE_10_PORT_D,WIRE_11_PORT_D,WIRE_12_PORT_D,
                WIRE_13_PORT_D,WIRE_14_PORT_D,WIRE_15_PORT_D,WIRE_16_PORT_D};
#endif
#ifdef __AVR_ATmega32U4__ // Arduino Leonardo
byte pinsB[] = {0x00,WIRE_1_PORT_B,WIRE_2_PORT_B,WIRE_3_PORT_B,WIRE_4_PORT_B,
                WIRE_5_PORT_B,WIRE_6_PORT_B,WIRE_7_PORT_B,WIRE_8_PORT_B,
                WIRE_9_PORT_B,WIRE_10_PORT_B,WIRE_11_PORT_B,WIRE_12_PORT_B,
                WIRE_13_PORT_B,WIRE_14_PORT_B,WIRE_15_PORT_B,WIRE_16_PORT_B};
byte pinsC[] = {0x00,WIRE_1_PORT_C,WIRE_2_PORT_C,WIRE_3_PORT_C,WIRE_4_PORT_C,
                WIRE_5_PORT_C,WIRE_6_PORT_C,WIRE_7_PORT_C,WIRE_8_PORT_C,
                WIRE_9_PORT_C,WIRE_10_PORT_C,WIRE_11_PORT_C,WIRE_12_PORT_C,
                WIRE_13_PORT_C,WIRE_14_PORT_C,WIRE_15_PORT_C,WIRE_16_PORT_C};
byte pinsD[] = {0x00,WIRE_1_PORT_D,WIRE_2_PORT_D,WIRE_3_PORT_D,WIRE_4_PORT_D,
                WIRE_5_PORT_D,WIRE_6_PORT_D,WIRE_7_PORT_D,WIRE_8_PORT_D,
                WIRE_9_PORT_D,WIRE_10_PORT_D,WIRE_11_PORT_D,WIRE_12_PORT_D,
                WIRE_13_PORT_D,WIRE_14_PORT_D,WIRE_15_PORT_D,WIRE_16_PORT_D};
byte pinsE[] = {0x00,WIRE_1_PORT_E,WIRE_2_PORT_E,WIRE_3_PORT_E,WIRE_4_PORT_E,
                WIRE_5_PORT_E,WIRE_6_PORT_E,WIRE_7_PORT_E,WIRE_8_PORT_E,
                WIRE_9_PORT_E,WIRE_10_PORT_E,WIRE_11_PORT_E,WIRE_12_PORT_E,
                WIRE_13_PORT_E,WIRE_14_PORT_E,WIRE_15_PORT_E,WIRE_16_PORT_E};
byte pinsF[] = {0x00,WIRE_1_PORT_F,WIRE_2_PORT_F,WIRE_3_PORT_F,WIRE_4_PORT_F,
                WIRE_5_PORT_F,WIRE_6_PORT_F,WIRE_7_PORT_F,WIRE_8_PORT_F,
                WIRE_9_PORT_F,WIRE_10_PORT_F,WIRE_11_PORT_F,WIRE_12_PORT_F,
                WIRE_13_PORT_F,WIRE_14_PORT_F,WIRE_15_PORT_F,WIRE_16_PORT_F};
#endif

#ifdef __AVR_ATmega2560__ // Arduino Mega
byte pinsA[] = {0x00,WIRE_1_PORT_A,WIRE_2_PORT_A,WIRE_3_PORT_A,WIRE_4_PORT_A,WIRE_5_PORT_A,WIRE_6_PORT_A,WIRE_7_PORT_A,WIRE_8_PORT_A,WIRE_9_PORT_A,WIRE_10_PORT_A,WIRE_11_PORT_A,WIRE_12_PORT_A,WIRE_13_PORT_A,WIRE_14_PORT_A,WIRE_15_PORT_A,WIRE_16_PORT_A};
byte pinsB[] = {0x00,WIRE_1_PORT_B,WIRE_2_PORT_B,WIRE_3_PORT_B,WIRE_4_PORT_B,WIRE_5_PORT_B,WIRE_6_PORT_B,WIRE_7_PORT_B,WIRE_8_PORT_B,WIRE_9_PORT_B,WIRE_10_PORT_B,WIRE_11_PORT_B,WIRE_12_PORT_B,WIRE_13_PORT_B,WIRE_14_PORT_B,WIRE_15_PORT_B,WIRE_16_PORT_B};
byte pinsC[] = {0x00,WIRE_1_PORT_C,WIRE_2_PORT_C,WIRE_3_PORT_C,WIRE_4_PORT_C,WIRE_5_PORT_C,WIRE_6_PORT_C,WIRE_7_PORT_C,WIRE_8_PORT_C,WIRE_9_PORT_C,WIRE_10_PORT_C,WIRE_11_PORT_C,WIRE_12_PORT_C,WIRE_13_PORT_C,WIRE_14_PORT_C,WIRE_15_PORT_C,WIRE_16_PORT_C};
byte pinsD[] = {0x00,WIRE_1_PORT_D,WIRE_2_PORT_D,WIRE_3_PORT_D,WIRE_4_PORT_D,WIRE_5_PORT_D,WIRE_6_PORT_D,WIRE_7_PORT_D,WIRE_8_PORT_D,WIRE_9_PORT_D,WIRE_10_PORT_D,WIRE_11_PORT_D,WIRE_12_PORT_D,WIRE_13_PORT_D,WIRE_14_PORT_D,WIRE_15_PORT_D,WIRE_16_PORT_D};
byte pinsE[] = {0x00,WIRE_1_PORT_E,WIRE_2_PORT_E,WIRE_3_PORT_E,WIRE_4_PORT_E,WIRE_5_PORT_E,WIRE_6_PORT_E,WIRE_7_PORT_E,WIRE_8_PORT_E,WIRE_9_PORT_E,WIRE_10_PORT_E,WIRE_11_PORT_E,WIRE_12_PORT_E,WIRE_13_PORT_E,WIRE_14_PORT_E,WIRE_15_PORT_E,WIRE_16_PORT_E};
byte pinsF[] = {0x00,WIRE_1_PORT_F,WIRE_2_PORT_F,WIRE_3_PORT_F,WIRE_4_PORT_F,WIRE_5_PORT_F,WIRE_6_PORT_F,WIRE_7_PORT_F,WIRE_8_PORT_F,WIRE_9_PORT_F,WIRE_10_PORT_F,WIRE_11_PORT_F,WIRE_12_PORT_F,WIRE_13_PORT_F,WIRE_14_PORT_F,WIRE_15_PORT_F,WIRE_16_PORT_F};
byte pinsG[] = {0x00,WIRE_1_PORT_G,WIRE_2_PORT_G,WIRE_3_PORT_G,WIRE_4_PORT_G,WIRE_5_PORT_G,WIRE_6_PORT_G,WIRE_7_PORT_G,WIRE_8_PORT_G,WIRE_9_PORT_G,WIRE_10_PORT_G,WIRE_11_PORT_G,WIRE_12_PORT_G,WIRE_13_PORT_G,WIRE_14_PORT_G,WIRE_15_PORT_G,WIRE_16_PORT_G};
byte pinsH[] = {0x00,WIRE_1_PORT_H,WIRE_2_PORT_H,WIRE_3_PORT_H,WIRE_4_PORT_H,WIRE_5_PORT_H,WIRE_6_PORT_H,WIRE_7_PORT_H,WIRE_8_PORT_H,WIRE_9_PORT_H,WIRE_10_PORT_H,WIRE_11_PORT_H,WIRE_12_PORT_H,WIRE_13_PORT_H,WIRE_14_PORT_H,WIRE_15_PORT_H,WIRE_16_PORT_H};
byte pinsJ[] = {0x00,WIRE_1_PORT_J,WIRE_2_PORT_J,WIRE_3_PORT_J,WIRE_4_PORT_J,WIRE_5_PORT_J,WIRE_6_PORT_J,WIRE_7_PORT_J,WIRE_8_PORT_J,WIRE_9_PORT_J,WIRE_10_PORT_J,WIRE_11_PORT_J,WIRE_12_PORT_J,WIRE_13_PORT_J,WIRE_14_PORT_J,WIRE_15_PORT_J,WIRE_16_PORT_J};
byte pinsK[] = {0x00,WIRE_1_PORT_K,WIRE_2_PORT_K,WIRE_3_PORT_K,WIRE_4_PORT_K,WIRE_5_PORT_K,WIRE_6_PORT_K,WIRE_7_PORT_K,WIRE_8_PORT_K,WIRE_9_PORT_K,WIRE_10_PORT_K,WIRE_11_PORT_K,WIRE_12_PORT_K,WIRE_13_PORT_K,WIRE_14_PORT_K,WIRE_15_PORT_K,WIRE_16_PORT_K};
byte pinsL[] = {0x00,WIRE_1_PORT_L,WIRE_2_PORT_L,WIRE_3_PORT_L,WIRE_4_PORT_L,WIRE_5_PORT_L,WIRE_6_PORT_L,WIRE_7_PORT_L,WIRE_8_PORT_L,WIRE_9_PORT_L,WIRE_10_PORT_L,WIRE_11_PORT_L,WIRE_12_PORT_L,WIRE_13_PORT_L,WIRE_14_PORT_L,WIRE_15_PORT_L,WIRE_16_PORT_L};
#endif


ISR(TIMER1_OVF_vect) {
  #ifdef __AVR_ATmega328P__ // Arduino Duemilinova / Uno
  PORTB = 0x00;
  PORTC = 0x00;
  PORTD = 0x00;
  #endif
  #ifdef __AVR_ATmega32U4__ // Arduino Leonardo
  PORTB = 0x00;
  PORTC = 0x00;
  PORTD = 0x00;
  PORTE = 0x00;
  PORTF = 0x00;
  #endif 
  #ifdef __AVR_ATmega2560__
  PORTA = 0x00;
  PORTB = 0x00;
  PORTC = 0x00;
  PORTD = 0x00;
  PORTE = 0x00;
  PORTF = 0x00;
  PORTG = 0x00;
  PORTH = 0x00;
  PORTJ = 0x00;
  PORTK = 0x00;
  PORTL = 0x00;
  #endif
  
  int pin1 = charliecubeCurrentLED->pin1;
  int pin2 = charliecubeCurrentLED->pin2;
  int brightness = charliecubeCurrentLED->brightness;
  
  charliecubeCurrentLED = charliecubeForegroundBuffer + charliecubeCurrentLED->next;
  
  #ifdef __AVR_ATmega328P__ // Arduino Duemilinova / Uno 
  DDRB = pinsB[pin1] | pinsB[pin2];
  DDRC = pinsC[pin1] | pinsC[pin2];
  DDRD = pinsD[pin1] | pinsD[pin2];
  
  PORTB = pinsB[pin1];
  PORTC = pinsC[pin1];
  PORTD = pinsD[pin1];
  #endif
  
  #ifdef __AVR_ATmega32U4__ // Arduino Leonardo
  DDRB = pinsB[pin1] | pinsB[pin2];
  DDRC = pinsC[pin1] | pinsC[pin2];
  DDRD = pinsD[pin1] | pinsD[pin2];
  DDRE = pinsE[pin1] | pinsE[pin2];
  DDRF = pinsF[pin1] | pinsF[pin2];
  
  PORTB = pinsB[pin1];
  PORTC = pinsC[pin1];
  PORTD = pinsD[pin1];
  PORTE = pinsE[pin1];
  PORTF = pinsF[pin1];
  #endif
  
  #ifdef __AVR_ATmega2560__
  DDRA = pinsA[pin1] | pinsA[pin2];
  DDRB = pinsB[pin1] | pinsB[pin2];
  DDRC = pinsC[pin1] | pinsC[pin2];
  DDRD = pinsD[pin1] | pinsD[pin2];
  DDRE = pinsE[pin1] | pinsE[pin2];
  DDRF = pinsF[pin1] | pinsF[pin2];
  DDRG = pinsG[pin1] | pinsG[pin2];
  DDRH = pinsH[pin1] | pinsH[pin2];
  DDRJ = pinsJ[pin1] | pinsJ[pin2];
  DDRK = pinsK[pin1] | pinsK[pin2];
  DDRL = pinsL[pin1] | pinsL[pin2];
  
  PORTA = pinsA[pin1];
  PORTB = pinsB[pin1];
  PORTC = pinsC[pin1];
  PORTD = pinsD[pin1];
  PORTE = pinsE[pin1];
  PORTF = pinsF[pin1];
  PORTG = pinsG[pin1];
  PORTH = pinsH[pin1];
  PORTJ = pinsJ[pin1];
  PORTK = pinsK[pin1];
  PORTL = pinsL[pin1];
  
  
  /*
  for (int i = 0; i < 16; i++) {
    pinMode(pins[i], INPUT);
  }
      pinMode(pins[pin1],OUTPUT);
      pinMode(pins[pin2],OUTPUT);
      digitalWrite(pins[pin1],HIGH);
      digitalWrite(pins[pin2],LOW);*/
  
  #endif

  Timer1_setValue(0xFFFF - brightness);
}



// Allocate the current time and the maximum time variables
int animationTimer = 0;
int animationMax = 0;
// Detect the correct interrupt to trigger on based on chip
#if defined(__AVR_ATmega328P__)
  #define TIMER_INTERRUPT_VECTOR TIMER2_OVF_vect
#elif defined(__AVR_ATmega32U4__)
  #define TIMER_INTERRUPT_VECTOR TIMER3_OVF_vect
#elif defined(__AVR_ATmega2560__)
  #define TIMER_INTERRUPT_VECTOR TIMER2_OVF_vect
#endif
// The advance animation interrupt
ISR(TIMER_INTERRUPT_VECTOR) {
  animationTimer++;
  if (animationTimer >= animationMax) {
    continuePattern = false;
    animationTimer=0;
  }  
}

void setAnimationTime(unsigned int maxValue) {
  #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__)
    animationMax = maxValue; // prescaler 255 on a 8 bit timer
  #elif defined(__AVR_ATmega32U4__)
    animationMax = maxValue/256; // prescaler 255 on a 16 bit timer
  #endif
  
}


#endif
