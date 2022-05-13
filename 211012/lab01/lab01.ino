// 201533631 김도균

void setup() {
    pinMode(9, OUTPUT);
}

void loop() {
    
    if(analogRead(A0) > 512){
        digitalWrite(9, LOW);
    } else {
        digitalWrite(9, HIGH);
    }
    delay(100);

}
