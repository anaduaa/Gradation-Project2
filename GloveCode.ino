#include <MPU6050.h>

/*
NAME OF THE PROJECT : SIGN LANGUAGE TRANSLATOR
MADE BY - MANMOHAN GUPTA

THIS PROJECT READS SENSOR VALUE AND TRY TO UNDERSTAND SYMBOLS GENERATED FROM AMERICAN SIGN LANGUAGE (ASL) CHART
AND DISPLAY ON A SMARTPHONE.
-------PIN CONFIGURATION----------------
A0-A4 : FLEX SENSOR
D4&D5 : FOR BLUETOOTH RX AND TX
A5&A6 : XPIN AND YPIN FOR ACCELROMETER
*/




#include "Wire.h"       
#include "I2Cdev.h" 

#include <SoftwareSerial.h>

SoftwareSerial mySerial(5,4);

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
};

MyData data;

int gesture = 0; 

const float flatResistance = 450; // resistance when flat
const float bendResistance = 650;  // resistance at 90 deg

float newAngle, previousAngle1 ,previousAngle2 , previousAngle3 , previousAngle4 , previousAngle5;


char temp = '0';

//variable initializtion

int FLEX_PIN1 = A7; 
int flexADC1 = 0; 

int FLEX_PIN2 = A1; 
int flexADC2 = 0; 

int FLEX_PIN3 = A2; 
int flexADC3 = 0; 

int FLEX_PIN4 = A3; 
int flexADC4 = 0; 

int FLEX_PIN5 = A6; 
int flexADC5 = 0; 


void setup() 
{
  mySerial.begin(9600);
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

 while (!Serial) 
  {
      ; // wait for serial port to connect. Needed for native USB port only
  }

// callibrating the sensors for adaptivity with different bends
while(millis()<15000)
{
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(FLEX_PIN1, INPUT);
  pinMode(FLEX_PIN2, INPUT);
  pinMode(FLEX_PIN3, INPUT);
  pinMode(FLEX_PIN4, INPUT);
  pinMode(FLEX_PIN5, INPUT);
}
}

void printfun(char cp){
  if(cp!=temp){
  mySerial.print(cp);
  temp=cp;
  }
}

void printfun1(float ang1 , float ang2 ,float ang3,float ang4,float ang5  ) //to avoid printing repeating symbols
{
 Serial.print("#1 : ");
  Serial.println(ang1);
  Serial.print("#2 : ");
  Serial.println(ang2);
  Serial.print("#3 : ");
  Serial.println(ang3);
  Serial.print("#4 : ");
  Serial.println(ang4);
  Serial.print("#5 : ");
  Serial.println(ang5);
}

void loop() 
{


 mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255);  // Y axis data
  //delay(500);
     // Serial.println(data.Y);

 if (data.Y < 80) { //gesture : down 
    Serial.println("gesture 1");
    gesture =1;
    }
 if (data.Y > 145) {//gesture : up
  Serial.println("gesture 2");
  gesture=2;
    }
 if (data.X > 155) {//gesture : left
  Serial.println("gesture 3");
   gesture=3;
    }
 if (data.X < 80) {//gesture : right
  Serial.println("gesture 4");
   gesture=4;
    }
 if (data.X > 100 && data.X < 170 && data.Y > 80 && data.Y < 130) { //gesture : little bit down
    Serial.println("gesture 5");
     gesture=5;
    }

float flexADC1 = analogRead(FLEX_PIN1);
float flexADC2 = analogRead(FLEX_PIN2);
float flexADC3 = analogRead(FLEX_PIN3);
float flexADC4 = analogRead(FLEX_PIN4);
float flexADC5 = analogRead(FLEX_PIN5);
//Serial.println(analogRead(FLEX_PIN1));
//Serial.println((digitalRead(7) == HIGH));

//Serial.println(analogRead(FLEX_PIN1));
//Serial.println(analogRead(FLEX_PIN4));

     float angle1 = map(flexADC1, 555,720 , 0, 90);
    angle1 = constrain(angle1, 0, 90); // optional


       float angle2 = map(flexADC2, 480,650, 0, 90);
    angle2 = constrain(angle2, 0, 90); // optional



         float angle3 = map(flexADC3, 385,450, 0, 90);
    angle3 = constrain(angle3, 0, 90); // optional


         float angle4 = map(flexADC4,490 ,660, 0, 90);
    angle4 = constrain(angle4, 0, 90); // optional



           float angle5 = map(flexADC5, 490,620, 0, 90);
    angle5 = constrain(angle5, 0, 90); // optional




//printfun1(angle1 ,angle2 , angle3 ,angle4 ,angle5 );



if(((angle1>=70)&&(angle1<=90))&&((angle2>=70)&&(angle2<=90))&&((angle3>=70)&&(angle3<=90))&&((angle4>=70)&&(angle4<=90))&&((angle5>=0)&&(angle5<=20))&&(digitalRead(7) == LOW )){
//Serial.println("A");
  printfun('A');

}
if(((angle1>=0)&&(angle1<=20))&&((angle2>=0)&&(angle2<=20))&&((angle3>=0)&&(angle3<=20))&&((angle4>=0)&&(angle4<=20))&&((angle5>=65)&&(angle5<=90)  )){
//Serial.println("B");
printfun('B');
}
if(((angle1>=30)&&(angle1<=65))&&((angle2>=30)&&(angle2<=65))&&((angle3>=30)&&(angle3<=65))&&((angle4>=30)&&(angle4<=60))&&((angle5>=25)&&(angle5<=60))&&(digitalRead(7) ==LOW )){
 // Serial.println("C");
 // mySerial.println('C');
  printfun('C');
  //}
}

if(((angle1>=50)&&(angle1<=90))&&((angle2>=45)&&(angle2<=90))&&((angle3>=35)&&(angle3<=90))&&((angle4>=0)&&(angle4<=10))&&((angle5>=45)&&(angle5<=90))&&(gesture!=1)){
printfun('D');
 //Serial.println("D");
}
if(((angle1>=60)&&(angle1<=90))&&((angle2>=20)&&(angle2<=30))&&((angle3>=60)&&(angle3<=90))&&((angle4>=36)&&(angle4<=70))&&((angle5>=40)&&(angle5<=60))&&(gesture!=2)){
printfun('E');
 //Serial.println("E");
}
if(((angle1>=0)&&(angle1<=30))&&((angle2>=0)&&(angle2<=30))&&((angle3>=0)&&(angle3<=30))&&((angle5>=30)&&(angle5<=65))&&((angle4>=60)&&(angle4<=90))){
printfun('F');
 //Serial.println("F");
}
if(((angle1>=55)&&(angle1<=90))&&((angle2>=55)&&(angle2<=90))&&((angle3>=65)&&(angle3<=90))&&((angle4>=0)&&(angle4<=25))&&((angle5>=0)&&(angle5<=25))&&(gesture==1)){
printfun('G');
 //Serial.println("G");
}
if(((angle1>=60)&&(angle1<=90))&&((angle2>=60)&&(angle2<=90))&&((angle3>=0)&&(angle3<=20))&&((angle4>=0)&&(angle4<=20))&&((angle5>=30)&&(angle5<=90))&&(gesture==1)){

printfun('H');
 //Serial.println("H");
}
if(((angle1>=0)&&(angle1<=25))&&((angle2>=50)&&(angle2<=90))&&((angle3>=40)&&(angle3<=90))&&((angle4>=50)&&(angle4<=90))&&((angle5>=50)&&(angle5<=90))&&(gesture!=1)){
printfun('I');
//Serial.println("I");
}

if(((angle1>=0)&&(angle1<=25))&&((angle2>=50)&&(angle2<=90))&&((angle3>=40)&&(angle3<=90))&&((angle4>=50)&&(angle4<=90))&&((angle5>=50)&&(angle5<=90))&&(gesture==1)){
printfun('J');
//Serial.println("J");
}
//if(((angle1>=60)&&(angle1<=75))&&((angle2>=60)&&(angle2<=85))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=15))&&((angle5>=30)&&(angle5<=55))&&(((xadc>=404)&&(xadc<=415))&&((yadc>=368)&&(yadc<=380))))
if(((angle1>=70)&&(angle1<=90))&&((angle2>=70)&&(angle2<=90))&&((angle3>=0)&&(angle3<=20))&&((angle4>=0)&&(angle4<=20))&&((angle5>=30)&&(angle5<=55))&&(gesture!=1)&&(digitalRead(7) == LOW)) {
printfun('K');

//Serial.println('K');

}
//if(((angle1>=75)&&(angle1<=90))&&((angle2>=75)&&(angle2<=90))&&((angle3>=70)&&(angle3<=90))&&((angle4>=0)&&(angle4<=15))&&((angle5>=0)&&(angle5<=30))&&(((xadc>=390)&&(xadc<=405))&&((yadc>=360)&&(yadc<=380)))&&!((xadc>=270)&&(xadc<=300))&&((yadc>=360)&&(yadc<=390)))
if(((angle1>=55)&&(angle1<=90))&&((angle2>=55)&&(angle2<=90))&&((angle3>=55)&&(angle3<=90))&&((angle4>=0)&&(angle4<=25))&&((angle5>=0)&&(angle5<=25))&&(gesture!=1&&(gesture!=3))){
 printfun('L'); 

//Serial.println('L');
}

if(((angle1>=30)&&(angle1<=55))&&((angle2>=30)&&(angle2<=55))&&((angle3>=70)&&(angle3<=90))&&((angle4>=30)&&(angle4<=60))&&((angle5>=30)&&(angle5<=60))){
printfun('M');
//Serial.println('M');
}
if(((angle1>=70)&&(angle1<=90))&&((angle2>=40)&&(angle2<=60))&&((angle3>=70)&&(angle3<=90))&&((angle4>=40)&&(angle4<=80))&&((angle5>=0)&&(angle5<=30))){
  
//Serial.println('N');
printfun('N');
}
if(((angle1>=30)&&(angle1<=65))&&((angle2>=30)&&(angle2<=65))&&((angle3>=30)&&(angle3<=65))&&((angle4>=0)&&(angle4<=60))&&((angle5>=0)&&(angle5<=60))&&(digitalRead(7) ==HIGH )){


  //Serial.println('O');
printfun('O');
}
if(((angle1>=60)&&(angle1<=90))&&((angle2>=60)&&(angle2<=90))&&((angle3>=40)&&(angle3<=60))&&((angle4>=0)&&(angle4<=15))&&((angle5>=0)&&(angle5<=20))&&( gesture==1)){
printfun('P');

//Serial.println('P');
}
if(((angle1>=55)&&(angle1<=90))&&((angle2>=55)&&(angle2<=90))&&((angle3>=55)&&(angle3<=90))&&((angle4>=0)&&(angle4<=25))&&((angle5>=0)&&(angle5<=25))&&(gesture==3)){

printfun('Q'); 

//Serial.println('Q');
}
if(((angle1>=60)&&(angle1<=90))&&((angle2>=60)&&(angle2<=90))&&((angle3>=0)&&(angle3<=20))&&((angle4>=0)&&(angle4<=20))&&((angle5>=0)&&(angle5<=20))&&(gesture!=1)){
printfun('R');
//Serial.println('R');
}
if(((angle1>=60)&&(angle1<=90))&&((angle2>=60)&&(angle2<=90))&&((angle3>=60)&&(angle3<=90))&&((angle4>=30)&&(angle4<=70))&&((angle5>=30)&&(angle5<=60))&&(digitalRead(7) == HIGH )){

  //Serial.println('S');
printfun('S');
}
if(((angle1>=60)&&(angle1<=90))&&((angle2>=60)&&(angle2<=60))&&((angle3>=60)&&(angle3<=90))&&((angle4>=60)&&(angle4<=90))&&((angle5>=30)&&(angle5<=90))&&(digitalRead(7)==HIGH)&&(digitalRead(8)==LOW)){
//Serial.println('T');
  
printfun('T');
}
if(((angle1>=70)&&(angle1<=90))&&((angle2>=70)&&(angle2<=90))&&((angle3>=0)&&(angle3<=20))&&((angle4>=0)&&(angle4<=20))&&((angle5>=60)&&(angle5<=90))&&(gesture!=1)&&(digitalRead(8) == HIGH)) {
printfun('U'); 
//Serial.println('U');

}


if(((angle1>=70)&&(angle1<=90))&&((angle2>=70)&&(angle2<=90))&&((angle3>=0)&&(angle3<=20))&&((angle4>=0)&&(angle4<=20))&&((angle5>=60)&&(angle5<=90))&&(gesture!=1)&&(digitalRead(8) == LOW)) {
printfun('V');

//Serial.println('V');

}
if(((angle1>=70)&&(angle1<=90))&&((angle2>=0)&&(angle2<=20))&&((angle3>=0)&&(angle3<=20))&&((angle4>=0)&&(angle4<=20))&&((angle5>=30)&&(angle5<=90))){
//printfun('W');
//Serial.println('W');
}

 if(((angle1>=70)&&(angle1<=90))&&((angle2>=70)&&(angle2<=90))&&((angle3>=70)&&(angle3<=90))&&((angle4>=25)&&(angle4<=35))&&((angle5>=60)&&(angle5<=90))&&(gesture==4)){
//printfun('X');
//Serial.println('X');
}
if(((angle1>=0)&&(angle1<=20))&&((angle2>=70)&&(angle2<=90))&&((angle3>=60)&&(angle3<=90))&&((angle4>=80)&&(angle4<=90))&&((angle5>=0)&&(angle5<=20))){
//Serial.println('Y');
  
 printfun('Y');
}

//if(((angle1>=50)&&(angle1<=72))&&((angle2>=45)&&(angle2<=90))&&((angle3>=35)&&(angle3<=75))&&((angle4>=0)&&(angle4<=10))&&((angle5>=45)&&(angle5<=80))&&(((xadc>=412)&&(xadc<=418))&&((yadc>=340)&&(yadc<=360))))
//printfun('Z');




delay(500);

}
//----------------------END-----------------------------
