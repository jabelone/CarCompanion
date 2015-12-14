#include <SoftwareSerial.h> //Include our software serial library

//-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ START USER CONFIG /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/
//Pin Definitions//
SoftwareSerial BTserial(2, 3); // Define our software serial pins (RX, TX)
const int ledPin =  13; //Status LED
const int blinkerPin = 9; //Pin that controls transistor connected to blinkers.
const int lockPin = 7;  //The pin connected to the "locking" wire
const int unlockPin = 8;  //The pin connected to the "unlocking" wire

///Timing///
const int heartBeatTimeOut = 2000; //How long to wait after we don't get a heartbeat message before locking car. (in milliseconds)
const int blinkerFlashDelay = 500; //How long the lights stay on for when flashing blinkers. (in milliseconds)

///Other Options///
const String carUnlockType = "LOW"; //"LOW" car locks/unlocks when pins pulled low, "HIGH" when pins pulled high. (if none work open a feature request in github)
                                    //NOTE: HIGH only works at 5V logic!  If it needs 12v, hook up a transistor or relay.
const boolean blinkerFlashOnLock = true; //true - blinkers flash on lock/unlock, false - blinkers don't flash on lock/unlock.
//-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/ END USER CONFIG /-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/


///Declare our variables
String btVal; //Where we store what we got via Bluetooth.
unsigned long lastHeartBeat; //Where we store when our last heartbeat was.
boolean dontunLock = false; //A flag to check if we manually locked it, so we shouldn't auto unlock if we get a heartbeat.

void setup() {
  pinMode(ledPin, OUTPUT);  //Set our various GPIO pins to output/input
  pinMode(blinkerPin, OUTPUT);  //Set our various GPIO pins to output/input
  pinMode(A3, OUTPUT);  //Set our various GPIO pins to output/input
  pinMode(lockPin, OUTPUT);  //Set our various GPIO pins to output/input
  pinMode(unlockPin, OUTPUT);  //Set our various GPIO pins to output/input

  //Initial Outputs
  digitalWrite(A3, LOW); //To lazy to run separate wire to GND
  
  //Serial port settings
  BTserial.begin(9600); // HC-06 default serial speed is 38400
  Serial.begin(38400); //Enable our hardware serial ports (for debugging etc)
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
    lastHeartBeat = millis(); //If it's a heartbeat message, update the time we last received one.
    if (dontunLock == false) unlockCar();  //If we haven't manually locked it, unlock it.
  }
  else if (btVal == "Lockcar") {  //If we get a command to manually lock it.
    dontunLock = true;  //Set our flag so it won't auto unlock until we manually unlock it.
    lockCar(); //Lock car
  }
  else if (btVal == "Unlockcar") {  //If we get a command to manually unlock it.
    dontunLock = false; //Set our flag so it may auto unlock again.
    unlockCar(); //Unlock car
  }
  else Serial.println("Error: Unrecognised command received from phone!"); //If it's anything else we aren't expecting it!
  btVal = ""; //Reset the received commadn before the next loop.
  
  if (millis() - lastHeartBeat > heartBeatTimeOut) {
    lockCar();
  }

  /*  //Read from hardware serial and send to HC-06 for debugging purposes (disabled by default)
  if (Serial.available())
  {
    digitalWrite(ledPin, HIGH); //Set the received somethiing via Bluetooth LED to on.
    BTserial.write(Serial.read()); //Send to the bluetooth serial port whatever we got.
    digitalWrite(ledPin, LOW); //Set the received somethiing via Bluetooth LED back to off.
  }*/ 
}
