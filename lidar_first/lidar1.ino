// I2C SRF10 or SRF08 Devantech Ultrasonic Ranger Finder
// by Nicholas Zambetti <http://www.zambetti.com>
// and James Tichenor <http://www.jamestichenor.net>

// Demonstrates use of the Wire library reading data from the
// Devantech Utrasonic Rangers SFR08 and SFR10

// Created 29 April 2006

// This example code is in the public domain.


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define LCDLINE_1 0
#define LCDLINE_2 1
#define LCDLINE_3 2
#define LCDLINE_4 3


void setup() {
  Wire.begin();                // join i2c bus (address optional for master)
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("LCD: OK. ");

  lcd.print("LIDAR init...");
  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  myLidarLite.configure(0); // Change this number to try out alternate configurations

  lcd.setCursor(9,0);
  lcd.print("LIDAR: OK.   ");

}

int maxDist = 0;
int d;
int dd;
int lastdd = 0;

char lineBuf[21];

void loop() {

  d = myLidarLite.distance();

  for(int i = 0; i < 99; i++)
  {
    maxDist = max(d, maxDist);

    showGraphPos( d, LCDLINE_4 );
    
    showDistance( d, LCDLINE_2);
    
    d = myLidarLite.distance(false);
  }  
  showMaxDistance( maxDist, LCDLINE_3);
}

void printFormattedDistance(char* buf, int dist) {
    int m = dist/100;
    int cm=dist%100; 
    sprintf(buf, "%.2um %.2ucm", m, cm);
}

void showMaxDistance(int d, int line) {
  lcd.setCursor(7,line);
  printFormattedDistance(lineBuf, maxDist);
  lcd.print("max: "); 
  lcd.print( lineBuf );
}

void showDistance(int d, int line) {
    printFormattedDistance(lineBuf, d);
    lcd.setCursor(0,line);
    lcd.print(lineBuf);
}

void showGraphPos( int d, int line ) {
    lcd.setCursor(lastdd,line); 
    lcd.print(" ");
    dd = map(d, 0, maxDist, 0, 19);
    lcd.setCursor(dd,line); 
    lcd.print("X");
    lastdd = dd;
}
