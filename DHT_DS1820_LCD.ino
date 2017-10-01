#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#define DHT11_PIN 4
#define DHT22_PIN 2
#define DS1820_PIN 3


DHT dht11(DHT11_PIN, DHT11);
DHT dht22(DHT22_PIN, DHT22);
LiquidCrystal_I2C lcd(0x3f, 20,4);
OneWire oneWire(DS1820_PIN); 
DallasTemperature sensors(&oneWire);

void setup()
{
	// initialize the LCD
	lcd.begin();
  dht11.begin();
  dht22.begin();
  sensors.begin();
  lcd.setCursor(0, 0);
  lcd.print("Water Temp:");
  lcd.setCursor(0, 1);
  lcd.print("Air flow Temp:");
  lcd.setCursor(0, 2);
  lcd.print("Ambient Temp:");
  lcd.setCursor(0, 3);
  lcd.print("Ambient Humi:");
}

void loop()
{
	 delay(1000);

  float Ambient_Humi = dht22.readHumidity();
  float Ambient_Temp = dht22.readTemperature();
  float Air_flow_Temp = dht11.readTemperature();;

  // Check if any reads failed and exit early (to try again).
  if (isnan(Ambient_Humi) || isnan(Ambient_Temp)||isnan(Air_flow_Temp) ) {
    //Serial.println("Failed to read from DHT sensor!");
    return;
  }

  sensors.requestTemperatures(); // Send the command to get temperatures
	lcd.setCursor(0, 0);
  lcd.print("Water Temp");
  lcd.print((sensors.getTempCByIndex(0)));
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Air flow Temp");
  lcd.print(Air_flow_Temp);
  lcd.print(" C");
  lcd.setCursor(0, 2);
  lcd.print("Ambient Temp");
  lcd.print(Ambient_Temp);
  lcd.print(" C");
  lcd.setCursor(0, 3);
  lcd.print("Ambient Humi");
  lcd.print(Ambient_Humi);
  lcd.print(" %");

}
