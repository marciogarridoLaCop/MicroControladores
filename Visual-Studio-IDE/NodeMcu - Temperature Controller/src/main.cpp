/*********
  Projeto NodeMucu com Visual Studio
  Marcio Garrido
*********/

#include <Arduino.h>
#include <esp8266wifi.h>
#include <DHT.h> 
#include "ESPAsyncWebServer.h"
#include <Adafruit_Sensor.h>

#define LED 2

#define DHTPIN D3
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

////////////////// Configuração do ThingSpeak /////////////////////////x

String apiKey = "L0EFAB0E0JQBFYM5";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "RealFibra_Garrido";     // replace with your wifi ssid and wpa2 key
const char *pass =  "master10";
const char* server = "api.thingspeak.com";

int wifiStatus;
WiFiClient client;
 
void setup() 
{
       Serial.begin(9600);
       delay(10);
       pinMode(LED, OUTPUT);
       dht.begin();
       Serial.println("Connecting to ");
       Serial.println(ssid);
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      h=77.3;
      t=21.5;
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }

                         if (client.connect(server,80))   //   api.thingspeak.com
                      {  
                            
                            String postStr = apiKey;
                            postStr +="&field1=";
                            postStr += String(t);
                            postStr +="&field2=";
                            postStr += String(h);
                            postStr += "\r\n\r\n";
                            client.print("POST /update HTTP/1.1\n");
                            client.print("Host: api.thingspeak.com\n");
                            client.print("Connection: close\n");
                            client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                            client.print("Content-Type: application/x-www-form-urlencoded\n");
                            client.print("Content-Length: ");
                            client.print(postStr.length());
                            client.print("\n\n");
                            client.print(postStr);
                            Serial.print("Temperature: ");
                            Serial.print(t);
                            Serial.print(" degrees Celcius, Humidity: ");
                            Serial.print(h);
                            Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10000);
}