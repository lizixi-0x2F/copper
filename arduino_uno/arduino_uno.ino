/**
 * 项目名称		：		copper
 * 程序名称		：		arduino_uno
 * 目的				：		通过物联网温湿度计来实践MQTT协议和串口通讯
 * 作者				：		籽溪
 * 时间(YYYYMMDD)			:			20210710
*/
#include <SoftwareSerial.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 2

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial mySerial(6, 7);

void setup()
{
	Serial.begin(9600);
	Serial.println("MySerial Is Ready");
	mySerial.begin(9600);
	dht.begin();
}
void loop()
{
	delay(1000);
	float humidity = dht.readHumidity();
	float temperature = dht.readTemperature();
	if (isnan(humidity) or isnan(temperature))
	{
		Serial.println("Failed to read from DHT sensor!");
		return;
	}
	Serial.print(humidity);
	Serial.print(" %\t");
	Serial.print(temperature);
	Serial.print(" *C ");
	Serial.println("");
	mySerial.print(humidity);
	mySerial.print(" %\t");
	mySerial.print(temperature);
	mySerial.print(" *C ");
	mySerial.println("");
}
