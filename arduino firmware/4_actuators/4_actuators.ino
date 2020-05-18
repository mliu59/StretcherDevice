#include <Stepper.h>
 
// change this to the number of steps on your motor
#define STEPS 200
 
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper1(STEPS, 4, 5, 6, 7);
Stepper stepper2(STEPS, 8, 9, 10, 11);
Stepper stepper3(STEPS, 24, 26, 28, 30);
Stepper stepper4(STEPS, 42, 44, 46, 48);
const float MM_PER_INCH = 25.4;
const int THREAD_PER_INCH = 40; 
const int GEAR_RATIO = 16; 
const int STEPS_PER_REV = 200;
const float MM_TO_STEPS = 1 / MM_PER_INCH * THREAD_PER_INCH * STEPS_PER_REV * GEAR_RATIO;
 
void setup()
{
  Serial.begin(9600);
  // set the speed of the motor to 30 RPMs
  stepper1.setSpeed(60);
  stepper2.setSpeed(60);
  stepper3.setSpeed(60);
  stepper4.setSpeed(60);
}
 
void loop()
{
  if(Serial.available() > 0){
    int distance = Serial.readStringUntil('\n').toInt();
    for (int i = 0; i < (int)(distance* MM_TO_STEPS); i++){
      stepper1.step(1);
      stepper2.step(1);
      stepper3.step(1);
      stepper4.step(1);
    }
    Serial.println("DONE");
  }
}
