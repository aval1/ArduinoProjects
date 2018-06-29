//www.elegoo.com
//2016.12.08
#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11
int ledPin = 2;
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;
  boolean light;
  int cloc = 0;  int BLUE = 3;
  int GREEN = 6;
  int RED = 5;
  int redValue;
int greenValue;
int blueValue;
  

void setup() {
  pinMode(ledPin, OUTPUT);
   Serial.begin(9600);
   delay(1000);
      pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);
digitalWrite(RED, LOW);
digitalWrite(GREEN, LOW);
digitalWrite(BLUE, LOW);
}

void loop() {
  a=sr04.Distance();
    redValue = 0; // choose a value between 1 and 255 to change the color.
greenValue = 0;
blueValue = 0;
  if(a<60){
      redValue = 255; // choose a value between 1 and 255 to change the color.
greenValue = 255;
blueValue = 255;
     analogWrite(BLUE, redValue);
    analogWrite(RED,redValue);
    light = true;
    delay(1000);
    while(light){
      Serial.println("ive reached this part of the loop");
      a = sr04.Distance();
      cloc +=1;
      Serial.println(a);
      if(a<60||cloc>=10000){
        analogWrite(BLUE, 0);
    analogWrite(RED,0);
        light = false;
        delay(1000);
      }
    }
  }
}



