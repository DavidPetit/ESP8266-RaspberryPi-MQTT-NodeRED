#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WEMOS_SHT3X.h>

// Wifi constants
const char* wifi_ssid = "...";
const char* wifi_pass = "...";

// MQTT constants
const char* mqtt_server = "...";
const char* mqtt_topic = "...";
const int mqtt_port = 1883;
boolean retained = true;

// SHT30 object
SHT3X sht30(0x45);

// Wifi client object
WiFiClient espClient;

// PubSub object
PubSubClient client(espClient);

// Callback for mqtt client
void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

// Setup function
void setup() {
  //pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

// Wifi Setup function
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Connect to MQTT broker function
void connect() {
  // Loop until we're connected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client_unit1")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// Loop
void loop() {
 if (!client.connected()) {
     connect();
  }

  sht30.get();

  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject();
  char bufferTemp[10];
  char bufferHum[10];
 
  JSONencoder["device"] = "SHT30#1";
  JSONencoder["temperature"] = sht30.cTemp;
  JSONencoder["humidity"] = sht30.humidity;
 
  char JSONmessageBuffer[100];
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));

  String messageTopic = "Sending message to topic: ";
  messageTopic += mqtt_topic;
  Serial.println(messageTopic);
  Serial.println(JSONmessageBuffer);  
  if (client.publish(mqtt_topic, JSONmessageBuffer) == true) {
    Serial.println("Success sending message");
  } else {
    Serial.println("Error sending message");
  }

  client.loop();
  
  Serial.println();
  delay(10000);
}
