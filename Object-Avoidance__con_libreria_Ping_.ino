#include <Servo.h>
#include <ControlledServo.h>
#include <NewPing.h>

Servo ultrasonic_sensor;
ControlledServo cservo_motor;

int Echo = A4;
int Trig = A5;

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
const int angleRate = 2;
#define max_distance 200
#define velocita 120
int distanzaDestra = 0, distanzaSinistra = 0;

NewPing sonar(Trig, Echo, max_distance);

void avanti(){ 
  analogWrite(ENA, velocita);
  analogWrite(ENB, velocita);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Vado in avanti");
}

void indietro() {
  analogWrite(ENA, velocita);
  analogWrite(ENB, velocita);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Vado indietro");
}

void sinistra() {
  analogWrite(ENA, velocita);
  analogWrite(ENB, velocita);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  Serial.println("Vado a sinistra");
}

void destra() {
  analogWrite(ENA, velocita);
  analogWrite(ENB, velocita);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Vado a destra");
}

void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Fermo!");
} 


int readPing(){
  int cm = sonar.ping_cm();
  if(cm >= max_distance || cm <= 2){
    cm = max_distance;
  }
  return cm;
}


void setup() {
  ultrasonic_sensor.attach(3,700,2400);
  Serial.begin(9600); 
  ultrasonic_sensor.write(90);
  cservo_motor.setServo(ultrasonic_sensor);
}

void controlla_bene(){
  stop();
  delay(300);
  ultrasonic_sensor.write(10);
  delay(1000);
  distanzaDestra = readPing();
  delay(300);
  ultrasonic_sensor.write(180);
  delay(1500);
  distanzaSinistra = readPing();
  delay(300);
  ultrasonic_sensor.write(90);
  delay(500);
  
  if(distanzaDestra >= distanzaSinistra){
    destra();
    delay(750);
    stop();
  } else if(distanzaDestra < distanzaSinistra){
    sinistra();
    delay(750);
    stop();
  } else {
    avanti();
  }
 }


void loop() {
  
  cservo_motor.moveToNow(90);
  cservo_motor.setRate(angleRate);
  cservo_motor.moveTo(130);
  
  while(cservo_motor.moving()){
    cservo_motor.update();
    int distanza = readPing();
    if(distanza <= 30){
      stop();
      delay(300);
      indietro();
      delay(600);
      stop();
      controlla_bene();
    }else{
      avanti();
    }
 }
   
  cservo_motor.moveToNow(130);
  cservo_motor.setRate(angleRate);
  cservo_motor.moveTo(50);

  while(cservo_motor.moving()){
    cservo_motor.update();
    int distanza = readPing();
    if(distanza <= 30){
      stop();
      delay(300);
      indietro();
      delay(600);
      stop();
      controlla_bene();
    }else{
      avanti();
    }
 }
 
  cservo_motor.moveToNow(50);
  cservo_motor.setRate(angleRate);
  cservo_motor.moveTo(90);

  while(cservo_motor.moving()){
    cservo_motor.update();
    int distanza = readPing();
    if(distanza <= 30){
      stop();
      delay(300);
      indietro();
      delay(600);
      stop();
      controlla_bene();
    }else{
      avanti();
    }
 }
}
