#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position


const int trig = 6;  
const int echo = 5;    
int tien1 = 10;    
int tien2 = 11;        
int lui1 = 12;        
int lui2 = 13;        
int dongcoservo = 9; 


int gioihan = 25;//khoảng cách nhận biết vật 
int i;
int x = 0;
unsigned long thoigian; 
int khoangcach;          
int khoangcachtrai, khoangcachphai;
int maxspeed=30;

// void convert_analog_map()
// {
//   int tien1_analog = analogRead(tien1_analog);
//   int tien2_analog = analogRead(tien2_analog);
//   int lui1_analog = analogRead(lui1_analog);
//   int lui2_analog = analogRead(lui2_analog);

//   pmwTien1 = map(tien1_analog, 0, 1023, 0, 255);
//   pmwTien2 = map(tien2_analog, 0, 1023, 0, 255);
//   pmwLui1 = map(lui1_analog, 0, 1023, 0, 255);
//   pmwLui1 = map(lui2_analog, 0, 1023, 0, 255)
// }
void dokhoangcach();
void dithang(int duongdi);
void disangtrai();
void disangphai();
void dilui();
void resetdongco();
void quaycbsangphai();
void quaycbsangtrai();
void setup() {
  // put your setup code here, to run once:
  myservo.attach(9); 
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);   

  pinMode(tien1, OUTPUT);
  pinMode(tien2, OUTPUT);
  pinMode(lui1, OUTPUT);
  pinMode(lui2, OUTPUT);
  digitalWrite(tien1, LOW);
  digitalWrite(tien2, LOW);
  digitalWrite(lui1, LOW);
  digitalWrite(lui1, LOW);
  myservo.write(90);
  delay(500);



}
int desiredPoint = 2;
int Kp = 0.1;
int vantocdichuyen = 1; // đây là phần sẽ cài vào trong analogRead(dongco,vantocdichuyen);
int vantoctrungbinh = 100; //! đây là phần sẽ đưa vào các hàm như đi thẳng, đi lùi
void loop()
{
  khoangcach = 0;
  dokhoangcach(); /*!Trả về khoảng cách từ sonar tới vật cản. return khoangcach*/
  if (khoangcach > gioihan || khoangcach == 0)
  {
      dithang(vantoctrungbinh);
  }
  else
  {
    if (khoangcach > 2 && khoangcach < gioihan)
    {
      // nếu vận tốc đang ở 100, mà đùng một cái xuống 10 có sao không? 
      vantocdichuyen = khoangcach*Kp;
      vantoctrungbinh = vantocdichuyen; // Làm thế này tức là mọi nơi động cơ sẽ giảm từ 100 xuống còn 10 (đi chậm hơn)
    }
    resetdongco();
    quaycbsangtrai();
    dokhoangcach();
    khoangcachtrai = khoangcach;
    quaycbsangphai();
    dokhoangcach();
    khoangcachphai = khoangcach;
    if (khoangcachphai < 30 && khoangcachtrai < 30) {
      dilui(vantoctrungbinh);
    }
    else
    {
      if (khoangcachphai >= khoangcachtrai)
      {        
        disangphai(vantoctrungbinh);
        delay(500);
      }
      if (khoangcachphai < khoangcachtrai)
      {
        disangtrai(vantoctrungbinh);
        delay(500);
      }
    }
  }

}
void dithang(int vantoc)
{
  analogWrite(tien1, vantoc);
  analogWrite(tien2, vantoc);
}

void disangphai(int vantoc)
{
  resetdongco();
  analogWrite(lui1, vantoc);
  delay(2000);//thời gian lùi
  analogWrite(lui1, 0);


}
void disangtrai(int vantoc)
{
  resetdongco();
  analogWrite(lui2, vantoc);
  delay(2000);//thời gian 
  analogWrite(lui2, 0);

}

void dilui(int vantoc)
{
  resetdongco();
  for (i = 0; i < 20; i++)
  {
    analogWrite(lui1, vantoc);
    analogWrite(lui2, vantoc);
  }
  
  delay(2000);


  analogWrite(lui1, 0);
  analogWrite(lui2, 0);
}

void resetdongco()
{
  analogWrite(tien1, 0);
  analogWrite(tien2, 0);
  analogWrite(lui1, 0);
  analogWrite(lui2, 0);
}

void dokhoangcach()
{

  digitalWrite(trig, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);  
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); 


  // Đo độ rộng xung HIGH ở chân echo.
  thoigian = pulseIn(echo, HIGH);

  khoangcach = thoigian / 2 / 29.412;

}


void quaycbsangtrai()
{
  myservo.write(180);              // tell servo to go to position in variable 'pos'
  delay(1000);
  dokhoangcach();
  myservo.write(90);              // tell servo to go to position in variable 'pos'
}
void quaycbsangphai()
{
  myservo.write(0);              // tell servo to go to position in variable 'pos'
  delay(1000);
  dokhoangcach();
  myservo.write(90);              // tell servo to go to position in variable 'pos'
}
void resetservo()
{
  myservo.write(90);
}
