#include <Servo.h>

Servo myservo;

int i;
int value;

int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int TRIG = 3;
int ECHO = 2;
const int bunper_pin = 13;  //赤外線センサーのボタン
const int mech_pin = 12;
double duration = 0;
double distance = 0;
double speed_of_sound = 331.5 + 0.6 * 25;

bool stopFlag = false;

void DC_motor_a() {
  //前進
  digitalWrite(IN1, HIGH);  //モーター1:正転
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, HIGH);  //モーター２：反転
  digitalWrite(IN3, LOW);
  delay(20);
}

void DC_motor_s() {
  //停止
  digitalWrite(IN1, LOW);  //停止(惰性回転)
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);  //停止(惰性回転)
  digitalWrite(IN3, LOW);
  delay(2000);  //移動距離は電圧出力時間に比例する
}

void DC_motor_r() {
  //回転
  digitalWrite(IN1, HIGH);  //モーター１：正転
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);  //モーター２：正転
  digitalWrite(IN3, HIGH);
  delay(20);
}

void DC_motor_rr() {
  //逆回転
  digitalWrite(IN1, LOW);  //モーター１：逆転
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH);  //モーター２：逆転
  digitalWrite(IN3, LOW);
  delay(20);
}

void servo_a1() {  //後から参照、持ち上げる
  for (int j = 0, j <= 720, j++) {
    myservo.write(j);
  }
}

void servo_a2() {  //アームの保持を解除する
  myservo.write();
}

void servo_0() {
  myservo.write(0);
}

void servo_90() {
  myservo.write(90);
}

//void sensor_A() {//out red
//value = analogRead(A0);
//Serial.print("Data1=");
//Serial.print(value);
//Serial.print(", ");
//}

void sensor_echo() {  //echo sensor
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

void setup() {
  Serial.begin(9600);
  myservo.attach(9, 1000, 2000);  // Servoの正しいパルス幅範囲を設定
  servo_0();

  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(, );
}

void loop() {
  if (!stopFlag) {  //StopfFlag変数が真値でない場合は実行する
    for (int i = 0; i <= 100; i++) {
      DC_motor_r();   //ロボット回転
      sensor_A();     //赤外反射センサー検知
      sensor_echo();  //超音波距離センサー検知

      if (distance <= 20) {  // ポールに近づき, sensor_echo(); で検出した値 (distance)が20以下になったら、
        DC_motor_rr();       // ロボット停止
        delay(500);

        if (digitalWrite(bunper_pin == LOW)) {       //servo_a1でオブジェクトをつかんでbunper_pinで検知。
          while (digitalWrite(bunper_pin == LOW)) {  //servo_a1が働いて、bunper_pin==HIGHになるまで。
            servo_a1();
            delay(10);  //mmsec
          }
        } else {  //bunper_pinがLOWになるまでservo_a1を逆転しなければならない
          digitalWrite(bunper_pin == LOW)
        }
        servo_a1(-j);
        servo_a2();
        stopFlag = true;  // ループを停止するフラグを設定
      } 
      else {            //オブジェクト探索
        for (int i = 0; i <= 100; i++) {
          DC_motor_b();   //ロボット回転
          sensor_A();     //赤外反射センサー検知
          sensor_echo();  //超音波距離センサー検知

          if (distance <= 1600) {
            DC_motor_a() {
              if (distance <= 50) {
                DC_motor_s();
                servo_a1();
                if (value >= 250) {  // 黒いテープに近づき, sensor_A() で検出した値 (value)が250以上になったら、
                  DC_motor_s();      // ロボット停止
                  ();         // RCサーボを0度する
                  break;             // for 文から出る
                }
                break;
              }
              break;
            }
          }
          break;  // for 文から出る
        }
      }
      break;  // for 文から出る
    }
  }
}