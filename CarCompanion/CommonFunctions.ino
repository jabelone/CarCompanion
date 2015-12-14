void lockCar() {
  if (carUnlockType == "LOW") {
    digitalWrite(lockPin, LOW); //"Connect" the lock wire by pulling it LOW
    digitalWrite(unlockPin, HIGH); //"Disconnect" the unlock wire by pulling it HIGH
  }
  if (carUnlockType == "HIGH") {
    digitalWrite(lockPin, HIGH); //"Connect" the lock wire by pulling it HIGH
    digitalWrite(unlockPin, LOW); //"Disconnect" the unlock wire by pulling it LOW
  }
  if (blinkerFlashOnLock == true) flashBlinkers();  //If we should, then flash blinkers.
}

void unlockCar() {  
  if (carUnlockType == "LOW") {
    digitalWrite(lockPin, HIGH); //"Disconnect" the lock wire by pulling it HIGH
    digitalWrite(unlockPin, LOW); //"Connect" the unlock wire by pulling it LOW
  }
  else if (carUnlockType == "HIGH") {
    digitalWrite(lockPin, LOW); //"Connect" the lock wire by pulling it LOW
    digitalWrite(unlockPin, HIGH); //"Disconnect" the unlock wire by pulling it HIGH
  }
  if (blinkerFlashOnLock == true){ //Double flash signifies lock
    flashBlinkers(); //flash blinkers.
    delay(blinkerFlashDelay); //OK to use delay() here for now.
    flashBlinkers(); //flash blinkers.
  }
}

void flashBlinkers() {
  digitalWrite(blinkerPin, HIGH); //Set our blinker trigger pin to HIGH
  digitalWrite(ledPin, HIGH); //Set our LED status pin to HIGH
  delay(blinkerFlashDelay); //OK to use delay() here for now.
  digitalWrite(blinkerPin, LOW); //Set our blinker trigger pin to LOW
  digitalWrite(ledPin, LOW); //Set our LED status pin to HIGH
}
