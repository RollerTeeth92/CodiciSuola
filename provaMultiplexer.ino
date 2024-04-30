
/*
#include <SoftwareSerial.h>
SoftwareSerial BTserial(0,1);
*/
#define EN 2
#define S0 3
#define S1 4
#define S2 5
#define S3 6

// Alimentation voltage
float V_cc = 4.99;

// Divider resistor
int rDiv = 94000;
//Mux in "SIG" pin
int SIG_pin = A1;

void setup(){
  Serial.begin(9600);
  pinMode(S0, OUTPUT); 
  pinMode(S1, OUTPUT); 
  pinMode(S2, OUTPUT); 
  pinMode(S3, OUTPUT);
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
  Serial.print("S1 S2 S3 S4 S5 S6 S7 S8 S9 S10 S11 S12 S13 S14 S15 S16");
  Serial.println();
  // BTserial.begin(9600);

}

void loop(){
  
  //Loop through and read all 16 values
  //Reports back Value at channel 6 is: 346
  for(int i = 0; i < 16; i ++)
  { 
    /*
    if (readMux(i) <= 180)
    {
       Serial.println("Il sensore " + String(i+1) + " mostra un valore superiore alla soglia, probabile iperpronazione");
    }
    */
    digitalWrite(EN, LOW);
    Serial.print(readMux(i));
    Serial.print(",");
    digitalWrite(EN, HIGH);
    /*
    BTserial.print(readMux(i));
    BTserial.print(";");
    */
  }
  Serial.println();
  Serial.println();
  delay(500);
}

int readMux(int channel)
{
  int controlPin[] = {S0, S1, S2, S3};
  int muxChannel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}, //channel 15
  };
  //loop through the 5 sig
  for(int i = 0; i < 4; i++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  //read the value at the SIG pin
  int fsrADC = analogRead(SIG_pin);
  fsrADC = map(fsrADC, 0, 1023, 255, 0);
  float fsrV = fsrADC*V_cc/255;
  float fsrR = (rDiv/1000) * (V_cc/fsrV - 1.0);
 

  //return the value
  return fsrADC;
}
