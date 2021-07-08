#include <Ticker.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
Ticker ticker;
int count=0;
const char *ssid = "your Wifi name";
const char *passwd = "the password of your wifi";
SoftwareSerial RxSerial(2, 5);
char value[31];
const char *mqttServer = "test.ranye-iot.net";

void setup()
{
  Serial.begin(9600);
  RxSerial.begin(9600);
  WiFi.mode(WIFI_STA);
  connectWiFi();

  mqttClient.setServer(mqttServer, 1883);
  connectMQTTServer();
  ticker.attach(1, tickerCount);
}

void loop()
{
  if (RxSerial.available())
  {
    if (mqttClient.connected())
    {
      if (count >= 5)
      {
        for (int i = 0; i < RxSerial.available(); i++)
        {
          value[i] = RxSerial.read();
        }
        pubMQTTmsg(value);
        count = 0;
      }
      mqttClient.loop();
    }
    else
    {
      connectMQTTServer();
    }
  }
}

void tickerCount()
{
  count++;
}

void connectWiFi()
{
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
}

void connectMQTTServer()
{
  String clientId = "ESP8266-0x2F";

  if (mqttClient.connect(clientId.c_str()))
  {
    Serial.println("MQTT Server Connected.");
    Serial.println("Server Address: ");
    Serial.println(mqttServer);
    Serial.println("ClientId:");
    Serial.println(clientId);
  }
  else
  {
    Serial.print("MQTT Server Connect Failed. Client State:");
    Serial.println(mqttClient.state());
    delay(3000);
  }
}
void pubMQTTmsg(const char *publishMsg)
{
  String topicString = "0x2F-HT";
  char publishTopic[topicString.length() + 1];
  strcpy(publishTopic, topicString.c_str());
  if (mqttClient.publish(publishTopic, publishMsg))
  {
    Serial.println("Successed!");
  }
  else
  {
    Serial.println("Failed.");
  }
}
