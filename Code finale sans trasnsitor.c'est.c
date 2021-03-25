// arret = 0 eco =1 confort =2 horsgel =3 pour la radiateur
#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"
const char *ssid = "Wifi-Girardet";
const char *mot_de_passe = "royalbolt131";
WebServer server(80);
int lumiere;
int ouverture;
bool etatJour;
char texteetatJour[2][10] = {"jour, le volet est ouvert","nuit, le volet est fermé"};
#define DHTTYPE DHT22
uint8_t DHTPin = 18;
DHT dht(DHTPin, DHTTYPE);

float Temperature;
float Humidite;
float F;
float FH;
float temperature_ressentie;




void handleRoot()
{
    String page = "<!DOCTYPE html>";
    page += "<html lang='fr'>";
    page += "<head>";
    page += "    <title>Serveur ESP32</title>";
    page += "<body>";
    page += "    <h1>Serveur Esp32 IUT de Roanne</h1>";

    page += "    <div class='w3-bar'>";
    page += "        <a href='/0' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>Arret du chauffage</a>";
    page += "        <a href='/1' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>Mode eco du chauffage</a>";
    page += "        <a href='/2' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>Mode confort du chauffage</a>";
    page += "        <a href='/3' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>Mode horsgel du chauffage</a>";
    page += "<br>";
    page += "<br>";
    page += "        <a href='/on' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>Ouvrir Volet</a>";
    page += "        <a href='/off' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>Fermer Volet</a>";
    page += "<br>";
    page += "<br>";
    page += "        <p>Moment: "; page += texteetatJour[etatJour]; + "</p>";
    page += "        <p>Temperature: "; page += Temperature; + "</p>";
    page += "        <p>Humidite: "; page += Humidite; + "</p>";
    page += "        <p>Temperature Ressentie: "; page += temperature_ressentie; + "</p>";
    page += "    </div>";


    page += "</body>";

    page += "</html>";

    server.setContentLength(page.length()); //on envoit la page html
    server.send(200, "text/html", page);
}
void handle0()
{
    digitalWrite(14, LOW);
    digitalWrite(12, HIGH);
    server.sendHeader("Location","/");
    server.send(303);
}

void handle1()
{
    digitalWrite(14, HIGH);
    digitalWrite(12, HIGH);
    server.sendHeader("Location","/");
    server.send(303);
}

void handle2()
{
    digitalWrite(14, LOW);
    digitalWrite(12, LOW);
    server.sendHeader("Location","/");
    server.send(303);
}
void handle3()
{
    digitalWrite(14, HIGH);
    digitalWrite(12,LOW);
    server.sendHeader("Location","/");
    server.send(303);
}

void handleOuvrir()
{
    digitalWrite(26, HIGH);
    digitalWrite(27, LOW);
    delay(15000);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
    ouverture == 1;
    server.sendHeader("Location","/");
    server.send(303);
}

void handleFermer()
{
    digitalWrite(26, LOW);
    digitalWrite(27, HIGH);
    delay(15000);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
    ouverture == 2;
    server.sendHeader("Location","/");
    server.send(303);
}


void setup()
{
    
    
    pinMode(14, OUTPUT);
    pinMode(12, OUTPUT);
    digitalWrite(14, LOW);
    digitalWrite(12, HIGH);
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
    pinMode(19, INPUT);
    pinMode(DHTPin, INPUT);
    dht.begin();
    
    WiFi.persistent(false);
    WiFi.begin(ssid, mot_de_passe);
    Serial.begin(115200); // on demarre la connexion au moniteur
     Serial.println("\n");
      Serial.print("Tentative de connexion au wifi indiqué");
       while (WiFi.status() != WL_CONNECTED)
        {
            Serial.print("."); //on affiche ... tant qjue l'on est pas connecte au wifi, on met cela apres le wifi. begin
            delay(100);
        }
    Serial.println("\n");
          Serial.println("Connexion etablie!"); //on affiche que l'on ce connecte bien au connecte
        Serial.print("Adresse IP: ");
    Serial.println(WiFi.localIP());  //on affiche l'addresse ip
    server.on("/", handleRoot);
    server.on("/0", handle0);
    server.on("/1", handle1);
    server.on("/2", handle2);
    server.on("/3", handle3);
    server.on("/on", handleOuvrir);
    server.on("/off", handleFermer);
    server.begin();
    Serial.println("Serveur web actif!");  // on dit que le serveur est lancé, apres le serveur begin ,
    lumiere = analogRead(19);
    
}

void loop()
{
    server.handleClient();
    lumiere = analogRead(19);
    if(lumiere < 1000){
        etatJour == 1;
        if(ouverture == 2){
            }
        else if(ouverture == 1){
            digitalWrite(26, LOW);                      //automatisation de l'ouverture et la fermeture du volet en fonction de la luminosité
            digitalWrite(27, HIGH);
            delay(15000);
            digitalWrite(26, LOW);
            digitalWrite(27, LOW);
            ouverture == 2;
        }
    }
    if(lumiere > 1100){
        etatJour == 0;
        if(ouverture == 1){
            }
        else if(ouverture == 2){
            digitalWrite(26, HIGH);     //automatisation de l'ouverture et la fermeture du volet en fonction de la luminosité
            digitalWrite(27, LOW);
            delay(15000);
            digitalWrite(26, LOW);
            digitalWrite(27, LOW);
            ouverture == 1;
        }
    }
    Temperature = dht.readTemperature();
    Humidite = dht.readHumidity();
    F = dht.readTemperature(true);
    FH = dht.computeHeatIndex(F, Humidite);
    temperature_ressentie = dht.convertFtoC(FH);
    
    //automatisation pour chauffage si en dessu de 22 degrés, on eteint le chauffage et si en dessous de 20 degrés on allume le chauffage
    if(temperature_ressentie < 20){
        digitalWrite(14, LOW);  //on ce met en mode confort
        digitalWrite(12, LOW);
    }
    if(temperature_ressentie > 22){
        digitalWrite(14, LOW); //on arrete le chauffage
        digitalWrite(12, HIGH);
    }
    
    

}
 

