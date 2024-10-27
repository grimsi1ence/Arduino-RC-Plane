#include <Servo.h>

// Налаштування мотору
Servo motor;
int joyMotorPin = A2;   // Пін для осі лівого джойстика (керування мотором)
int motorPin = 9;       // Пін для мотору
int motorSpeed = 1500;  // Початкове значення для ESC регуляторів

// Налаштування сервоприводів
Servo servoX;           // Сервопривід по осі X
Servo servoY;           // Сервопривід по осі Y
int joystickX = A0;     // Пін для осі X правого джойстика
int joystickY = A1;     // Пін для осі Y правого джойстика

void setup() {
  // Налаштовуємо мотор
  motor.attach(motorPin, 1000, 2300);  // Підключаємо мотор до піна 9 з діапазоном ШІМ від 1 до 2.3 мс

  // Налаштовуємо серво
  servoX.attach(10);  // Пін 10 для серво X
  servoY.attach(11);  // Пін 11 для серво Y

  // Ініціалізуємо серійну комунікацію для моніторингу
  Serial.begin(9600);
}

void loop() {
  // Читаємо значення з лівого джойстика для керування мотором
  int joyMotorValue = analogRead(joyMotorPin);
  motorSpeed = map(joyMotorValue, 0, 1023, 10, 130);
  motor.write(motorSpeed);  // Встановлюємо швидкість мотора

  // Читаємо значення з правого джойстика для керування сервоприводами
  int valX = analogRead(joystickX);
  int valY = analogRead(joystickY);

  // Мапуємо значення на діапазон від 0 до 180 градусів для серво
  int angleX = map(valX, 0, 1023, 0, 180);
  int angleY = map(valY, 0, 1023, 0, 180);

  // Керування серво
  servoX.write(angleX);
  servoY.write(angleY);

  // Вивід у серійний монітор
  Serial.print("Motor Speed: ");
  Serial.print(motorSpeed);
  Serial.print(" | X angle: ");
  Serial.print(angleX);
  Serial.print(" | Y angle: ");
  Serial.println(angleY);

  delay(20);  // Невелика затримка для стабільності
}
