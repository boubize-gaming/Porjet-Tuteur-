#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "Wifi-Girardet";
const char *mot_de_passe = "royalbolt131";
WebServer server(80);


void handleRoot()
{
    String page = "<!DOCTYPE html>";

    page += "<body>";
   

    page += "    <div class='w3-bar'>";
    page += "        <a href='/on' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>Ouvrir Volet</a>";
    page += "        <a href='/off' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>Fermer Volet</a>";
    page += "    </div>";


    page += "</body>";

    page += "</html>";

    server.setContentLength(page.length()); //on envoit la page html
    server.send(200, "text/html", page);
}

void handleOuvrir()
{
    digitalWrite(26, HIGH);
    digitalWrite(27, LOW);
    delay(15000);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
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
    server.sendHeader("Location","/");
    server.send(303);
}

void setup()
{
    
    
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
    WiFi.persistent(false);
    WiFi.begin(ssid, mot_de_passe);
    server.on("/", handleRoot);
    server.on("/on", handleOuvrir);
    server.on("/off", handleFermer);
    server.begin();
}

void loop()
{
    server.handleClient();
}

