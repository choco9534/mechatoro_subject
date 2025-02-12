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
double duration = 0;
double distance = 0;
double speed_of_sound = 331.5 + 0.6 * 25;

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
//  delay(20);
}

void DC_motor_rr() {
  //逆回転
  digitalWrite(IN1, LOW);  //モーター１：逆転
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, LOW);  //モーター２：逆転
  digitalWrite(IN3, HIGH);
//  delay(20);
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
  myservo.attach(9, 1000, 2000); // Servoの正しいパルス幅範囲を設定
  servo_0();

  pinMode(ECHO, INPUT); 
  pinMode(TRIG, OUTPUT); 
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT);
}

//先ずは、テスト。ロボットが探索して近づいて3秒経ったら探索再開。
//この時の走行テストでは、見つけて近づいたら自分でオブジェを除去して全部探索して近づけたら成功。
//次の段階で掴む→持ち上げる→離す→腕を降ろすの動作をさせる。
//最終段階でこれをくっつけて完成

void loop() {
  if (!stopFlag) {
    for (int i = 0; i <= 100; i++) {
      
//      sensor_echo();
//1600は要検討。探索して見つからなかったらその場で回転を続ける

//      DC_motor_rr();
//      delay(50);
//      DC_motor_r(); //ロボット前進
      sensor_A(); //赤外反射センサー検知
      sensor_echo(); //超音波距離センサー検知



//      while(distance <= 60){
//      DC_motor_r();
//        sensor_echo();
//        delay(20);
//        if(distance <= 60){
//          DC_motor_rr();
//          delay(5);
//        }
//      }

        for (int i = 0; i <= 100; i++) {//不採用！！！！！！！！！！！！！！ルンバ形式でつくろう！！！！！！！！！！！！１
          DC_motor_a(); //ロボット後退
          DC_motor_s();
          delay(500);
          sensor_A();

          DC_motor_r();
          delay(100);
          DC_motor_s();
          sensor_A();

          DC_motor_a();
          delay(100);
          DC_motor_s();
          sensor_A();

          DC_motor_rr();
          sensor_A();
          delay(200);
          DC_motor_s();

          DC_motor_r();
          delay(50);
          DC_motor_a();
          delay(100);       

          sensor_A(); //赤外反射センサー検知
          sensor_echo(); //超音波距離センサー検知
          if (distance <= 20) { // ポールに近づき, sensor_echo(); で検出した値 (distance)が20以下になったら、
            DC_motor_s(); // ロボット停止
            //servo_90(); // RCサーボを90度する
            //stopFlag = true; // ループを停止するフラグを設定
            delay(1000);
            DC_motor_r();
             delay(500);
            break; // for 文から出る
           }
//        while(value <= 50) { // 黒いテープに近づき, sensor_A() で検出した値 (value)が250以上になったら、
//          DC_motor_r();
//          delay(100);
//          sensor_A();
//          DC_motor_s(); // ロボット停止
//          servo_0(); // RCサーボを0度する
//          break; // for 文から出る
//      }
  }
    }
  } 
}