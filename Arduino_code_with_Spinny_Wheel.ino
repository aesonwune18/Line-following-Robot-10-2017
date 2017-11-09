 
 // Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define FORWARD  0
#define REVERSE 1

// Motor definitions to make life easier:
#define Motor_A 0
#define Motor_B 1

// Pin Assignments //
//Default pins:
#define DIRA 2 // Direction control for motor A
#define PWMA 3  // PWM control (speed) for motor A
#define DIRB 4 // Direction control for motor B
#define PWMB 11 // PWM control (speed) for motor B

////Alternate pins:
//#define DIRA 8 // Direction control for motor A
//#define PWMA 9 // PWM control (speed) for motor A
//#define DIRB 7 // Direction control for motor B
//#define PWMB 10 // PWM control (speed) for motor B


 void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);

  
}

void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == Motor_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == Motor_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
setupArdumoto();
 
}


void loop() {

  int lPinRdg = analogRead(0);
  int cPinRdg = analogRead(1);
  int rPinRdg = analogRead(2);

  Serial.print(lPinRdg);
  Serial.print("\t"); //Separating the values of all the sensors with a tab ("\t") 
  Serial.print(cPinRdg);
  Serial.print("\t");
  Serial.println(rPinRdg);
  //delay(3000);
  


  int motorSpeed = 80;
  int backSpeed = 60;
  int threshhold = 770;
  
  //TURN RIGHT, RIGHT SENSOR DARK

  if (rPinRdg > threshhold && cPinRdg < threshhold && lPinRdg < threshhold)
  {
    driveArdumoto(Motor_A, 1, backSpeed);
    driveArdumoto(Motor_B, 0, motorSpeed);
  }

  //GO STRAIGHT WHEN RIGHT AND MIDDLE SENSOR ARE DARK
  
  else if (rPinRdg > threshhold && cPinRdg > threshhold && lPinRdg < threshhold)
  {
    driveArdumoto(Motor_A, 1, backSpeed);
    driveArdumoto(Motor_B, 0, motorSpeed);
  }

  //TURN LEFT, LEFT SENSOR DARK
  
   else if (rPinRdg < threshhold && cPinRdg < threshhold && lPinRdg > threshhold)
  {
    driveArdumoto(Motor_A, 0, motorSpeed);
    driveArdumoto(Motor_B, 1, backSpeed);
  }

  //GO STRAIGHT WHEN LEFT AND MIDDLE SENSOR ARE DARK
  
  else if (rPinRdg < threshhold && cPinRdg > threshhold && lPinRdg > threshhold)
  {
    driveArdumoto(Motor_A, 0, motorSpeed);
    driveArdumoto(Motor_B, 1, backSpeed);
  }

  //GO STRAIGHT, CENTER SENSOR DARK
  
   else if (rPinRdg < threshhold && cPinRdg > threshhold && lPinRdg < threshhold)
  {
    driveArdumoto(Motor_A, 0, motorSpeed);
    driveArdumoto(Motor_B, 0, motorSpeed);
  }

  //FIND THE BLACK TAPE, NO SENSOR DARK
   else if (rPinRdg < threshhold && cPinRdg < threshhold && lPinRdg < threshhold)
  {
    driveArdumoto(Motor_A, 1, 80);
    driveArdumoto(Motor_B, 0, motorSpeed);
  }

  //GO STRAIGHT, ALL SENSORS DARK
   else if (rPinRdg > threshhold && cPinRdg > threshhold && lPinRdg > threshhold)
  {
    driveArdumoto(Motor_A, 0, motorSpeed);
    driveArdumoto(Motor_B, 0, motorSpeed);
  }

}
