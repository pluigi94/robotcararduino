#include <IRremote.h>

// Pin del ricevitore IR. 
#define PIN_RICEVITORE 12
IRrecv irrecv(PIN_RICEVITORE);

// Codice input per ogni tastierino del telecomando
#define FRECCIA_SU 16736925
#define FRECCIA_GIU 16754775
#define FRECCIA_DESTRA 16761405
#define FRECCIA_SINISTRA 16720605
#define NUMERO_0 16730805
#define NUMERO_1 16738455
#define NUMERO_2 16750695
#define NUMERO_3 16756815
#define NUMERO_4 16724175
#define NUMERO_5 16718055
#define NUMERO_6 16743045
#define NUMERO_7 16716015
#define NUMERO_8 16726215
#define NUMERO_9 16734885
#define SIMBOLO_STAR 16728765
#define SIMBOLO_HASH 16732845
#define OK 16712445

// Motori ruote
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

// Velocità della car
int velocita = 150;

decode_results results;
unsigned long valore;
unsigned long preMillis;

void avanti(){ 
  analogWrite(ENA,velocita);
  analogWrite(ENB,velocita);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  Serial.println("Avanti!");
}
void indietro(){
  analogWrite(ENA,velocita);
  analogWrite(ENB,velocita);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.println("Indietro!");
}
void sinistra(){
  analogWrite(ENA,velocita);
  analogWrite(ENB,velocita);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
  Serial.println("Sinistra!");
}
void destra(){
  analogWrite(ENA,velocita);
  analogWrite(ENB,velocita);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.println("Destra!");
}
void fermo(){
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Fermo!");  
}

void aumenta_velocita(){
  if(velocita + 30 > 250){
    velocita = 250;
  }else{
    velocita = velocita + 30;
  }
  delay(1000);
}

void diminuisci_velocita(){
  if(velocita - 30 < 130){
    velocita = 130;
  }else{
    velocita = velocita - 30;
  }
  delay(1000);
}

void imposta_velocita_buona(){
  velocita = 150;
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  fermo();
  irrecv.enableIRIn();
}

void loop() {
  if(irrecv.decode(&results)){
    preMillis = millis();
    valore = results.value;
    Serial.println(valore);
    irrecv.resume();
    switch(valore){
      case NUMERO_0: imposta_velocita_buona(); break;
      case NUMERO_1: sinistra(); delay(300); fermo(); break;
      case FRECCIA_SU: avanti(); break;
      case NUMERO_2: avanti(); break;
      case FRECCIA_GIU: indietro(); break;
      case NUMERO_3: destra(); delay(350); fermo(); break;
      case NUMERO_8: indietro(); break;
      case NUMERO_9: destra(); delay(700); fermo(); break;
      case FRECCIA_DESTRA: destra(); break;
      case NUMERO_5: fermo();break;
      case NUMERO_6: destra(); break;
      case NUMERO_7: sinistra(); delay(700); fermo(); break;
      case FRECCIA_SINISTRA: sinistra(); break;
      case NUMERO_4: sinistra(); break;
      case SIMBOLO_HASH: aumenta_velocita(); break;
      case SIMBOLO_STAR: diminuisci_velocita(); break;
      case OK: fermo(); break;
      default: break;
    }
  }else{
    if(millis() - preMillis > 500){
      fermo();
      preMillis = millis();
    }
  }

}
