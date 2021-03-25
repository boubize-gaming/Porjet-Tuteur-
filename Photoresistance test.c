int lumiere;

void setup(){
    
    Serial.begin(115200);
  
    pinMode(26, INPUT);
    
}

void loop(){
    lumiere = analogRead(26);
    Serial.println(lumiere);
    delay(5000);

}
