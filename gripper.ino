/**
 * @file    gripper.ino
 * @author  Fabian Gand
 * @version V1.0.0
 * @date    2016/12/28
 * @brief   Description: this file is used to control(open/close) the mini gripper.
 * </pre>
 */

MePort port(PORT_7);
Servo gripperServo;  // create a servo object to control a servo 
int16_t servo2pin =  port.pin2(); //attaches the servo on PORT_3 SLOT2 to the servo object
const int changeDegrees = 20;


void setupGripper(){
gripperServo.write(150);
}

void openGripper() {
  // NOTE: To avoid interferences with other components the servo is attached and deatached each time it is being used
  gripperServo.attach(servo2pin);
  int newDeg = gripperServo.read() + changeDegrees;
  if(newDeg > 150) {
    newDeg = 150;
  }
  gripperServo.write(newDeg);
  delay(100);
  gripperServo.detach();
  
}

void closeGripper() {
  gripperServo.attach(servo2pin);
  int newDegClose = gripperServo.read() - changeDegrees;
  if(newDegClose < 10) {
    newDegClose = 10;
  }
  gripperServo.write(newDegClose);
  delay(100);
  gripperServo.detach();
}

  
