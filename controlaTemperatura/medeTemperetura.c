#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include "DS18B20.h"  // Biblioteca para o sensor

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

DS18B20 sensor(4);  // Pino D4 do ESP32

void setup() {
  Serial.begin(115200);
  BLEDevice::init("MonitorPicolé");
  BLEServer *server = BLEDevice::createServer();
  BLEService *service = server->createService(SERVICE_UUID);
  BLECharacteristic *characteristic = service->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
  );
  service->start();
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID);
  advertising->start();
}

void loop() {
  float temp = sensor.readTempC();
  Serial.println("Temperatura: " + String(temp) + "°C");
  
  if (temp > -10.0) {  // Alerta se acima de -10°C
    Serial.println("ALERTA: Picolé descongelando!");
    // Enviar notificação via BLE ou Wi-Fi
  }
  delay(5000);  // Verifica a cada 5 segundos
}