/**
   项目名称		：		copper
   程序名称		：		esp8266
   开发板			：		NodeMcu1.0 (ESP12-Model)
   目的				：		通过物联网温湿度计来实践MQTT协议和串口通讯
   作者				：		籽溪
   时间(YYYYMMDD)			:			20210710
*/
#include <Ticker.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
Ticker ticker;
int count = 0;
const char *ssid = "SSID";
const char *passwd = "PASSWORD";
SoftwareSerial RxSerial(2, 5); //设置串口读取信息
char *value;
const char *mqttServer = "test.ranye-iot.net"; //定义MQTT伺服器地址

void tickerCount();
void connectWiFi();
void connectMQTTServer();
void pubMQTTmsg(const char *);

void setup()
{
  Serial.begin(9600);
  RxSerial.begin(9600);
  WiFi.mode(WIFI_STA);
  connectWiFi(); //链接无线网

  mqttClient.setServer(mqttServer, 1883); //设置MQTT参数,端口号1883
  connectMQTTServer();
  ticker.attach(1, tickerCount); //设置计时器,五秒钟发送一次串口信息到MQTT伺服器
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
      mqttClient.loop(); //保持心跳机制
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
  String topicString = "0x2F-HT"; //发布的主题名,主题千万别重复
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