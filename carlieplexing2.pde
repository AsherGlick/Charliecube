#include "cubeplex.h"

int color = red;


void setup() {
  initCube();
  
  // how many secconds until the animation is told to progress
  animationMax = 10;
}
void loop() {
  // animations to display \\ 
  planarSpin();
  fountian();
  trifade();
  shiftSquares();
  tunnel();
  chaseTheDot();
  planarFlop();
  
}

/********************************* PLANAR SPIN ********************************\
| A plane of light spins around the virtical center of the cube and changes    |
| colors after a certian number of rotations                                   |
|                                                                              |
| Written By: Asher Glick                                                      |
\******************************************************************************/
void planarSpin() {
  continuePattern = true;
  while (continuePattern) {
    for (int x = 0; x < 3; x++) {
      drawLine(color,x,0,0,3-x,3,0); // TODO repeat z
    }
    for (int y = 0; y < 3; y++) {
      drawLine(color,3,y,0,0,3-y,0); // TODO repeat z
    }
  }
}

/********************************** FOUNTIAN **********************************\
| Light shoots up the middle of the cube then once it reaches the top fall     |
| back down on the outside of the cube. After it hits the bottom it changes    |
| color and starts again                                                       |
|                                                                              |
| Written By: Asher Glick                                                      |
\******************************************************************************/
void fountian() {
  continuePattern = true;
  int animationSpeed = 10;
  while (continuePattern) {
    for (int z = 0; z <= 3; z++) {
      drawBoxWalls(color,1,1,z,2,2,z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    for (int z = 3; z >= 0; z--) {
      drawBoxWalls(color,0,0,z,3,3,z);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
  }
}

/********************************** TRI-FADE **********************************\
| This animation fades through the red green and blue colors of the leds       |
| creating different mixtures of each of the colors.                           |
|                                                                              |
| Written By: Asher Glick                                                      |
\******************************************************************************/
void trifade() {
  continuePattern = true;
  int animationSpeed = 10;
  while (continuePattern) {
    // blue fade out, red fade in
    for (int i = 1; i <= 8; i++) {
      drawBox(blue,9-i,0,0,0,3,3,3);
      drawBox(red,i,0,0,0,3,3,3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    // red fade out, green fade in
    for (int i = 1; i <= 8; i++) {
      drawBox(red,9-i,0,0,0,3,3,3);
      drawBox(green,i,0,0,0,3,3,3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
    // green fade out, blue fade in
    for (int i = 1; i <= 8; i++) {
      drawBox(green,9-i,0,0,0,3,3,3);
      drawBox(blue,i,0,0,0,3,3,3);
      flushBuffer();
      clearBuffer();
      delay(animationSpeed);
    }
  }
}

/******************************** SHIFT SQUARES *******************************\
|

-1 0 1 2

((bluex+3)%6)-2


\******************************************************************************/
void shiftSquares() {
  continuePattern = true;
  int animationSpeed = 10;
  
  int bluex = 0;
  int bluey = 0;
  int bluez = 0;
  
  int redx = 0;
  int redy = 0;
  int redz = 0;
  
  int greenx = 0;
  int greeny = 0;
  int greenz = 0;
  
  while(continuePattern) {
    switch (random(0,9)) {
      case 0:
        bluex = bluex^0x01;
      case 1:
        //bluey
      case 2:
        bluez=bluez;
        
    }
    drawBox(blue,bluex*2,bluey*2,bluez*2,bluex*2+1,bluey*2+1,bluez*2);
  }
}
/*********************************** TUNNEL ***********************************\
|
\******************************************************************************/
void tunnel() {
  continuePattern = true;
  while (continuePattern) {
    
  }
}
/******************************** CHASE THE DOT *******************************\
| A single point of light moves around the cube randomly and changes colors    |
| when it tries to go out of bounds                                            |
|                                                                              |
| Inspired By: Jonah Glick                                                     |
| Written By: Asher Glick                                                      |
\******************************************************************************/
void chaseTheDot() {
  continuePattern = true;
  int animationSpeed = 10;
  
  int xpos = 0;
  int ypos = 0;
  int zpos = 0;
  
  while (continuePattern) {
    switch(random(0,6)) {
      case 0:
        if (xpos > 0) {xpos--;break;}
        else color=nextColor(color);
      case 1:
        if (xpos < 3) {xpos++;break;}
        else color=nextColor(color);
        xpos--; break;
        
      case 2:
        if (ypos > 0) {ypos--;break;}
        else color=nextColor(color);
      case 3:
        if (ypos < 3) {ypos++;break;}
        else color=nextColor(color);
        ypos--; break;
      
      case 4:
        if (ypos > 0) {ypos--;break;}
        else color=nextColor(color);
      case 5:
        if (ypos < 3) {ypos++;break;}
        else color=nextColor(color);
        ypos--; break;
    }
    drawLed(color,xpos,ypos,zpos);
    flushBuffer();
    clearBuffer();
    delay(animationSpeed);
  }
}
/********************************* PLANAR FLOP ********************************\
|
\******************************************************************************/
void planarFlop() {
  continuePattern = true;
  while (continuePattern) {
    
  }
}
