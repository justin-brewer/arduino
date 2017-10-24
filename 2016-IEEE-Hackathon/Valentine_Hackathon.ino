#include <Servo.h>

Servo arch;
Servo aim;
Servo fire;

//servo angles
int currentArch, currentAim, currentFire;

//kinematic variables
double distance = 4.04; //(m)
double gunHeight = 0.91; //(m)
double targetHeight = 1.45; //(m)
double deltaHeight = targetHeight - gunHeight; //(m)
double velocity = 7.62; //(m/s)

// COORDINATES 
//left gun
int leftAim = 98, leftArch = 113; 
//middle gun
int middleAim = 95, middleArch = 126; 
//right gun
int rightAim = 78, rightArch = 135; 

// GUN SELECTION
int gun = 3; // left = 1, middle = 2, right = 3

//---------------------------------------------------------

void setup() {
  arch.attach(10);
  aim.attach(9);
  fire.attach(11);
  fire.write(90);

  gunSelect(gun);
  // OPTIONAL CORRECTION METHOD
  //updateCoordinates(6, -6); //(∆x, ∆y) (in inches)

  arch.write(currentArch); 
  aim.write(currentAim);

  Serial.begin(9600);
}
//---------------------------------------------------------

void loop() {
 
  if(Serial.available() > 0){
    char input = Serial.read();

    if(input == 'u'){
      tilt(1);  
    }
    else if(input == 'd'){
      tilt(-1); 
    }
    else if(input == 'r'){
      rotate(1);  
    }
    else if(input == 'l'){
      rotate(-1); 
    }
    else if(input == 'f'){
      fire.write(0);  
    } 
    else if(isDigit(input)){
      gunSelect(input - '0');
    }
    
    Serial.println(input);
  }
  delay(500);
  Serial.println("aim, arch");
  Serial.print(currentAim);
  Serial.print(", ");
  Serial.println(currentArch);
}
//---------------------------------------------------------

void rotate(int a){
  Serial.print("aim:  ");
  currentAim +=a;
  aim.write(currentAim);
  Serial.println(currentAim);
}
//---------------------------------------------------------

void tilt(int a){
  Serial.print("tilt: ");
  currentArch += a;
  arch.write(currentArch);
  Serial.println(currentArch);
}
//---------------------------------------------------------

void gunSelect(int g){
  switch(g){
  
    case 1: currentArch = leftArch; //Left
             currentAim = leftAim; 
             Serial.println("left gun");
            break;
    case 2:  currentArch = middleArch; // Middle
            currentAim = middleAim; 
            Serial.println("middle gun");
            break;

    case 3:  currentArch = rightArch; // Right
             currentAim = rightAim; 
             Serial.println("right gun");
             break;

     default: Serial.println("no gun selected");
              break;

  }
}
//---------------------------------------------------------

void updateCoordinates(int x, int y){
  // update currentAim
  double d = x*.0254;
  Serial.print("d: ");
  Serial.println(d);
  currentAim = (d/distance)*57.3 + currentAim;
  //update currentArch
  d = -y*.0254;
  Serial.print("d: ");
  Serial.println(d);
  currentArch = 2*(d/distance)*57.3 + currentArch;
}
//---------------------------------------------------------