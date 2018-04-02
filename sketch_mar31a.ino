//这个程序给 1 2 号舵机使用

#define EN        8       //步进电机使能端，低电平有效
#define X_DIR     5       //X轴 步进电机方向控制
#define Y_DIR     6       //y轴 步进电机方向控制

#define X_STP     2       //x轴 步进控制
#define Y_STP     3       //y轴 步进控制

/*
  //函数：step    功能：控制步进电机方向，步数。
  //参数：dir 方向控制, dirPin对应步进电机的DIR引脚，stepperPin 对应步进电机的step引脚， steps 步进的步数
  //无返回值
*/
void step(boolean dir, byte dirPin, byte stepperPin, int steps)
{
  digitalWrite(dirPin, dir);
  delay(20);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(700);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(700);
  }
}
void setup() { //将步进电机用到的IO管脚设置成输出
  Serial.begin(9600);
  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);
  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);

  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
}
void loop() {

  char x;

  if (Serial.available()) {
    x = Serial.read();

    if (x == '1') {
       step(true, X_DIR, X_STP, 50); //X轴电机 正转1圈，200步为一圈
     
       delayMicroseconds(100);
      step(false, X_DIR, X_STP, 50); //X轴电机 反转1圈，200步为一圈

    }

    if (x == '2') {
      step(false, Y_DIR, Y_STP, 50); //y轴电机 反转1圈，200步为一圈
      delayMicroseconds(100);
      step(true, Y_DIR, Y_STP, 50); //y轴电机 正转1圈，200步为一圈
    }

  }
}
