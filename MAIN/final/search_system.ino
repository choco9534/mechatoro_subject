#include <Servo.h>

Servo myservo;

int i;
int value;
int t;

int IN1 = 4;
int IN2 = 5; 
int IN3 = 6;
int IN4 = 7;
int TRIG = 3;
int ECHO = 2;

int duration = 0;
int distance = 0;
double speed_of_sound = 331.5 + 0.6 * 25;
int distances[75];

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

void servo_0() {
    myservo.write(0);
}

void servo_90() {
  myservo.write(90);
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

void setup() {
  Serial.begin(9600); 
//  myservo.attach(9, 1000, 2000); // Servoの正しいパルス幅範囲を設定
//  servo_0();

  pinMode(ECHO, INPUT); 
  pinMode(TRIG, OUTPUT); 
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT);
}

int angle;
int minDistance = distances[0];
int j;

void loop(){

if(!stopFlag){
  for(angle = 0; angle <= 75; angle++){
    DC_motor_r();
    sensor_echo();
    distances[angle] = distance;
    delay(50);
  }

  for(j = 1; j <= 75; j++){
    if(distances[j] <= minDistance && minDistance >= 0){
      minDistance = distances[j];
      Serial.println(minDistance);
      Serial.println("数値を更新しました。");
      DC_motor_s();
      delay(100);
      DC_motor_a();
      
    }
  }

  //もう一周して、計測した値が誤差含んで同じ値になれば、その方向に進む
  //for(i = 0; i = 50; i++){
    //DC_motor_r();
    //sensor_echo();
    //if(minDistance == distance){
      //DC_motor_s();
      //delay(1000);
    //}
  //}
}

}