#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;
Servo servo05;
Servo servo06;

//SoftwareSerial Bluetooth(3, 4); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)

byte servo1Pos, servo2Pos, servo3Pos, servo4Pos, servo5Pos, servo6Pos; // current position
byte servo1PPos, servo2PPos, servo3PPos, servo4PPos, servo5PPos, servo6PPos; // previous position
byte servo101SP[50], servo102SP[50], servo103SP[50], servo104SP[50], servo105SP[50], servo106SP[50]; // for storing positions/steps
byte servo201SP[50], servo202SP[50], servo203SP[50], servo204SP[50], servo205SP[50], servo206SP[50]; // for storing positions/steps
byte servo301SP[50], servo302SP[50], servo303SP[50], servo304SP[50], servo305SP[50], servo306SP[50]; // for storing positions/steps
int speedDelay = 20;
int index = 0;
int test =0;
String dataIn = "";
// Define color sensor pins
#define S0 12
#define S1 2
#define S2 3
#define S3 4
#define sensorOut 11

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

void setup() {
   servo01.attach(5);
  servo02.attach(6);
  servo03.attach(7);
  servo04.attach(8);
  servo05.attach(9);
  servo06.attach(10);
 // Bluetooth.begin(38400); // Default baud rate of the Bluetooth module
  //Bluetooth.setTimeout(1);
  delay(20);
  // Robot arm initial position
  servo1PPos = 120;
  servo01.write(servo1PPos);
  servo2PPos = 170;
  servo02.write(servo2PPos);
  servo3PPos = 120;
  servo03.write(servo3PPos);
  servo4PPos = 0;
  servo04.write(servo4PPos);
  servo5PPos = 94;
  servo05.write(servo5PPos);
  servo6PPos = 120;
  servo06.write(servo6PPos);
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Set Pulse Width scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  // Set Sensor output as input
  pinMode(sensorOut, INPUT);

  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Read Red Pulse Width
  redPW = getRedPW();
  // Delay to stabilize sensor
  delay(200);

  // Read Green Pulse Width
  greenPW = getGreenPW();
  // Delay to stabilize sensor
  delay(200);

  // Read Blue Pulse Width
  bluePW = getBluePW();
  // Delay to stabilize sensor
  delay(200);

  // Print output to Serial Monitor
  /*Serial.print("Red PW = ");
  Serial.print(redPW);
  Serial.print(" - Green PW = ");
  Serial.print(greenPW);
  Serial.print(" - Blue PW = ");
  Serial.println(bluePW);
  Serial.print(" the current color is ");
  Serial.println(minvalue(redPW,greenPW,bluePW));*/
   // Check for incoming data
  if (Serial.available() > 0) {
    dataIn = Serial.readString();  // Read the data as string
    Serial.print(dataIn);
    // If "Waist" slider has changed value - Move Servo 1 to position
    if (dataIn.startsWith("s1")) {
      String dataInS = dataIn.substring(2, dataIn.length()); // Extract only the number. E.g. from "s1120" to "120"
      servo1Pos = dataInS.toInt();  // Convert the string into integer
      // We use for loops so we can control the speed of the servo
      // If previous position is bigger then current position
      if (servo1PPos > servo1Pos) {
        for ( int j = servo1PPos; j >= servo1Pos; j--) {   // Run servo down
          servo01.write(j);
          delay(20);    // defines the speed at which the servo rotates
        }
      }
      // If previous position is smaller then current position
      if (servo1PPos < servo1Pos) {
        for ( int j = servo1PPos; j <= servo1Pos; j++) {   // Run servo up
          servo01.write(j);
          delay(20);
        }
      }
      servo1PPos = servo1Pos;   // set current position as previous position
    }
    
    // Move Servo 2
    if (dataIn.startsWith("s2")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo2Pos = dataInS.toInt();

      if (servo2PPos > servo2Pos) {
        for ( int j = servo2PPos; j >= servo2Pos; j--) {
          servo02.write(j);
          delay(50);
        }
      }
      if (servo2PPos < servo2Pos) {
        for ( int j = servo2PPos; j <= servo2Pos; j++) {
          servo02.write(j);
          delay(50);
        }
      }
      servo2PPos = servo2Pos;
    }
    // Move Servo 3
    if (dataIn.startsWith("s3")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo3Pos = dataInS.toInt();
      if (servo3PPos > servo3Pos) {
        for ( int j = servo3PPos; j >= servo3Pos; j--) {
          servo03.write(j);
          delay(30);
        }
      }
      if (servo3PPos < servo3Pos) {
        for ( int j = servo3PPos; j <= servo3Pos; j++) {
          servo03.write(j);
          delay(30);
        }
      }
      servo3PPos = servo3Pos;
    }
    // Move Servo 4
    if (dataIn.startsWith("s4")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo4Pos = dataInS.toInt();
      if (servo4PPos > servo4Pos) {
        for ( int j = servo4PPos; j >= servo4Pos; j--) {
          servo04.write(j);
          delay(30);
        }
      }
      if (servo4PPos < servo4Pos) {
        for ( int j = servo4PPos; j <= servo4Pos; j++) {
          servo04.write(j);
          delay(30);
        }
      }
      servo4PPos = servo4Pos;
    }
    // Move Servo 5
    if (dataIn.startsWith("s5")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo5Pos = dataInS.toInt();
      if (servo5PPos > servo5Pos) {
        for ( int j = servo5PPos; j >= servo5Pos; j--) {
          servo05.write(j);
          delay(30);
        }
      }
      if (servo5PPos < servo5Pos) {
        for ( int j = servo5PPos; j <= servo5Pos; j++) {
          servo05.write(j);
          delay(30);
        }
      }
      servo5PPos = servo5Pos;
    }
    // Move Servo 6
    if (dataIn.startsWith("s6")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo6Pos = dataInS.toInt();
      if (servo6PPos > servo6Pos) {
        for ( int j = servo6PPos; j >= servo6Pos; j--) {
          servo06.write(j);
          delay(30);
        }
      }
      if (servo6PPos < servo6Pos) {
        for ( int j = servo6PPos; j <= servo6Pos; j++) {
          servo06.write(j);
          delay(30);
        }
      }
      servo6PPos = servo6Pos; 
    }
    // If button "SAVE" is pressed
    if (dataIn.startsWith("SAVE RED")) {
      servo101SP[index] = servo1PPos;  // save position into the array
      servo102SP[index] = servo2PPos;
      servo103SP[index] = servo3PPos;
      servo104SP[index] = servo4PPos;
      servo105SP[index] = servo5PPos;
      servo106SP[index] = servo6PPos;
      index++;                        // Increase the array index
    }
    // If button "SAVE" is pressed
    if (dataIn.startsWith("SAVE BLUE")) {
      servo201SP[index] = servo1PPos;  // save position into the array
      servo202SP[index] = servo2PPos;
      servo203SP[index] = servo3PPos;
      servo204SP[index] = servo4PPos;
      servo205SP[index] = servo5PPos;
      servo206SP[index] = servo6PPos;
      index++;                        // Increase the array index
    }
     // If button "SAVE" is pressed
    if (dataIn.startsWith("SAVE GREEN")) {
      servo301SP[index] = servo1PPos;  // save position into the array
      servo302SP[index] = servo2PPos;
      servo303SP[index] = servo3PPos;
      servo304SP[index] = servo4PPos;
      servo305SP[index] = servo5PPos;
      servo306SP[index] = servo6PPos;
      index++;                        // Increase the array index
    }
    // If button "RUN" is pressed
    if (dataIn.startsWith("RUN")) {
test =1;      
      //runservo();  // Automatic mode - run the saved steps 
    }
    // If button "RESET" is pressed
    if ( dataIn == "RESET RED") {
      memset(servo101SP, 0, sizeof(servo101SP)); // Clear the array data to 0
      memset(servo102SP, 0, sizeof(servo102SP));
      memset(servo103SP, 0, sizeof(servo103SP));
      memset(servo104SP, 0, sizeof(servo104SP));
      memset(servo105SP, 0, sizeof(servo105SP));
      memset(servo106SP, 0, sizeof(servo106SP));
      index = 0;  // Index to 0
    }
    // If button "RESET" is pressed
    if ( dataIn == "RESET BLUE") {
      memset(servo201SP, 0, sizeof(servo201SP)); // Clear the array data to 0
      memset(servo202SP, 0, sizeof(servo202SP));
      memset(servo203SP, 0, sizeof(servo203SP));
      memset(servo204SP, 0, sizeof(servo204SP));
      memset(servo205SP, 0, sizeof(servo205SP));
      memset(servo206SP, 0, sizeof(servo206SP));
      index = 0;  // Index to 0
    }
     // If button "RESET" is pressed
    if ( dataIn == "RESET GREEN") {
      memset(servo301SP, 0, sizeof(servo301SP)); // Clear the array data to 0
      memset(servo302SP, 0, sizeof(servo302SP));
      memset(servo303SP, 0, sizeof(servo303SP));
      memset(servo304SP, 0, sizeof(servo304SP));
      memset(servo305SP, 0, sizeof(servo305SP));
      memset(servo306SP, 0, sizeof(servo306SP));
      index = 0;  // Index to 0
    }
  }
if(test){
  
Serial.println(minvalue(redPW,greenPW,bluePW));      
      if(minvalue(redPW,greenPW,bluePW)=="red")
test=      runservo(servo101SP, servo102SP, servo103SP, servo104SP, servo105SP, servo106SP);
       else if(minvalue(redPW,greenPW,bluePW)=="blue")
     test= runservo(servo201SP, servo202SP, servo203SP, servo204SP, servo205SP, servo206SP);
      else test= runservo(servo301SP, servo302SP, servo303SP, servo304SP, servo305SP, servo306SP);
}
  
}

// Automatic mode custom function - run the saved steps
int runservo(byte servo01SP[],byte servo02SP[],byte servo03SP[],byte servo04SP[],byte servo05SP[],byte servo06SP[]) {
  //while ((dataIn != "RESET BLUE")&&(dataIn != "RESET RED")&&(dataIn != "RESET GREEN")) {   // Run the steps over and over again until "RESET" button is 
int x;
    for (int i = 0; i <= index - 2; i++) {  // Run through all steps(index)
      if (Serial.available() > 0) {      // Check for incomding data
        dataIn =Serial.readString();
        if ( dataIn == "PAUSE") {           // If button "PAUSE" is pressed
          while (dataIn != "RUN") {         // Wait until "RUN" is pressed again
            if (Serial.available() > 0) {
              dataIn = Serial.readString();
              if ( (dataIn == "RESET BLUE")||(dataIn == "RESET RED")||(dataIn == "RESET GREEN")) {     
                Serial.println("reeeeset*-*");                 
                x=0;
                return x;
                break;
              }
            }
          }
        }
        // If speed slider is changed
        if (dataIn.startsWith("ss")) {
          String dataInS = dataIn.substring(2, dataIn.length());
          speedDelay = dataInS.toInt(); // Change servo speed (delay time)
        }
      }
      // Servo 1
      if (servo01SP == servo01SP[i + 1]) {
      }
      if (servo01SP[i] > servo01SP[i + 1]) {
        for ( int j = servo01SP[i]; j >= servo01SP[i + 1]; j--) {
          servo01.write(j);
          delay(speedDelay);
        }
      }
      if (servo01SP[i] < servo01SP[i + 1]) {
        for ( int j = servo01SP[i]; j <= servo01SP[i + 1]; j++) {
          servo01.write(j);
          delay(speedDelay);
        }
      }

      // Servo 2
      if (servo02SP[i] == servo02SP[i + 1]) {
      }
      if (servo02SP[i] > servo02SP[i + 1]) {
        for ( int j = servo02SP[i]; j >= servo02SP[i + 1]; j--) {
          servo02.write(j);
          delay(speedDelay);
        }
      }
      if (servo02SP[i] < servo02SP[i + 1]) {
        for ( int j = servo02SP[i]; j <= servo02SP[i + 1]; j++) {
          servo02.write(j);
          delay(speedDelay);
        }
      }

      // Servo 3
      if (servo03SP[i] == servo03SP[i + 1]) {
      }
      if (servo03SP[i] > servo03SP[i + 1]) {
        for ( int j = servo03SP[i]; j >= servo03SP[i + 1]; j--) {
          servo03.write(j);
          delay(speedDelay);
        }
      }
      if (servo03SP[i] < servo03SP[i + 1]) {
        for ( int j = servo03SP[i]; j <= servo03SP[i + 1]; j++) {
          servo03.write(j);
          delay(speedDelay);
        }
      }

      // Servo 4
      if (servo04SP[i] == servo04SP[i + 1]) {
      }
      if (servo04SP[i] > servo04SP[i + 1]) {
        for ( int j = servo04SP[i]; j >= servo04SP[i + 1]; j--) {
          servo04.write(j);
          delay(speedDelay);
        }
      }
      if (servo04SP[i] < servo04SP[i + 1]) {
        for ( int j = servo04SP[i]; j <= servo04SP[i + 1]; j++) {
          servo04.write(j);
          delay(speedDelay);
        }
      }

      // Servo 5
      if (servo05SP[i] == servo05SP[i + 1]) {
      }
      if (servo05SP[i] > servo05SP[i + 1]) {
        for ( int j = servo05SP[i]; j >= servo05SP[i + 1]; j--) {
          servo05.write(j);
          delay(speedDelay);
        }
      }
      if (servo05SP[i] < servo05SP[i + 1]) {
        for ( int j = servo05SP[i]; j <= servo05SP[i + 1]; j++) {
          servo05.write(j);
          delay(speedDelay);
        }
      }

      // Servo 6
      if (servo06SP[i] == servo06SP[i + 1]) {
      }
      if (servo06SP[i] > servo06SP[i + 1]) {
        for ( int j = servo06SP[i]; j >= servo06SP[i + 1]; j--) {
          servo06.write(j);
          delay(speedDelay);
        }
      }
      if (servo06SP[i] < servo06SP[i + 1]) {
        for ( int j = servo06SP[i]; j <= servo06SP[i + 1]; j++) {
          servo06.write(j);
          delay(speedDelay);
        }
      }
    }
  //}
  x=1;
  return x;
}
String minvalue(int num1,int num2,int num3){
  if(num1 < num2 && num1 < num3)
  {
    return "red";
  }
  else if(num2 < num3)
  {
    return "green";
  }
  else
  {
    return "blue";
  }
  }

// Function to read Red Pulse Widths
int getRedPW() {
  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}
