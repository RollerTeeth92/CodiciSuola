int rDiv = 3300; //valore dei resistori che costituiscono il partitore di tensione con ciascuno dei sensori
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // leggo i valori dei 5 sensori
  int sensorValue1 = analogRead(A1); 
  int sensorValue2 = analogRead(A2);
  int sensorValue3 = analogRead(A3);
  int sensorValue4 = analogRead(A4);
  int sensorValue5 = analogRead(A5);
  // converto i valori acquisiti (compresi tra 0 e 1023) in valori di tensione (compresi tra 0 e 5 volt)
  float voltage1 = sensorValue1 * (5.0 / 1023.0);
  float voltage2 = sensorValue2 * (5.0 / 1023.0);
  float voltage3 = sensorValue3 * (5.0 / 1023.0);
  float voltage4 = sensorValue4 * (5.0 / 1023.0);
  float voltage5 = sensorValue5 * (5.0 / 1023.0);
  // uso la formula inversa del partitore per ricavare il valore di resistenza dei sensori.
  float fsr1 = rDiv*5/voltage1 - rDiv;
  float fsr2 = rDiv*5/voltage2 - rDiv;
  float fsr3 = rDiv*5/voltage3 - rDiv;
  float fsr4 = rDiv*5/voltage4 - rDiv;
  float fsr5 = rDiv*5/voltage5 - rDiv;

  // stampo a video il valore di resistenza dei 5 sensori
  Serial.print("Sensore 1: ");
  Serial.println(fsr1);
  delay(500);
  Serial.print("Sensore 2: ");
  Serial.println(fsr2);
  delay(500);
  Serial.print("Sensore 3: ");
  Serial.println(fsr3);
  delay(500);
  Serial.print("Sensore 4: ");
  Serial.println(fsr4);
  delay(500);
  Serial.print("Sensore 5: ");
  Serial.println(fsr5);
}
