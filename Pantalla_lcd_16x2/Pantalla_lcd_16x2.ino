/*
	Programa que permite mostrar en el modulo LCD la temperatura sensada
  utilizando un sensor PT111 cuya señal ha sido previamente amplificada.

	Autor: Mateo Morales 

*/

#include <LiquidCrystal.h>		// importa libreria
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);	// pines RS, E, D4, D5, D6, D7 de modulo 1602A

int analoginput = 0;
int value = 0;
float vout = 0.0;

void setup() {
  pinMode(analoginput, INPUT)
  lcd.begin(16, 2);			// inicializa a display de 16 columnas y 2 lineas
}

void loop() {
  value = analogRead(analoginput); // Valor de 0 a 1024 sensado por el Arduino
  vout = (value*5.0)/1024.0; // Conersión digital analógica del valor digital sensado

  lcd.setCursor(0, 0);			// ubica cursor en columna 0, linea 0
  lcd.print("DC VOLTAGE");	// escribe el texto en pantalla
  lcd.setCursor(0, 1);			// ubica cursor en columna 0, linea 1
  lcd.print("INPUT V= ");			// imprime INPUT V=
  lcd.print(vout);		// escribe valor de voltaje
  delay(500)
}


