#include <ESP32Servo.h>
#include <LiquidCrystal.h>

#define BOTAO 6

Servo servo;

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

const int servoPin = 26;
int pos;

bool direcao = false;
bool botaoEstadoAtual;
bool botaoEstadoAnterior = HIGH;

void setup() {
  servo.attach(servoPin, 500, 2400);
  
  lcd.begin(16, 2);

  pinMode(BOTAO, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  botaoEstadoAtual = digitalRead(BOTAO);

  if (botaoEstadoAtual == LOW && botaoEstadoAnterior == HIGH) {
    direcao = !direcao;
    lcd.clear();

    if (direcao == 1) {
      lcd.print("Girando para");
      lcd.setCursor(0, 1);
      lcd.print("direita");
    } else {
      lcd.print("Girando para");
      lcd.setCursor(0, 1);
      lcd.print("esquerda");
    }
    delay(200);
  }

  botaoEstadoAnterior = botaoEstadoAtual;

  if (direcao == true) {
    if (pos < 180) {
      pos++;
      servo.write(pos);
      delay(15);
    }
  } else {
    if (pos > 0) {
      pos--;
      servo.write(pos);
      delay(15);
    }
  }
}
