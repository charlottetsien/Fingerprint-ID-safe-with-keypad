#include <Servo.h>
#include <SoftwareSerial.h>
#include <FPS_GT511C3.h>
#include <Key.h>
#include <Keypad.h>


int buttonPin = A1;
int buttonState = 1;
//int count = 0;

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'},
};
byte rowPins[ROWS] = {7,8,9,13};
byte colPins[COLS] = {2,3,6};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int redPin = 10;
const int greenPin = 11;
const int bluePin = 12;


FPS_GT511C3 fps(4,5);
char inputArray[4];
char Password[4] = {'0','9','2','8'};
char outputArray[4];
char Passcode[4] = {'0','0','0','0'};

Servo myservo_1;
int pos_1 = 180;
Servo myservo_3;
int pos_3 = 0;
boolean off = false;

int i = 0;
int MasterGuest()
{
  {
    if((inputArray[0] == Password[0] &&
        inputArray[1] == Password[1] &&
        inputArray[2] == Password[2] &&
        inputArray[3] == Password[3] )){
          open();
          //fingerprint();
    }
    if((outputArray[0] == Passcode[0] && 
        outputArray[1] == Passcode[1] &&
        outputArray[2] == Passcode[2] &&
        outputArray[3] == Passcode[3] &&
        outputArray[4] == Passcode[4] )){
          
        }
    else{
      close();
     }
    
  }
}



int open()
{
  analogWrite(redPin,0);
  analogWrite(greenPin,255);
  analogWrite(bluePin,255);
  delay(1000);
  analogWrite(redPin,0);
  analogWrite(greenPin,0);
  analogWrite(bluePin,0);
  fps.SetLED(true);
  delay(1000);
  fingerprint();
  return 0;
};

int close()
{
 11 analogWrite(redPin,255);
  analogWrite(greenPin,60);
  analogWrite(bluePin,0);
  delay(1000);
  analogWrite(redPin,0);
  analogWrite(greenPin,0);
  analogWrite(bluePin,0);
  return 0;
}

int fingerprint()
{  
  myservo_1.attach(A0);
  myservo_3.attach(A3);
  if (fps.IsPressFinger()){
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    if (id<200){
       //Serial.println("enter");
       //Serial.println(id);
       analogWrite(redPin,0);
       analogWrite(greenPin,255);
       analogWrite(bluePin,0);
       delay(1000);
       analogWrite(redPin,0);
       analogWrite(greenPin,0);
       analogWrite(bluePin,0);
       delay(1000);
       fps.SetLED(false);
       servo();
       //myservo.detach();
       
    }
    else{
      analogWrite(redPin,255);
      analogWrite(greenPin,0);
      analogWrite(bluePin,0);
      //Serial.println("go away");
      delay(1000);
      analogWrite(redPin,0);
      analogWrite(greenPin,0);
      analogWrite(bluePin,0);
      delay(1000);
      fps.SetLED(false);
    }
  }
  else{
    delay(1000);
    analogWrite(redPin,0);
    analogWrite(greenPin,0);
    analogWrite(bluePin,255);
    delay(1000);
    analogWrite(redPin,0);
    analogWrite(greenPin,0);
    analogWrite(bluePin,0);
  }
  
}

int servo()
{
  //myservo_2.attach();
  //myservo_3.attach();
  for (pos_1 = 180; pos_1 >=0; pos_1 -=1){
    myservo_1.write(pos_1);
    delay(5);
  }
  for(pos_3 = 0; pos_3 <= 180; pos_3 +=1){
    myservo_3.write(pos_3);
    delay(5);
  }
  fps.SetLED(false);
  //count++;
}
 /*int servo_return()
 {
  Serial.println("got here");
  for (pos_1 = 0; pos_1 <= 180; pos_1 +=1){
    myservo_1.write(pos_1);
    delay(5);
  }
  for(pos_3 = 180; pos_3 >= 0; pos_3 -=1){
    myservo_3.write(pos_3);
    delay(5);
  }
  myservo_1.detach();
  myservo_3.detach();
  char key = keypad.getKey();
  if(key){
    analogWrite(redPin,0);  
    analogWrite(greenPin,0);
    analogWrite(bluePin,0);
  }
  myservo_1.detach();
  myservo_3.detach();
 }*/

 int next()
{
        
        myservo_1.attach(A0);
        myservo_3.attach(A3);
        delay(1000);
        Serial.println("got here");         
            for (pos_1 = 0; pos_1 <= 180; pos_1 +=1){
              myservo_1.write(pos_1);
              delay(5);
            }
            for (pos_3 = 180; pos_3 >= 0; pos_3 -=1){
              myservo_3.write(pos_3);
              delay(5);
            }
        
            myservo_1.detach();
            myservo_3.detach();
        
            delay(1000);
            
}
          

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);       
  fps.SetLED(false);//send serial command to initialize fps
  fps.Open();//turn on LED so fps can see fingerprint
  myservo_1.write(pos_1);
  myservo_3.write(pos_3);    
}

void loop() {
  buttonState = digitalRead(buttonPin);
    if(buttonState == LOW){
      next();
    }
    if(buttonState == HIGH){
      Serial.println("im here");
      char key = keypad.getKey();
      if (key){
        analogWrite(redPin,255);  
        analogWrite(greenPin,255);
        analogWrite(bluePin,255);
        delay(100);
        analogWrite(redPin,0);
        analogWrite(greenPin,0);
        analogWrite(bluePin,0);
        inputArray[i] = key;
        i++;
        if (key=='*'){
          i=0;
        } 
        if (i == 4){
          MasterGuest();
          {
            i=0;          
          }
        }
     
      } 
    }
    
}
   
 

 
  
 
  
