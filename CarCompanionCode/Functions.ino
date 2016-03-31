/*This file is part of CarCompanion.

Copyright (C) 2016 Jaimyn Mayer (Known as "Jabelone" online)

CarCompanion is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

CarCompanion is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with CarCompanion.  If not, see <http://www.gnu.org/licenses/>. */


// Declare our variables - do not modify unless you know what you're doing!
String btVal; //Where we store what we got via Bluetooth
unsigned long lastHeartBeat; //For timing of heartbeat message
unsigned long headLightsMillis; //For timing of headlights
boolean headLightsState = false; //For keeping track of headlights state
unsigned long indicatorLightsMillis; //For timing of indicators
boolean indicatorLightsState = false; //For keeping track of indicators state
unsigned long interiorLightsMillis;  //For timing of the interior light(s) (currently not used)
boolean interiorLightsState = false; //For keeping track of interior light(s) state (currently not used)
boolean dontunLock = false; //A flag to check if we manually locked it
boolean carLocked; //A flag to keep track of the lock status

boolean buttonState = true; //For storing the last state of the button, true = pressed, false = not
long buttonLastTime = 0;  //Keep track of the time so we can debounce the button
long debounceBrakeDelay = 30;    // the debounce time; increase if the output flickers

SoftwareSerial BTserial(btRX, btTX); //Not a variable but still needs to be "declared"

void lockCar() {
  carLocked = true;
  if (carUnlockType == "LOW") {
    digitalWrite(unlockPin, HIGH); //"Disconnect" the unlock wire by pulling it HIGH
    digitalWrite(lockPin, LOW); //"Connect" the lock wire by pulling it LOW
  }
  if (carUnlockType == "HIGH") {
    digitalWrite(unlockPin, LOW); //"Disconnect" the unlock wire by pulling it LOW
    digitalWrite(lockPin, HIGH); //"Connect" the lock wire by pulling it LOW
  }
  flashIndicatorLightsSetter();
}

void unlockCar() {
  carLocked = false;
  if (carUnlockType == "LOW") {
    digitalWrite(lockPin, HIGH); //"Disconnect" the lock wire by pulling it HIGH
    digitalWrite(unlockPin, LOW); //"Connect" the unlock wire by pulling it LOW
  }
  else if (carUnlockType == "HIGH") {
    digitalWrite(unlockPin, HIGH); //"Disconnect" the unlock wire by pulling it HIGH
    digitalWrite(lockPin, LOW); //"Connect" the lock wire by pulling it LOW
  }
  flashIndicatorLightsSetter();
}

void flashIndicatorLightsSetter() { //When we want to flash lights, check if we should, then set the flag so it happens in Main
  if (indicatorFlashOnLock == true) indicatorLightsMillis = millis() + indicatorLightsFlashDelay;
}

void flashHeadLightsSetter() { //When we want to flash lights, check if we should, then set the flag so it happens in Main
  if (headLightsFlashOnLock == true) headLightsMillis = millis() + headLightsFlashDelay;
}

void triggerBrakeLights(boolean lightStatus) {
  if (lightStatus) { //If we want the light on
    digitalWrite(brakeLightsPin, HIGH); //Set our light trigger pin to HIGH
  }
  else {
    digitalWrite(brakeLightsPin, LOW); //Set our light trigger pin to LOW
  }
}
