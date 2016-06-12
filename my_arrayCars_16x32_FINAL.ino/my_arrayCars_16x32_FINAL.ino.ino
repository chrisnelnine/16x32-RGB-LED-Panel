// This sketch shows an animation of cars passing by
// Written by chrisnelnine@github
// for a 16x32 LED Panel driven by an Aduino Mega 2560
// Features a number decal on each car and a static background scene
// Cars consists of parts drawn from shapes which move in unison with the car 

// Adapted from testshapes demo for Adafruit RGBmatrixPanel library.
// which Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420
// written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 11  // MUST be on PORTB! (This is wriiten for Mega using pin 11)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true); //"true" for double buffering

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  32

//predefining some colours
const int red =           matrix.Color333(7,0,0);
const int lightRed =      matrix.Color333(1,0,0);
const int blue =          matrix.Color333(0,0,7);
const int lightBlue =     matrix.Color333(0,0,1);
const int green =         matrix.Color333(0,7,0);
const int lightGreen =    matrix.Color333(0,1,0);
const int yellow =        matrix.Color333(7,7,0);
const int lightYellow =   matrix.Color333(1,1,0);
const int cyan =          matrix.Color333(0,7,7);
const int lightCyan =     matrix.Color333(0,1,1);
const int magenta =       matrix.Color333(7,0,7);
const int lightMagenta =  matrix.Color333(1,0,1);
const int black =         matrix.Color333(0,0,0);
const int grey =          matrix.Color333(2,2,2);
const int darkGrey =      matrix.Color333(1,1,1);
const int white =         matrix.Color333(3,3,3);

int car1StartX = -64;  // starting position of left side of first car (which is hidden to the virtual left off screen)
int lagCar = 120;       // distance between cars minimum is 70 else cars overlap

#define CAR_NOS 8       //the number of cars

int startY = 0;         // vertical position of top of car body 
int carXlength = 64;    // car length
int carYheight = 11;    // visible car height
int carRoundness = 3;   // roundness of ends of car as each car is a rounded rectangle
int headlightOff = 62;  // offset horizontal distance from car left side to headlamps left
int frWheelOff = 48;    // offset horizontal distance from car left side to front wheel centre
int reWheelOff = 12;    // offset horizontal distance from car left side to rear wheel centre
int exhaustOff = -2;    // offset horizontal distance from car left side to exhaust left
int wheelY = 9;         // vertical distancee from screen top to wheel centre
int innerWheelR = 3;    // hub radius
int outerWheelR = 6;    // wheel radius

int incLimit = 120 * CAR_NOS; // loops when limit for the counter "inc" is reached

int carStart[CAR_NOS] = { car1StartX, car1StartX - lagCar, car1StartX - 2 * lagCar, 
car1StartX - 3 * lagCar, car1StartX - 4 * lagCar, car1StartX - 5 * lagCar, 
car1StartX - 6 * lagCar, car1StartX - 7 * lagCar}; //cars starting positions

//int numPositionX, numPositionY;

int col[CAR_NOS][8] = { // 8 colours for 8 car parts, respectively: body, headlight, tail pipe, front tyre, front hub, rear tyre, rear hub, number decal
  { lightYellow,  darkGrey,       darkGrey,       lightBlue,      lightGreen,   lightBlue,      lightGreen,   red       }, 
  { lightBlue,    darkGrey,       darkGrey,       lightRed,       lightYellow,  lightRed,       lightYellow,  red       },
  { lightRed,     darkGrey,       darkGrey,       lightGreen,     lightCyan,    lightGreen,     lightCyan,    white     },
  { lightMagenta, lightBlue,      lightBlue,      lightYellow,    lightRed,     lightYellow,    lightRed,     white     },
  { darkGrey,     lightRed,       lightRed,       lightBlue,      lightGreen,   lightBlue,      lightGreen,   blue      },
  { lightGreen,   lightBlue,      lightBlue,      lightRed,       lightYellow,  lightRed,       lightYellow,  yellow    },
  { lightCyan,    lightYellow,    lightYellow,    lightGreen,     lightRed,     lightGreen,     lightRed,     yellow    },
  { darkGrey,     lightGreen,     lightGreen,     lightMagenta,   lightGreen,   lightMagenta,   lightGreen,   black     }
};


void setup() {

matrix.begin();

}


void loop() {

for (int inc = 0; inc < incLimit; inc++) {
matrix.fillScreen(black);

//tree 1 in static background
matrix.drawLine(3, 0, 3, 31, matrix.Color333(4, 1, 0));
matrix.drawLine(4, 0, 4, 31, matrix.Color333(4, 1, 0));
matrix.fillTriangle(3, 0, -1, 8, 7, 8, matrix.Color333(0, 1, 0));
matrix.fillTriangle(4, 0, 0, 8, 8, 8, matrix.Color333(0, 1, 0));

//tree 2 in static background
matrix.drawLine(24, 6, 24, 31, matrix.Color333(4, 1, 0));
matrix.drawLine(25, 6, 25, 31, matrix.Color333(4, 1, 0));
matrix.fillTriangle(24, 6, 22, 9, 26, 9, matrix.Color333(0, 1, 0));
matrix.fillTriangle(25, 6, 23, 9, 27, 9, matrix.Color333(0, 1, 0));

//ground in static background
matrix.drawLine(0, 15, 31, 15, darkGrey);

//shop in static background
matrix.fillRect(10, 8, 11, 7, matrix.Color333(3, 1, 2));
matrix.fillRect(12, 10, 3, 5, matrix.Color333(1, 2, 3));

//stars in static background
matrix.fillRect(12, 5, 1, 1, matrix.Color333(1, 1, 1));
matrix.fillRect(14, 3, 1, 1, matrix.Color333(1, 1, 1));
matrix.fillRect(17, 6, 1, 1, matrix.Color333(1, 1, 1));
matrix.fillRect(23, 4, 1, 1, matrix.Color333(1, 1, 1));
matrix.fillRect(29, 2, 1, 1, matrix.Color333(1, 1, 1));

//the animated cars
for (int car = 0; car < CAR_NOS; car++) {
matrix.fillRoundRect(carStart[car] + inc, startY, carXlength, carYheight, carRoundness, col[car][0]); //draws car body
matrix.fillRect(carStart[car] + headlightOff + inc, 3, 2, 4, col[car][1]);                            //draws headlight
matrix.fillRect(carStart[car] + exhaustOff + inc, 7, 4, 2, col[car][2]);                              //draws exhaust
matrix.fillCircle(carStart[car] + reWheelOff + inc, wheelY, outerWheelR, col[car][3]);                //draws rear wheel
matrix.fillCircle(carStart[car] + reWheelOff + inc, wheelY, innerWheelR, col[car][4]);                //draws rear hub
matrix.fillCircle(carStart[car] + frWheelOff + inc, wheelY, outerWheelR, col[car][5]);                //draws front wheel
matrix.fillCircle(carStart[car] + frWheelOff + inc, wheelY, innerWheelR, col[car][6]);                //draws front hub
matrix.setTextColor(col[car][7]);
int const numPositionX = carStart[car] + inc + 27;
int const numPositionY = startY + 2;
matrix.setTextWrap(false);
matrix.setCursor(numPositionX, numPositionY );
matrix.print(car + 1);
//matrix.setTextColor(black);
//matrix.setCursor(0, 10 );
//matrix.print(car + 1);

}

// Update display, this line necessary with the "true" in RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true) for double buffering
matrix.swapBuffers(false);
}
 
}
