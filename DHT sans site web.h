#include "DHT.h"
#define DHTTYPE DHT22

uint8_t DHTPin = 32;
DHT dht(DHTPin, DHTTYPE);

float Temperature;
float Humidite;
float F;
float FH;
float temperature_ressentie;

void setup() {

  pinMode(DHTPin, INPUT);
  dht.begin();
    Serial.begin(115200);

}
void loop() {
  
    Temperature = dht.readTemperature();
    Humidite = dht.readHumidity();
    F = dht.readTemperature(true);
    FH = dht.computeHeatIndex(F, Humidite);
    temperature_ressentie = dht.convertFtoC(FH);
    
    Serial.println("La température est de :");
    Serial.println(Temperature);
    Serial.println("L'humidite est de :");
    Serial.println(Humidite);
    Serial.println("La température ressentie est de :");
    Serial.println(temperature_ressentie);
    delay(5000);
  
}
