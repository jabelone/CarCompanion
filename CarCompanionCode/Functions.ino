/*This file is part of CarCompanion.

Copyright (C) 2015 Jaimyn Mayer (Known as "Jabelone" online)

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

void lockCar() {
  carLocked = true;
  if (carUnlockType == "LOW") {
    digitalWrite(lockPin, LOW); //"Connect" the lock wire by pulling it LOW
    digitalWrite(unlockPin, HIGH); //"Disconnect" the unlock wire by pulling it HIGH
  }
  if (carUnlockType == "HIGH") {
    digitalWrite(unlockPin, LOW); //"Disconnect" the unlock wire by pulling it LOW
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
    digitalWrite(lockPin, LOW); //"Connect" the lock wire by pulling it LOW
    digitalWrite(unlockPin, HIGH); //"Disconnect" the unlock wire by pulling it HIGH
  }
  flashIndicatorLightsSetter();
}

void flashIndicatorLightsSetter() { //When we want to flash lights, check if we should, then set the flag so it happens in Main
  if (indicatorFlashOnLock == true) indicatorLightsMillis = millis() + indicatorFlashDelay;
}

void flashIndicatorLights() {
  if ((indicatorLightsMillis - millis()) > 0){ //If the light is meant to be on still
    digitalWrite(indicatorPin, HIGH); //Set our indicator trigger pin to HIGH
    indicatorLightsState = true;
  }
  else {
    digitalWrite(indicatorPin, LOW); //Set our indicator trigger pin to LOW
    indicatorLightsState = false;
  }
}

void flashHeadLightsSetter() { //When we want to flash lights, check if we should, then set the flag so it happens in Main
  if (headLightsFlashOnLock == true) headLightsMillis = millis() + headLightsFlashDelay;
}

void flashHeadLights() {
  if ((headLightsMillis - millis()) > 0){ //If the light is meant to be on still
    digitalWrite(headLightsPin, HIGH); //Set our indicator trigger pin to HIGH
   headLightsState = true;
  }
  else {
    digitalWrite(headLightsPin, LOW); //Set our light trigger pin to LOW
    headLightsState = false;
  }
}

void flashbrakeLightsSetter() { //When we want to flash lights, check if we should, then set the flag so it happens in Main
  if (headLightsFlashOnLock == true) headLightsMillis = millis() + headLightsFlashDelay;
}

void flashbrakeLights() {
  if ((brakeLightsMillis - millis()) > 0){ //If the light is meant to be on still
    digitalWrite(brakeLightsPin, HIGH); //Set our light trigger pin to HIGH
   brakeLightsState = true;
  }
  else {
    digitalWrite(brakeLightsPin, LOW); //Set our light trigger pin to LOW
    brakeLightsState = false;
  }
}
