/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->  http://www.adafruit.com/products/1438
*/
#include <MyoController.h>
#include <Servo.h>
#define trigPin 3 // green
#define echoPin 4 // red
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//int inputPin=4;  // connect digital I/O 4 to the ECHO/Rx Pin
//int outputPin=5; // connect digital I/O 5 to the TRIG/TX Pin

MyoController myo = MyoController();
void stopRED_LED_ON();
void stopRED_LED_OFF();

void goGREEN_LED_ON();
void goGREEN_LED_OFF();

void turn_ALL_LEDS_OFF();

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

void setup() {
    Serial.begin(9600);           // set up Serial library at 9600 bps
    Serial.println("Adafruit Motorshield v2 - DC Motor test!");
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, OUTPUT);
    
    AFMS.begin();  // create with the default frequency 1.6KHz
    //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
    myo.initMyo();
    // Set the speed to start, from 0 (off) to 255 (max speed)
    myMotor->setSpeed(150);
    myMotor2->setSpeed(150);
    myo.initMyo();
}

void loop() {
   //uint8_t i;
   detectGestures();
   delay(500); 
  
}

void detectGestures(){
    myo.updatePose();
    // Getting current pose then apply specific motor function
    switch ( myo.getCurrentPose() ) {
      
      case rest:
           turn_ALL_LEDS_OFF();
          break;
          
      case fist: 
          myMotor->run(RELEASE);
          myMotor2->run(RELEASE);
          stopRED_LED_ON();
          goGREEN_LED_OFF();
          break;
          
      case waveOut:
          myMotor->setSpeed(150);
          myMotor2->setSpeed(150);
          myMotor->run(FORWARD);
          myMotor2->run(BACKWARD);
          break;
          
      case waveIn:
          myMotor->setSpeed(150);
          myMotor2->setSpeed(150);
          myMotor->run(BACKWARD);
          myMotor2->run(FORWARD);
          break;
          
      case fingersSpread:
           myMotor->setSpeed(150);
           myMotor2->setSpeed(150);
           myMotor->run(FORWARD);
           myMotor2->run(FORWARD);
           stopRED_LED_OFF();
           goGREEN_LED_ON();
          break;
    }
    
    
}
void stopRED_LED_ON()
{
     digitalWrite(echoPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    
      
 }

 void stopRED_LED_OFF()
 {
    digitalWrite(echoPin, LOW);    // turn the LED off by making the voltage LOW
   
 }


 void goGREEN_LED_ON()
{
     digitalWrite(trigPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    
      
 }

 void goGREEN_LED_OFF()
 {
    digitalWrite(trigPin, LOW);    // turn the LED off by making the voltage LOW
  
 }

 void turn_ALL_LEDS_OFF()
 {
  digitalWrite(trigPin, LOW);
  digitalWrite(echoPin, LOW);
  
 }


