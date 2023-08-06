#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);  // RX, TX
const int motorSpeedPinA = 12;
const int motorSpeedPinB = 13;
const int switchPin = 22;
const int buzzer = 20;
int pos = 0;
boolean fire = false;

#define Left 7     // left sensor
#define Right 8    // right sensor
#define Forward 9  //front sensor

#define LM1 2  // left motor
#define LM2 3  // left motor
#define RM1 4  // right motor
#define RM2 5  // right motor
#define pump 17

void Move_Forward() {
  Serial.println("Move_Forward");
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  analogWrite(motorSpeedPinA, 170);
  analogWrite(motorSpeedPinB, 170);
}
void Move_Backward() {
  Serial.println("Move_Backward");
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  analogWrite(motorSpeedPinA, 170);
  analogWrite(motorSpeedPinB, 170);
}
void Move_Right() {
  Serial.println("Move_Right");
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  analogWrite(motorSpeedPinA, 255);
  analogWrite(motorSpeedPinB,255);
}
void Move_Left() {
  Serial.println("Move_Left");
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  analogWrite(motorSpeedPinA, 255);
  analogWrite(motorSpeedPinB, 255);
}
void Move_Stop() {
  Serial.println("Move_Stop");

  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);
  analogWrite(motorSpeedPinA, 0);
  analogWrite(motorSpeedPinB, 0);
}

void TURN_ON() {
  Serial.println("turn on:");
  digitalWrite(pump, HIGH);
}
void TURN_OFF() {
  Serial.println("turn OFF:");
  digitalWrite(pump, LOW);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;  // wait for serial port to connect (needed for native USB port only)
  }

  Serial.println("Goodnight moon!");

  mySerial.begin(115200);
  mySerial.println("Hello, world?");
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(motorSpeedPinA, OUTPUT);
  pinMode(motorSpeedPinB, OUTPUT);
  digitalWrite(switchPin, HIGH);  // turn on pullup resistor
  pinMode(buzzer, OUTPUT);
  delay(30);

}
void put_off_fire() {
  delay(500);

  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(LM1,  LOW);
  digitalWrite(LM2,  LOW);
  digitalWrite(RM1,  LOW);
  digitalWrite(RM2,  LOW);
  analogWrite(motorSpeedPinA, 0);
  analogWrite(motorSpeedPinB, 0);
  digitalWrite(pump, HIGH);
  delay(5000);



  digitalWrite(pump,LOW);




  fire = false;
}

void loop() {

  if (digitalRead(switchPin) == HIGH) {
    // switch is pressed - pullup keeps pin high normally
    delay(30);
    Serial.println("key is on ");

    if (digitalRead(Left) == 1 && digitalRead(Right) == 1 && digitalRead(Forward) == 1) {

      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, HIGH);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, HIGH);
      analogWrite(motorSpeedPinA, 0);
      analogWrite(motorSpeedPinB, 0);
        fire = true;
   
    }

    else if (digitalRead(Forward) == 0 ) {
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(motorSpeedPinA, 150);
      analogWrite(motorSpeedPinB, 150);
       delay(750);
       digitalWrite(LM1, HIGH);
      digitalWrite(LM2, HIGH);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, HIGH);
      analogWrite(motorSpeedPinA, 0);
      analogWrite(motorSpeedPinB, 0);
       delay(2000);

      
    }

    else if (digitalRead(Left) == 0 ) {
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      analogWrite(motorSpeedPinA,255);
      analogWrite(motorSpeedPinB, 255);
       delay(750);
       digitalWrite(LM1, HIGH);
      digitalWrite(LM2, HIGH);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, HIGH);
      analogWrite(motorSpeedPinA, 0);
      analogWrite(motorSpeedPinB, 0);
       delay(2000);
    }

    else if (digitalRead(Right) == 0 ) {
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      analogWrite(motorSpeedPinA, 255);
      analogWrite(motorSpeedPinB, 255);
       delay(750);
       digitalWrite(LM1, HIGH);
      digitalWrite(LM2, HIGH);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, HIGH);
      analogWrite(motorSpeedPinA, 0);
      analogWrite(motorSpeedPinB, 0);
       delay(2000);
    }

    delay(200);  //change this value to increase the distance
    while (fire == true ) {
      put_off_fire();

    }
 


  }
  if (mySerial.available()) {
    String receivedData = mySerial.readStringUntil('\n');
    receivedData.trim();  // Remove leading/trailing whitespaces
    Serial.println(receivedData);

    if (receivedData.indexOf("MF") != -1) {
      Serial.println("MOVE forward");
      Move_Forward();

    } else {
      Serial.print("Received: ");
      Serial.println(receivedData);
    }
    if (receivedData.indexOf("MB") != -1) {
      Serial.println("MOVE BACKWARD");
      Move_Backward();

    } else {
      Serial.print("Received: ");
      Serial.println(receivedData);
    }

    if (receivedData.indexOf("MR") != -1) {
      Serial.println("MOVE RIGHT");
      Move_Right();

    } else {
      Serial.print("Received: ");
      Serial.println(receivedData);
    }

    if (receivedData.indexOf("ML") != -1) {
      Serial.println("MOVE LEFT");
      Move_Left();

    } else {
      Serial.print("Received: ");
      Serial.println(receivedData);
    }

    if (receivedData.indexOf("MS") != -1) {
      Serial.println("MOVE STOP");
      Move_Stop();

    } else {
      Serial.print("Received: ");
      Serial.println(receivedData);
    }


    if (receivedData.indexOf("TN") != -1) {
      Serial.println("TURN ON");
      TURN_ON();

    } else {
      Serial.print("Received: ");
      Serial.println(receivedData);
    }

    if (receivedData.indexOf("TF") != -1) {
      Serial.println("TURN OFF");
      TURN_OFF();

    } else {
      Serial.print("Received: ");
      Serial.println(receivedData);
    }
    if (receivedData.indexOf("Alarm") != -1) {
      Serial.println("Alarm");
      TURN_ON();


    } else {
      Serial.print("Received: ");
      Serial.println(receivedData);
    }

    if (Serial.available()) {
      String sendData = Serial.readStringUntil('\n');
      mySerial.println(sendData);
    }
  }
}
