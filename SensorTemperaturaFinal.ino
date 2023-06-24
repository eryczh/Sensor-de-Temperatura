#include "DHT.h"

#define UM_SEGUNDO 1000
#define MEIO_SEGUNDO 500

#define LED D2

#define DHTPIN D4
#define DHTTYPE DHT11

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL2hj-uej6R"
#define BLYNK_TEMPLATE_NAME "Temperature and Humidity Monitor"
#define BLYNK_AUTH_TOKEN "it30_9wagNjgbt-yl2iAXRaVXpAHsE6b"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

DHT dht(DHTPIN, DHTTYPE);

char auth[] = BLYNK_AUTH_TOKEN; //Enter the auth code which was send by Blynk
char ssid[] = ""; // Enter WiFi Name
char pass[] = ""; // Enter WiFi Password


void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("DHT Test");
  dht.begin();

  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(UM_SEGUNDO);
    Serial.println("Connecting to WiFi...");
  }
  

  // Blynk Connection
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);

  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(t) || isnan(f)) {
    Serial.println("Erro to read DHT sensor/");
    
    return;
  }

  Serial.print("T: ");
  Serial.print(t);
  Serial.print("'C");

  Serial.print("T: ");
  Serial.print(f);
  Serial.print("'F");

  if (t > 20) {
    piscaLed(LED);
  }

  Blynk.run();

  //send sensor data to blynk
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, f);
}

void piscaLed(int portaLed) {
  digitalWrite(portaLed, HIGH);
  delay(UM_SEGUNDO);
  digitalWrite(portaLed, LOW);
  delay(MEIO_SEGUNDO);
}
