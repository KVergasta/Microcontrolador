#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 2        // Pino de sinal do sensor
#define DHTTYPE DHT22   // Tipo do sensor (DHT11 ou DHT22)

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  lcd.print("Monitorando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    lcd.setCursor(0, 0);
    lcd.print("Erro no sensor!");
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");

  if (temp > -5.0) {
    lcd.setCursor(0, 1);
    lcd.print("Alerta! Verifique.");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Status: OK        ");
  }

  delay(3000);
}
