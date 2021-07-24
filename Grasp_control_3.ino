// Include the Servo.h library
#include <Servo.h>

const float max_EMG = 300;

// Declare the digital pin D2 for the pushbutton
const int pushbutton = 2;

// Declare the servos 
Servo index;
Servo middle;
Servo ring;
Servo small;
Servo thumb_flexion;
Servo thumb_opposition;

// Declare the buttonstate variable
int buttonstate = 0;

void setup() 
{

  // Set the serial comunication at 9600 bauds
  Serial.begin(9600);
  
  //Declare the pushbutton digital port as an input
  pinMode(pushbutton, INPUT_PULLUP);

  // Declare the digital pins where the linear servos are attached
  index.attach(6);  
  middle.attach(5);  
  ring.attach(10);  
  small.attach(9); 
  thumb_flexion.attach(3);
  thumb_opposition.attach(11); 
}

void loop() 
{
  // Increase the buttonstate value if the pushbutton is HIGH
  if (digitalRead(pushbutton) == HIGH) 
  {
    buttonstate = (buttonstate + 1) % 6;
    delay(200);
  }

  // Read the analog EMG signal from the port A0
  int flexion2= analogRead(A0);
  //Convert the flexion sensor (calibration function)
  float flexion3 = (-107/max_EMG) * flexion2 + 145;
  int flexion4 = int(flexion3);

  // Repeat the last 3 steps for the thumb opposition
  int opposition2= analogRead(A0);
  int opposition3 = 0.6 * opposition2 + 60;

  // Change across the different types of grasps when the buttonstate changes calling their functions in each case
  switch (buttonstate) {
    case 0:
      tip_grasp(flexion4,opposition3);
      break;
    case 1:
      trippod_grasp(flexion4,opposition3);
      break;
    case 2:
      lateral_grasp(flexion4,opposition3);
      break;
    case 3:
      hook_grasp(flexion4,opposition3);
      break;
    case 4:
      spherical_grasp(flexion4,opposition3);
      break;
    case 5:
      cylindrical_grasp(flexion4,opposition3);
      break;
  }
  
  
}


// Tip grasp function
void tip_grasp(int flexion3, int opposition3)
{
  index.write(flexion3);
  thumb_opposition.write(140);
  thumb_flexion.write(70);
} 

// Trippod grasp function
void trippod_grasp(int flexion3, int opposition3)
{
 index.write(flexion3);
 middle.write(flexion3);
 thumb_opposition.write(140);
 thumb_flexion.write(70);
} 

// Lateral grasp function
void lateral_grasp(int flexion3, int opposition3)
{
 index.write(flexion3);
 middle.write(flexion3);
 ring.write(flexion3);
 small.write(flexion3);
 thumb_opposition.write(60);
 thumb_flexion.write(flexion3);
} 

// Hook grasp function
void hook_grasp(int flexion3, int opposition3)
{
 index.write(flexion3);
 middle.write(flexion3);
 ring.write(flexion3);
 small.write(flexion3);
 thumb_opposition.write(60);
 thumb_flexion.write(120);
} 

// Spherical grasp function
void spherical_grasp (int flexion3, int opposition3)
{
 index.write(flexion3);
 middle.write(flexion3);
 ring.write(flexion3);
 small.write(flexion3);
 thumb_opposition.write(140);
 thumb_flexion.write(flexion3);
} 

// Cylindrical grasp function
void cylindrical_grasp (int flexion3, int opposition3)
{
 index.write(flexion3);
 middle.write(flexion3);
 ring.write(flexion3);
 small.write(flexion3);
 thumb_opposition.write(140);
 thumb_flexion.write(flexion3);
} 
