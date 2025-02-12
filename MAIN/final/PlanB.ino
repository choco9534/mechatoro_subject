#include <Servo.h>
#include <MsTimer2.h>

Servo myservo;

int i;
int value;

int IN1 = 4;
int IN2 = 5; 
int IN3 = 6;
int IN4 = 7;
int TRIG = 3;
int ECHO = 2;
double duration = 0;
double distance = 0;
double speed_of_sound = 331.5 + 0.6 * 25;

bool stopFlag = false;


void DC_motor_a() {
  //前進
  digitalWrite(IN1, HIGH); //モーター1:正転
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, HIGH); //モーター２：反転
  digitalWrite(IN3, LOW);
}

void DC_motor_s() {
  //停止
  digitalWrite(IN1, LOW);  //停止(惰性回転)
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW); //停止(惰性回転)
  digitalWrite(IN3, LOW);
}

void DC_motor_b() {
  //後退
  digitalWrite(IN1, LOW); //モーター１：逆転
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, LOW); //モーター２：正転
  digitalWrite(IN3, HIGH);
}

void DC_motor_r() {
  //回転
  digitalWrite(IN1, HIGH);  //モーター１：正転
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);  //モーター２：正転
  digitalWrite(IN3, HIGH);
}

/*
void servo_0() {
    myservo.write(0);
}

void servo_90() {
  myservo.write(90);
}
*/

void sensor_A() {//out red
  value = analogRead(A0); 
  Serial.print("Data1=");
  Serial.println(value);
}

void flash(){
  sensor_A();
}
/*

void sensor_echo() {//echo sensor
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW); 
  duration = pulseIn(ECHO, HIGH);

  if (duration > 0) {
    duration = duration / 2;
    distance = duration * speed_of_sound * 100 / 1000000;
    Serial.print("Data2=");
    Serial.println(distance);
  }
}
*/

void setup() {
  Serial.begin(9600); 
  myservo.attach(9, 1000, 2000); // Servoの正しいパルス幅範囲を設定
  //servo_0();

  MsTimer2::set(50, flash);
  MsTimer2::start();

  pinMode(ECHO, INPUT); 
  pinMode(TRIG, OUTPUT); 
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT);
}

void loop() {
  if (!stopFlag) {
    
  if(value >= 170){
    DC_motor_a();
  }
  else{
    DC_motor_b();
    delay(1000);
    DC_motor_s();
    delay(1000);
    DC_motor_r();
    delay(1000);
  }
    
  }
}
