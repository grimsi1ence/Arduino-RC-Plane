#include <Servo.h>
int joy = A3;
Servo motor;
int mot_pin = 9;//Подключаем левый мотор к пину 9
int nach = 1500;//Начальная позиция, всегда 1.5 мс для регуляторов бесколлекторных двигателей
void setup() {
  pinMode(joy,INPUT);
  motor.attach(mot_pin, nach, 2300);//Максимальное значение ШИМ 2.3 мс
  Serial.begin(9600);}

void loop() {
  nach = analogRead(joy);
  nach = map(nach,0,1023,10,130);
  Serial.println(nach);
  motor.write(nach);
  delay(20);
}
