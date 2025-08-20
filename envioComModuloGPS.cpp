#include <TinyGPSPlus.h>
#include <SoftwareSerial.h> // Para Arduino Uno/Nano

// --- Configuração dos pinos seriais ---
// Se estiver usando Arduino Uno, use SoftwareSerial
static const int RXPin = 4, TXPin = 5; // Pinos 4 e 5 para o GPS
static const uint32_t GPSBaud = 9600;  // Velocidade de comunicação padrão do GPS

// Se estiver usando ESP32, você pode usar uma serial de hardware
// static const int RXPin = 16, TXPin = 17;
// static const uint32_t GPSBaud = 9600;
// #define GPS_SERIAL Serial2 // Use a Serial2 do ESP32

// A TinyGPS++ usa a serial para se comunicar com o módulo
// Se for ESP32, use GPS_SERIAL. Se for Uno, use gpsSerial
SoftwareSerial gpsSerial(RXPin, TXPin);
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200); // Inicia a comunicação com o PC para ver os dados
  
  Serial.print("Iniciando...");
  
  // Inicia a serial para comunicação com o módulo GPS
  gpsSerial.begin(GPSBaud);
  // GPS_SERIAL.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin); // Se for ESP32
  
  Serial.println("Pronto para receber dados do GPS.");
}

void loop() {
  // Esta função lê e processa os dados recebidos do GPS
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      // Quando um novo pacote de dados completo é recebido, mostra as informações
      displayInfo();
    }
  }

  // Verifica se o GPS está inativo por muito tempo
  // Isso pode indicar um problema de conexão
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(F("Nenhum dado do GPS recebido. Verifique as conexões e a antena."));
    while(true);
  }
}

void displayInfo() {
  Serial.println();
  
  if (gps.location.isValid()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
  } else {
    Serial.println("Localizacao invalida!");
  }

  // Você pode pegar outras informações também
  if (gps.altitude.isValid()) {
    Serial.print("Altitude (m): ");
    Serial.println(gps.altitude.meters());
  }

  if (gps.satellites.isValid()) {
    Serial.print("Numero de satelites: ");
    Serial.println(gps.satellites.value());
  }

  Serial.println();
}