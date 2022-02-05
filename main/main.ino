// Capteurs de position de l'ascenceur
#define CAPTEUR_ETAGE_RDC_HAUT 7
#define CAPTEUR_ETAGE_RDC_BAS 8
#define CAPTEUR_ETAGE_1_HAUT 9
#define CAPTEUR_ETAGE_1_BAS 10
#define CAPTEUR_ETAGE_2_HAUT 11
#define CAPTEUR_ETAGE_2_BAS 12

// Boutons d'appel
#define BTN_APPEL_RDC 4
#define BTN_APPEL_1 5
#define BTN_APPEL_2 6
 
// Sorties pour commander le moteur 
#define COMMANDE_UP 2
#define COMMANDE_DOWN 3

// Pins pour le bluetooth
#define PIN_BLU_TX 11
#define PIN_BLU_RX 12

#define NULPART 999

#include <SoftwareSerial.h> 
SoftwareSerial RecepteurBlue(PIN_BLU_TX,PIN_BLU_RX); // RX | TX 

// Varible pour savoir vers où se dirige l'ascenceur
int etageCible;

bool monte;
bool descend;
 
void setup() {
  Serial.begin(9600);

  pinMode(CAPTEUR_ETAGE_RDC_HAUT, INPUT);
  pinMode(CAPTEUR_ETAGE_RDC_BAS, INPUT);
  pinMode(CAPTEUR_ETAGE_1_HAUT, INPUT);
  pinMode(CAPTEUR_ETAGE_1_BAS, INPUT);
  /*pinMode(CAPTEUR_ETAGE_2_BAS, INPUT);
  pinMode(CAPTEUR_ETAGE_2_HAUT, INPUT);*/
  pinMode(BTN_APPEL_RDC, INPUT);
  pinMode(BTN_APPEL_1, INPUT);
  pinMode(BTN_APPEL_2, INPUT);

  pinMode(COMMANDE_UP, OUTPUT);
  pinMode(COMMANDE_DOWN, OUTPUT);

  etageCible = NULPART;

  
  digitalWrite(COMMANDE_UP, LOW);
  digitalWrite(COMMANDE_DOWN, LOW);

  monte = false;
  descend = false;
 
  RecepteurBlue.begin(9600);
  Serial.println("Ready to connect\nDefault password is 1234 or 0000"); 
}

void loop() {  
  if(etageCible == NULPART) {
    // Si on attend une commande
    if(digitalRead(BTN_APPEL_RDC) == HIGH) {
      etageCible = 0;
    } else if (digitalRead(BTN_APPEL_1) == HIGH) {
      etageCible = -1;
    /*} else if (digitalRead(BTN_APPEL_2) == HIGH) {
      etageCible = -2;*/
    } else if (RecepteurBlue.available()) {
      etageCible = RecepteurBlue.readString().toInt();
      Serial.println(etageCible);
      if(etageCible < -2 || etageCible > 0) etageCible = NULPART;
    }
    if(etageCible != NULPART) {
      Serial.println("On va au ");
      Serial.println(etageCible);
    }
  } 

  if(etageCible != NULPART) {
    bool doitMonter = false;
    bool doitDescendre = false;
    if(etageCible == 0 && !digitalRead(CAPTEUR_ETAGE_RDC_HAUT) == LOW) 
      doitMonter = true;
    else if(etageCible == -1 && (
                            digitalRead(CAPTEUR_ETAGE_1_HAUT) == LOW 
                            && !digitalRead(CAPTEUR_ETAGE_1_BAS) == LOW 
                            || digitalRead(CAPTEUR_ETAGE_RDC_HAUT) == LOW
                            || digitalRead(CAPTEUR_ETAGE_RDC_BAS) == LOW))
      doitDescendre = true;
    else if(etageCible == -1 && (digitalRead(CAPTEUR_ETAGE_1_BAS) == LOW 
                            && !digitalRead(CAPTEUR_ETAGE_1_HAUT) == LOW 
                            /*|| digitalRead(CAPTEUR_ETAGE_2_BAS) == LOW
                            || digitalRead(CAPTEUR_ETAGE_2_HAUT) == LOW)*/))
      doitMonter = true;
    /*else if(etageCible == -2 && digitalRead(CAPTEUR_ETAGE_2_BAS) == LOW)
      doitDescendre = true;*/
      
    if(doitMonter) {
      monte = true;
      digitalWrite(COMMANDE_UP, HIGH);
    } else if(doitDescendre) {
      descend = true;
      digitalWrite(COMMANDE_DOWN, HIGH);
    } 
  if(!doitDescendre && !doitMonter && !monte && !descend && etageCible != NULPART) {
      Serial.println("Arrivé au " + String(etageCible));
      etageCible = NULPART;  
    }
  }
  
  if (
      etageCible == -1 
      && digitalRead(CAPTEUR_ETAGE_1_BAS) == LOW 
      && digitalRead(CAPTEUR_ETAGE_1_HAUT) == LOW
    ) {
    // Si on se dirige vers le -1 et qu'on est arrivé
    digitalWrite(COMMANDE_UP, LOW);
    digitalWrite(COMMANDE_DOWN, LOW);
    monte = false;
    descend = false;
    etageCible = NULPART;
    Serial.println("Arrivé au -1");
  } else if (monte && digitalRead(CAPTEUR_ETAGE_RDC_HAUT) == LOW) {
    // Si on se dirige vers le RDC et qu'on est arrivé
    digitalWrite(COMMANDE_UP, LOW);
    monte = false;
    if(etageCible != NULPART) {
    Serial.println("Arrivé au 0");
    }
    etageCible = NULPART;
  }  /* else  if (descend && digitalRead(CAPTEUR_ETAGE_2_BAS) == LOW) {
    Serial.println(descend);
    // Si on se dirige vers le -2 et qu'on est arrivé
    digitalWrite(COMMANDE_DOWN, HIGH);
    descend = false;
    if(etageCible != NULPART) {
      Serial.println("Arrivé au -2");
    }
    etageCible = NULPART;
  }  */
  
}
                                       
