#include<SoftwareSerial.h>
#define Rx 6  // for uno reciever
#define Tx 7  // for uno transmitter
#define trig 13 // altrasonic pin
#define echo 12 // altrasonic pin
SoftwareSerial bls(Rx, Tx);
void setup() {
  // altrasonic setup
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  // bluetooth setup
  Serial.begin(9600);
  pinMode(Rx, INPUT);
  pinMode(Tx, OUTPUT);
  setupBlueToothConnection();
  Serial.println("Start");

  // pin setup for motors
    // first motor
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
    // first second
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
    // first third
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
    // first forth
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  while(getAltrasonicDistance() > 60){
  int input;
  if (bls.available())
  {
    input = bls.read();
    //input = input - 128;
    Serial.println(input);
    if (input == 1) // forward
    { 
      moveForward();
    }
    if (input == 2) // right
    {
      moveLeft();
    }
    if (input == 3) //left
    {
      moveRight();
    }
    if (input == 4) //backword
    {
      moveBackward();
    }
    if (input == 5) //stop
    {
      stopCar();
    }
  }  
  if(getAltrasonicDistance() < 60){
    stopCar();
  }
}
}

void moveForward() {
  // first motor
  digitalWrite(2,1);
  digitalWrite(3,0);
  // second motor
  digitalWrite(4,1);
  digitalWrite(5,0);
  // third motor
  digitalWrite(8,1);
  digitalWrite(9,0);
  // forth motor
  digitalWrite(10,1);
  digitalWrite(11,0); 
}

void moveBackward() {
  // first motor
  digitalWrite(2,0);
  digitalWrite(3,1);
  // second motor
  digitalWrite(4,0);
  digitalWrite(5,1);
  // third motor
  digitalWrite(8,0);
  digitalWrite(9,1);
  // forth motor
  digitalWrite(10,0);
  digitalWrite(11,1);
}

void moveRight() {
  //first and second motors will move backward
  // first motor
  digitalWrite(2,0);
  digitalWrite(3,1);
  // second motor
  digitalWrite(4,0);
  digitalWrite(5,1);
  //third and forth motors will move forward
  // third motor
  digitalWrite(8,1);
  digitalWrite(9,0);
  // forth motor
  digitalWrite(10,1);
  digitalWrite(11,0);
}

void moveLeft() {
  //first and second motors will move forward
  // first motor
  digitalWrite(2,1);
  digitalWrite(3,0);
  // second motor
  digitalWrite(4,1);
  digitalWrite(5,0);
  //third and forth motors will move backward
  // third motor
  digitalWrite(8,0);
  digitalWrite(9,1);
  // forth motor
  digitalWrite(10,0);
  digitalWrite(11,1);
}


void stopCar() {
  // first motor
  digitalWrite(2,0);
  digitalWrite(3,0);
  // second motor
  digitalWrite(4,0);
  digitalWrite(5,0);
  // third motor
  digitalWrite(8,0);
  digitalWrite(9,0);
  // forth motor
  digitalWrite(10,0);
  digitalWrite(11,0);
}

int getAltrasonicDistance(){
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);  
  delayMicroseconds(10);
  digitalWrite(trig,LOW);   
  float time = pulseIn(echo,HIGH); // tol mahya 1 27sb 23dt w2t ad a
  float distance = time/58; // 58 is the altrasonic velocity   v=340 m/sec
  Serial.println(distance);
  return distance;
  //delay(100);
}

void setupBlueToothConnection(){
  bls.begin(9600); //Set BluetoothBee BaudRate to default baud rate 38400
  bls.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in Slave mode
  bls.print("\r\n+STNA=HC-05\r\n"); //set the bluetooth name as "HC-05"
  bls.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  bls.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  delay(2000); // This delay is required.
  bls.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable
  // Serial.println("The slave bluetooth is inquirable!");
  delay(2000); // This delay is required.
  bls.flush();
}

