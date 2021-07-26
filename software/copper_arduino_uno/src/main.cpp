/**
  项目名称		:		copper
  程序名称		:		arduino_uno
  MCU		:			Arduino Uno R3
  目的				:		通过物联网温湿度计来实践MQTT协议和串口通讯
  作者				:		籽溪
  时间(YYYYMMDD)			:			20210710
 */
#include <SoftwareSerial.h>
#include <DHT.h>

#define DHTTYPE DHT11 //设置测温模块型号
#define DHTPIN 2      //设置测温模块所在的引脚

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial mySerial(6, 7); //定义到ESP8266的通讯串口

void setup()
{
  Serial.begin(9600);
  Serial.println("MySerial Is Ready");
  mySerial.begin(9600); //串口初始化
  dht.begin();          //测温模块初始化
}
void loop()
{
  delay(1000);
  float humidity = dht.readHumidity(); //浮点数读取温度和湿度
  float temperature = dht.readTemperature();
  if (isnan(humidity) or isnan(temperature))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  } //判断是否成功读取,不成功直接返回
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print(temperature);
  Serial.print(" *C ");
  Serial.println(""); //想电脑发送温湿度数据,以供调试
  mySerial.print(humidity);
  mySerial.print(" %\t");
  mySerial.print(temperature);
  mySerial.print(" *C ");
  mySerial.println(""); //向软串口发送传感器读到的温湿度
}