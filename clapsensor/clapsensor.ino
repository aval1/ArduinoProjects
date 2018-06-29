int ledpin=13; // ledpin and soundpin are not changed throughout the process 
 int soundpin=A0;
 int dig = A2;
 int threshold=544; // sets threshold value for sound sensor
 int oldVal=0;
 int dif=0;
 int latchPin = 11;
int clockPin = 9;
int dataPin = 12;
int difnorm=0;
int numLEDSLit=0;

int leds = 0;
void setup() {
Serial.begin(9600);
 pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
pinMode(ledpin,OUTPUT);
pinMode(soundpin,INPUT);
}
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}

void loop() {
int soundsens=analogRead(soundpin); 
int digsen=digitalRead(dig);
//Serial.println(soundsens);// reads analog data from sound sensor
dif=abs(oldVal-soundsens);
numLEDSLit = ((dif/2)%10);
Serial.println(numLEDSLit);
  if (numLEDSLit > 8) numLEDSLit = 8;
  leds = 0;   // no LEDs lit to start
  for (int i = 0; i < numLEDSLit; i++)
  {
    leds = leds + (1 << i);  // sets the i'th bit
  }
  updateShiftRegister();
  delay(7);
oldVal=soundsens;

}
