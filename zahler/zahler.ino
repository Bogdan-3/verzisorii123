int IR = 13;
int IR2 = 12;
int IR3 = 11;
int Quantity = 0;
int Quantity2 = 0;
int Quantity3 = 0;
int last = 0;
int last2 = 0;
int last3 = 0;
int number = 0;
int number2 = 0;
int number3 = 0;



void setup() {
  Serial.begin(9600);  // Starte die serielle Kommunikation mit 115200 Baud
  Serial.println("Serial communication test");  // Testnachricht
  pinMode(IR, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
}

void loop() {
  int sensorValue = digitalRead(IR);
  int sensorValue2 = digitalRead(IR2);
  int sensorValue3 = digitalRead(IR3);
  number = 0;
  number2 = 0;
  number3 = 0;

  if (sensorValue == 1){
    last = 0;
  }
  if (sensorValue2 == 1){
    last2 = 0;
  }
  if (sensorValue3 == 1){
    last3 = 0;
  }


  while (sensorValue == 0 && number == 0 && last == 0){
    Quantity = Quantity + 1;
    last = 1;
    number = number + 1;
  }
  while (sensorValue2 == 0 && number2 == 0 && last2 == 0){
    Quantity2 = Quantity2 + 1;
    last2 = 1;
    number2 = number2 + 1;
  }
  while (sensorValue3 == 0 && number3 == 0 && last3 == 0){
    Quantity3 = Quantity3 + 1;
    last3 = 1;
    number3 = number3 + 1;
    }

  Serial.println(Quantity);
  Serial.print("     ");
  Serial.print(Quantity2);
  Serial.print("     ");
  Serial.print(Quantity3);
  Serial.print("     ");
  

}
