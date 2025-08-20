#include <WiFi.h> // Para ESP32
//#include <ESP8266WiFi.h> // Se estiver usando ESP8266, use esta linha em vez da de cima
#include <PubSubClient.h>

// Dados da sua rede Wi-Fi
const char* ssid = "SEU_SSID";
const char* password = "SUA_SENHA";

// Dados do Broker MQTT Maquiatto
const char* mqtt_server = "MAQUIATTO_BROKER.com"; // Exemplo: "test.mosquitto.org"
const char* mqtt_user = "MAQUIATTO_USER";
const char* mqtt_password = "MAQUIATTO_PASSWORD";
const int mqtt_port = 1883; // Porta padrão do MQTT

// Tópico para publicar os dados
const char* mqtt_topic = "dispositivo/localizacao";

WiFiClient espClient;
PubSubClient client(espClient);

// Protótipos das funções
void setup_wifi();
void reconnect();

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  // Não precisamos de um callback de mensagem recebida se só vamos publicar
  // client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Dados de latitude e longitude (valores de exemplo)
  float latitude = -23.550520; // São Paulo
  float longitude = -46.633308;
  
  // Cria a string do JSON para enviar
  String payload = "{\"latitude\":" + String(latitude, 6) + ",\"longitude\":" + String(longitude, 6) + "}";

  // Publica a mensagem no tópico com QoS=1
  if (client.publish(mqtt_topic, payload.c_str(), false)) {
    Serial.println("Mensagem publicada com sucesso:");
    Serial.println(payload);
  } else {
    Serial.println("Falha ao publicar a mensagem.");
  }

  delay(5000); // Envia os dados a cada 5 segundos
}

// Função para conectar ao Wi-Fi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

// Função para reconectar ao broker MQTT
void reconnect() {
  // Loop até estar reconectado
  while (!client.connected()) {
    Serial.print("Tentando conectar ao broker MQTT...");
    // Tenta se conectar usando o ID do cliente, usuário e senha
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("conectado!");
    } else {
      Serial.print("falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      // Espera 5 segundos antes de tentar novamente
      delay(5000);
    }
  }
}