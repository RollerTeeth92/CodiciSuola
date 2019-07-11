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
int rDiv = 94000;  // valore della resistenza da mettere in serie al sensore per formare il partitore.
//Mux in "SIG" pin
int SIG_pin = A1; // Pin analogico della scheda arduino che acquisisce il dato

void setup(){
  Serial.begin(9600);
  // Pin 3, 4, 5 e 6, connessi ai pin S0, S1, S2 ed S3 del multiplexer, impostati come uscita 
  pinMode(S0, OUTPUT);  
  pinMode(S1, OUTPUT);  
  pinMode(S2, OUTPUT); 
  pinMode(S3, OUTPUT);
  // Inizialmente i segnali del multiplexer sono disattivati
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // imposto il pin 2, connesso al pin di enable del multiplexer, come uscita e lo imposto basso
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
  // istruzioni per stampare a video i dati provenienti dai sensori
  Serial.print("S1 S2 S3 S4 S5 S6 S7 S8 S9 S10 S11 S12 S13 S14 S15 S16");
  Serial.println();
  // BTserial.begin(9600);

}

void loop(){
  
  // ciclo for con il quale leggo i dati provenienti dai sensori
  for(int i = 0; i < 5; i ++)
  { 
    digitalWrite(EN, LOW);
    Serial.print(readMux(i));
    Serial.print(", ");
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
  int controlPin[] = {S0, S1, S2, S3}; // vettore dei pin di selezione del multiplexer
  int quoziente = int(channel/2); 
  int binRap[4];
  binRap[0] = channel%2;
  digitalWrite(controlPin[0], binRap[0]);
  for (int i=1; i<3; i++)
  {
    binRap[i] = quoziente%2;
    digitalWrite(controlPin[i], binRap[i]);
    quoziente = int(quoziente/2);
  }

  // leggo il valore di SIG_pin
  int fsrADC = analogRead(SIG_pin);
  // imposto la scala di fsrADC tra 0 e 255 
  fsrADC = map(fsrADC, 0, 1023, 0, 255);
  // passo dal valore adimensionale di fsrADC, al valore in tensione di fsrV
  float fsrV = fsrADC*V_cc/255; 
  // formula del partitore di tensione per ottenere la resistenza del sensore in kOhms
  float fsrR = (rDiv/1000) * (V_cc/fsrV - 1.0);
 

  // restituisce il valore
  return fsrADC;
}
