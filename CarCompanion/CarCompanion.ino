#include <SoftwareSerial.h> //Include our software serial library

///////////////// START USER CONFIG /////////////////
SoftwareSerial BTserial(2, 3); // Define our software serial pins (RX | TX)
const int ledPin =  13; //Status LED
const int blinkerPin = 9; //Pin that controls transistor connected to blinkers.
const int lockPin = 7;  //The pin connected to the "locking" wire
const int unlockPin = 8;  //The pin connected to the "unlocking" wire
const int heartBeatTimeOut = 1500; //How long to wait after we don't get a heartbeat message before locking car. (in milliseconds)
////////////////// END USER CONFIG //////////////////

String btVal; //Where we store what we got via Bluetooth.
unsigned long lastHeartBeat; //Where we store when our last heartbeat was.
boolean dontunLock = false; //A flag to check if we manually locked it, so we shouldn't auto unlock if we get a heartbeat.

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(blinkerPin, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(lockPin, OUTPUT);
  pinMode(unlockPin, OUTPUT);
  digitalWrite(unlockPin, HIGH); //"Disconnect" the unlock wire by pulling it high  
  digitalWrite(lockPin, HIGH); //"Disconnect" the lock wire by pulling it high
  digitalWrite(A3, LOW); //To lazy to wire BT module to GND

  BTserial.begin(9600); // HC-06 default serial speed is 38400
  Serial.begin(38400);
}

void loop() {
  // Keep reading from HC-06 and send to Arduino Serial Monitor for debugging purposes

  while (BTserial.available() > 0)
  {
    digitalWrite(ledPin, HIGH);
    btVal = BTserial.readStringUntil('\n');
    Serial.println(btVal);
    digitalWrite(ledPin, LOW);
  }
  
  
  if (btVal == "Heartbeat") {
    lastHeartBeat = millis(); //If it's a heartbeat message, update the time we last received it.
    if (dontunLock == false) unlockCar();
  }
  else if (btVal == "Lockcar") {
    dontunLock = true;
    lockCar(); //Lock car
  }
  else if (btVal == "Unlockcar") {
    dontunLock = false;
    unlockCar(); //Unlock car
  }
  //else Serial.println("Error: Unrecognised command received from phone!"); //If it's anything else we aren't expecting it!
  btVal = "";
  
  if (millis() - lastHeartBeat > heartBeatTimeOut) {
    lockCar();
  }

  // Keep reading from Arduino Serial Monitor and send to HC-06 for debugging purposes
  if (Serial.available())
  {
    digitalWrite(ledPin, HIGH);
    BTserial.write(Serial.read());
    digitalWrite(ledPin, LOW); //Set the received somethiing via Bluetooth LED back to off.
  }
}

void lockCar() {
  digitalWrite(lockPin, LOW); //"Connect" the lock wire by pulling it low
  digitalWrite(unlockPin, HIGH); //"Disconnect" the unlock wire by pulling it high
  flashBlinkers();
}

void unlockCar() {  
  digitalWrite(lockPin, HIGH); //"Disconnect" the lock wire by pulling it high
  digitalWrite(unlockPin, LOW); //"Connect" the unlock wire by pulling it low
  flashBlinkers();
  delay(250);
  flashBlinkers();
}

void flashBlinkers() {
  digitalWrite(blinkerPin, HIGH);
  digitalWrite(ledPin, HIGH);
  delay(250);
  digitalWrite(blinkerPin, LOW);
  digitalWrite(ledPin, LOW);
}

