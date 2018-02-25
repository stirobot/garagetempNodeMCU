//gets garage temp from ___ sensor and posts it to thinger.io

#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>
#include <DHT.h>

#define DHTPIN1 D2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht1(DHTPIN1, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

#define DHTPIN2 D3     // what pin we're connected to
DHT dht2(DHTPIN2, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

// Configuration of the WiFi AP settings.
#define WIFI_AP "APNAME"
#define WIFI_PASSWORD "password"


ThingerESP8266 thing("a", "a", "a");

void setup() {
  dht1.begin();
  dht2.begin();
  thing.add_wifi(WIFI_AP, WIFI_PASSWORD);
  thing["garageTemp1"] >> outputValue(dht1filterReadTemperature()*1.8+32);
  thing["garageTemp2"] >> outputValue(dht2filterReadTemperature()*1.8+32);
  thing["garageHumidity1"] >> outputValue(dht1filterReadHumidity());
  thing["garageHumidity2"] >> outputValue(dht2filterReadHumidity());
  Serial.begin(9600);
}

void loop() {
  //read data
  thing.handle();
  Serial.println(dht1.readTemperature());
}

float dht1filterReadTemperature(){
  float temp = dht1.readTemperature();
  while ((isnan(temp))){
    temp = dht1.readTemperature();    
  }
  return(temp);
}

float dht2filterReadTemperature(){
  float temp = dht2.readTemperature();
  while ((isnan(temp))){
    temp = dht2.readTemperature();    
  }
  return(temp);
}

float dht1filterReadHumidity(){
  float temp = dht1.readHumidity();
  while ((isnan(temp))){
    temp = dht1.readHumidity();    
  }
  return(temp);
}

float dht2filterReadHumidity(){
  float temp = dht2.readHumidity();
  while ((isnan(temp))){
    temp = dht2.readHumidity();    
  }
  return(temp);
}

