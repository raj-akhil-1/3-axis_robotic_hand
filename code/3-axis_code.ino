
#include <Stepper.h>

const int stepsPerRevolution = 2038;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 2, 4, 3, 5);
//axis one homing
 int a=1,a1=1,a2=1;
 long int b,c,d;
 long int b1,c1,d1;
 long int b2,c2,d2;
 const int tol=4; //square of tolerance
 unsigned long startMillis,currentMillis;  

 
void axis_homing_1()
{
  while(a!=0)
  {
    a=digitalRead(A0);
    myStepper.step(-1);
    delay(10);
  }
}
void axis_homing_2()
{
  while(a1!=0)
  {
    a1=digitalRead(6);
    digitalWrite(9,HIGH);
    digitalWrite(8,LOW);
  }
  digitalWrite(9,LOW);
  digitalWrite(8,LOW);
}
void axis_homing_3()
{
  
  while(a2!=0)
  {
    a2=digitalRead(12);
    digitalWrite(13,HIGH);
    digitalWrite(10,LOW);
    delay(10);
  }
  digitalWrite(13,LOW);
  digitalWrite(10,LOW);
}
void turn_axis_ccw_3(unsigned long period)
{
  currentMillis = millis();
  startMillis=millis();
  while(currentMillis - startMillis <= period)
  {
    
  digitalWrite(10,HIGH);
  digitalWrite(13,LOW);  
  currentMillis = millis();  
  }
  digitalWrite(13,LOW);
  digitalWrite(10,LOW);
  
}
void turn_axis_cw_3(unsigned long period)
{
  currentMillis = millis();
  startMillis=millis();
  while(currentMillis - startMillis <= period)
  {
    
  digitalWrite(13,HIGH);
  digitalWrite(10,LOW);  
  currentMillis = millis();  
  }
  digitalWrite(13,LOW);
  digitalWrite(10,LOW);
  
}
void turn_axis_ccw_2(unsigned long period)
{
  currentMillis = millis();
  startMillis=millis();
  while(currentMillis - startMillis <= period)
  {
    
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);  
  currentMillis = millis();  
  }
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  
}
void turn_axis_cw_2(unsigned long period)
{
  currentMillis = millis();
  startMillis=millis();
  while(currentMillis - startMillis <= period)
  {
    
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);  
  currentMillis = millis();  
  }
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  
}
void axis_turn_angle_1(long int x)
{
  x=stepsPerRevolution*x/360;
  myStepper.step(x);

}


void setup() {
  // set the speed at 10 rpm:
  myStepper.setSpeed(10);
  // initialize the serial port:
  Serial.begin(9600);
  pinMode (A0, INPUT_PULLUP);
  pinMode (6, INPUT_PULLUP);
  pinMode (12, INPUT_PULLUP);
  pinMode (A1, INPUT);
  pinMode (A2, INPUT);
  pinMode (A3, INPUT);
  pinMode (8,OUTPUT);
  pinMode (9,OUTPUT);
  pinMode (13,OUTPUT);
  pinMode (10,OUTPUT);
  axis_homing_1();
  Serial.println("axis one homing completed");
  axis_homing_2();
  Serial.println("axis two homing completed");
  axis_homing_3();
  Serial.println("axis three homing completed");
}

void loop() 
{
  c=b;
  c1=b1;
  c2=b2;
  b=analogRead(A1);
  b1=analogRead(A3);
  b2=analogRead(A2);
  d=b-c;
  d1=b1-c1;
  d2=b2-c2;
  a=digitalRead(A0);
  a1=digitalRead(6);
  a2=digitalRead(12);
  Serial.println();
  Serial.print("x  : y  : z  :  ");
  Serial.print(a);
  Serial.print("  ");
  Serial.print(a1);
  Serial.print("  ");
  Serial.print(a2);
  
  if(a==0)
  {
    axis_turn_angle_1(5);
  }
  else if(d*d>tol && d>=0 && d<=10)
  {
    axis_turn_angle_1(5);
  }
  else if(d*d>tol && d<0 && d>=-10)
  {
    axis_turn_angle_1(-5);
  }
  if(a1==0)
  {
    turn_axis_ccw_2(50);
  }
  else if(d1*d1>tol && d1>=0 && d1<=10)
  {
    turn_axis_ccw_2(100);
  }
  else if(d1*d1>tol && d1<0 && d1>=-10)
  {
    turn_axis_cw_2(100);
  }
    if(a2==0)
  {
    turn_axis_ccw_3(10);
  }
  else if(d2*d2>tol && d2>=0 && d2<=10)
  {
    turn_axis_ccw_3(20);
  }
  else if(d2*d2>tol && d2<0 && d2>=-10)
  {
    turn_axis_cw_3(20);
  }
delay(100);
}
