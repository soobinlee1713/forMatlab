#include <EEPROM.h>

#define motor1pole1 8
#define motor1pole2 7
#define enablePin 9
#define motor2pole3 5
#define motor2pole4 4
#define enablePin2 3

int motorSpeed = 100;
char buf[256];

int addr,address= 1;
int sum= 0;
int i,value,average;

void setup()
{
  Serial.begin(9600);
  pinMode(enablePin, OUTPUT); //지정한 핀을 출력 모드로 사용
  pinMode( motor1pole1 , OUTPUT);//지정한 핀을 출력 모드로 사용
  pinMode( motor1pole2, OUTPUT);//지정한 핀을 출력 모드로 사용
  pinMode(enablePin2, OUTPUT); 
  pinMode( motor2pole3 , OUTPUT);//지정한 핀을 출력 모드로 사용
  pinMode( motor2pole4, OUTPUT);//지정한 핀을 출력 모드로 사용
}


void loop()
{
  for(i=0;i<50;i++)
  {
    int val = analogRead(A0);
    EEPROM.write(addr, val);
    addr = addr + 1;
    value = EEPROM.read(address);
    address = address + 1;
    Serial.println("value");
    Serial.println(value, DEC);
    Serial.println("\t");
    sum+=value;
    
  }
  Serial.println("sum");
  Serial.println(sum, DEC);
  Serial.println("\t");
 
  average=sum/50;
  Serial.println("average");
  Serial.println(average, DEC);
  Serial.println("\t");

  if (average >= 100)
  {
    sprintf( buf, "모터 스피드 %d\n", motorSpeed );
    Serial.print(buf);
    analogWrite(enablePin, motorSpeed);
    analogWrite(enablePin2, motorSpeed);

    Serial.println("모터 역방향 회전");
    digitalWrite(motor1pole1, LOW),digitalWrite(motor2pole3,HIGH );
    digitalWrite(motor1pole2, HIGH),digitalWrite(motor2pole4, LOW);
    digitalWrite(motor1pole1, LOW),digitalWrite(motor2pole3,HIGH );
    digitalWrite(motor1pole2, HIGH),digitalWrite(motor2pole4, LOW);
    delay(19000);
   
    Serial.println("모터 정방향 회전");
    digitalWrite(motor1pole1, HIGH),digitalWrite(motor2pole3, LOW);
    digitalWrite(motor1pole2, LOW),digitalWrite(motor2pole4, HIGH);
    digitalWrite(motor1pole1, HIGH),digitalWrite(motor2pole3, LOW);
    digitalWrite(motor1pole2, LOW),digitalWrite(motor2pole4, HIGH);
    delay(6000);

    
    Serial.println("정지");
    digitalWrite(motor1pole1, LOW),digitalWrite(motor2pole3, LOW);
    digitalWrite(motor1pole2, LOW),digitalWrite(motor2pole4, LOW);
    delay(8000);
   
  }
  while(true);
}
