#define BTN_ETAGE_RDC 2
#define BTN_ETAGE_1 3
#define BTN_ETAGE_2 4
#define BTN_ETAGE_3 5
#define BTN_FERMETURE 6
#define BTN_OUVERTURE 7
#define BTN_STOP 10
#define PIN_BLU_TX 8
#define PIN_BLU_RX 9

#include <SoftwareSerial.h> 
SoftwareSerial RecepteurBlue(PIN_BLU_TX,PIN_BLU_RX); // RX | TX 

void setup() {
  pinMode(BTN_ETAGE_RDC, INPUT);
  pinMode(BTN_ETAGE_1, INPUT);
  pinMode(BTN_ETAGE_2, INPUT);
  pinMode(BTN_ETAGE_3, INPUT);
  pinMode(BTN_FERMETURE, INPUT);
  pinMode(BTN_OUVERTURE, INPUT);
  pinMode(BTN_STOP, INPUT);

  RecepteurBlue.begin(9600);
  Serial.begin(9600);
  Serial.write("Ready");
}

void loop() {
    if(digitalRead(BTN_ETAGE_RDC)) {
      RecepteurBlue.write("0");
      Serial.println("0");
    } else if(digitalRead(BTN_ETAGE_1)) {
      RecepteurBlue.write("-1");
      Serial.println("1");
    }
    else if(digitalRead(BTN_ETAGE_2)) {
      RecepteurBlue.write("-2");
      Serial.println("2");
    }
    else if(digitalRead(BTN_ETAGE_3)) {
      RecepteurBlue.write("-3");
      Serial.println("3");
    }
}
