#include <Servo.h>

Servo myservo;

int i;
int value;

int IN1 = 4;
int IN2 = 5; 
int IN3 = 6;
int IN4 = 7;
int TRIG=3;
int ECHO=2;
double duration=0;
double distance=0;
double speed_of_sound = 331.5 +0.6 * 25;
//外部関数



void DC_motor_a(){
//前進

  digitalWrite(IN1, HIGH); //モーター1:正転
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, HIGH); //モーター２：反転
  digitalWrite(IN3, LOW);
  delay(20);
}



void DC_motor_s(){
//停止

digitalWrite(IN1,LOW);  //停止(惰性回転)
digitalWrite(IN2,LOW);
digitalWrite(IN4,LOW); //停止(惰性回転)
digitalWrite(IN3,LOW);
delay(2000);  //移動距離は電圧出力時間に比例する
}



void DC_motor_b(){
//停止

digitalWrite(IN1,LOW); //モーター１：逆転
digitalWrite(IN2,HIGH);
digitalWrite(IN4,LOW); //モーター２：正転
digitalWrite(IN3,HIGH);
delay(2000);
}


void servo_0(){
  myservo.write(0);
}


void servo_90(){
myservo.write(90);
}


void sensor_A(){
  value = analogRead(A0); 
  Serial.print("Data1=");
  Serial.print(value);
  Serial.print(", ");
}




void sensor_B(){
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW); 
  duration= pulseIn (ECHO, HIGH);

if(duration > 0){
  duration = duration/2;
  distance = duration*speed_of_sound*100/1000000;
  Serial.print("Data2=");
  Serial.println(distance);
}

}



void setup() {

Serial.begin(9600); 
myservo.attach(9,1000,20000); 
servo_0();

pinMode(ECHO, INPUT); 
pinMode(TRIG, OUTPUT); 
pinMode(IN1, OUTPUT); 
pinMode(IN2, OUTPUT); 
pinMode(IN3, OUTPUT); 
pinMode(IN4, OUTPUT);

}



//メインプログラム
void loop() {
  for (int i = 0; i <= 100; i++) {

    DC_motor_a(); //ロボット前進
    sensor_A(); //赤外反射センサー検知
    sensor_B();//超音波距離センサー検知

    if(distance <=20){ // ポールに近づき, sensor_B(); で検出した値 (distance)が20以下になったら、

      DC_motor_s();// ロボット停止
      servo_90();// RCサーボを90度する
      break;// for 分から出る

    }

}

for (int i = 0; i <= 100; i++) {
 
  DC_motor_b(); //ロボット後退
  sensor_A(); //赤外反射センサー検知
  sensor_B();//超音波距離センサー検知

  if(value >=250){ // 黒いテープに近づき, sensor_A(0; で検出した値 (value)が250以上になったら、

    DC_motor_s();// ロボット停止
    servo_0(); // RCサーボを0度する
    break; // for 分から出る

  }

}

exit(0); //プログラム停止

}