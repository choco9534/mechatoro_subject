#include <Servo.h>
#include <MsTimer2.h>

Servo servo01;
Servo servo02;

int i;
int t;
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
int distances[500];
int angle = 0;

bool stopFlag = false;

void DC_motor_a() {
  //前進
  digitalWrite(IN1, LOW); //モーター1:正転
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH); //モーター２：反転
  digitalWrite(IN3, LOW);
}

void DC_motor_s() {
  //停止
  digitalWrite(IN1, LOW);  //停止(惰性回転)
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW); //停止(惰性回転)
  digitalWrite(IN3, LOW);
  delay(100);  //移動距離は電圧出力時間に比例する
}

void DC_motor_b() {
  //後退
  digitalWrite(IN1, HIGH); //モーター１：逆転
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW); //モーター２：正転
  digitalWrite(IN3, HIGH);
  delay(2000);
}

void DC_motor_r() {
  //回転
  digitalWrite(IN1, HIGH);  //モーター１：正転
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, HIGH);  //モーター２：正転
  digitalWrite(IN3, LOW);
}

void DC_motor_rr() {
  //逆回転
  digitalWrite(IN1, LOW);  //モーター１：逆転
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, LOW);  //モーター２：逆転
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

void servo_tukamu(){
  servo01.write(150);
  delay(10);
}

void servo_hirogeru(){
  servo01.write(30);
  delay(10);
}

void servo_motiageru(){
  servo02.write(150);
  delay(10);
}

void servo_sageru(){
  servo02.write(30);
  delay(10);
}

void sensor_A() {//out red
  value = analogRead(A0); 
  Serial.print("ORed=");
  Serial.print(value);
  Serial.print(" , ");
  if(value <= 80){
    DC_motor_r();
    delay(1500);
  }
}

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
    Serial.print("Echopulse=");
    Serial.println(distance);
  }
}

void action(){//オブジェクトを掴む＿持ち上げる＿放す＿元に戻す
  servo_sageru();
  delay(4000);
  servo_tukamu();
  delay(40000);
  servo_motiageru();
  delay(8000);
  servo_hirogeru();
  delay(3000);
  servo_sageru();
  delay(4000);
}

void flash(){
  sensor_echo();
}

void setup() {
  Serial.begin(9600); 
  servo01.attach(9, 1000, 2000);
  servo02.attach(10, 1000, 2000);
  //servo_0();

  MsTimer2::set(50, flash);
  MsTimer2::start();

  pinMode(ECHO, INPUT); 
  pinMode(TRIG, OUTPUT); 
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT);

  servo_motiageru();
  delay(1000);
  servo_hirogeru();
  delay(800);
}

void loop(){

if(!stopFlag){


    DC_motor_r();
    delay(1000);

    distances[angle] = distance;

    int minDistance = distances[0];
    if(distances[angle] <= 80 && minDistance <= 80){
      if(distances[angle] <= minDistance && distances[angle] >= 0){
        minDistance = distances[angle];
        Serial.println(minDistance);
        //Serial.println("数値を更新しました。");
        DC_motor_s();
        //Serial.println("停止します");
        delay(1000);
        action();
        //Serial.print("実行します");
        while(distance <= minDistance){
          //Serial.println("直進します。");
          DC_motor_a();
          //delay(1000);
          if(distance <= 5){
            DC_motor_s();
            servo_sageru();
            delay(500);
            action();
            break;
          }
        }
        DC_motor_s();
        delay(500);
      }
    }
  }

  //もう一周して、計測した値が誤差含んで同じ値になれば、その方向に進む
    
    
    
    //if(minDistance == distance){
      //DC_motor_s();
      //delay(1000);
    //}


}