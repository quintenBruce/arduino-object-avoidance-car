#include <AFMotor.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

AF_DCMotor motor(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

const int MAX_SPEED = 255;
const int MAX_TURN_SPEED = 255;

const int pingPin = 2; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 13; // Echo Pin of Ultrasonic Sensor

const int MAX_DISTANCE = 13;
const int NUM_DURATION_READINGS = 3;
const int SERVO_SPEED = 0;  //lower = faster



void setup() 
{


  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  myservo.write(90);  
	//Set initial speed of the motor & stop
	motor.setSpeed(MAX_SPEED);
	motor.run(RELEASE);
  motor2.setSpeed(MAX_SPEED);
	motor2.run(RELEASE);
  motor3.setSpeed(MAX_SPEED);
	motor3.run(RELEASE);
  motor4.setSpeed(MAX_SPEED);
	motor4.run(RELEASE);

  delay(1000);
}

void loop() 
{
  int servoPositions[] = {90, 40, 90, 140};
  int j = 0;
  while (microsecondsToInches(captureDuration()) > MAX_DISTANCE) {
    myservo.write(servoPositions[j]); 
    if (j != 3)
      j++;
    else 
      j = 0;
    moveBackward();
    delay(80);
  }
  
  brake();
  determineDirection();
}


void collectDurations(long *left, long *right); //function declaration






void determineDirection() {
  long left, right;

  collectDurations(&left, &right);

  if (left < right) {
    turnLeft();
    return;
  }

  turnRight();
}



long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}





/*Ultrasonic Sensor Functions*/

long captureDuration() {
  long duration;

   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);

  return duration;
   
}



/*Servo Functions*/

void collectDurations(long *left, long *right) {
  int pos;

  long sum;

  for (pos = 90; pos >= 4; pos -= 1) {
    myservo.write(pos);         
    delay(SERVO_SPEED);                         
  }

  for (int i = 0; i < NUM_DURATION_READINGS; i++) 
    sum += microsecondsToInches(captureDuration());
  
  *right = sum / NUM_DURATION_READINGS;
  
  for (pos = 10; pos <= 170; pos += 1) { 
    myservo.write(pos);              
    delay(SERVO_SPEED);                       
  }

  for (int i = 0; i < NUM_DURATION_READINGS; i++) 
    sum = microsecondsToInches(captureDuration());

  *left = sum / NUM_DURATION_READINGS;
  for (pos = 180; pos >= 90; pos -= 1) { 
    myservo.write(pos);              
    delay(SERVO_SPEED);                       
  }
}





/*Motor Driver Shield Functions*/


void accelerate() {
  for (int i=80; i<MAX_SPEED; i++) {
		motor.setSpeed(i);  
    motor2.setSpeed(i);  
    motor3.setSpeed(i);  
    motor4.setSpeed(i);   
		delay(2);
	}
}

void accelerateForward() {
  motor.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  accelerate();
}

void moveForward() {
  motor.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

	motor.setSpeed(MAX_SPEED);  
  motor2.setSpeed(MAX_SPEED);  
  motor3.setSpeed(MAX_SPEED);  
  motor4.setSpeed(MAX_SPEED);   
	delay(10);
}

void accelerateBackward() {
  motor.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  accelerate();
}

void moveBackward() {
  motor.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);

	motor.setSpeed(MAX_SPEED);  
  motor2.setSpeed(MAX_SPEED);  
  motor3.setSpeed(MAX_SPEED);  
  motor4.setSpeed(MAX_SPEED);   
	delay(10);
}

void brake() {
  motor.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void turnRight() {
  motor.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);

  motor.setSpeed(MAX_TURN_SPEED);  
  motor2.setSpeed(MAX_TURN_SPEED);  
  motor3.setSpeed(MAX_TURN_SPEED);  
  motor4.setSpeed(MAX_TURN_SPEED);   
  delay(500);


}

void turnLeft() {
  motor.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  motor.setSpeed(MAX_TURN_SPEED);  
  motor2.setSpeed(MAX_TURN_SPEED);  
  motor3.setSpeed(MAX_TURN_SPEED);  
  motor4.setSpeed(MAX_TURN_SPEED);   

  delay(500);

}



