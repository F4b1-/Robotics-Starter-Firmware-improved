/**
 * @file    autonomous.ino
 * @author  Fabian Gand
 * @version V1.0.0
 * @date    2016/12/28
 * @brief   Description: this file is an extension for the starter_factory_firmware aimed at improving the standard wall-avoidance/ultrasound mode.
 * </pre>
 */
/* *** Will be added later ***
class MovementVector {
   public:
      double gyroX;  
      double gyroY;  
      int ticks;   
};
*/

MeGyro gyro(PORT_8);

int gyroCounter = 0;
// Boolean flags
boolean rightTurn = false;
boolean turning = false;
boolean getStarted = true;
int tickCounter = 0;
//MovementVector vectorArr[10];   

// Consts may be adjusted
const int minDistance = 25;
const int minDistanceWhenTurning = 250;
const double movementThreshold = 2.4;
const int stuckThreshold = 10;

void setupAuto() {
  gyro.begin();
  randomSeed(analogRead(0));
}

void loopAuto() {

  int distance = us.distanceCm();
  // When turning, check if path is clear
  if (turning) {
    if (distance <= minDistanceWhenTurning) {
      if (rightTurn) {
        TurnRight();
      } else {
        TurnLeft();
      }
      delay(300);
    } else {
      turning = false;
      int randomNr = random(0, 2);
      if (randomNr == 0) {
        rightTurn = false;
      } else {
        rightTurn = true;
      }

    }

  } else if ((distance <= minDistance) || (carIsStuck() && !getStarted)) {
    Stop();

/*
    double gyroX = gyro.getGyroX();
    double gyroY = gyro.getGyroY();
    MovementVector v;
    v.gyroX = gyroX;
    v.gyroY = gyroY;
    v.ticks = tickCounter;
    tickCounter = 0;
    vectorArr[sizeof(vectorArr)%5] = v;
    */
    
    buzzerOn();
    delay(1);
    buzzerOff();
    delay(1);
    Backward();
    delay(1200);
    if (rightTurn) {
      TurnRight();
    } else {
      TurnLeft();
    }

    turning = true;
    int randomDelay = random(500, 1000);
    delay(randomDelay);
  } else {
    Forward();
    tickCounter = tickCounter + 1;
    if(getStarted) {
      getStarted = false;
    }
    
  }
}

boolean movementIsDetected() {
  gyro.update();
  double gyroX = gyro.getGyroX();
  double gyroY = gyro.getGyroY();
  if(gyroX > -movementThreshold && gyroX <= movementThreshold && gyroY > -movementThreshold && gyroY <= movementThreshold) {
      return false;
  }
  return true;
}

boolean carIsStuck() {
  if(!movementIsDetected()) {
    if (gyroCounter > stuckThreshold) {
        gyroCounter = 0;
         return true;
    } else {
      gyroCounter++;
    }
  } 
  return false;
}

