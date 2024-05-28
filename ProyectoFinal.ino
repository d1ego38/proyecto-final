#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

#define f1_teclado 2
#define f2_teclado 3
#define f3_teclado 4
#define f4_teclado 5
#define c1_teclado 6
#define c2_teclado 7
#define c3_teclado 8
#define c4_teclado 9

#define filas_teclado 4
#define columnas_teclado 4

char keys[filas_teclado][columnas_teclado] = {
  {'1', '2', '3', '4'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[filas_teclado] = {f1_teclado, f2_teclado, f3_teclado, f4_teclado};
byte colPins[columnas_teclado] = {c1_teclado, c2_teclado, c3_teclado, c4_teclado};

Keypad teclado = Keypad(makeKeymap(keys), rowPins, colPins, filas_teclado, columnas_teclado);
Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define servoPin 10
#define LED1 A2
#define LED2 A3
#define LED3 A4
#define LED4 A5

#define CI1 1
#define CI2 2
#define CI3 3
#define CI4 4

int contador = 0;
bool contando = false;
bool decrementando = false;
bool animacion = false;
bool contadorDisplay = false;
char ultimaTecla = NO_KEY;

void setup() {
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(CI1, OUTPUT);
  pinMode(CI2, OUTPUT);
  pinMode(CI3, OUTPUT);
  pinMode(CI4, OUTPUT);

  myservo.attach(servoPin);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("    Diego Yos    ");
  lcd.setCursor(0, 1);
  lcd.print("Proyecto Final");

  Serial.println("Presione '1' para iniciar el contador ascendente.");
  Serial.println("Presione '2' para iniciar el contador descendente.");
  Serial.println("Presione '3' para iniciar la animación del auto fantástico.");
  Serial.println("Presione '4' para iniciar el contador de 0 a 9 en el display.");
  Serial.println("Presione '5' para mover el servomotor de 0 a 180 grados.");
}

void loop() {
  char tecla = teclado.getKey();

  if (tecla != NO_KEY) {
    if (tecla == '1') {
      Serial.println("Contador ascendente iniciado.");
      for (int i = 0; i <= 99; i++) {
        Serial.println(i);
        delay(200);
      }
    }

    if (tecla == '2') {
      Serial.println("Contador descendente iniciado.");
      for (int i = 99; i >= 0; i--) {
        Serial.println(i);
        delay(200);
      }
    }

    if (tecla == '3') {
      Serial.println("Animación del auto fantástico iniciada.");
      for (int i = 0; i < 4; i++) {
        digitalWrite(LED1 + i, HIGH);
        delay(200);
        digitalWrite(LED1 + i, LOW);
      }
    }

    if (tecla == '4') {
      Serial.println("Animacion");
      digitalWrite(CI1, LOW);
      digitalWrite(CI2, LOW);
      digitalWrite(CI3, LOW);
      digitalWrite(CI4, HIGH);
      delay(500);
    }

    if (tecla == '5') {
      Serial.println("Movimiento del servomotor iniciado.");
      myservo.write(0);
      delay(1000);
      myservo.write(180);
      delay(1000);
    }
  }
}
