#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "Wifi-Girardet";
const char *password = "royalbolt131";
WebServer server(80);
int lumiere;
bool etatJour;
char texteetatJour[2][10] = {"jour","nuit"};

void handleRoot()
{
    String page = "<!DOCTYPE html>";
    
    page += "    <div class='w3-card w3-blue w3-padding-small w3-jumbo w3-center'>";
    page += "        <p>Moment: "; page += texteetatJour[etatJour]; + "</p>";
    page += "    </div>";

    server.setContentLength(page.length());
    server.send(200, "text/html", page);
}


void setup()
{
    pinMode(34, INPUT);
    WiFi.persistent(false);
    WiFi.begin(ssid, password);
    server.on("/", handleRoot);
    server.begin();
    lumiere = analogRead(34);

    
}

void loop()
{
    server.handleClient();
    lumiere = analogRead();
    if(lumiere < 1000){
        etatJour == 1;
    }
    if(lumiere > 1100){
        etatJour == 0;
    }
}

