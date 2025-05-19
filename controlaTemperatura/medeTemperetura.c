#include <DHT.h>
#include <LiquidCrystal.h>

// Definições de constantes
#define DHTPIN 2        // Pino de sinal do sensor
#define DHTTYPE DHT22   // Tipo do sensor (DHT22)
#define LCD_COLS 16     // Número de colunas do LCD
#define LCD_ROWS 2      // Número de linhas do LCD
#define UPDATE_INTERVAL 2000  // Intervalo de atualização em ms
#define ALERT_THRESHOLD -5.0  // Limite de temperatura para alerta

// Inicialização dos objetos
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  // Inicializa o LCD
  lcd.begin(LCD_COLS, LCD_ROWS);
  
  // Inicializa o sensor DHT
  dht.begin();
  
  // Mensagem inicial
  lcd.print("Inicializando...");
  delay(1000);
  lcd.clear();
}

void loop() {
  static unsigned long lastUpdate = 0;
  unsigned long currentMillis = millis();
  
  // Verifica se é hora de atualizar a leitura
  if (currentMillis - lastUpdate >= UPDATE_INTERVAL) {
    lastUpdate = currentMillis;
    
    // Lê a temperatura
    float temp = dht.readTemperature();
    
    // Limpa o display
    lcd.clear();
    
    // Verifica se a leitura é válida
    if (isnan(temp)) {
      displayError();
    } else {
      displayTemperature(temp);
      checkTemperatureAlert(temp);
    }
  }
}

void displayTemperature(float temperature) {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);  // Mostra com 1 casa decimal
  lcd.print(" \xDF""C");      // Usa o símbolo de grau
}

void checkTemperatureAlert(float temperature) {
  lcd.setCursor(0, 1);
  if (temperature > ALERT_THRESHOLD) {
    lcd.print("ALERTA! Temp Alta");
  } else {
    lcd.print("Status: Normal   ");
  }
}

void displayError() {
  lcd.setCursor(0, 0);
  lcd.print("Erro na leitura!");
  lcd.setCursor(0, 1);
  lcd.print("Verifique sensor");
}
