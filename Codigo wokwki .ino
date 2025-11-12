#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>

//Configuraçao de Wi-Fi e MQTT
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;
const char* mqtt_topic = "pfc/sedentario_luz";

//Definição de Pinos
#define DHTPIN 4
#define DHTTYPE DHT22
#define BOTAO_RESET_PIN 12
#define BUZZER_PIN 15
#define LDR_PIN 34

//Variáveis
DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

float temperatura, umidade;
int luminosidade;

unsigned long tempo_sentado = 0;
unsigned long ultimo_update = 0;
unsigned long limite_tempo = 300000; //Alerta p tempo sentado

float limite_temp = 30.0;   // Temperatura alta
float limite_umid = 40.0;   // Umidade baixa

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32_Sedentario")) break;
    delay(1500);
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(BOTAO_RESET_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(200);

  client.setServer(mqtt_server, mqtt_port);
  ultimo_update = millis();
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  unsigned long agora = millis();
  tempo_sentado += (agora - ultimo_update);
  ultimo_update = agora;

  // Reset da contagem do tempo sentado
  if (digitalRead(BOTAO_RESET_PIN) == LOW) {
    tempo_sentado = 0;
    digitalWrite(BUZZER_PIN, LOW);
    delay(300);
  }

  // Leitura de sensores
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();
  if (isnan(temperatura) || isnan(umidade)) {
    temperatura = umidade = 0;
  }
  luminosidade = analogRead(LDR_PIN);

  String alerta_sentado = "";
  String alerta_temp = "";
  String alerta_umid = "";

  if (tempo_sentado >= limite_tempo) {
    alerta_sentado = "Tempo sentado excessivo! Levante-se e movimente-se!";
  }

  if (temperatura > limite_temp) {
    alerta_temp = "Temperatura elevada! Hidrate-se e procure sombra!";
  }

  if (umidade < limite_umid) {
    alerta_umid = "Umidade baixa! O ar pode estar ressecado.";
  }

  // Controle do buzzer - toca se qualquer alerta ocorrer
  if (alerta_sentado != "" || alerta_temp != "" || alerta_umid != "") {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Envio de dados
  static unsigned long lastMsg = 0;
  if (agora - lastMsg > 800) {
    lastMsg = agora;

    String json = "{";
    json += "\"temperatura\":" + String(temperatura, 1) + ",";
    json += "\"umidade\":" + String(umidade, 1) + ",";
    json += "\"tempo_sentado_s\":" + String(tempo_sentado / 1000.0, 1) + ",";
    json += "\"luminosidade_raw\":" + String(luminosidade) + ",";
    json += "\"alerta_sentado\":\"" + alerta_sentado + "\",";
    json += "\"alerta_temperatura\":\"" + alerta_temp + "\",";
    json += "\"alerta_umidade\":\"" + alerta_umid + "\"";
    json += "}";

    client.publish(mqtt_topic, json.c_str());
    Serial.println(json);
  }
}
