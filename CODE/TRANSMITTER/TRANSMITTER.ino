#include"lcd.h"
#include"dht11.h"
#ifndef SOFT_H
#define SOFT_H

#include<SoftwareSerial.h>
SoftwareSerial ss(A0, A1);
#endif

DHT dht;
#define t_pin 4
#define heart_pin 5
#define nir_pin 6
#define VIB_pin 7
#define P1 8
#define P2 9


int temp;
int G_i, G_i1;
int HR = 0;
int NIR = 0;

String sensorValue1 = "";
int count;

void setup() {
  
  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.setCursor(0, 0);
  lcd.print(" SOIL DATA");
  ss.begin(9600);
  pinMode(heart_pin, INPUT);
  pinMode(nir_pin, INPUT);
  pinMode(VIB_pin, INPUT);
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  delay(1000);
}

void loop() {
  heart();
  nir();
  if (G_i != 0 && G_i1 != 120)
  {
    HR = G_i;
  }
  if (G_i1 != 0 && G_i1 != 180)
  {
    NIR = G_i1;
  }
  dht.dht_read(t_pin);
  int temp1 = dht.temperature;
  temp = (temp1 * 1.8) + 32;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:" + String(temp));
  lcd.setCursor(0, 1);
  lcd.print("GL:");
  lcd.setCursor(3, 1);
  lcd.print(String(NIR));
  lcd.setCursor(8, 0);
  lcd.print("HR:" );
  lcd.setCursor(11, 0);
  lcd.print(String(HR));
  if (digitalRead(VIB_pin) == 0)
  {
    iot_serial("*EARTHQUAKE OCCURED#");
  }
  if (digitalRead(P1) == 0)
  {
    iot_serial("*EMERGENCY #");
  }
  if (digitalRead(P2) == 0)
  {
    iot_serial("*NEED OXYGEN#");
  }
  if (count % 10 == 0)
  {
    iot_serial("@" + String(temp) + "#" + "%" + String(HR) + "#" + "$" + String(NIR) + "#");
  }
  count++;
  if (Serial.available() > 0)
  {
    char inchar = Serial.read();
    if (inchar == '*') {
      while (Serial.available() > 0)
      {
        char t = Serial.read();
        if (t == '#') {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(sensorValue1);
          iot_serial("*" + sensorValue1 + "#");
          sensorValue1 = "";
          break;
        }
        sensorValue1 += t;
      }
    }

  }
  delay(1000);
}
void heart(void)
{
  int j = 120;
  int i = 0;
  while (j > 0)
  {
    if (digitalRead(heart_pin) == LOW)
      i++;
    j--;
    delay(14);
  }
  G_i = i;
}
void nir(void)
{
  int k = 180;
  int l = 0;
  while (k > 0)
  {
    if (digitalRead(nir_pin) == LOW)
      l++;
    k--;
    delay(14);
  }
  G_i1 = l;
}

void iot_serial(String s)
{
  for (int i = 0; i < s.length(); i++)
  {
    Serial.write(s[i]);
  }
  delay(2000);
}
void py_serial(String p)
{
  for (int i = 0; i < p.length(); i++)
  {
    ss.write(p[i]);
  }
  delay(3000);
}
