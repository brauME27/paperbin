#include <LiquidCrystal.h>
#include <NewPing.h>
#include <Servo.h>
#include<EEPROM.h>
   int distancia;
   int lectura;
   float volt,temp;
   NewPing sonar(7,6); //trigger:7  echo:6
   Servo servoMotor;
   LiquidCrystal lcd(12,11,5,4,3,2);
   //sensor de tiempo
   #include <Wire.h>
   #include "RTClib.h"
   RTC_DS3231 rtc;
   String daysOfTheWeek[7] = { "Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab" };
   String monthsNames[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo",  "Junio", "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre" };
   
void setup() {
   Serial.begin(9600);
   
   servoMotor.attach(9);
   lcd.begin(16,2);

   if (!rtc.begin()) {
      Serial.println(F("Couldn't find RTC"));
      while (1);
   }
   // Si se ha perdido la corriente, fijar fecha y hora
   if (rtc.lostPower()) {
      // Fijar a fecha y hora de compilacion
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   }
 }
 void printDate(DateTime date)
{
  lcd.setCursor(0,0);
   lcd.print(date.year(), DEC);
   lcd.print('/');
   lcd.print(date.month(), DEC);
   lcd.print('/');
   lcd.print(date.day(), DEC);
   lcd.print(" (");
   lcd.print(daysOfTheWeek[date.dayOfTheWeek()]);
   lcd.print(") ");
   lcd.setCursor(0,1);
   lcd.print(date.hour(), DEC);
   lcd.print(':');
   lcd.print(date.minute(), DEC);
   //lcd.print(':');
}
void loop() {
  //programamos el sensor de temperatura
   lectura=analogRead(A0);
   volt=(lectura/1024.0)*5.0;
   temp =(volt)*100*0.96;
   lcd.setCursor(10,1);
   lcd.print(int(temp));
   lcd.print("C");
   delay(1000);
  //programamos el sonar con el servo
  distancia=sonar.ping_cm();
  Serial.println ( distancia);
  servoMotor.write(0);
  
  if(distancia<=15&& distancia >1){
   servoMotor.write(60);
   delay(2000);
   servoMotor.write(0);
  }
  delay (100);
   
   DateTime now = rtc.now();
   printDate(now);
}
