/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AV 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Dev: Diego Emanuel Yos Pinzon
   link HitHub: 
   
*/

#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define direccion_lcd 0x27

LiquidCrystal_I2C LCD_PF(direccion_lcd, 16, 2);
Servo servo_1;

const int filas = 2;
const int columnas = 3;
char keys[filas][columnas] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
};
byte pinesFila[filas] = {13, 12};
byte pinesColumna[columnas] = {10, 9, 8};
Keypad teclado = Keypad(makeKeymap(keys), pinesFila, pinesColumna, filas, columnas);

char teclaPresionada;

int tiempo = 100;
const int pinesLeds[] = {14, 15, 16, 17};
const int pinesDisplay[] = {7, 6, 5, 4, 3, 2, 1};

void setup() {
  servo_1.attach(11);
  servo_1.write(0);

  LCD_PF.init();
  LCD_PF.backlight();
  LCD_PF.clear();
  LCD_PF.setCursor(5, 0);
  LCD_PF.print("Diego");
  LCD_PF.setCursor(1, 1);
  LCD_PF.print("Proyecto Final");

  for (int i = 0; i < 4; i++) {
    pinMode(pinesLeds[i], OUTPUT);
  }
  for (int i = 0; i < 7; i++) {
    pinMode(pinesDisplay[i], OUTPUT);
  }
}

void loop() {
  teclaPresionada = teclado.getKey();
  switch (teclaPresionada) {
    case '1':
      Serial.begin(9600);
      Serial.println("contador de 0 a 99;");
      for (int i = 0; i < 100; i++) {
        Serial.println(i);
        delay(tiempo);
      }
      Serial.end();
      break;

    case '2':
      Serial.begin(9600);
      Serial.println("contador de 99 a 0;");
      for (int i = 99; i >= 0; i--) {
        Serial.println(i);
        delay(tiempo);
      }
      Serial.end();
      break;

    case '3':
      for (int led = 0; led < 3; led++) {
        digitalWrite(pinesLeds[led], HIGH);
        delay(tiempo);
        if (led + 1 < 4) {
          digitalWrite(pinesLeds[led + 1], HIGH);
          delay(tiempo);
          digitalWrite(pinesLeds[led], LOW);
          delay(tiempo);
        }
      }
      for (int led = 3; led > 0; led--) {
        digitalWrite(pinesLeds[led], HIGH);
        delay(tiempo);
        digitalWrite(pinesLeds[led - 1], HIGH);
        delay(tiempo);
        digitalWrite(pinesLeds[led], LOW);
        delay(tiempo);
      }
      digitalWrite(14, LOW);
      break;

    case '4':
      delay(1000);
      animacionDisplay();
      break;

    case '5':
      delay(tiempo);
      servo_1.write(180);
      delay(5000);
      servo_1.write(0);
      break;
  }
}

void animacionDisplay() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(pinesDisplay[0], HIGH);
    digitalWrite(pinesDisplay[2], HIGH);
    digitalWrite(pinesDisplay[3], HIGH);
    digitalWrite(pinesDisplay[5], HIGH);
    delay(tiempo);
    apagarDisplay();
    delay(tiempo);
  }
}

void apagarDisplay() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(pinesDisplay[i], LOW);
  }
}

