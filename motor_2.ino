#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Налаштування RF24
RF24 radio(7, 8); // CE та CSN піни для nRF24L01
const byte address[6] = "00001"; // Адреса зв'язку

// Налаштування мотору та сервоприводів
Servo motor;
Servo servoX;
Servo servoY;
int motorPin = 9;       // Пін для мотору
int servoXPin = 10;     // Пін для серво X
int servoYPin = 11;     // Пін для серво Y

// Дані для прийому
struct DataPacket {
  int motorSpeed;
  int angleX;
  int angleY;
};
DataPacket data;

void setup() {
  // Ініціалізуємо мотор і серво
  motor.attach(motorPin, 1000, 2300);
  servoX.attach(servoXPin);
  servoY.attach(servoYPin);

  // Ініціалізуємо серійну комунікацію для моніторингу
  Serial.begin(9600);

  // Налаштовуємо радіо
  radio.begin();
  radio.openReadingPipe(0, address); // Відкриваємо канал для читання
  radio.setPALevel(RF24_PA_HIGH);    // Встановлюємо потужність сигналу
  radio.startListening();            // Вмикаємо режим читання
}

void loop() {
  // Перевіряємо, чи прийшли дані з антени
  if (radio.available()) {
    radio.read(&data, sizeof(data)); // Читаємо дані в структуру

    // Керування мотором
    int motorSpeed = map(data.motorSpeed, 0, 1023, 10, 130);
    motor.write(motorSpeed);

    // Керування сервоприводами
    int angleX = map(data.angleX, 0, 1023, 0, 180);
    int angleY = map(data.angleY, 0, 1023, 0, 180);

    servoX.write(angleX);
    servoY.write(angleY);

    // Вивід даних у серійний монітор
    Serial.print("Motor Speed: ");
    Serial.print(motorSpeed);
    Serial.print(" | X angle: ");
    Serial.print(angleX);
    Serial.print(" | Y angle: ");
    Serial.println(angleY);
  }

  delay(20);  // Невелика затримка для стабільності
}
