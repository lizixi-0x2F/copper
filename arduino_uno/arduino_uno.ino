/*
Author : Zixi Lee
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
