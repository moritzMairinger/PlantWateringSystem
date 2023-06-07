#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

String  output = "";
IPAddress staticIP262_10(192,168,1,10);
IPAddress gateway262_10(192,168,0,1);
IPAddress subnet262_10(255,255,255,0);

WiFiClient client;

String myurl = "/";
String line = "";
String IotClientSendWithAnswer(String IPcache, String monmessagecache) {
line = "";
client.print(String("GET ") + myurl + monmessagecache + " HTTP/1.1\r\n" +
          "Host: " + IPcache + "\r\n" +
         "Connection: close\r\n\r\n");
unsigned long timeout = millis();
while (client.available() == 0) {
  if (millis() - timeout > 5000) {
    return "Client Timeout!";
  }
}
while(client.available()) {line += client.readStringUntil('\r');}
return line;
}

void setup() {

  Serial.begin(9600);
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));

  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("WLAN4712","a83i15e84u07o91");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  //WiFi.config(staticIP262_10, gateway262_10, subnet262_10);
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
}


void loop() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  output = (String)event.temperature;
  Serial.println(event.temperature);
  //dht.humidity().getEvent(&event);
  //output += (String)event.relative_humidity;
  if (client.connect("192.168.0.172", 8080)) {
    Serial.println((IotClientSendWithAnswer("192.168.0.172:8080",output)));
  }
  delay(5000);
}