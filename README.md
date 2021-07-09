# copper
> 一个物联网温湿度计😉
* * * * * * *
## **你可能需要:**
* 1 Arduino UNO R3 开发板(官方板 or 克隆板) P.S.: 以下简称UNO
* 2 DHT温湿度模块 x1
* 3 NodeMcu1.0 (ESP-12E Moudel) x1
* 4 公对母跳线 x3 公对公跳线 x3
* * * * * * *
## **接线方法:**
* 1 DHT11 "+"管脚接UNO的3v3接口, "-"管脚接GND接口, "out"脚接UNO上的d2接口
* 2 NodeMcu Vin管脚接UNO上的5v接口, GND接UNO上的GND接口, D4脚接UNO上的7接口
* * * * * * *
## **ESP8266链接WiFi:**
```cpp
const char *ssid = "SSID";
const char *passwd = "PASSWORD";
```
> **将esp8266.ino中的如下代码改动至你家WiFi名和WiFi密码即可.**