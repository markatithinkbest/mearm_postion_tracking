/*
 * 10/19/2015
 * Mark Chen in Caotun, Taiwan
 *
 */

#include <Servo.h>

// === 調試使用 (由於伺服馬達的起始位置不完全相同,可供不同 MeArm 使用)===

int STD_DELAY=12; //連續動作時,每一度的delay, 4很快,12很有機器人的慢節奏
int MOVE_DELAY=50; //一個小動作後的delay


int D90=90;
// 手指
int m1Min=60; //縮
int m1Max=100; //張

// 前後
int m2Min=75; // 後
int m2Max=125; // 前

// 上下
int m3Min=45;  // 下
int m3Max=100; // 上

int m4Min=30; // 順時針
int m4Max=150; // 逆時針

// === 程式底層定義 (共同,不要隨意更動)===
// 4個伺服馬達
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;


// 四個pin腳
// Arduino Senser Sheld 5.0
int m1Pin=3;
int m2Pin=5;
int m3Pin=6;
int m4Pin=9;

int m1Pos=90;
int m2Pos=90;
int m3Pos=90;
int m4Pos=90;

void servoRun(int servoNum,int pos){
  Servo servo;
  int fromPos;
  
  if (servoNum==1){
    servo=servo1;
    fromPos=m1Pos;
    m1Pos=pos;
  }
  if (servoNum==2){
    servo=servo2;
    fromPos=m2Pos;
    m2Pos=pos;
  }
  if (servoNum==3){
    servo=servo3;
    fromPos=m3Pos;
    m3Pos=pos;
}
  if (servoNum==4){
    servo=servo4;
    fromPos=m4Pos;
    m4Pos=pos;
  }  
  servoAct(servo, fromPos, pos);
}


// 給定的伺服馬達,從 m 運動到 n
// 這兩個值的區間是 0 到180
// 但受到手臂結構限制,不能全部運動
// 因此要一個一個調試
void servoAct(Servo servo,int m, int n){
  if (m<n){
    for (int i=m;i<=n;i++){
      servo.write(i*1);
      delay(STD_DELAY);
    }
  }  
  if (m>n){
    for (int i=m;i>=n;i--){
      servo.write(i*1);
      delay(STD_DELAY);
    }
  } 
  delay(MOVE_DELAY);
}


void takeObjLite(){
  servoRun(3,m3Min);//手臂向下  
  servoRun(2,m2Max);//手臂向前
  delay(500); 
  //m1Close(); 
  servoRun(1,m1Min);//
  delay(500); 
  servoRun(2,m2Min); 
  servoRun(3,m3Max);  
}
void putObjLite(){
  servoRun(3,m3Min);//手臂向下  
  servoRun(2,m2Max);//手臂向前
  delay(500); 
  //m1Close(); 
  servoRun(1,m1Max);//
  delay(500); 
  servoRun(2,m2Min); 
  servoRun(3,m3Max);  
}



void wakeup(){
  int temp;
  for (int i=1;i<=4;i++){
    for (int k=1;k<=3;k++){
      temp=k*10;
      servoRun(i,90-temp);
      servoRun(i,90+temp);
    }
  }
  delay(1000);
} 

void initPos(){
  servoRun(1,90);
  servoRun(2,90);
  servoRun(3,90);
  servoRun(4,90);
  delay(1000);
}
void testMin(){
  servoRun(1,m1Min);
  servoRun(2,m2Min);
  servoRun(3,m3Min);
  servoRun(4,m4Min);
  delay(1000);
} 

void testMax(){
  servoRun(1,m1Max);
  servoRun(2,m2Max);
  servoRun(3,m3Max);
  servoRun(4,m4Max);
  delay(1000);
} 

void moveObjFromAtoB(int fromPos, int toPos){
  servoRun(4,fromPos);  
  takeObjLite();  
  servoRun(4,toPos);
  putObjLite();
}

void combo2Lite(){
  moveObjFromAtoB(120, 150);
  moveObjFromAtoB(90, 120);
  moveObjFromAtoB(60, 90);
  moveObjFromAtoB(30, 60);

  moveObjFromAtoB(60, 30);
  moveObjFromAtoB(90, 60);
  moveObjFromAtoB(120, 90);
  moveObjFromAtoB(150, 120);
} 

void setup() {
  // === attach ===
  servo1.attach(m1Pin); // 手爪
  servo2.attach(m2Pin); // 前後
  servo3.attach(m3Pin); // 上下
  servo4.attach(m4Pin); // 底盤

  // === initial movement ===
//  wakeup();   
//  initPos();
//  testMin();
//  initPos();  
//  testMax();
//  initPos();
  initPos();
  combo2Lite();
  delay(1000);
  initPos();
}

void loop() {
  // 另案開發,此處空白
}
