// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>

#define DHTPIN_A 2    // Digital pin connected to the DHT sensor
#define DHTPIN_B 17
#define DHTPIN_C 14 

const char* ssid     = "wifi id";
const char* password = "wifi pass";

const char* host = "35.158.123.140"; //http://35.158.123.140/  remoote server

// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)


String temperature;
String humidity;

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht_a(DHTPIN_A, DHTTYPE);
DHT_Unified dht_b(DHTPIN_B, DHTTYPE);
DHT_Unified dht_c(DHTPIN_C, DHTTYPE);

uint32_t delayMS;

void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);
  delay(10);
//WIFI CONNECTION
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
  // Initialize device.
  dht_a.begin();
  dht_b.begin();
  dht_c.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht_a.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht_a.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}
void call_dht_a(){
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht_a.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("DHT_A Error reading temperature!"));
  }
  else {
    temperature = String(event.temperature);
    Serial.print(F("DHT_A Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht_a.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("DHT_A Error reading humidity!"));
  }
  else {
    humidity = String(event.relative_humidity);
    Serial.print(F("DHT_A Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
  delay(500);
  connectAWS("C01A",temperature,humidity);
}
void call_dht_b(){
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht_b.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("DHT_B Error reading temperature!"));
  }
  else {
    temperature = String(event.temperature);
    Serial.print(F("DHT_B Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht_b.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("DHT_B Error reading humidity!"));
  }
  else {
    humidity = String(event.relative_humidity);
    Serial.print(F("DHT_B Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
  delay(500);
  connectAWS("C01B",temperature,humidity);
}
void call_dht_c(){
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht_c.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("DHT_C Error reading temperature!"));
  }
  else {
    temperature = String(event.temperature);
    Serial.print(F("DHT_C Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht_c.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("DHT_C Error reading humidity!"));
  }
  else {
    humidity = String(event.relative_humidity);
    Serial.print(F("DHT_C Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
  delay(500);
  connectAWS("C01C",temperature,humidity);
}
 void connectAWS(String deviceName, String temp, String hum){
   delay(500);
   Serial.print("connecting to ");
   Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }
    temp.replace('.',',');
    hum.replace('.',',');
    Serial.print("newTemp: "+temp);
    // We now create a URI for the request
    String url = "/dash/DashboardApi/SendDataToServer";
    url += "?deviceName=";
    url += deviceName;
    url += "&Temp=";
    url += temp;
    url += "&Hum=";
    url += hum;
    /*url += "?private_key=";
    url += privateKey;
    url += "&value=";
    url += value;
*/
    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }
  }
void loop() {
  delay(2000);
  call_dht_a();
  call_dht_b();
  call_dht_c();
  
}
