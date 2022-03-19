#include<LiquidCrystal.h>
LiquidCrystal lcd(11,12,5,4,3,2);
long pwm;
float temperatura;
float T3;
float T2;
int L;
float Temp;
float T;
int corrientemotor;
float V;
void setup()
{102
Serial.begin(9600);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(10,OUTPUT);
pinMode(9,INPUT);
digitalWrite(10,0);
lcd.begin(16,2);
L=0;
lcd.setCursor(5,0);
lcd.print("BOREAS");
delay(2000);
lcd.setCursor(4,1);
lcd.print("wellcome");
delay(5000);
}
void loop()
{
digitalWrite(7,LOW);
digitalWrite(8,LOW);
pwm=0;
lcd.setCursor(0,0);
lcd.print("Fix Temperature");
Temp=analogRead(A3); //Lee la perilla para seleccionar la temperatura
Serial.print(Temp);
T=(Temp*5/1024);
T=0.2177*Temp+77;
lcd.setCursor(0,1);103
lcd.print("Temp is "+String(T,0)+" K");
if (digitalRead(9)==HIGH) // inicial el control cuando se presiona el
pulsador
{
T3=analogRead(A0);
Serial.print(T3);
T3=((((T3*5)/1024)/51)*2837); //considera corriente de 3.5mA y gananacia
de 51.3
T2=2.5452*T3-15.171; // ecuación de calibración del sensor RTD propia
lcd.clear();
lcd.setCursor(0,0);
lcd.print(" R is: "+String(T3,2)); //muestra la resisitencia del sensor
lcd.setCursor(0,1);
lcd.print("Temp is "+String(T2,1)+"K"); //muestra la temepratura
correspondiente
delay (2000);
if (T<T2-1.5 && T2+1.5<T) //define si enciende o no el calefactor
{
V=voltaje(T,T2); // va a la función que calcula la señal de control
según la tmeepratura
lcd.clear();
lcd.setCursor(0,0);
lcd.print("volt is "+String(V,2)+" V"); // muestra la señal de control
calculada
pwm=(V*12)/1024;
analogWrite(6,pwm); // activa el controlador
delay (20000);
}
else104
{
pwm=0; // inactiva el controlador
analogWrite(6,pwm);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("cooling");
delay(2000);
}
}
}
float voltaje(float x, float y)
{
int i;
int j;
float q2;
i=int((y)-70)/10;
Serial.println(i);
Serial.print(x);
j=(int(x)-70)/10;
Serial.println(j);
float q=0;
float L;
float
H[24]={175.407,208.241,236.062,259.236,278.441,294.410,307.815,319.218,329.0
72,337.723,345.431,352.384,358.713,364.506,369.813,374.662,379.057,382.990,3
86.441,389.381,391.778,393.597,394.803,395.361};
// vector para calcular el calor especifico del cobre
float
S[23]={603.558,529.277,486.980,461.549,445.467,434.809,427.428,422.098,418.0105
94,414.969,412.445,410.341,408.536,406.952,405.533,404.240,403.046,401.932,4
00.884,399.890,398.942,398.035,396.324};
//vector para calcular la conductividad térmica del cobre
if (j>i)
{
for (int i;i<=j;i=i+1)
{
q=H[i]*10+q; // calculo de la integral del calor especifico
Serial.println(q);
Serial.println(i);
}
for (int i;i<=j;i=i+1)
{
q2=S[i]*10+q2;// calculo de la integral de la conductividad térmica
Serial.println(q);
Serial.println(i);
}
//L=q;
L=sqrt(9*((q/419.6)+(q2/27.6))); //calculo de la señal del controlador
return L;
}
else // en caso de que la temepratura sensada es mayor que la referencia
no enciende el calefactor
{
L=0;
return L;
}
}