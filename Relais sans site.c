void setup()
{
    Serial.begin(115200);
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
    while(!Serial);
    Serial.println("Que voulez vous faire, 1 pour ouvrir et 2 pour fermer");
    
    
}

void loop()
{

    
    
    
    if (Serial.available()){
        int etat = Serial.parseInt();

    if (etat == 1) {
        digitalWrite(26, HIGH);
        digitalWrite(27, LOW);
        delay(15000);
        digitalWrite(26, LOW);
        digitalWrite(27, LOW);
        Serial.println("Le volet est ouvert");
    }
    if (etat == 2){
        digitalWrite(26, LOW);
        digitalWrite(27, HIGH);
        delay(15000);
        digitalWrite(26, LOW);
        digitalWrite(27, LOW);
        Serial.println("Le volet est fermé");
    }
    }
}
    

