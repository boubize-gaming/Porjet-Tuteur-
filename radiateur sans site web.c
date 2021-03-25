int mode; //variable mode pour définir dazns quel mode on est
// arret = 0 eco =1 confort =2 horsgel =3
void setup()
{
    Serial.begin(115200); //demarrage du moniteur serie a 115200 bauds
    pinMode(14, OUTPUT);
    pinMode(12, OUTPUT); //on met les port 12 et 14 en sortie
    digitalWrite(14, LOW);
    digitalWrite(12, HIGH);  //on met le chauffage des le debut en arret
    while(!Serial);
    Serial.println("Que faire arret = 0 eco =1 confort =2 horsgel =3"); //on ecris les choix possible a l'utilisateur
    
    
}


void loop()
{


if (Serial.available()){  //on lit la valuer donnée par l'utilisateur
    int mode = Serial.parseInt();

if (mode == 0) {
digitalWrite(14, LOW);       //boucle if en fonction du resultat, et en fonction de ce resultat on allume ou nous le chauffage etc ...
    digitalWrite(12, HIGH);
}
if (mode == 1) {
digitalWrite(14, HIGH);
digitalWrite(12, HIGH);
}
if (mode == 2) {
digitalWrite(14, LOW);
digitalWrite(12, LOW);
    
}
if (mode == 3) {
digitalWrite(14, HIGH);
digitalWrite(12,LOW);
    
}
}

}
