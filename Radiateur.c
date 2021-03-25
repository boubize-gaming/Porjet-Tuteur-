
// arret = 0 eco =1 confort =2 horsgel =3
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
    page += "        <a href='/0' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>Arret du chauffage</a>";
    page += "        <a href='/1' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>Mode eco du chauffage</a>";
    page += "        <a href='/2' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>Mode confort du chauffage</a>";
    page += "        <a href='/3' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>Mode horsgel du chauffage</a>";
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


void setup()
{
    
    
    pinMode(14, OUTPUT);
    pinMode(12, OUTPUT);
    digitalWrite(14, LOW);
    digitalWrite(12, HIGH);
    
    WiFi.persistent(false);
    WiFi.begin(ssid, mot_de_passe);
    server.on("/", handleRoot);
    server.on("/0", handle0);
    server.on("/1", handle1);
    server.on("/2", handle2);
    server.on("/3", handle3);
    server.begin();
}

void loop()
{
    server.handleClient();
}
