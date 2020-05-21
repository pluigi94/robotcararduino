#define SENSORE_DX !digitalRead(10)
#define SENSORE_C !digitalRead(4)
#define SENSORE_SX !digitalRead(2)

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

#define velocita 250

void avanti(){
  analogWrite(ENA, velocita);
  analogWrite(ENB, velocita);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Vado avanti!");
}

void indietro(){
  analogWrite(ENA, velocita);
  analogWrite(ENB, velocita);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Vado indietro!");
}

void sinistra(){
  analogWrite(ENA, velocita);
  analogWrite(ENB, velocita);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Vado a sinistra!");
}

void destra(){
  analogWrite(ENA, velocita);
  analogWrite(ENB, velocita);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  Serial.println("Vado a destra!");
} 

void stop(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   Serial.println("Mi fermo!");
} 

void setup(){
  Serial.begin(9600);
  pinMode(10,INPUT);
  pinMode(4,INPUT);
  pinMode(2,INPUT);
}

void loop() {
  if(SENSORE_C){
    avanti();
  }
  else if(SENSORE_DX) { 
    destra();
    while(SENSORE_DX);                             
  }   
  else if(SENSORE_SX) {
    sinistra();
    while(SENSORE_SX);  
  }
}
