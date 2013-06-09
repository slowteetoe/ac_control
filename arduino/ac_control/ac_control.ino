#include <Servo.h>

Servo myservo;  // create servo object to control the servo
int servoPos = 0;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  Serial.begin(9600);  // communicate via serial port
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
}

void loop(){
   if (Serial.available()) {
        while (Serial.available()) {
            char inChar = (char)Serial.read(); 
            inputString += inChar;
            if (inChar == '\n') {
                stringComplete = true;
                handleCommand(inputString);
                inputString = "";
                stringComplete = false;
                break;
            }
        }
    }
}

void handleCommand(String cmd){
  if(inputString.startsWith("LEDON")){
    rotateForward(180);
  } else if(inputString.startsWith("LEDOFF")){
    rotateBack(180);
  }
}

void rotateForward(int degs){
  for(int pos = 0; pos < degs; pos +=1){
    myservo.write(pos);
    delay(5);
  }
  servoPos += degs;
}

void rotateBack(int degs){
  if( servoPos <= 0){
    return;
  }
  for(int pos = degs; pos>=1; pos-=1){
    myservo.write(pos);
    delay(5);
  }
  servoPos -= degs;
}
