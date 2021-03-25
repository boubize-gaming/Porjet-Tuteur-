#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

#define DHTTYPE DHT22

const char* ssid = "Nom du réseau Wifi";
const char* mot_de_passe = "Mot de passe wifi";

WebServer server(80);
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
  WiFi.begin(ssid, mot_de_passe);
  server.on("/", Calcul_DHT22);
  server.begin();

}
void loop() {
  
  server.handleClient();
  
}

void Calcule_DHT22() {

  Temperature = dht.readTemperature();
  Humidite = dht.readHumidity();
  F = dht.readTemperature(true);
  FH = dht.computeHeatIndex(F, Humidite);
  temperature_ressentie = dht.convertFtoC(FH);
    
    
  server.send(200, "text/html", SendHTML(Temperature,Humidite,temperature_ressentie));
}

String SendHTML(float Temperaturestat,float Humiditestat, float tempressentie){
  String ptr = "<!DOCTYPE html> <html>\n";
  
  ptr +="<p>Temperature: ";
  ptr +=(int)Temperaturestat;
  ptr +="C</p>";
  ptr +="<p>Humidite: ";
  ptr +=(int)Humiditestat;
  ptr +="%</p>";
  ptr +="<p>Temperature ressentie: ";
  ptr +=(int)tempressentie;
  ptr +="C</p>";
  
  ptr +="</html>\n";
  return ptr;
}

